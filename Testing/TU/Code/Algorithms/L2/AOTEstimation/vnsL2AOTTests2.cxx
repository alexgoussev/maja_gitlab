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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 7 juillet 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
// this file defines the vnsBusinessCommonTest for the test driver
// and all it expects is that you have a function called RegisterTests
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

//
#include "vnsTestMain.h"
#include "vnsConfigure.h"

void
RegisterTests()
{
    REGISTER_TEST(vnsGapFillingImageFilterNew);
    REGISTER_TEST(vnsGapFillingImageFilterTest);
    REGISTER_TEST(vnsRunLevenbergMarquardtOptimizationMSNew);
    REGISTER_TEST(vnsRunLevenbergMarquardtOptimizationMSValid);
    REGISTER_TEST(vnsRunLevenbergMarquardtOptimizationSTNew);
    REGISTER_TEST(vnsRunLevenbergMarquardtOptimizationSTValid);
    REGISTER_TEST(vnsMultiTemporalAOTMethodFunctionsNew);
    REGISTER_TEST(vnsMultiSpectralAOTMethodFunctionsNew);
    REGISTER_TEST(vnsMultiTemporalAOTMethodThresholdsGeneratorTest);
}
