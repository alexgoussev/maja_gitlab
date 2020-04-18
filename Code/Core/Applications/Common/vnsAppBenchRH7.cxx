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
#include "vnsBenchRH7Filter.h"
#include "vnsLoggers.h"
#include <string>

namespace vns
{

namespace Wrapper
{

using namespace otb::Wrapper;

class BenchRH7: public Application
{
public:
	/** Standard class typedefs. */
	typedef BenchRH7  	 		  Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(BenchRH7, otb::Wrapper::Application);

	/** Some convenient typedefs. */
	typedef DoubleVectorImageType InImageType;
	typedef FloatVectorImageType OutImageType;
	typedef vns::BenchRH7<InImageType, OutImageType> MachinFilterType;


private:
	void DoInit()
	{
		SetName("BenchRH7");
		SetDescription("BenchRH7");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocLongDescription("BenchRH7 test the bug on rh7");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Benchmark");

		AddParameter(ParameterType_Int, "nbthreads","nbthreads");
		AddParameter(ParameterType_Int, "nbpixels","nbpixels");
		AddParameter(ParameterType_Int, "nbbands","nbbands");

	}

	void DoUpdateParameters()
	{

	}


	void DoExecute()
	{
		//Get param
		const unsigned int l_nbBands = this->GetParameterFloat("nbbands");
		const unsigned int l_nbPixels = this->GetParameterFloat("nbpixels");
		const unsigned int l_nbThreads = this->GetParameterFloat("nbthreads");
		// Init filters
		MachinFilterType filter(l_nbThreads,	l_nbBands, l_nbPixels);
		filter.Update();
	}

};

}
}

OTB_APPLICATION_EXPORT(vns::Wrapper::BenchRH7)
