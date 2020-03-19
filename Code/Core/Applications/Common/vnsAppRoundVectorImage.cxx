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
#include "vnsRoundVectorImageFunctor.h"
#include "otbUnaryFunctorVectorImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include <string>
#include "vnsLoggers.h"
#include "vnsMacro.h"

namespace vns
{

namespace Wrapper
{

using namespace otb::Wrapper;

class RoundVectorImage : public Application
{
public:
	/** Standard class typedefs. */
	typedef RoundVectorImage			 		  Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(RoundVectorImage, otb::Wrapper::Application);

	/** Some convenient typedefs. */
	typedef DoubleVectorImageType InputImageType;

	typedef Int16VectorImageType VectorImageType;
    typedef VectorImageType::Pointer ImagePointerType;


//	typedef UInt16VectorImageType UnsignedVectorImageType;
//    typedef UInt16VectorImageType::Pointer UnsignedImagePointerType;


	typedef vns::Functor::RoundVectorImage<InputImageType::PixelType, VectorImageType::PixelType> RoundVectorImageFunctor;
	typedef otb::UnaryFunctorVectorImageFilter<InputImageType, VectorImageType, RoundVectorImageFunctor> RealToMaskRoundVectorImageFilterType;


private:
	void DoInit()
	{
		SetName("RoundVectorImage");
		SetDescription("Round the image to the closest int value.");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocName("OneBandEqualThreshold");
		SetDocLongDescription("If one band equal threshold the band equal value");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Mask");

		AddParameter(ParameterType_InputImage,  "im",   "image");
		AddParameter(ParameterType_OutputImage, "out", "image");
		SetParameterOutputImagePixelType("out", ImagePixelType_int16);
		SetParameterDescription("out","output image");
		AddParameter(ParameterType_Float,"coef","multiplication coeff");
		MandatoryOff("coef");
		AddRAMParameter("ram");
		SetDefaultParameterInt("ram", 2048);

	}

	void DoUpdateParameters()
	{
	}


	void DoExecute()
	{
		// Init filters
		DoubleVectorImageType::ConstPointer l_im = this->GetParameterDoubleVectorImage("im");
		m_filter = RealToMaskRoundVectorImageFilterType::New();
        m_filter->SetInput(l_im);
        if(HasValue("coef"))
        {
        	m_filter->GetFunctor().SetCoef(this->GetParameterFloat("coef"));
        }
		SetParameterOutputImage<VectorImageType>("out", m_filter->GetOutput());
	}

	/** Filters declaration */
	 RealToMaskRoundVectorImageFilterType::Pointer m_filter;
};

}
}

OTB_APPLICATION_EXPORT(vns::Wrapper::RoundVectorImage)
