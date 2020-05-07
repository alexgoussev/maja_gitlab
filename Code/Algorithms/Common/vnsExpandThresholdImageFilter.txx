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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 11 janv. 2011 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsExpandThresholdImageFilter_txx
#define __vnsExpandThresholdImageFilter_txx

#include "vnsExpandThresholdImageFilter.h"
#include "vnsResamplerHelper.h"

namespace vns
{

// Constructor
    template<class TInputImage, class TOutputImage>
        ExpandThresholdImageFilter<TInputImage, TOutputImage>::ExpandThresholdImageFilter() :
                m_EdgePaddingValue(0.)
        {

            m_Caster = RealCasterImageFilterType::New();
            m_Expander = RealExpandFilterType::New();
            m_Thresholder = BinaryThresholdFilterType::New();

            this->SetUpperThreshold(0.25);
            this->SetInsideValue(0);
            this->SetOutsideValue(1);

            m_Output0 = OutputImageType::New();
        }

// UpdateWithCaching method
    template<class TInputImage, class TOutputImage>
        void
        ExpandThresholdImageFilter<TInputImage, TOutputImage>::UpdateWithCaching()
        {
            // Simply

            m_Caster->SetInput(this->GetInput0());

//    m_Expander->SetInput(m_Caster->GetOutput());
            vnsImagePadAndResamplerMacro("ExpandThresholdImageFilter::Expander", /*RealExpandFilterType,*/m_Expander,
                    m_Caster->GetOutput() /* Input */,ResamplerHelper::RB_INTERPOLATOR_LINEAR /* Interpolator */,
                    m_AreaToOutputImageResolution)
            //, m_EdgePaddingValue /* edgePaddingValue */ )

            m_Thresholder->SetInput(m_Expander->GetOutput());

            m_Output0 = m_Thresholder->GetOutput();

        }

} // End namespace vns

#endif /* __vnsExpandThresholdImageFilter_txx */
