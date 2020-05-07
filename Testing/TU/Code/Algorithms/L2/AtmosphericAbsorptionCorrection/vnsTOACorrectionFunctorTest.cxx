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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 23 avr. 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsLoggers.h"

#include "vnsTOACorrectionImageFunctor.h"
#include "vnsSmacCoefContainer.h"
#include "itkVariableLengthVector.h"
#include "vnsUtilities.h"
#include <fstream>
#include <iostream>

int
vnsTOACorrectionFunctorTest(int /*argc*/, char * argv[])
{
    // Configure Logger
    vns::Loggers::GetInstance()->Initialize(argv[0]);
    vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);

    /** Pixel typedefs */
    typedef double PixelType;
    typedef itk::VariableLengthVector<PixelType> VectorPixelType;

    typedef vns::Functor::TOACorrectionImageFunctor<VectorPixelType, PixelType, PixelType, VectorPixelType> FunctorType;
    typedef vns::SmacCoefContainer SmacCoefType;
    typedef std::vector<SmacCoefType> SmacCoefVectorType;
    typedef std::vector<double> VectorType;
    typedef std::vector<VectorType> VectorVectorType;

    const char * filename = argv[1];
    const char * out_filename = argv[2];
    PixelType water = atof(argv[3]);
    PixelType pressure = atof(argv[4]);
    double o3Amount = atof(argv[5]);
    double thetaS = atof(argv[6]);
    double thetaV = atof(argv[7]);

    VectorVectorType vectVect;
    VectorType vect1, vect3, vect2, vect4;

    std::ifstream file(filename);

    std::vector<std::string> splittedLine;
    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {

            //splittedLine = line.explode(separator);
            std::string l_Line = line;
            splittedLine = vns::Utilities::SplitString(l_Line, '\t');
            if (splittedLine.size() < 4)
            {
                file.close();
                std::cout << "Invalid input smac file." << std::endl;
                return EXIT_FAILURE;
            }
            vect1.push_back(vns::Utilities::AsDouble(splittedLine.at(0)));
            vect2.push_back(vns::Utilities::AsDouble(splittedLine.at(1)));
            vect3.push_back(vns::Utilities::AsDouble(splittedLine.at(2)));
            vect4.push_back(vns::Utilities::AsDouble(splittedLine.at(3)));
        }
    }

    else
    {
        file.close();
        std::cout << "Invalid input smac file name " << filename << std::endl;
        return EXIT_FAILURE;
    }

    std::ofstream out_file(out_filename);


    SmacCoefVectorType vectCont;
    SmacCoefType cont1(vect1);
    std::cout << "loool3" << std::endl;
    out_file << "loool3" << std::endl;
    vectCont.push_back(cont1);
    SmacCoefType cont2(vect2);
    vectCont.push_back(cont2);
    SmacCoefType cont3(vect3);
    vectCont.push_back(cont3);
    SmacCoefType cont4(vect4);
    vectCont.push_back(cont4);

    VectorPixelType toaPix;
    toaPix.SetSize(4);
    toaPix.Fill(1.);
    const unsigned int nbBands(toaPix.GetSize());

    FunctorType functor;
    functor.SetSmacCoefsList(vectCont);

    functor.SetOzoneAmount(o3Amount);
    functor.SetThetaS(12.);
    VectorType vThetaV(4, 22.);
    functor.SetThetaV(vThetaV);

    std::cout << "toa   : " << toaPix[1] << std::endl;
    std::cout << "thetaS: " << thetaS << std::endl;
    std::cout << "thetaV: " << thetaV << std::endl;
    std::cout << "press : " << pressure << std::endl;
    std::cout << "o3    : " << o3Amount << std::endl;
    std::cout << "water : " << water << std::endl;
    std::cout << "coef  :" << std::endl;
    functor.GetSmacCoefsList()[0].Print(std::cout);
    out_file << "toa   : " << toaPix[1] << std::endl;
    out_file << "thetaS: " << thetaS << std::endl;
    out_file << "thetaV: " << thetaV << std::endl;
    out_file << "press : " << pressure << std::endl;
    out_file << "o3    : " << o3Amount << std::endl;
    out_file << "water : " << water << std::endl;
    out_file << "coef  :" << std::endl;
    functor.GetSmacCoefsList()[0].Print(out_file);

    VectorPixelType outPix;
    outPix.SetSize(nbBands);
    outPix.Fill(0.);

    functor(toaPix, water, pressure, nbBands, outPix);

    std::cout << outPix << std::endl;
    out_file << outPix << std::endl;

    out_file.close();

    return EXIT_SUCCESS;
}
