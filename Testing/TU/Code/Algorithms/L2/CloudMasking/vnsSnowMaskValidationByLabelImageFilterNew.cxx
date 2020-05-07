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
 * $Id: vnsSnowMaskValidationByLabelImageFilterNew.cxx 3279 2011-10-04 14:44:32Z cruffel $
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsSnowMaskValidationByLabelImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"

int vnsSnowMaskValidationByLabelImageFilterNew(int /*argc*/, char * /*argv*/ [])
{

	const unsigned int Dimension = 2;
	/** Pixel typedefs */
    typedef unsigned int MaskPixelType;
    /** Image typedefs */
    typedef otb::Image<MaskPixelType,Dimension> MaskImageType;

    typedef vns::SnowMaskValidationByLabelImageFilter<MaskImageType>  FilterType;

    /** instantiating the filter */
    FilterType::Pointer filter = FilterType::New();

    return EXIT_SUCCESS;
}
