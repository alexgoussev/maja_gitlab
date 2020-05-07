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
 * MOD : VERSION : 1-0-0  : 27 oct. 2011 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsMultiSpectralAOTMethodFunctions.h"
#include "otbImage.h"

#include "otbVectorImage.h"

int vnsMultiSpectralAOTMethodFunctionsNew(int /*argc*/, char * /*argv*/ [])
{
    const unsigned int Dimension = 2;
    /** Pixel typedefs */
    typedef float ImagePixelType;
    typedef unsigned char MaskPixelType;
    typedef short DatePixelType;

    /** Image typedefs */
    typedef otb::VectorImage<ImagePixelType, Dimension>     InputImageType;
    typedef otb::VectorImage<MaskPixelType, Dimension>      InputVectorMaskType;

    typedef otb::Image<MaskPixelType, Dimension>            InputMaskType;

    typedef vns::MultiSpectralAOTMethodFunctions<InputImageType,InputMaskType,InputVectorMaskType> FilterType;

    /** instantiating the filter */
    FilterType::Pointer filter = FilterType::New();

    return EXIT_SUCCESS;
}
