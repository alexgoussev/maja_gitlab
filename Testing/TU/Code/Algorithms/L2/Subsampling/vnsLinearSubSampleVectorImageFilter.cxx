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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 8 avr. 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsLinearSubSampleVectorImageFilter.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbMultiChannelExtractROI.h"
#include "vnsLoggers.h"
#include "itkTimeProbe.h"


int vnsLinearSubSampleVectorImageFilter(int argc, char * argv [])
{
  typedef double PixelType;
  typedef otb::VectorImage<PixelType> ImageType;
  typedef otb::ImageFileReader<ImageType> ReaderType;
  typedef otb::ImageFileWriter<ImageType> WriterType;

  typedef otb::MultiChannelExtractROI<PixelType, PixelType> ExtractorType;
  typedef vns::LinearSubSampleVectorImageFilter<ImageType, ImageType>  FilterType;



  /** instantiating the filter */
  FilterType::Pointer filter = FilterType::New();
  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  ExtractorType::Pointer extract = ExtractorType::New();

  reader->SetFileName(argv[1]);
  writer->SetFileName(argv[2]);

  if(argc > 4)
    {
      extract->SetInput(reader->GetOutput());
      ImageType::RegionType region;
      ImageType::SizeType size;
      ImageType::IndexType id;
      size.Fill(atoi(argv[5]));
      id.Fill(atoi(argv[4]));
      region.SetSize(size);
      region.SetIndex(id);
      extract->SetExtractionRegion(region);
      filter->SetInput(extract->GetOutput());
    }
    else
    {
      filter->SetInput(reader->GetOutput());
    }
 
  filter->SetSubsampleFactor( atoi(argv[3]));
  writer->SetInput(filter->GetOutput());

  itk::TimeProbe clock;
  clock.Start();
  writer->Update();
  clock.Stop();
  std::cout<<"Total entier: "<<clock.GetTotal()<<std::endl;

  return EXIT_SUCCESS;
}
