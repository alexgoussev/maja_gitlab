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
 * VERSION : 2.1.0 : DM : LAIG-DM-MAJA-157814-CS : 17 mai 2017 : Refactoring plus de unary                   *
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsOneBandEqualThresholdFunctor_h
#define __vnsOneBandEqualThresholdFunctor_h
#include "vnsMacro.h"
#include "vnsMath.h"

namespace vns
{
    /** \class  ThresholdImageFunctor
     * \brief This class generates a mask thresholding the input image.
     *
     * It tests if the value of the input pixel is equal to a threshold value.
     * If it is true, this functor sets the value of the output pixel to m_EqualValue,
     * else it sets the value of the output pixel to m_OutsideValue.
     *
     * \author CS Systemes d'Information
     *
     * \ingroup L2
     *
     */
    namespace Functor
    {
        template<class TInputPixel, class TOutputPixel>
            class OneBandEqualThresholdFunctor
            {
            public:
                typedef OneBandEqualThresholdFunctor<TInputPixel, TOutputPixel> OneBandEqualThresholdFunctorType;

                OneBandEqualThresholdFunctor(void)
                {
                    m_ThresholdValue = 0;
                    m_EqualValue = 0;
                    m_OutsideValue = 1;
                    m_OutputSize = 1;
                }

                ~OneBandEqualThresholdFunctor(void)
                {
                }

                typedef TInputPixel InputPixelType;
                typedef TOutputPixel OutputPixelType;
                typedef typename InputPixelType::ValueType InputInternalPixelType;

                /** Get the threshold value */
                InputInternalPixelType
                GetThresholdValue(void)
                {
                    return static_cast<InputInternalPixelType>(m_ThresholdValue);
                }
                /** Set the threshold value */
                void
                SetThresholdValue(const InputInternalPixelType &val)
                {
                    m_ThresholdValue = static_cast<double>(val);
                }

                /** Get the equal value set to the output mask*/
                OutputPixelType
                GetEqualValue(void)
                {
                    return m_EqualValue;
                }
                /** Set the equal value set to the output mask */
                void
                SetEqualValue(OutputPixelType val)
                {
                    m_EqualValue = val;
                }

                /** Get the outside value set to the output mask*/
                OutputPixelType
                GetOutsideValue()
                {
                    return m_OutsideValue;
                }
                /** Set the Outside value set to the output mask */
                void
                SetOutsideValue(OutputPixelType val)
                {
                    m_OutsideValue = val;
                }

                /** Get the output size of the output mask */
                unsigned int
                GetOutputSize(void)
                {
                    return m_OutputSize;
                }

                inline OutputPixelType
                operator()(InputPixelType inPix) const
                {
                    const unsigned int l_size = inPix.Size();
                    // Band Loop
                    for (unsigned int bd = 0; bd < l_size; bd++)
                    {
                        if (vnsEqualsDoubleMacro( m_ThresholdValue,static_cast<double>(inPix[bd]) ))
                        {
                            return m_EqualValue;
                        }
                    }
                    return m_OutsideValue;
                }

            protected:
                /** Threshold value declaration */
                double m_ThresholdValue;
                /** Mask equal value declaration */
                OutputPixelType m_EqualValue;
                /** Mask output value declaration */
                OutputPixelType m_OutsideValue;
                /** Output image dimension declaration 
                 * Fixed at one. No set accessor. Keep this Get to be able to call it with an
                 * otbFunctorImageFilter and thus generate a VectorImage with only  band.
                 */
                unsigned int m_OutputSize;

            };

    } // end namespace functor

} // End namespace vns


#endif /* __vnsOneBandEqualThresholdFunctor_h */
