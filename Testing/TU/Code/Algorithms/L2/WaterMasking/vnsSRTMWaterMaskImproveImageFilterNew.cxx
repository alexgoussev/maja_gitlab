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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 22 juil. 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsSRTMWaterMaskImproveImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"
#include "vnsLoggers.h"

int vnsSRTMWaterMaskImproveImageFilterNew(int /*argc*/, char * /*argv*/ [])
{
    const unsigned int Dimension = 2;
    /** Pixel typedefs */
    typedef unsigned char InputPixelType;
    typedef unsigned char SRTMPixelType;
    typedef unsigned char OutputPixelType;
    /** Image typedefs */
    typedef otb::Image<InputPixelType,Dimension> InputMaskType;
    typedef otb::VectorImage<InputPixelType,Dimension> VectorMaskType;
    typedef otb::Image<SRTMPixelType,Dimension> SRTMMaskType;
    typedef otb::Image<OutputPixelType,Dimension> OutputImageType;

    typedef vns::SRTMWaterMaskImproveImageFilter<InputMaskType,
                                                 VectorMaskType,
                                                 SRTMMaskType,
                                                 OutputImageType>  FilterType;

    /** instantiating the filter */
    FilterType::Pointer l_Filter = FilterType::New();

    return EXIT_SUCCESS;
}
