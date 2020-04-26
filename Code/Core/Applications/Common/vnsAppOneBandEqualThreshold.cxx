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
#include "vnsOneBandEqualThresholdFunctor.h"
#include "otbFunctorImageFilter.h"
#include <string>

namespace vns
{

namespace Wrapper
{

using namespace otb::Wrapper;

class OneBandEqualThreshold : public Application
{
public:
	/** Standard class typedefs. */
	typedef OneBandEqualThreshold 		  Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(OneBandEqualThreshold, otb::Wrapper::Application);

	/** Some convenient typedefs. */
	typedef DoubleVectorImageType VectorImageType;
	typedef UInt8ImageType MaskType;
	typedef DoubleVectorImageType::PixelType RealVectorPixelType;
	typedef MaskType::InternalPixelType MaskPixelType;
	typedef Functor::OneBandEqualThresholdFunctor<RealVectorPixelType, MaskPixelType> OneBandEqualThresholdFunctorType;
	typedef itk::UnaryFunctorImageFilter<VectorImageType, MaskType, OneBandEqualThresholdFunctorType> OneBandEqualThresholdFilterType;
	typedef typename OneBandEqualThresholdFilterType::Pointer OneBandEqualThresholdFilterPointer;

private:
	void DoInit()
	{
		SetName("OneBandEqualThreshold");
		SetDescription("If one band equal threshold the band equal value.");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocLongDescription("If one band equal threshold the band equal value");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Mask");

		AddParameter(ParameterType_InputImage,  "im",   "vectorimage");
		AddParameter(ParameterType_Float, "thresholdvalue","ThresholdCoeff to detect");
		AddParameter(ParameterType_Float, "equalvalue","Equal value for output");
		AddParameter(ParameterType_Float, "outsidevalue","Outside value for output");
		AddParameter(ParameterType_OutputImage, "out", "image");
		SetParameterDescription("out","output image");
		SetParameterOutputImagePixelType("out",ImagePixelType_uint8);

		AddRAMParameter("ram");
		SetDefaultParameterInt("ram",2048);

	}

	void DoUpdateParameters()
	{

	}


	void DoExecute()
	{
		// Init filters
		m_filter = OneBandEqualThresholdFilterType::New();
		m_filter->SetReleaseDataFlag(true);
		m_filter->SetReleaseDataBeforeUpdateFlag(true);
		//Get Image
		VectorImageType::ConstPointer l_im = this->GetParameterDoubleVectorImage("im");
		const double l_thresholdValue = this->GetParameterFloat("thresholdvalue");
		const double l_equalValue = this->GetParameterFloat("equalvalue");
		const double l_outsideValue = this->GetParameterFloat("outsidevalue");

		m_filter->SetInput(l_im);
		m_filter->GetFunctor().SetThresholdValue(l_thresholdValue); // 0
		m_filter->GetFunctor().SetEqualValue(l_equalValue); // 255
		m_filter->GetFunctor().SetOutsideValue(l_outsideValue); //0
		m_filter->UpdateOutputInformation();
		SetParameterOutputImage<MaskType>("out",m_filter->GetOutput());

	}


	/** Filters declaration */
	OneBandEqualThresholdFilterType::Pointer m_filter;
};

}
}

OTB_APPLICATION_EXPORT(vns::Wrapper::OneBandEqualThreshold)
