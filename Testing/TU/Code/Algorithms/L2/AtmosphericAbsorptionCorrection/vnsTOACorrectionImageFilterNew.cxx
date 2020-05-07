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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 26 mai 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/

#include "itkMacro.h"

#include "vnsTOACorrectionImageFilter.h"
#include "otbVectorImage.h"
#include "otbImage.h"


int vnsTOACorrectionImageFilterNew(int /*argc*/, char * /*argv*/[])
{
  typedef double                      PixelType;
  typedef otb::VectorImage<PixelType> VectorInpuImageType;
  typedef otb::Image<PixelType>       ImageType;
 
  typedef vns::TOACorrectionImageFilter<VectorInpuImageType,ImageType,VectorInpuImageType,ImageType>  TOACorrectionImageFilterType;

  // Instantiating object
  TOACorrectionImageFilterType::Pointer object = TOACorrectionImageFilterType::New();

 typedef vns::TOACorrectionImageFilter<VectorInpuImageType,ImageType,VectorInpuImageType>  TOACorrectionImageDefaultFilterType;

  // Instantiating object
  TOACorrectionImageDefaultFilterType::Pointer objectDef = TOACorrectionImageDefaultFilterType::New();

  return EXIT_SUCCESS;
}
