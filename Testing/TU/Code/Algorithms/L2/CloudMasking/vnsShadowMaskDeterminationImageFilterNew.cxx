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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 18 juin 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsShadowMaskDeterminationImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"

int vnsShadowMaskDeterminationImageFilterNew(int /*argc*/, char * /*argv*/ [])
{
    const unsigned int Dimension = 2;
    /** Pixel typedefs */
    typedef double InputPixelType;
    typedef unsigned char InputMaskPixelType;
    typedef unsigned short LabelPixelType;
    typedef double GRIDPixelType;
    typedef double CLAPixelType;
    typedef double DTMPixelType;
    typedef unsigned char OutputImagePixelType;
    /** Image typedefs */
    typedef otb::VectorImage<InputPixelType,Dimension> InputImageType;
    typedef otb::Image<InputMaskPixelType,Dimension> InputMaskType;
    typedef otb::Image<LabelPixelType,Dimension> LabelImageType;
    typedef otb::VectorImage<GRIDPixelType,Dimension> GRIDImageType;
    typedef otb::Image<CLAPixelType,Dimension> CLAImageType;
    typedef otb::Image<DTMPixelType,Dimension> DTMImageType;
    typedef otb::Image<OutputImagePixelType,Dimension> OutputImageType;

    typedef vns::ShadowMaskDeterminationImageFilter<InputImageType,
                                         InputMaskType,
                                         LabelImageType,
                                         GRIDImageType,
                                         CLAImageType,
                                         DTMImageType,
                                         OutputImageType>  FilterType;

    /** instantiating the filter */
    FilterType::Pointer l_Filter = FilterType::New();

    return EXIT_SUCCESS;
}
