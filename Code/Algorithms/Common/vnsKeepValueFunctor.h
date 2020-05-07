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
 * VERSION : 2.0.0 : DM : LAIG-DM-MAJA-153436-CS : 13 avril 2017 : Refactoring de classe doublons           *
 * VERSION : 5-0-0 : DM : LAIG-DM-MAC-982-CNES : 5 avr. 2016 : Creation                                       *
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id:
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsKeepValueFunctor_h
#define __vnsKeepValueFunctor_h

#include "itkImageToImageFilter.h"

namespace vns
{
    /** \class  KeepValueFunctor
     * \brief This class sets the input pixel value to default value if the
     *  pixel value is equal to the keeped value.
     *
     * The input and output pixel types are scalar (otb::Image).
     *
     * \author CS Systemes d'Information
     *
     * \ingroup L2
     *
     */
    namespace Functor
    {
        template<class TInputPixel, class TOutputPixel>
            class KeepValueFunctor
            {
            public:
                KeepValueFunctor()
                {
                }

                virtual
                ~KeepValueFunctor()
                {
                }

                typedef TInputPixel InputPixelType;
                typedef TOutputPixel OutputPixelType;

                /** Set the excluded value */
                void
                SetKeepedValue(InputPixelType value)
                {
                    m_KeepedValue = value;
                }

                /** Set the default value */
                void
                SetDefaultValue(OutputPixelType value)
                {
                    m_DefaultValue = value;
                }

                inline OutputPixelType
                operator()(InputPixelType inPix) const
                {
                    // Test if one of the pixel value of the three input mask is equal to 1
                    if (inPix == m_KeepedValue)
                    {
                        // Set output pixel value to default value
                        return static_cast<OutputPixelType>(m_KeepedValue);
                    }
                    return m_DefaultValue;
                }

            protected:
                /** Excluded value declaration */
                InputPixelType m_KeepedValue;
                /** Default value declaration */
                OutputPixelType m_DefaultValue;

            };

    } // End namespace functor

} // End namespace vns

#endif /* __vnsKeepValueFunctor_h */
