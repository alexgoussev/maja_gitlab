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
 * VERSION : 5-0-0 : FA : LAIG-FA-MAC-143764-CS : 12 avril 2016 : Mise en forme du code (indentation, etc.) *
 * VERSION : 4-0-0 : DM : LAIG-DM-MAC-517-CNES : 6 janvier 2014 : Améliorations algorithmiques (Spec v2.1)	*
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: vnsCloudLabelUpdatingFunctor.h 2406 2011-01-19 15:38:23Z tfeuvrie $
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsCloudLabelUpdatingFunctor_h
#define __vnsCloudLabelUpdatingFunctor_h

#include "itkImageToImageFilter.h"

namespace vns
{
    /** \class  CloudLabelUpdatingFunctor
     * \brief This class updates an input cloud label image with a list that
     * contains the labels that must be kept.
     *
     * \author CS Systemes d'Information
     *
     * \sa ImageToImageFilter
     *
     * \ingroup L2
     *
     */
    namespace Functor
    {
        template<class TLabelPixel>
            class CloudLabelUpdatingFunctor
            {
            public:
                typedef CloudLabelUpdatingFunctor<TLabelPixel> CloudLabelUpdatingFunctorType;

                CloudLabelUpdatingFunctor()
                {
                }

                virtual
                ~CloudLabelUpdatingFunctor()
                {
                }

                typedef TLabelPixel LabelPixelType;

                typedef typename std::list<LabelPixelType> LabelListType;

                /** Get the map */
                LabelListType
                GetLabelList()
                {
                    return m_LabelList;
                }
                /** Set the map */
                void
                SetLabelList(LabelListType list)
                {
                    m_LabelList = list;
                }

                inline LabelPixelType
                operator()(LabelPixelType inPix) const
                {
                    LabelPixelType outPix;

                    // Initialization of the output pixel with 0
                    outPix = static_cast<LabelPixelType>(0);

                    // The background pixels (label = 0) are not processed
                    if (inPix > 0)
                    {
                        // iterator associated to the input label list
                        typename LabelListType::const_iterator it = m_LabelList.begin();

                        while (it != m_LabelList.end())
                        {
                            // If the label exists in the list
                            if (inPix == (*it))
                            {
                                // It must be kept in the output cloud label image
                                outPix = static_cast<LabelPixelType>(inPix);
                            }
                            ++it;
                        }
                    }

                    return outPix;
                }

            protected:
                /** Altitude correction map */
                LabelListType m_LabelList;

            };

    } // End namespace functor

} // End namespace vns

#endif /* __vnsCloudLabelUpdatingFunctor_h */
