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
 * VERSION : 2.0.0 : DM : LAIG-DM-MAJA-153436-CS : 17 mars 2017 : Creation pou ameliorer la qualite         *
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsNormalizeAndThresholdFunctor_h
#define __vnsNormalizeAndThresholdFunctor_h

#include "vnsMath.h"

namespace vns
{
    /** \class  NormalizeAndThresholdFunctor
     * \brief This class set the output to 1 if the image is over the normalization factor,
     * else set the output to in/normalizationFactor
     *
     * \author CS Systemes d'Information
     *
     * \ingroup L2
     *
     */
    namespace Functor
    {
        template<class TInputPixel, class TOutputPixel>
            class NormalizeAndThresholdFunctor
            {
            public:
                typedef NormalizeAndThresholdFunctor<TInputPixel, TOutputPixel>
                        NormalizeAndThresholdFunctorType;

                NormalizeAndThresholdFunctor() : m_NormalizeFactor(1)
                {
                }

                virtual ~NormalizeAndThresholdFunctor()
                {
                }

                /** Get the normalize factor*/
                double
                GetNormalizeFactor(void)
                {
                    return m_NormalizeFactor;
                }
                /** Set the output size of the output mask */
                void
                SetNormalizeFactor(const double &val)
                {
                    m_NormalizeFactor = val;
                }

                typedef TInputPixel InputPixelType;
                typedef TOutputPixel OutputPixelType;

                inline OutputPixelType
                operator()(const InputPixelType& inPix) const
                {
                    OutputPixelType outPix;
                    if (vnsStrictlySupDoubleMacro(static_cast<double>(inPix), m_NormalizeFactor, CONST_EPSILON))
                    {
                        outPix = static_cast<double>(1.0);
                    } else
                    {
                        outPix = static_cast<OutputPixelType>(static_cast<double>(inPix)/m_NormalizeFactor);
                    }

                    return outPix;
                }

            protected:

                double m_NormalizeFactor;

            };

    } // end namespace functor

} // End namespace vns

#endif /* __vnsMultiplyByVectorFunctor_h */
