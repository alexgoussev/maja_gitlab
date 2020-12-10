/*
* Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
/************************************************************************************************************
 *                                                                                                          *
 *                                ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo         *
 *                             o                                                                            *
 *                          o                                                                               *
 *                        o                                                                                 *
 *                      o                                                                                   *
 *                     o       ooooooo       ooooooo    o         o      oo                                 *
 *    o              o       o        o     o       o   o         o     o   o                               *
 *      o           o       o          o   o         o  o         o    o      o                             *
 *        o        o       o           o   o         o  o         o    o        o                           *
 *         o      o        o      oooo     o         o  o         o   o           o                         *
 *          o    o          o              o         o  o         o   o           o                         *
 *           o  o            o             o         o  o o      o   o          o                           *
 *            oo              oooooooo    o         o   o  oooooo   o      oooo                             *
 *                                                     o                                                    *
 *                                                     o                                                    *
 *                                                    o                            o                        *
 *                                                    o            o      oooo     o   o      oooo          *
 *                                                   o             o         o    o    o         o          *
 *                                                   o            o       ooo     o   o       ooo           *
 *                                                               o       o       o   o          o           *
 *                                                               ooooo   oooo    o   ooooo  oooo            *
 *                                                                              o                           *
 *                                                                                                          *
 ************************************************************************************************************
 *                                                                                                          *
 * Author: CS Systemes d'Information  (France)                                                              *
 *                                                                                                          *
 ************************************************************************************************************
 * HISTORIQUE                                                                                               *
 *                                                                                                          *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 15 nov. 2017 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/


#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"
#include "vnsSimpleLutXMLFileHandler.h"
#include "vnsVectorLookUpTableExtractor.h"
#include "vnsMultiplyByVectorFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "vnsLookUpTableFileReader.h"
#include "itkImageFileWriter.h"
#include "vnsAtomicRegistry.h"
#include "itkMetaImageIOFactory.h"

namespace vns
{
namespace Wrapper
{

using namespace otb::Wrapper;

class ReduceLut : public Application
{
public:
	/** Standard class typedefs. */
	typedef ReduceLut Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(ReduceLut, otb::Wrapper::Application);

	/** Image typedef */
	//Full dimension LUT typedef
	typedef VNSLUT6DType LutType;
	typedef LutType::ConstPointer LutConstPointer;
	typedef LutType::Pointer LutPointer;
	typedef LutType::RegionType RegionType;
	typedef LutType::PixelType LutPixelType;
	typedef LutType::SizeType LutSizeType;
	typedef LutType::ParameterValuesType ParameterValuesType;
	typedef LutType::InternalPixelType LutInternalPixelType;
	//Reduced output lut typedef
	typedef VNSLUT3DType ReducedLutType;
	typedef ReducedLutType::ConstPointer ReducedLutConstPointer;
	typedef ReducedLutType::Pointer ReducedLutPointer;
	//LookupTable Reader
	typedef LookUpTableFileReader<LutType> LookUpTableReaderType;
	typedef LookUpTableReaderType::Pointer LookUpTableReaderPointer;
	typedef vns::Functor::MultiplyByVectorFunctor<ReducedLutType::PixelType, ReducedLutType::PixelType> FunctorType;
	typedef itk::UnaryFunctorImageFilter<ReducedLutType, ReducedLutType, FunctorType> MultiplyByVectorFilterType;
	typedef MultiplyByVectorFilterType::Pointer MultiplyByVectorFilterPointerType;
	//Extract LUT filter
	typedef VectorLookUpTableExtractor<LutType,ReducedLutType> VectorLookUpTableExtractorType;
	/**LutXml handler typedef */
	typedef SimpleLutXMLFileHandler LutXMLHandlerType;
	typedef LutXMLHandlerType::Pointer LutXMLHandlerPointer;

private:
	void DoInit()
	{
		SetName("ReduceLut");
		SetDescription("Generate the reduce lut 3D from a 6D lut.");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocLongDescription("This application computes the reduced lut in 3D from a 6D lut");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Statistics");

		AddParameter(ParameterType_String,  "lut",   "Lut6D");
		SetParameterDescription("lut", "Full LUT xml file");
		AddParameter(ParameterType_OutputFilename,  "reducelut",   "Lut3D");
		SetParameterDescription("reducelut", "ReduceLUT");
		AddParameter(ParameterType_Group, "solar","Solar angles");
		AddParameter(ParameterType_Float, "solar.zenith","Solar zenith");
		AddParameter(ParameterType_Float, "solar.azimuth","Solar azimuth");
		AddParameter(ParameterType_Group, "viewing","Mean Viewing angles");
		AddParameter(ParameterType_StringList, "viewing.zenith","Viewing zenith");
		AddParameter(ParameterType_StringList, "viewing.azimuth","Viewing azimuth");
		AddParameter(ParameterType_StringList, "dircoefs", "directional correction coefs");
		MandatoryOff("dircoefs");

		AddRAMParameter("ram");
		SetDefaultParameterInt("ram",2048);

	}

	void DoUpdateParameters()
	{
	}


	void DoExecute()
	{
		// For mha reader/writer with otb::ImageFileReader/Writer. Otherwise, use itk::ImageFileReader/Writer.
		itk::ObjectFactoryBase::RegisterFactory(itk::MetaImageIOFactory::New());

		// Init filters
		LookUpTableReaderPointer l_lookUpTableReader = LookUpTableReaderType::New();


		//Solar Angles
		double m_SolarZenith = GetParameterFloat("solar.zenith");
		double m_SolarAzimuth = GetParameterFloat("solar.azimuth");
		//VViewing Angles
		Utilities::ListOfDoubles m_MeanViewingZenithAngles;
		const std::vector<std::string> l_ZenStr = GetParameterStringList("viewing.zenith");
		for (unsigned int i = 0; i < l_ZenStr.size();i++)
		{
			m_MeanViewingZenithAngles.push_back(Utilities::AsDouble(l_ZenStr[i]));
		}
		Utilities::ListOfDoubles m_MeanViewingAzimuthAngles;
		const std::vector<std::string> l_AzStr = GetParameterStringList("viewing.azimuth");
		for (unsigned int i = 0; i < l_AzStr.size();i++)
		{
			m_MeanViewingAzimuthAngles.push_back(Utilities::AsDouble(l_AzStr[i]));
		}
		//Load the LUT
		//--------------------------------------------
		const std::string l_GIPPFilename = GetParameterString("lut");
		LutXMLHandlerPointer l_LUTXMLHandler = LutXMLHandlerType::New();
		// Load the XML file and check with the schema
		l_LUTXMLHandler->LoadFile(l_GIPPFilename);
		const SimpleLutXMLContainer& l_lutxml = l_LUTXMLHandler->GetLutContainer();

		// Read the files
		const Utilities::ListOfFilenames& l_GIP_L2TOCR_ListOfFilenames = l_lutxml.GetListOfPackaged_DBL_Files();
		// Get the number of file that matches with the number of band
		unsigned int fileNumber = l_GIP_L2TOCR_ListOfFilenames.size();
		vnsLogDebugMacro("=================================================================")
		vnsLogDebugMacro("GIP_L2TOCR number of filenames: "<<fileNumber)

		// For each spectral band, add the filename of the LUT to the reader
		for (unsigned int file = 0; file < fileNumber; file++)
		{
			// Set the filename of each band
			l_lookUpTableReader->AddBandFilename(l_GIP_L2TOCR_ListOfFilenames[file]);
			vnsLogDebugMacro("BandFilename : " <<l_GIP_L2TOCR_ListOfFilenames[file]);
		}


		// Read informations from the GIPP file
		const Utilities::ListOfDoubles& l_GIP_L2TOCR_SolarZenithalAngleIndexes = l_lutxml.GetSolar_Zenith_Angle_Indexes();
		const Utilities::ListOfDoubles& l_GIP_L2TOCR_ViewZenithalAngleIndexes = l_lutxml.GetView_Zenith_Angle_Indexes();
		const Utilities::ListOfDoubles& l_GIP_L2TOCR_RelativeAzimuthAngleIndexes = l_lutxml.GetRelative_Azimuth_Angle_Indexes();
		const Utilities::ListOfDoubles& l_GIP_L2TOCR_AltitudeIndexes = l_lutxml.GetAltitude_Indexes();
		const Utilities::ListOfDoubles& l_GIP_L2TOCR_AOTIndexes = l_lutxml.GetAOT_Indexes();
		const Utilities::ListOfDoubles& l_GIP_L2TOCR_TOAReflectanceIndexes = l_lutxml.GetTOA_Reflectance_Indexes();

		vnsLogDebugMacro("  l_GIP_L2TOCR_ViewZenithalAngleIndexes: "<<l_GIP_L2TOCR_ViewZenithalAngleIndexes.size())
		vnsLogDebugMacro("  l_GIP_L2TOCR_ViewZenithalAngleIndexes: "<<l_GIP_L2TOCR_ViewZenithalAngleIndexes.size())
		vnsLogDebugMacro("  l_GIP_L2TOCR_RelativeAzimuthAngleIndexes: "<<l_GIP_L2TOCR_RelativeAzimuthAngleIndexes.size())
		vnsLogDebugMacro("  l_GIP_L2TOCR_AltitudeIndexes: "<<l_GIP_L2TOCR_AltitudeIndexes.size())
		vnsLogDebugMacro("  l_GIP_L2TOCR_AOTIndexes: "<<l_GIP_L2TOCR_AOTIndexes.size())
		vnsLogDebugMacro("  l_GIP_L2TOCR_TOAReflectanceIndexes: "<<l_GIP_L2TOCR_TOAReflectanceIndexes.size())

		/* parameters are added one by one to the LUT */
		ParameterValuesType l_TOCRParam1;
		l_TOCRParam1.ParameterName = "Solar_Zenith_Angle_Indexes";
		l_TOCRParam1.ParameterValues = l_GIP_L2TOCR_SolarZenithalAngleIndexes;
		l_lookUpTableReader->AddParameterValues(l_TOCRParam1);

		ParameterValuesType l_TOCRParam2;
		l_TOCRParam2.ParameterName = "View_Zenith_Angle_Indexes";
		l_TOCRParam2.ParameterValues = l_GIP_L2TOCR_ViewZenithalAngleIndexes;
		l_lookUpTableReader->AddParameterValues(l_TOCRParam2);

		ParameterValuesType l_TOCRParam3;
		l_TOCRParam3.ParameterName = "Relative_Azimuth_Angle_Indexes";
		l_TOCRParam3.ParameterValues = l_GIP_L2TOCR_RelativeAzimuthAngleIndexes;
		l_lookUpTableReader->AddParameterValues(l_TOCRParam3);

		ParameterValuesType l_TOCRParam4;
		l_TOCRParam4.ParameterName = "Altitude_Indexes";
		l_TOCRParam4.ParameterValues = l_GIP_L2TOCR_AltitudeIndexes;
		l_lookUpTableReader->AddParameterValues(l_TOCRParam4);

		ParameterValuesType l_TOCRParam5;
		l_TOCRParam5.ParameterName = "AOT_Indexes";
		l_TOCRParam5.ParameterValues = l_GIP_L2TOCR_AOTIndexes;
		l_lookUpTableReader->AddParameterValues(l_TOCRParam5);

		ParameterValuesType l_TOCRParam6;
		l_TOCRParam6.ParameterName = "TOA_Reflectance_Indexes";
		l_TOCRParam6.ParameterValues = l_GIP_L2TOCR_TOAReflectanceIndexes;
		l_lookUpTableReader->AddParameterValues(l_TOCRParam6);

		vnsLogDebugMacro(
				" Mean solar angles [Z;A] => ["<<m_SolarZenith<<";"<<m_SolarAzimuth<<"]")

		//Gen Lut
		l_lookUpTableReader->GenerateLUT();
		//Point to interpolate
		VectorLookUpTableExtractorType::VectorExtractPointType vectorPoint;
		// Get the number of band
		const unsigned int numberOfBand(m_MeanViewingZenithAngles.size());

		vnsLogDebugMacro(" Mean viewing angles (one per band) => nb bands = ["<<numberOfBand<<"]")
		for (unsigned int bandNum = 0; bandNum < numberOfBand; bandNum++)
		{
			vnsLogDebugMacro(
					"        [Z;A] => ["<<m_MeanViewingZenithAngles.at(bandNum)<<";"<<m_MeanViewingAzimuthAngles.at(bandNum)<<"] (p_InputL1ImageInformationsProvider->GetListOfViewingAngles Zenith/Azimuth PerBandAtL2CoarseResolution().at(bandNum).")
		}

		// Band Loop
		for (unsigned int bandNum = 0; bandNum < numberOfBand; bandNum++)
		{
			// Get the extract point values for each band because
			// viewing angles depend on spectral band
			VectorLookUpTableExtractorType::ExtractPointType point;
			point[0] = m_SolarZenith;
			point[1] = m_MeanViewingZenithAngles[bandNum];

			// Get the relative azimuth angle
			double deltaPhi = m_SolarAzimuth - m_MeanViewingAzimuthAngles[bandNum];
			if (deltaPhi < 0.)
			{
				deltaPhi = -deltaPhi;
			}
			if (deltaPhi > 180.)
			{
				deltaPhi = 360 - deltaPhi;
			}
			point[2] = deltaPhi;

			vectorPoint.push_back(point);
		}

		// Get pointers to the input and output images

		LutPointer l_LutInPtr = l_lookUpTableReader->GetLUT();
		//Extract the lut for the point
		m_CRLutNotCorrected = VectorLookUpTableExtractorType::ExtractLUT(l_LutInPtr, vectorPoint);


		const bool l_hasDirCorr = IsParameterEnabled("dircoefs");
        //Is the directional correction enabled ?
        if(l_hasDirCorr){
        	vnsLogDebugMacro("Applying directional correction coefficients");

			Utilities::ListOfDoubles l_dircorrcoefs = Utilities::StringListAsDouble(
					this->GetParameterStringList("dircoefs"));

            // Set the size of the output image ( because the Unary Functor calls GetOutputSize() )
        	m_MultiplyFilter = MultiplyByVectorFilterType::New();
            m_MultiplyFilter->GetFunctor().SetOutputSize(numberOfBand);
            m_MultiplyFilter->GetFunctor().SetCoefs(l_dircorrcoefs);
            m_MultiplyFilter->SetInput(m_CRLutNotCorrected);
            //Update the multiply filter
            vnsLogDebugMacro("Updating Multiply");
            m_MultiplyFilter->Update();
            m_CRLut = m_MultiplyFilter->GetOutput();
            // Set kept parameters values */
            m_CRLut->copyParametersValue(m_CRLutNotCorrected);
        } else {
            //No Correct then same output
            m_CRLut = m_CRLutNotCorrected;
        }

		//Set outputs
		const std::string l_outFileName = GetParameterString("reducelut");
		itk::ImageFileWriter<ReducedLutType>::Pointer l_Writer = itk::ImageFileWriter<ReducedLutType>::New();
		l_Writer->SetInput(m_CRLut);
		l_Writer->SetFileName(l_outFileName);
		l_Writer->Update();
	}

	/** Filters declaration */
	MultiplyByVectorFilterPointerType m_MultiplyFilter;
	/** LUT */
	ReducedLutPointer m_CRLutNotCorrected;
	ReducedLutPointer m_CRLut;


};

}
}

OTB_APPLICATION_EXPORT(vns::Wrapper::ReduceLut)
