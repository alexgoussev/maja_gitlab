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
#include "vnsMultiplyByScalarVectorImageFilter.h"
#include "vnsLoggers.h"
#include <string>

namespace vns
{

namespace Wrapper
{

using namespace otb::Wrapper;

class MultiplyByScalar : public Application
{
public:
	/** Standard class typedefs. */
	typedef MultiplyByScalar  	 		  Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(MultiplyByScalar, otb::Wrapper::Application);

	/** Some convenient typedefs. */
	typedef DoubleVectorImageType ImageType;
	typedef vns::MultiplyByScalarVectorImageFilter<ImageType, ImageType> RealToRealScalarVectorImageFilterType;


private:
	void DoInit()
	{
		SetName("MultiplyByScalar");
		SetDescription("Multiply by scalar algo.");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocName("MultiplyByScalar");
		SetDocLongDescription("This application multiply each image of a vector image by a factor");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Statistics");

		AddParameter(ParameterType_InputImage,  "im",   "vectorimage");
		AddParameter(ParameterType_Float, "coef","Coeff to multiply");
		AddParameter(ParameterType_OutputImage, "out", "image");
		SetParameterDescription("out","output image");

		AddRAMParameter("ram");
		SetDefaultParameterInt("ram",2048);

	}

	void DoUpdateParameters()
	{

	}


	void DoExecute()
	{
		// Init filters
		m_filter = RealToRealScalarVectorImageFilterType::New();

		//Get Image
		ImageType::ConstPointer l_im = this->GetParameterDoubleVectorImage("im");
		const double l_coeff = this->GetParameterFloat("coef");
		m_filter->SetInput(l_im);
		m_filter->SetCoeff(l_coeff);
		SetParameterOutputImage<ImageType>("out",m_filter->GetOutput());

	}


	/** Filters declaration */
	 RealToRealScalarVectorImageFilterType::Pointer m_filter;
};

}
}

OTB_APPLICATION_EXPORT(vns::Wrapper::MultiplyByScalar)
