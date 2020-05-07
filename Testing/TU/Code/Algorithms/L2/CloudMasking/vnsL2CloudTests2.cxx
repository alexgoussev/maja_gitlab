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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 22 juin 2010 : Creation
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

void
RegisterTests()
{
    REGISTER_TEST(vnsSolarDirectionForCloudAltitudeFunctorTest);
    REGISTER_TEST(vnsValidShadowMaskImageFilterNew);
    REGISTER_TEST(vnsValidShadowMaskImageFilterTest);
    REGISTER_TEST(vnsAltitudeCorrectionFunctorTest);
    REGISTER_TEST(vnsCloudAlreadyDetectedImageFilterNew);
    REGISTER_TEST(vnsCloudAlreadyDetectedImageFilterTest);
    REGISTER_TEST(vnsValidateMaskFromLabelMapAndValidityMapImageFilterTest);
    REGISTER_TEST(vnsCloudGeomMasksToKeptLabelMasksFilterTest);
    REGISTER_TEST(vnsCloudGeomMasksToKeptLabelMasksFilterGeneratedInputs);
    REGISTER_TEST(vnsFlattenCloudMaskImageListFilterGenerateInputs);
    REGISTER_TEST(vnsFlattenCloudMaskImageListFilter);
}
