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
#include "vnsThresholdImageFunctor.h"
#include "vnsThresholdVectorImageFunctor.h"
#include "otbUnaryFunctorVectorImageFilter.h"
#include "itkUnaryFunctorImageFilter.h"
#include <string>
#include "vnsLoggers.h"
#include "vnsMacro.h"

namespace vns
{

namespace Wrapper
{

using namespace otb::Wrapper;

class ThresholdImage : public Application
{
public:
	/** Standard class typedefs. */
	typedef ThresholdImage			 		  Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(ThresholdImage, otb::Wrapper::Application);

	/** Some convenient typedefs. */
	typedef DoubleVectorImageType InputImageType;

	typedef vns::Functor::ThresholdVectorImageFunctor<InputImageType::PixelType, InputImageType::PixelType> ThresholdVectorImageFunctor;
	typedef otb::UnaryFunctorVectorImageFilter<InputImageType, InputImageType, ThresholdVectorImageFunctor> RealToRealThresholdVectorImageFilterType;

	typedef vns::Functor::ThresholdImageFunctor<DoubleImageType::PixelType, DoubleImageType::PixelType> ThresholdImageFunctor;
	typedef itk::UnaryFunctorImageFilter<DoubleImageType, DoubleImageType, ThresholdImageFunctor> RealToRealThresholdImageFilterType;


private:
	void DoInit()
	{
		SetName("ThresholdImage");
		SetDescription("Round the image to the closest int value.");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocLongDescription("If one band equal threshold the band equal value");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Mask");

		AddParameter(ParameterType_InputImage,  "im",   "image");
		AddParameter(ParameterType_OutputImage, "out", "image");
		SetParameterOutputImagePixelType("out", ImagePixelType_double);
		SetParameterDescription("out","output image");
		AddParameter(ParameterType_Float,"threshold","threshold");
		AddParameter(ParameterType_Float,"abovevalue","abovevalue");
		AddParameter(ParameterType_Float,"undervalue","undervalue");
		AddRAMParameter("ram");
		SetDefaultParameterInt("ram", 2048);

	}

	void DoUpdateParameters()
	{
	}


	void DoExecute()
	{
		// Get input image pointers
		ImageBaseType* l_inPtr = GetParameterImageBase("im",0);
		// Guess the image type
		std::string className(l_inPtr->GetNameOfClass());


		if (className == "VectorImage") {
			// Init filters
			DoubleVectorImageType::ConstPointer l_im = this->GetParameterDoubleVectorImage("im");
			m_filter = RealToRealThresholdVectorImageFilterType::New();
			m_filter->SetInput(l_im);
			m_filter->GetFunctor().SetThresholdValue(this->GetParameterFloat("threshold"));
			m_filter->GetFunctor().SetOutputValue(this->GetParameterFloat("abovevalue"));
			m_filter->GetFunctor().SetInsideValue(this->GetParameterFloat("undervalue"));
			SetParameterOutputImage<InputImageType>("out", m_filter->GetOutput());
		} else {
			// Init filters
			DoubleImageType::ConstPointer l_im = this->GetParameterDoubleImage("im");
			m_single_filter = RealToRealThresholdImageFilterType::New();
			m_single_filter->SetInput(l_im);
			m_single_filter->GetFunctor().SetThresholdValue(this->GetParameterFloat("threshold"));
			m_single_filter->GetFunctor().SetOutputValue(this->GetParameterFloat("abovevalue"));
			m_single_filter->GetFunctor().SetInsideValue(this->GetParameterFloat("undervalue"));

			SetParameterOutputImage<DoubleImageType>("out", m_single_filter->GetOutput());
		}
	}

	/** Filters declaration */
	 RealToRealThresholdVectorImageFilterType::Pointer m_filter;
	 RealToRealThresholdImageFilterType::Pointer m_single_filter;
};

}
}

OTB_APPLICATION_EXPORT(vns::Wrapper::ThresholdImage)
