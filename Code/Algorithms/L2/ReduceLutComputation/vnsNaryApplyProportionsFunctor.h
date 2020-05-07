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
 * VERSION : 3.0.0 : DM : LAIG-DM-MAJA-2369-CNES : 28 aout 2017 : Introduction données des CAMS             *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 28 aout 2017 : Creation                                           *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsNaryApplyProportionsFunctor_h
#define __vnsNaryApplyProportionsFunctor_h
#include "vnsMath.h"
#include <vector>

namespace vns
{
    /** \class  NaryApplyProportionsFunctor
     * \brief This class computes the environment correction.
     *
     * For each pixel at L2_resolution. Input and output pixels are
     * variableLengthVector.
     *
     * \author CS Systemes d'Information
     *
     * \ingroup L2
     *
     */
    namespace Functor
    {
        template<class TInputPixel, class TOutputPixel>
        class NaryApplyProportionsFunctor
        {
        public:
            typedef NaryApplyProportionsFunctor<TInputPixel, TOutputPixel> NaryApplyProportionsFunctorType;



            NaryApplyProportionsFunctor(void)
            {
            }

            virtual
            ~NaryApplyProportionsFunctor(void)
            {
            }

            void
            SetFactors(const std::vector<double>& p_facts)
            {
                m_Factors = p_facts;
            }

            typedef TInputPixel PixelType;
            typedef TOutputPixel OutputPixelType;
            typedef typename OutputPixelType::ValueType InternalPixelType;

            inline OutputPixelType
            operator()(const std::vector<PixelType> & pVect)
            {
                const unsigned int lNbOfBands = pVect.front().Size();
                OutputPixelType outPix;
                // Init the output value
                outPix.SetSize(lNbOfBands);
                outPix.Fill(itk::NumericTraits<InternalPixelType>::Zero);
                //Input loop
                for (unsigned int idx = 0; idx < pVect.size();++idx)
                {
                    // Band Loop
                    for (unsigned int bd = 0; bd < lNbOfBands; bd++)
                    {
                        outPix[bd] += pVect[idx][bd] * m_Factors[idx];
                    }
                }
                return outPix;
            }

        private:
            std::vector<double> m_Factors;
        };

    } // end namespace functor

} // End namespace vns

#endif /* __vnsNaryEnvironmentCorrectionImageFilter_h */
