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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 18 nov. 2011 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/

#include "vnsLoggers.h"
#include "vnsEqualValueThresholdFunctor.h"
#include "otbImageFileReader.h"

#include "otbImage.h"
#include "otbImageFileWriter.h"

#include "itkUnaryFunctorImageFilter.h"

int
vnsEqualThresholdFunctorTest(int argc, char * argv[])
{
    if (argc != 6)
    {
        std::cerr << argv[0] << " <input filename> <output filename> <ThresholdValue> <EqualValue> <OutsideValue>" << std::endl;
        return EXIT_FAILURE;
    }
    // Configure Logger
    vns::Loggers::GetInstance()->Initialize(argv[0]);
    vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);

    const unsigned int Dimension = 2;
    const char * inputFileName = argv[1];
    const char * outputFileName = argv[2];

    /** Pixel typedefs */
    typedef double PixelType;

    /** Image typedefs */
    typedef otb::Image<PixelType, Dimension> InputImageType;
    typedef otb::Image<PixelType, Dimension> OutputImageType;
    typedef otb::ImageFileReader<InputImageType> ReaderType;
    typedef otb::ImageFileWriter<OutputImageType> WriterType;

    typedef vns::Functor::EqualValueThresholdFunctor<InputImageType::PixelType, OutputImageType::PixelType> FunctorType;

    typedef itk::UnaryFunctorImageFilter<InputImageType, OutputImageType, FunctorType> ImageFilterType;

    /** Parameters definition */
    PixelType lThresholdValue = static_cast<double>(atof(argv[3]));
    PixelType lEqualValue = static_cast<double>(atof(argv[4]));
    PixelType lOutsideValue = static_cast<double>(atof(argv[5]));

    std::cout << "---> List of parameters : " << std::endl;
    std::cout << "InputImage=" << inputFileName << std::endl;
    std::cout << "OutputImage=" << outputFileName << std::endl;
    std::cout << "ThresholdValue=" << lThresholdValue << std::endl;
    std::cout << "EqualValue=" << lEqualValue << std::endl;
    std::cout << "OutsideValue=" << lOutsideValue << std::endl;

    /** instantiating the filter */
    ImageFilterType::Pointer filter = ImageFilterType::New();
    ReaderType::Pointer reader = ReaderType::New();
    WriterType::Pointer writer = WriterType::New();
    reader->SetFileName(inputFileName);
    writer->SetFileName(outputFileName);

    filter->GetFunctor().SetThresholdValue(lThresholdValue);
    filter->GetFunctor().SetEqualValue(lEqualValue);
    filter->GetFunctor().SetOutsideValue(lOutsideValue);

    filter->SetInput(reader->GetOutput());
    writer->SetInput(filter->GetOutput());

    writer->Update();

    return EXIT_SUCCESS;
}
