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
#ifndef __vnsVectorLookUpTableExtractor_h
#define __vnsVectorLookUpTableExtractor_h

#include "itkObject.h"
#include "itkPoint.h"

namespace vns
{
    /** \class  VectorLookUpTableExtractor
     * \brief This class implements the extraction of sub-LUTs (also called reduced LUTs).
     *
     *  This class is used to extract sub-LUTs from a full VectorLUT, by semi-interpolating on
     *  the extract point values. This extract point is a "semi-point" for the full VectorLUT, i.e.
     *  the values are not filled for all dimensions.
     *  For extracting the sub-LUT, the LookUpTableExtractor uses the full VectorLUT interpolator
     *  (Linear by default).
     *
     * \sa VectorLookUpTable
     * \sa VLookUpTableExtractor
     *
     * \ingroup L2
     * \ingroup L3
     * \ingroup Checktool
     *
     */
    template<class TFullLUT, class TReducedLUT>
        class VectorLookUpTableExtractor
        {
        public:
            /** Standard class typedefs. */
            typedef VectorLookUpTableExtractor Self;

            typedef itk::Point<typename TFullLUT::InternalPixelType,
                    TFullLUT::LUTDimension - TReducedLUT::LUTDimension>
                    ExtractPointType;
	    
	    typedef std::vector<ExtractPointType> VectorExtractPointType;

	    typedef typename TFullLUT::PointType PointType;

	    typedef typename std::vector<PointType> VectorPointType;

        static typename TReducedLUT::Pointer
        ExtractLUT(typename TFullLUT::Pointer FullLUT,const VectorExtractPointType & ReducedPointList);

    protected:

        private:

        };

} // End namespace vns

#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsVectorLookUpTableExtractor.txx"
#endif

#endif /* __vnsVectorLookUpTableExtractor_h */
