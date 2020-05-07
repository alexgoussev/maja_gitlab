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
 * VERSION : 5-1-0 : FA : LAIG-FA-MAC-145739-CS : 13 juillet 2016 : Audit code - initialisation membre      *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 23 avr. 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsRoundVectorImageFunctor_h
#define __vnsRoundVectorImageFunctor_h

#include "itkMath.h"

namespace vns
{
     namespace Functor
     {
         template< typename TInput, typename TOutput >
         class RoundVectorImage
         {
             public:
             RoundVectorImage() = default;
             ~RoundVectorImage() = default;

             bool operator!=(const RoundVectorImage &) const
             {
                return false;
             }

             bool operator==(const RoundVectorImage & other) const
             {
                 return !( *this != other );
             }

             inline TOutput
             operator()(const TInput & A) const
             {
                const unsigned int lSize = A.Size();
                TOutput out(lSize);
                for (unsigned int bd = 0; bd < lSize; bd++)
                {
                out[bd] = itk::Math::Round<typename TOutput::ValueType,typename TInput::ValueType>(A[bd]);
                }
                return out ;
             }
            // unsigned int m_OutputSize;
         };
     }

} // end namespace vns

#endif
