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
 * HISTORIQUE                                                                                               *
 *                                                                                                          *
 * MOD : VERSION : 1-0-0  : 19 oct. 2011 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsSnowMaskDeterminationImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"

int
vnsSnowMaskDeterminationImageFilterNew(int /*argc*/, char * /*argv*/[])
{
    const unsigned int Dimension = 2;
    typedef double InputPixelType;
    typedef unsigned char MaskPixelType;

    typedef otb::VectorImage<InputPixelType, Dimension> InputImageType;
    typedef otb::Image<double, 2>                       InternalIncidenceAngleImageType;
    typedef otb::Image<MaskPixelType, Dimension> MaskType;
    typedef vns::SnowMaskDeterminationImageFilter<InputImageType, InternalIncidenceAngleImageType, MaskType, MaskType> FilterType;
    /** instantiating the filter */
    FilterType::Pointer filter = FilterType::New();
    return EXIT_SUCCESS;
}
