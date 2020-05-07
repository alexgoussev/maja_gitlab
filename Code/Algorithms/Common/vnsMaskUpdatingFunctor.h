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
 * VERSION : 5-1-0 : FA : LAIG-FA-MAC-145739-CS : 27 juin 2016 : Audit code - Supp de la macro ITK_EXPORT   *
 * VERSION : 4-0-0 : DM : LAIG-DM-MAC-517-CNES : 6 janvier 2014 : Améliorations algorithmiques (Spec v2.1)	*
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: vnsMaskUpdatingImageFilter.h 3545 2011-11-29 14:21:48Z cruffel $
 *                                                                                                          *
 ************************************************************************************************************/

#ifndef __vnsMaskUpdatingImageFunctor_h
#define __vnsMaskUpdatingImageFunctor_h

#include "itkBinaryFunctorImageFilter.h"



namespace vns
{
/** \class MaskUpdatingImageFilter
 *
 * \brief Update a mask with another one.
 * Input masks are otb::image.
 *
 *
 */
namespace Functor
{
  template< class TInputPixel, class TRefPixel, class TOutputPixel=TInputPixel>
    class MaskUpdatingImageFunctor
    {
      public:
      
	  MaskUpdatingImageFunctor() : m_ThresholdRefMaskValue(0), m_OutputMaskValue(0) {};
      virtual ~MaskUpdatingImageFunctor() {};
      
      void SetThresholdRefMaskValue(TRefPixel val)
      {
    	  m_ThresholdRefMaskValue = val;
      }
      
      void SetOutputMaskValue(TOutputPixel val)
      {
    	  m_OutputMaskValue = val;
      }

      inline TOutputPixel operator() ( const TInputPixel & inPix, const TRefPixel & refPix ) const
      {
        TOutputPixel outPix(inPix);
    
        if( refPix > m_ThresholdRefMaskValue)
        {
           outPix = m_OutputMaskValue;
        }
        return outPix;
      }

      protected:
      TRefPixel m_ThresholdRefMaskValue;
      TOutputPixel m_OutputMaskValue;

    };
}// namespace Functor

} // end namespace vns


#endif

