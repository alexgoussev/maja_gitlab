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

#include "vnsMacro.h"
#include "vnsOzoneValueExtractor.h"
#include "vnsGRIBImageIOFactory.h"
#include "itkObjectFactoryBase.h"

int
vnsOzoneValueExtractorTest(int argc, char * argv[])
{
    if (argc != 5)
    {
        std::cout << "Usage error bad parameters !!" << std::endl;
        return EXIT_FAILURE;
    }
    const char * filename = argv[1];

    itk::ObjectFactoryBase::RegisterFactory( vns::GRIBImageIOFactory::New() );

    vns::Loggers::GetInstance()->Initialize(argv[0]);
    vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);

    typedef vns::OzoneValueExtractor OzonerType;
    typedef OzonerType::PointType PointType;

    PointType point;
    point[1] = atof(argv[2]); // Lat
    point[0] = atof(argv[3]); // Long
    const double res = atof(argv[4]);

    const double oz = OzonerType::GetOzoneValue(filename, point);

    if ( vcl_abs(oz - res) > 1e-6 )
    {
        std::cout<<"Point : (lat: "<<point[0]<<"° , long: "<<point[1]<<"°) should have an Ozone value of "<<res<<" but the found value is "<<oz<<"."<<std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
