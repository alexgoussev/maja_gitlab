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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 31 août 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "otbThresholdVectorImageFilter.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"

int vnsThresholdVectorImageFilterTest(int /*argc*/, char * argv [])
{
    typedef double InputPixelType;
    typedef double OutputPixelType;
    /** Image typedefs */
    typedef otb::VectorImage<InputPixelType> InputImageType;
    typedef otb::VectorImage<OutputPixelType> OutputImageType;
    
    typedef otb::ImageFileReader<InputImageType> ReaderType;
    typedef otb::ImageFileWriter<OutputImageType> WriterType;

    typedef otb::ThresholdVectorImageFilter<InputImageType,OutputImageType>  FilterType;

    /** instantiating the filter */
    FilterType::Pointer filter = FilterType::New();
    ReaderType::Pointer reader = ReaderType::New();
    WriterType::Pointer writer = WriterType::New();   

    reader->SetFileName( argv[1] );
    filter->SetInput( reader->GetOutput() );
    filter->SetLower( 100 );
    filter->SetUpper( 150 );
    filter->SetOutsideValue(-100);

    writer->SetInput( filter->GetOutput() );
    writer->SetFileName( argv[2] );
    writer->Update();

    return EXIT_SUCCESS;
}
