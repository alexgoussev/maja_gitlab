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
#include "vnsLinearSubSampleImageFilter.h"
#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbExtractROI.h"
#include "vnsLoggers.h"
#include "itkTimeProbe.h"

int
vnsLinearSubSampleImageFilter(int argc, char * argv[])
{
    int cpt = 1;
    typedef double PixelType;
    typedef otb::Image<PixelType> ImageType;
    typedef otb::ImageFileReader<ImageType> ReaderType;
    typedef otb::ImageFileWriter<ImageType> WriterType;

    typedef otb::ExtractROI<PixelType, PixelType> ExtractorType;

    typedef vns::LinearSubSampleImageFilter<ImageType, ImageType> FilterType;

    /** instantiating the filter */
    FilterType::Pointer filter = FilterType::New();
    ReaderType::Pointer reader = ReaderType::New();
    WriterType::Pointer writer = WriterType::New();
    ExtractorType::Pointer extract = ExtractorType::New();

    reader->SetFileName(argv[cpt++]);
    writer->SetFileName(argv[cpt++]);

    extract->SetInput(reader->GetOutput());

    unsigned int factor = atoi(argv[cpt++]);

    filter->SetSubsampleFactor(factor);
    filter->SetNumberOfThreads(cpt++);

    std::cout << " Factor                                                                           : " << factor << std::endl;
    std::cout << " NbThreads                                                                        : " << itk::MultiThreader::GetGlobalDefaultNumberOfThreads() << std::endl;

    if (argc > 5)
    {
        ImageType::RegionType region;
        ImageType::SizeType size;
        ImageType::IndexType id;
        id.Fill(atoi(argv[cpt++]));
        size.Fill(atoi(argv[cpt++]));
        region.SetSize(size);
        region.SetIndex(id);
        extract->SetExtractionRegion(region);
    }

    filter->SetInput(extract->GetOutput());
    writer->SetInput(filter->GetOutput());

    itk::TimeProbe clock;
    clock.Start();
    writer->Update();
    clock.Stop();
    std::cout<<"Total entier: "<<clock.GetTotal()<<std::endl;

    return EXIT_SUCCESS;
}
