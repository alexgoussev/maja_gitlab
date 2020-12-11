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
#include "vnsDirectionalCorrectionCompute.h"
#include "vnsUtilities.h"
#include "vnsLookUpTableFileReader.h"
#include "vnsSimpleLutXMLFileHandler.h"
#include "vnsSimpleLutXMLContainer.h"
#include "vnsDirectionalCorrectionLUTCompute.h"

namespace vns
{

enum
{
	roy,
	lut
};


namespace Wrapper
{

using namespace otb::Wrapper;

class DirectionnalCorrection : public Application
{
public:
	/** Standard class typedefs. */
	typedef DirectionnalCorrection        Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(DirectionnalCorrection, otb::Wrapper::Application);

	/** Some convenient typedefs. */
    //Directional correction compute
    typedef DirectionalCorrectionCompute DirectionalCorrectionComputeType;

    //Reduced output lut typedef
    typedef VNSLUT3DType LutType;
    typedef typename LutType::ConstPointer ReducedLutConstPointer;
    typedef typename LutType::Pointer ReducedLutPointer;
    //LookupTable Reader
    typedef LookUpTableFileReader<LutType> LookUpTableReaderType;
    typedef typename LookUpTableReaderType::Pointer LookUpTableReaderPointer;
    typedef typename LutType::ParameterValuesType ParameterValuesType;

    typedef DirectionalCorrectionLUTCompute DirectionalCorrectionLUTComputeFilterType;
	typedef DirectionalCorrectionLUTComputeFilterType::Pointer DirectionalCorrectionLUTComputeFilterPointerType;


private:
	void DoInit()
	{
		SetName("DirectionnalCorrection");
		SetDescription("DirectionnalCorrection algo.");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocLongDescription("This application computes the directional correction coeffs");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Statistics");

		AddParameter(ParameterType_Group, "solar","Solar angles");
		AddParameter(ParameterType_Float, "solar.zenith","Solar zenith");
		AddParameter(ParameterType_Float, "solar.azimuth","Solar azimuth");
		AddParameter(ParameterType_Group, "viewing","Mean Viewing angles");
		AddParameter(ParameterType_StringList, "viewing.zenith","Viewing zenith");
		AddParameter(ParameterType_StringList, "viewing.azimuth","Viewing azimuth");
		AddParameter(ParameterType_Float,  "refzenith","refzenith");
		AddParameter(ParameterType_Float,  "refazimuth","refazimuth");

		AddParameter(ParameterType_String, "coeffs", "correction coeffs");
		SetParameterRole("coeffs", Role_Output);

		//Choose the mode
		AddParameter(ParameterType_Choice,"model", "directional correction option");
		AddChoice("model.roy", "ROY Model");
		AddChoice("model.lut", "LUT Model");

		AddParameter(ParameterType_Group,"roy", "roy model");
		MandatoryOff("roy");
		AddParameter(ParameterType_StringList, "roy.coeffsr","CoeffsR");
		AddParameter(ParameterType_StringList, "roy.coeffsv","CoeffsV");

		AddParameter(ParameterType_Group,"lut", "lut model");
		MandatoryOff("lut");
		AddParameter(ParameterType_String, "lut.filename","LUT filename");

		AddRAMParameter("ram");
		SetDefaultParameterInt("ram",2048);

	}

	void DoUpdateParameters()
	{
	}

	void DoExecute()
	{
		//Get Params
		double m_SolarZenith = GetParameterFloat("solar.zenith");
		double m_SolarAzimuth = GetParameterFloat("solar.azimuth");
		Utilities::ListOfDoubles m_MeanViewingZenithAngles = Utilities::StringListAsDouble(
				this->GetParameterStringList("viewing.zenith"));
		Utilities::ListOfDoubles m_MeanViewingAzimuthAngles = Utilities::StringListAsDouble(
				this->GetParameterStringList("viewing.azimuth"));
		double m_RefZenith = GetParameterFloat("refzenith");
		double m_RefAzimuth = GetParameterFloat("refazimuth");
		const unsigned int nb_MeanViewingAngles = m_MeanViewingZenithAngles.size();


		//Choose model
		Utilities::DirCorrModelEnumType l_DirCorrOption;
		// Get mell
		switch ( GetParameterInt("model") )
		{
		case roy:
			l_DirCorrOption = Utilities::ROY;
			break;
		case lut:
			l_DirCorrOption = Utilities::LUT;
			break;
		}

		Utilities::ListOfDoubles coefs ;


		if (l_DirCorrOption == Utilities::ROY)
		    {
		    vnsLogDebugMacro("Directional Correction model : ROY");
		    if ((!IsParameterEnabled("roy.coeffsr")) || (!IsParameterEnabled("roy.coeffsv")))
			    {
				vnsExceptionDataMacro("roy.coeffsr and roy.coeffsv parameter must be set in cas of ROY model!!!");
			    }

			//Correction coeff
		    Utilities::ListOfDoubles m_CoefsR = Utilities::StringListAsDouble(this->GetParameterStringList("roy.coeffsr"));
		    Utilities::ListOfDoubles m_CoefsV= Utilities::StringListAsDouble(this->GetParameterStringList("roy.coeffsv"));

		    //Verify consitency of input
            if (m_CoefsR.size() != m_MeanViewingZenithAngles.size()){
                vnsExceptionAlgorithmsProcessingMacro("Internal error: the number of CoefR '"<<m_CoefsR.size()<<
                        "' is different than the ViewingAnglesZenithPerBand'"<<m_MeanViewingZenithAngles.size()<<"'!")
            }
            if (m_CoefsV.size() != m_MeanViewingZenithAngles.size()){
                vnsExceptionAlgorithmsProcessingMacro("Internal error: the number of CoefV '"<<m_CoefsV.size()<<
                        "' is different than the ViewingAnglesZenithPerBand'"<<m_MeanViewingZenithAngles.size()<<"'!")
            }

            //Compute the ROY directional correction coeffs
		    coefs = DirectionalCorrectionComputeType::ComputeCorrectionCoeffs(m_SolarZenith,m_SolarAzimuth,
				m_RefZenith,m_RefAzimuth,m_MeanViewingZenithAngles, m_MeanViewingAzimuthAngles, m_CoefsR,m_CoefsV);
		    }

		else //l_DirCorrOption == Utilities::LUT
		    {
		    vnsLogDebugMacro("Directional Correction model : LUT");

		    // Init filters
            m_DirectionalCorrectionLUTComputeFilter = DirectionalCorrectionLUTComputeFilterType::New();

		    if (!IsParameterEnabled("lut.filename"))
			    {
				vnsExceptionDataMacro("Missing LUT : lut.filename parameter must be set in cas of LUT model!!!");
			    }

			const std::string m_strLutFileName = GetParameterString("lut.filename");
			vnsLogDebugMacro("lut filemane : " << m_strLutFileName) ;

			//Read the xml lut description file
            SimpleLutXMLFileHandler::Pointer l_LUTXMLHandler = vns::SimpleLutXMLFileHandler::New();
            // Load the XML file and check with the schema
            l_LUTXMLHandler->LoadFile(m_strLutFileName);
            const vns::SimpleLutXMLContainer& l_lutxml = l_LUTXMLHandler->GetLutContainer();

            // Init LUT filters
            LookUpTableReaderPointer l_lookUpTableReader = LookUpTableReaderType::New();
            // Get the number of file that matches with the number of band
            const std::vector<std::string>& l_GIP_DIRCOR_ListOfFilenames = l_lutxml.GetListOfPackaged_DBL_Files();
            const unsigned int fileNumber = l_GIP_DIRCOR_ListOfFilenames.size();

            for (unsigned int file = 0; file < fileNumber; file++)
		        {
                // Set the filename of each band
                l_lookUpTableReader->AddBandFilename(l_GIP_DIRCOR_ListOfFilenames[file]);
		        }

		    // Read informations from the GIPP file
            const std::vector<double>& l_GIP_DIRCOR_SolarZenithalAngleIndexes = l_lutxml.GetSolar_Zenith_Angle_Indexes();
            const std::vector<double>& l_GIP_DIRCOR_ViewZenithalAngleIndexes = l_lutxml.GetView_Zenith_Angle_Indexes();
            const std::vector<double>& l_GIP_DIRCOR_RelativeAzimuthAngleIndexes = l_lutxml.GetRelative_Azimuth_Angle_Indexes();

            /* parameters are added one by one to the LUT */
            ParameterValuesType l_GIP_DIRCORParam1;
            l_GIP_DIRCORParam1.ParameterName = "Solar_Zenith_Angle_Indexes";
            l_GIP_DIRCORParam1.ParameterValues = l_GIP_DIRCOR_SolarZenithalAngleIndexes;
            l_lookUpTableReader->AddParameterValues(l_GIP_DIRCORParam1);

            ParameterValuesType l_GIP_DIRCORParam2;
            l_GIP_DIRCORParam2.ParameterName = "View_Zenith_Angle_Indexes";
            l_GIP_DIRCORParam2.ParameterValues = l_GIP_DIRCOR_ViewZenithalAngleIndexes;
            l_lookUpTableReader->AddParameterValues(l_GIP_DIRCORParam2);

            ParameterValuesType l_GIP_DIRCORParam3;
            l_GIP_DIRCORParam3.ParameterName = "Relative_Azimuth_Angle_Indexes";
            l_GIP_DIRCORParam3.ParameterValues = l_GIP_DIRCOR_RelativeAzimuthAngleIndexes;
            l_lookUpTableReader->AddParameterValues(l_GIP_DIRCORParam3);

            //Generate Lut
            l_lookUpTableReader->GenerateLUT();
            //Useful typedef for LUT
            typedef LutType::PointType LUTPointType;
            typedef LutType::Pointer LUTPointer;
            //Get the lut pointer
            LUTPointer l_LutInPtr = l_lookUpTableReader->GetLUT();

            m_DirectionalCorrectionLUTComputeFilter->SetSolarZenith(m_SolarZenith);
            m_DirectionalCorrectionLUTComputeFilter->SetSolarAzimuth(m_SolarAzimuth);
            m_DirectionalCorrectionLUTComputeFilter->SetRefZenith(m_RefZenith);
            m_DirectionalCorrectionLUTComputeFilter->SetRefAzimuth(m_RefAzimuth);
            m_DirectionalCorrectionLUTComputeFilter->SetLUT(l_LutInPtr);
            m_DirectionalCorrectionLUTComputeFilter->SetMeanViewingZenithAngles(m_MeanViewingZenithAngles);
            m_DirectionalCorrectionLUTComputeFilter->SetMeanViewingAzimuthAngles(m_MeanViewingAzimuthAngles);
            // Compute the directional correction coeffs
            m_DirectionalCorrectionLUTComputeFilter->ComputeDirectionalCoeffs();
            // Get the directional correction coeffs
            coefs = m_DirectionalCorrectionLUTComputeFilter->GetCorrCoefs();
            }

        for (unsigned int bandNum = 0; bandNum < nb_MeanViewingAngles; bandNum++)
		    {
			vnsLogDebugMacro("Direction Correction Coeff band "<<bandNum<<" = "<<std::setprecision(20)<<coefs.at(bandNum));
		    }

		std::string l_String("");
		if (coefs.size() > 0)
		{
			for (unsigned int i = 0; i < coefs.size() - 1; i++)
			{
				std::ostringstream oss;
				oss << std::setprecision(12)<<coefs[i];
				l_String = l_String + oss.str() + " ";
			}
			std::ostringstream oss;
			oss << coefs[coefs.size() - 1];
			l_String = l_String + oss.str().c_str();
		}
		SetParameterString("coeffs",l_String);

    }

private:
    DirectionalCorrectionLUTComputeFilterPointerType m_DirectionalCorrectionLUTComputeFilter;



};

}
}


OTB_APPLICATION_EXPORT(vns::Wrapper::DirectionnalCorrection)
