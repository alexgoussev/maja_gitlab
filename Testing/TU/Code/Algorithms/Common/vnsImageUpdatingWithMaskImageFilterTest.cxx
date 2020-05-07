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
#include <vnsImageUpdatingWithMaskFunctor.h>

#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "itkTernaryFunctorImageFilter.h"

int vnsImageUpdatingWithMaskImageFilterTest(int /*argc*/, char * argv [])
{
    typedef unsigned char InputPixelType;
    typedef unsigned char MaskPixelType;
    typedef unsigned char OutputPixelType;
    /** Image typedefs */
    typedef otb::Image<InputPixelType> ImageType;
    typedef otb::Image<MaskPixelType> MaskType;
    
    typedef otb::ImageFileReader<ImageType> ReaderType;
    typedef otb::ImageFileReader<MaskType> MaskReaderType;
    typedef otb::ImageFileWriter<ImageType> WriterType;

    typedef vns::Functor::ImageUpdatingWithMaskImageFunctor<InputPixelType,MaskPixelType> FunctorType;
    typedef itk::TernaryFunctorImageFilter<ImageType, MaskType,ImageType,ImageType,FunctorType>  FilterType;

    /** instantiating the filter */
    FilterType::Pointer filter = FilterType::New();
    ReaderType::Pointer inReader = ReaderType::New();
    MaskReaderType::Pointer refReader = MaskReaderType::New();
    ReaderType::Pointer corrReader = ReaderType::New();
    WriterType::Pointer writer = WriterType::New();   

    inReader->SetFileName( argv[1] );
    filter->SetInput1( inReader->GetOutput() );
    refReader->SetFileName( argv[2] );
    filter->SetInput2( refReader->GetOutput() );
    corrReader->SetFileName( argv[3] );
    filter->SetInput3( corrReader->GetOutput() );

    writer->SetInput( filter->GetOutput() );
    writer->SetFileName( argv[4] );
    writer->Update();

    return EXIT_SUCCESS;
}
