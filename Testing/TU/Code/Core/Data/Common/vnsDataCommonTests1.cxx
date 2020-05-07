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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 14 fevrier 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

//
#include "vnsTestMain.h"

void
RegisterTests()
{
    REGISTER_TEST(vnsDateTest);
    REGISTER_TEST(vnsCheckTestMain);
    REGISTER_TEST(vnsLoggerTest);
    REGISTER_TEST(vnsLoggersTest);
    REGISTER_TEST(vnsSystemTest);
    REGISTER_TEST(vnsSystemFilenameTest);
    REGISTER_TEST(vnsSystemCallCommandBasicTest);
    REGISTER_TEST(vnsSystemReadBinaryFile);
    REGISTER_TEST(vnsLookUpTableNew);
    REGISTER_TEST(vnsLookUpTableLUT3);
    REGISTER_TEST(vnsLookUpTableLUTInterpolation);
    REGISTER_TEST(vnsLookUpTableLUTExtraction3_2ParametersNamesAndValues);
    REGISTER_TEST(vnsLookUpTableLUTExtraction3_2);
    REGISTER_TEST(vnsLookUpTableLUTExtraction6_3);
    REGISTER_TEST(vnsExceptionsClassTests);
}
