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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 12 juil. 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/

#include "vnsShadowMaskProjectionImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"

int vnsShadowMaskProjectionImageFilterNew(int /*argc*/, char * /*argv*/ [])
{
    const unsigned int Dimension = 2;
    /** Pixel typedefs */
    typedef unsigned char InputMaskPixelType;
    typedef unsigned long LabelPixelType;
    typedef double DTMPixelType;
    typedef double GRIDPixelType;
    typedef double CLAPixelType;
    typedef unsigned short OutputMaskPixelType;
    /** Image typedefs */
    typedef otb::Image<InputMaskPixelType,Dimension> InputMaskType;
    typedef otb::Image<LabelPixelType,Dimension> LabelImageType;
    typedef otb::Image<DTMPixelType,Dimension> DTMImageType;
    typedef otb::VectorImage<GRIDPixelType,Dimension> GRIDImageType;
    typedef otb::Image<CLAPixelType,Dimension> CLAImageType;
    typedef otb::Image<OutputMaskPixelType,Dimension> OutputImageType;


    typedef vns::ShadowMaskProjectionImageFilter<InputMaskType,
                                             LabelImageType,
                                             DTMImageType,
                                             GRIDImageType,
                                             CLAImageType,
                                             OutputImageType>  FilterType;
    /** instantiating the filter */
    FilterType::Pointer l_Filter = FilterType::New();

    return EXIT_SUCCESS;
}
