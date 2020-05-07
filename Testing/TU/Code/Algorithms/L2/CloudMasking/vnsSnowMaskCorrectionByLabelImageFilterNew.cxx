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
 * VERSION : 4-0-0 : <TypeFT> : <NumFT> : 6 janvier 2014 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: vnsShadowMaskDeterminationImageFilterNew.cxx 4915 2012-11-30 17:34:21Z tfeuvrie $
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsSnowMaskCorrectionByLabelImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"

int vnsSnowMaskCorrectionByLabelImageFilterNew(int /*argc*/, char * /*argv*/ [])
{
    const unsigned int Dimension = 2;
    /** Pixel typedefs */
    typedef unsigned char InputMaskPixelType;
    typedef unsigned short InputLabelPixelType;
    typedef unsigned char OutputMaskPixelType;
    /** Image typedefs */
    typedef otb::Image<InputMaskPixelType,Dimension> InputMaskType;
    typedef otb::Image<InputLabelPixelType,Dimension> InputLabelType;
    typedef otb::Image<InputMaskPixelType,Dimension> OutputMaskType;

    typedef vns::SnowMaskCorrectionByLabelImageFilter<InputMaskType, InputLabelType, OutputMaskType>  FilterType;

    /** instantiating the filter */
    FilterType::Pointer l_Filter = FilterType::New();

    return EXIT_SUCCESS;
}
