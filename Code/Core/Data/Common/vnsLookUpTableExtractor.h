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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 24 mars 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsLookUpTableExtractor_h
#define __vnsLookUpTableExtractor_h

#include "itkObject.h"
#include "itkPoint.h"

namespace vns
{
    /** \class  LookUpTableExtractor
     * \brief This class implements the extraction of sub-LUTs (also called reduced LUTs).
     *
     *  This class is used to extract sub-LUTs from a full LUT, by semi-interpolating on
     *  the extract point values. This extract point is a "semi-point" for the full LUT, i.e.
     *  the values are not filled for all dimensions.
     *  For extracting the sub-LUT, the LookUpTableExtractor uses the full LUT interpolator
     *  (Linear by default).
     *
     * \sa LookUpTable
     *
     * \ingroup L2
     * \ingroup L3
     * \ingroup Checktool
     *
     */
    template<class TFullLUT, class TReducedLUT>
        class LookUpTableExtractor
        {
        public:
            /** Standard class typedefs. */
            typedef LookUpTableExtractor Self;

            typedef itk::Point<typename TFullLUT::InternalPixelType,
                    TFullLUT::LUTDimension - TReducedLUT::LUTDimension>
                    ExtractPointType;

            static typename TReducedLUT::Pointer
            ExtractLUT(typename TFullLUT::Pointer FullLUT,const ExtractPointType & ReducedPoint);

        protected:

        private:

        };

} // End namespace vns

#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsLookUpTableExtractor.txx"
#endif

#endif /* __vnsLookUpTableExtractor_h */
