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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 21 mai 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/

#include "vnsLoggers.h"
#include "vnsConstantVectorImageSource.h"
#include "otbVectorImage.h"
#include "otbImageFileWriter.h"
#include "vnsUtilities.h"

int vnsConstantVectorImageSource(int argc, char * argv [])
{
    if(argc < 6)
    {
    	std::cerr << argv[0] << "<output filename> <nbline> <nbcolumn> <nbchannel> <values...>" << std::endl;
        return EXIT_FAILURE;
    }
    // Configure Logger
    vns::Loggers::GetInstance()->Initialize(argv[0]);
    vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);

    const unsigned int Dimension = 2;
    const char * outputFileName = argv[1];
    const int nbline(atoi(argv[2]));
    const int nbcol(atoi(argv[3]));
    const int nbchannel(atoi(argv[4]));
    
    /** Pixel typedefs */
    typedef double OutputPixelType;
    /** Image typedefs */
    typedef otb::VectorImage<OutputPixelType,Dimension>   OutputImageType;
    typedef OutputImageType::PixelType PixelType;
    typedef otb::ImageFileWriter<OutputImageType>   WriterType;
    typedef vns::ConstantVectorImageSource<OutputImageType>  FilterType;

    /** instantiating the filter */
    FilterType::Pointer filter = FilterType::New();
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(outputFileName);


    PixelType pixel;


    OutputImageType::SizeValueType randomSize[2];

    randomSize[0] = nbline;
    randomSize[1] = nbcol;
    filter->SetSize(randomSize);

    OutputImageType::SpacingValueType spacing[2] = {1., 1.};
    filter->SetSpacing( spacing );

    OutputImageType::PointValueType origin[2] = {0, 0};
    filter->SetOrigin( origin );


//    pixel.AllocateElements(nbchannel);
    pixel.SetSize(nbchannel);
    for (int i=0 ; i<nbchannel ; i++)
    {
        std::string value(argv[i+5]);
        pixel.SetElement(i,vns::Utilities::AsDouble(value));
    }
    filter->SetConstantValue(pixel);

    writer->SetInput(filter->GetOutput());
    writer->Update();

    return EXIT_SUCCESS;
}
