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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 18 mars 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/

#include "otbImage.h"
#include "otbImageFileWriter.h"
#include "vnsLoggers.h"

#include "otbImageFileReader.h"
#include "vnsGRIBImageIOFactory.h"
#include "itkObjectFactoryBase.h"


int vnsReadGRIBImage(int, char* argv[])
{  
  const char * inputFilename  = argv[1];
  const char * outputFilename = argv[2];

  vns::Loggers::GetInstance()->Initialize(argv[0]);
  vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);

  typedef double                            PixelType;
  typedef otb::Image< PixelType >           ImageType;

  itk::ObjectFactoryBase::RegisterFactory( vns::GRIBImageIOFactory::New() );
  typedef otb::ImageFileReader< ImageType >       ReaderType;

  typedef otb::ImageFileWriter< ImageType >       WriterType;

  ReaderType::Pointer    reader  = ReaderType::New();

  reader->SetFileName( inputFilename );

  WriterType::Pointer    writer  = WriterType::New();

  writer->SetFileName( outputFilename );
  writer->SetInput( reader->GetOutput() );

  writer->Update();

  return EXIT_SUCCESS;
}
