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
 * VERSION : 4-0-0 : <TypeFT> : <NumFT> : 6 janvier 2014 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: vnsSnowMaskValidationByLabelImageFilterNew.cxx 3279 2011-10-04 14:44:32Z cruffel $
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsSnowMaskValidationByLabelImageFilter.h"
#include "otbImage.h"
#include "otbImageFileReader.h"
#include "vnsLoggers.h"

int vnsSnowMaskValidationByLabelImageFilterTest(int argc, char * argv [])
{

    if (argc != 5)
	{
	  std::cerr << argv[0] << "<Snow label border mask filename> <Edge mask filename> "
			  "<Cloud refl mask filename> <Cloud refl Var mask filename>"<< std::endl;
	  return EXIT_FAILURE;
	}

	// Configure Logger
	vns::Loggers::GetInstance()->Initialize(argv[0]);
	vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);

	const unsigned int Dimension = 2;

	/** Pixel typedefs */
	typedef unsigned short MaskPixelType;
	/** Image typedefs */
	typedef otb::Image<MaskPixelType,Dimension> MaskImageType;

	typedef otb::ImageFileReader<MaskImageType>  MaskReaderType;

	typedef vns::SnowMaskValidationByLabelImageFilter<MaskImageType>  FilterType;

	MaskReaderType::Pointer snwReader  = MaskReaderType::New();
	MaskReaderType::Pointer edgReader  = MaskReaderType::New();
	MaskReaderType::Pointer cldReflReader  = MaskReaderType::New();
	MaskReaderType::Pointer cldReflVarReader  = MaskReaderType::New();

	snwReader->SetFileName(argv[1]);
	edgReader->SetFileName(argv[2]);
	cldReflReader->SetFileName(argv[3]);
	cldReflVarReader->SetFileName(argv[4]);


	/** instantiating the filter */
	FilterType::Pointer filter = FilterType::New();

	filter->SetSNWLabelBorderMask( snwReader->GetOutput() );
	filter->SetIPEDGMask( edgReader->GetOutput() );
	filter->SetIPCLDReflMask( cldReflReader->GetOutput() );
	filter->SetIPCLDReflVarMask( cldReflVarReader->GetOutput() );

	filter->Update();

	std::cout<<"Valid pixels "<<filter->GetNumberOfValidPixels()<<std::endl;
	std::cout<<"Snow pixels "<<filter->GetSnowPixels()<<std::endl;

	bool isValid = filter->GetIsValid();

	if (isValid)
	{
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
