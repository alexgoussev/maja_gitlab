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
 * $Id: vnsThresholdVectorImageFilterTest.cxx 2406 2011-01-19 15:38:23Z tfeuvrie $
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsMaskUpdatingFunctor.h"

#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"

int vnsMaskUpdatingImageFilterTest(int /*argc*/, char * argv [])
{
    typedef unsigned char InputPixelType;
    typedef unsigned char OutputPixelType;
    /** Image typedefs */
    typedef otb::Image<InputPixelType> MaskType;
    
    typedef otb::ImageFileReader<MaskType> ReaderType;
    typedef otb::ImageFileWriter<MaskType> WriterType;

    typedef vns::Functor::MaskUpdatingImageFunctor<InputPixelType,InputPixelType> FunctorType;
    typedef itk::BinaryFunctorImageFilter<MaskType, MaskType, MaskType, FunctorType>  FilterType;

    /** instantiating the filter */
    FilterType::Pointer filter = FilterType::New();
    ReaderType::Pointer inReader = ReaderType::New();
    ReaderType::Pointer refReader = ReaderType::New();
    WriterType::Pointer writer = WriterType::New();   

    inReader->SetFileName( argv[1] );
    filter->SetInput1( inReader->GetOutput() );
    refReader->SetFileName( argv[2] );
    filter->SetInput2( refReader->GetOutput() );
    filter->GetFunctor().SetThresholdRefMaskValue(0);
    filter->GetFunctor().SetOutputMaskValue(0);

    writer->SetInput( filter->GetOutput() );
    writer->SetFileName( argv[3] );
    writer->Update();

    return EXIT_SUCCESS;
}
