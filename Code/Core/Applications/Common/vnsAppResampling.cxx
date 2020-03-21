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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 15 juil. 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"
#include "vnsPadAndResampleImageFilter.h"
#include "vnsBinaryThresholdVectorImageFilter.h"
#include "otbVectorImageToImageListFilter.h"
#include "vnsBinaryThresholdVectorImageFilter.h"
#include <string>

namespace vns
{
enum
{
	interp_linear,
	interp_bco,
	interp_linearradius,
	interp_fastlinear,
	interp_cloudcla,
	interp_cloudclalt
};

namespace Wrapper
{

using namespace otb::Wrapper;

class Resampling : public Application
{
public:
	/** Standard class typedefs. */
	typedef Resampling             Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(Resampling, otb::Wrapper::Application);

	/** Some convenient typedefs. */
	typedef DoubleVectorImageType VectorImageType;
	typedef VectorImageType::ConstPointer VectorImageConstPointer;
	typedef VectorImageType::Pointer VectorImagePointer;
	typedef VectorImageType::PixelType VectorPixelType;

	typedef DoubleImageType ImageType;
	typedef ImageType::ConstPointer ImageConstPointer;
	typedef ImageType::Pointer ImagePointer;
	typedef ImageType::PixelType PixelType;

	typedef UInt8ImageType MaskType;
	typedef MaskType::Pointer MaskPointer;
	typedef MaskType::ConstPointer MaskConstPointer;

	/** PadFilter used to manipulate real data */
	typedef PadAndResampleImageFilter<VectorImageType, VectorImageType> PadAndResampleImageFilterType;
	typedef PadAndResampleImageFilterType::Pointer PadAndResampleImageFilterPointerType;

	typedef BinaryThresholdVectorImageFilter<VectorImageType, VectorImageType> BinaryThresholdVectorImageFilterType;
	typedef BinaryThresholdVectorImageFilterType::Pointer BinaryThresholdVectorImageFilterPointer;

	/* VectorImage to image converter */
	typedef otb::ImageList<ImageType> ImageListType;
	typedef otb::VectorImageToImageListFilter<VectorImageType, ImageListType> VectorToImageFilter;
	typedef VectorToImageFilter::Pointer VectorToImageFilterPointer;

private:
	void DoInit()
	{
		SetName("Resampling");
		SetDescription("Resampling algo.");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocName("resampling");
		SetDocLongDescription("This application resample the image according to the dtm");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Statistics");

		AddParameter(ParameterType_InputImage,  "dtm",   "DTM");
		SetParameterDescription("dtm", "Image used as reference grid");
		AddParameter(ParameterType_InputImage,  "im",   "image");
		SetParameterDescription("im", "Image to be resampled");
		AddParameter(ParameterType_Float,  "threshold", "Do threshold");
		SetParameterDescription("threshold", "Threshold the output image");
		MandatoryOff("threshold");

		AddParameter(ParameterType_Group,  "outareasize", "outareasize");
		SetParameterDescription("outareasize", "Size of the output image");
		MandatoryOff("outareasize");

		AddParameter(ParameterType_Int, "outareasize.x","outareasize.x" );
        SetParameterDescription("outareasize.x", "Size x");
		MandatoryOff("outareasize.x");

		AddParameter(ParameterType_Int, "outareasize.y","outareasize.y" );
        SetParameterDescription("outareasize.y", "Size y");
		MandatoryOff("outareasize.y");

		AddParameter(ParameterType_Float,  "padradius", "padradius");
		SetParameterDescription("padradius", "Radius to pad the input");
		MandatoryOff("padradius");


		AddParameter(ParameterType_Float,  "nodata", "nodata");
		SetParameterDescription("nodata", "nodata to use in CLA resampling");
		MandatoryOff("nodata");
		AddParameter(ParameterType_Choice, "interp", "Interpolator");
		AddChoice("interp.linear", "Linear Interpolation");
		AddChoice("interp.bco", "BCO Interpolation");
		AddChoice("interp.linearradius", "Linear with radius Interpolation");
		AddChoice("interp.fastlinear", "Fast Linear Interpolation");
		AddChoice("interp.cloudcla", "Cloud CLA special interpolation");
		AddChoice("interp.cloudclalt", "Cloud CLAlt special Interpolation");

		AddRAMParameter("ram");
		SetDefaultParameterInt("ram",2048);

		AddParameter(ParameterType_OutputImage, "out", "image");
		SetParameterDescription("out","output image");

	}

	void DoUpdateParameters()
	{
	}


	void DoExecute()
	{
		vns::Loggers::GetInstance()->Initialize(GetName());
		// Init filters
		vnsLogDebugMacro("Number of threads : "<<itk::MultiThreader::GetGlobalDefaultNumberOfThreads())
		// Get input image pointers
		VectorImagePointer l_inPtr = GetParameterDoubleVectorImage("im");
		l_inPtr->UpdateOutputInformation();
		bool l_isVec = true;

		ImagePointer l_dtmPtr = GetParameterDoubleImage("dtm");
		l_dtmPtr->UpdateOutputInformation();
		//Set Parameters
		unsigned int l_padradius = 0;
		if(HasValue("padradius"))
		{
			l_padradius = GetParameterInt("padradius");
		}


		Area l_outArea;
		l_outArea.Origin = l_dtmPtr->GetOrigin();
		l_outArea.Spacing = l_dtmPtr->GetSignedSpacing();
		l_outArea.Size = l_dtmPtr->GetLargestPossibleRegion().GetSize();


		//Choose interpolator
		ResamplerHelper::InterpolatorType l_interpolator;
		// Get Interpolator
		switch ( GetParameterInt("interp") )
		{
		case interp_linear:
			l_interpolator = ResamplerHelper::RB_INTERPOLATOR_LINEAR;
			break;
		case interp_bco:
			l_interpolator = ResamplerHelper::RB_INTERPOLATOR_BCO;
			break;
		case interp_linearradius:
			l_interpolator = ResamplerHelper::RB_INTERPOLATOR_LINEAR_WITH_RADIUS;
			break;
		case interp_fastlinear:
			l_interpolator = ResamplerHelper::RB_INTERPOLATOR_MAJA_FAST_LINEAR;
			break;
		case interp_cloudcla:
			l_interpolator = ResamplerHelper::RB_INTERPOLATOR_MAJA_CLOUD_UNDERSAMPLING_CLA;
			break;
		case interp_cloudclalt:
			l_interpolator = ResamplerHelper::RB_INTERPOLATOR_MAJA_CLOUD_UNDERSAMPLING_CLD_ALT;
			break;
		}



		const bool isSamePhysical = l_inPtr->GetOrigin().GetVnlVector().is_equal(l_dtmPtr->GetOrigin().GetVnlVector(), 1e-5) &&
				l_inPtr->GetLargestPossibleRegion() == l_dtmPtr->GetLargestPossibleRegion() &&
				l_inPtr->GetSpacing().GetVnlVector().is_equal(l_dtmPtr->GetSpacing().GetVnlVector(), 1e-5) &&
				l_inPtr->GetDirection().GetVnlMatrix().as_ref().is_equal(l_dtmPtr->GetDirection().GetVnlMatrix(), 1e-5);

		if( isSamePhysical && HasValue("outareasize.x")==false && HasValue("outareasize.y")==false)
		{
		   vnsLogDebugMacro("No resampling needed");
		   if(HasValue("threshold"))
		   {
			   m_Thresholder = BinaryThresholdVectorImageFilterType::New();
			   m_Thresholder->SetInput(l_inPtr);
			   m_Thresholder->ThresholdAbove(GetParameterFloat("threshold"));
			   m_Thresholder->SetInsideValue(0);
			   m_Thresholder->SetOutsideValue(1);
			   SetParameterOutputImagePixelType("out", ImagePixelType_uint8);
			   SetParameterOutputImage<VectorImageType>("out",m_Thresholder->GetOutput());

		   }
		   else
		   {
			   SetParameterOutputImagePixelType("out", ImagePixelType_double);
			   SetParameterOutputImage<VectorImageType>("out", l_inPtr);
		   }
		}
		else
		{
            //Compute
            m_PadAndResampleFilter = PadAndResampleImageFilterType::New();
            m_PadAndResampleFilter->SetInput0(l_inPtr);
            m_PadAndResampleFilter->SetInterpolator(l_interpolator);

            if(HasValue("outareasize.x") && HasValue("outareasize.y") )
            {
              vns::AreaType::SizeType l_outputSize;
              l_outputSize[0] = GetParameterInt("outareasize.x");
              l_outputSize[1] = GetParameterInt("outareasize.y");
              const AreaType l_area  = ResamplerHelper::ComputeResamplingCenteredImageAreaFromInputImageAreaAndSizeOutputImageCriteria(l_outArea, l_outputSize);
              m_PadAndResampleFilter->SetAreaToOutputImageResolution(l_area);
            }
            else
            {
                m_PadAndResampleFilter->SetAreaToOutputImageResolution(l_outArea);
            }

            m_PadAndResampleFilter->SetPadRadius(l_padradius);
            m_PadAndResampleFilter->UpdateWithCaching();
            VectorImagePointer l_tmpIm = m_PadAndResampleFilter->GetOutput();
            m_PadAndResampleFilter->GetOutput()->UpdateOutputInformation();

            if(HasValue("threshold"))
		    {
                m_Thresholder = BinaryThresholdVectorImageFilterType::New();
                m_Thresholder->SetInput(m_PadAndResampleFilter->GetOutput());
                m_Thresholder->ThresholdAbove(GetParameterFloat("threshold"));
                m_Thresholder->SetInsideValue(0);
                m_Thresholder->SetOutsideValue(1);
                SetParameterOutputImagePixelType("out", ImagePixelType_uint8);
                SetParameterOutputImage<VectorImageType>("out",m_Thresholder->GetOutput());

		    }
		    else
		    {
                SetParameterOutputImagePixelType("out", ImagePixelType_double);
                SetParameterOutputImage<VectorImageType>("out",m_PadAndResampleFilter->GetOutput());
		    }
		}
	}


	/** Filters declaration */
	PadAndResampleImageFilterPointerType m_PadAndResampleFilter;
	BinaryThresholdVectorImageFilterPointer m_Thresholder;
	VectorToImageFilterPointer m_Converter;

};

}
}

OTB_APPLICATION_EXPORT(vns::Wrapper::Resampling)
