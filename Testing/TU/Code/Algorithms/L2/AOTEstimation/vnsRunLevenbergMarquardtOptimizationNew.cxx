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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 25 juin 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsRunLevenbergMarquardtOptimization.h"
#include "vnsLoggers.h"
#include "otbImage.h"
#include "otbVectorImage.h"
#include "vnsVectorLookUpTable.h"
#include "vnsMultiTemporalAOTCostFunction.h"

int vnsRunLevenbergMarquardtOptimizationNew(int argc, char * argv [])
{

    if (argc != 1)
    {
        return EXIT_FAILURE;
    }

    // Configure Logger
    vns::Loggers::GetInstance()->Initialize(argv[0]);
    vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);


    /** Image typedefs */
    typedef otb::VectorImage<double,2>                  InputImageType;
    typedef otb::Image<float,2>                         DTMType;
    typedef vns::VectorLookUpTable<double,3>            LUTType;
    typedef otb::Image<double,2>                        OutputImageType;
    typedef vns::MultiTemporalAOTCostFunction<InputImageType, DTMType, LUTType>  AOTCostFunctionType;

    typedef vns::RunLevenbergMarquardtOptimization<InputImageType,DTMType,LUTType,OutputImageType, AOTCostFunctionType> FilterType;

    /** Instantiating the filter */
    FilterType::Pointer filter = FilterType::New();
    return EXIT_SUCCESS;
}
