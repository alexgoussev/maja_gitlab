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
 * VERSION : 2.1.0 : DM : LAIG-DM-MAJA-157814-CS : 18 mai 2017 : Refactoring, menage pour ameliorer qualite *
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsBinaryLogicalOrFunctor_h
#define __vnsBinaryLogicalOrFunctor_h

#include "itkImageToImageFilter.h"

namespace vns
{
    /** \class  BinaryLogicalOrFunctor
     * \brief This class applies the logical OR between two images of mask type.
     *
     * If the pixel value of one of two input images is equal to one,
     * the output pixel value is set to one.
     *
     * The input images are otb::Image.
     *
     * \author CS Systemes d'Information
     *
     * \ingroup L2
     *
     */
    namespace Functor
    {
        template<class TInputPixel1, class TInputPixel2, class TOutputPixel>
            class BinaryLogicalOrFunctor
            {
            public:
                typedef BinaryLogicalOrFunctor<TInputPixel1,
                                                TInputPixel2,
                                                TOutputPixel> BinaryLogicalOrFunctorType;

                BinaryLogicalOrFunctor(): m_PixelOne(1), m_PixelZero(0)
                {
                }

                virtual ~BinaryLogicalOrFunctor()
                {
                }

                typedef TInputPixel1 InputPixelType1;
                typedef TInputPixel2 InputPixelType2;
                typedef TOutputPixel OutputPixelType;

                inline OutputPixelType
                operator()(InputPixelType1 inPix1, InputPixelType2 inPix2) const
                {
                    // Test if one of the pixel value of the two input mask is equal to 1
                    if ( (inPix1 != static_cast<InputPixelType1>(0)) ||
                         (inPix2 != static_cast<InputPixelType2>(0)) )
                    {
                        // Set output pixel value to 1
                        return m_PixelOne;

                    }
                    return m_PixelZero;
                }
            private:
                OutputPixelType m_PixelOne;
                OutputPixelType m_PixelZero;

            };
    } // End namespace functor

} // End namespace vns


#endif /* __vnsBinaryLogicalOrFunctor_h */
