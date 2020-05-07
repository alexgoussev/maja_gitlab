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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 9 juil. 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <iostream>

#include "vnsLinearInterpolateImageFunction.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"


int vnsLinearInterpolateImageFunctionTest( int, char * argv[] )
{
  const char * inputFileName  = argv[1];


  typedef double                                         PixelType;
  typedef otb::VectorImage<PixelType>                    ImageType;
  typedef otb::ImageFileReader<ImageType>                ReaderType;
  typedef vns::LinearInterpolateImageFunction<ImageType> InterpolatorType;
  typedef InterpolatorType::ContinuousIndexType          ContinuousIndexType;

  ReaderType::Pointer   reader   = ReaderType::New();
  InterpolatorType::Pointer interpol = InterpolatorType::New();

  reader->SetFileName( inputFileName );
  reader->Update();
  interpol->SetInputImage( reader->GetOutput() );

  ContinuousIndexType id;
  id[0] = 10.9;
  id[1] = 10.2;
 


  ImageType::PixelType out = interpol->EvaluateAtContinuousIndex( id );

  ImageType::IndexType idd;
  idd[0] = static_cast<long int>(vcl_floor(id[0]+0.5));
  idd[1] = static_cast<long int>(vcl_floor(id[1]+0.5));
  
  std::cout<<reader->GetOutput()->GetPixel(idd)<<" -> "<<out<<std::endl;

  return EXIT_SUCCESS;
}
