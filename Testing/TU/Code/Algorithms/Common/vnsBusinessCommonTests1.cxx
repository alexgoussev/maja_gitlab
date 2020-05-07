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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 28 janvier 2010 : Creation
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

void RegisterTests()
{
  REGISTER_TEST(vnsProcessingModeTest);
  REGISTER_TEST(vnsConfigCommonParametersNew);
  REGISTER_TEST(vnsStreamingConditionalStatisticsVectorImageFilterNew);
  REGISTER_TEST(vnsStreamingConditionalStatisticsVectorImageFilterTest);
  REGISTER_TEST(vnsStreamingConditionalStatisticsImageFilterTest);
  REGISTER_TEST(vnsStreamingMaskConditionalStatisticsVectorImageFilterNew);
  REGISTER_TEST(vnsStreamingMaskConditionalStatisticsVectorImageFilterTest);
  REGISTER_TEST(vnsStreamingMaskConditionalStatisticsVectorImageFilterPipelineTest);
  REGISTER_TEST(vnsRegionForSubsampleNew);
  REGISTER_TEST(vnsBinaryConcatenationVectorImageFilterNew);
  REGISTER_TEST(vnsBinaryConcatenationVectorImageFilterTest);
  REGISTER_TEST(vnsBinaryConcatenationVectorImageFilterFailed);
  REGISTER_TEST(vnsBinaryConcatenationVectorImageFilterTestType);
  REGISTER_TEST(vnsBinaryToVectorImageFilterNew);
  REGISTER_TEST(vnsBinaryToVectorImageFilterTest);
  REGISTER_TEST(vnsConstantImageSourceNew);
  REGISTER_TEST(vnsConstantImageSource);
  REGISTER_TEST(vnsConstantVectorImageSourceNew);
  REGISTER_TEST(vnsConstantVectorImageSource);
  REGISTER_TEST(vnsPadAndResamplerReSamplingTest);
  REGISTER_TEST(vnsLinearInterpolateImageFunctionNew);
  REGISTER_TEST(vnsLinearInterpolateImageFunctionTest);
  REGISTER_TEST(vnsChangeValueVectorImageFilterNew);
  REGISTER_TEST(vnsChangeValueVectorImageFilterTest);
  REGISTER_TEST(vnsChangeValueWithMaskVectorFunctorTest);
  REGISTER_TEST(vnsImageListToImageListApplyMaskWithFunctorFilterTest);
  REGISTER_TEST(vnsApplyMaskFunctorNew);
  REGISTER_TEST(vnsChangeValueFunctorTest);
}
