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
 * VERSION : 4-0-0 : FA : LAIG-FA-MAC-120653-CS : 3 avril 2014 : Correction de règles de qualité			*
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 24 mars 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsVectorLookUpTableExtractor_txx
#define __vnsVectorLookUpTableExtractor_txx

#include "vnsVectorLookUpTableExtractor.h"

namespace vns
{

    template<class TFullLUT, class TReducedLUT>
        typename TReducedLUT::Pointer
        VectorLookUpTableExtractor<TFullLUT, TReducedLUT>::ExtractLUT(typename TFullLUT::Pointer FullLUT,
                const VectorExtractPointType & ReducedPointList)
        {
    		// Number of dimension of the input LUT
            unsigned int NbBand = FullLUT->GetNumberOfComponentsPerPixel();
            if (ReducedPointList.size() != NbBand)
            {
                vnsStaticExceptionDataMacro("Invalid reducePointList, its size ("<<ReducedPointList.size()<<") has to be the number of band of the FullLUT ("<<NbBand<<" !");
            }

            typename TReducedLUT::Pointer ret = TReducedLUT::New();

            // Dimension of the init LUT
            const unsigned int FullDimension = TFullLUT::LUTDimension;
            // Dimension of the "miniLUT" in which several dimensions were lost by setting
                        // fixed values for those parameters
            const unsigned int ReducedDimension = TReducedLUT::LUTDimension;
            const unsigned int DimensionLost = FullDimension - ReducedDimension;

            // Set kept parameters values */
            typename TFullLUT::ParametersValuesType ParametersValues = FullLUT->GetParametersValues();

            typename TReducedLUT::SizeType size;
            typename TReducedLUT::IndexType orig;
            unsigned int count = 0;

            // ----------------------------------------------------------------
			// For each kept dimension
			// ----------------------------------------------------------------
            for (unsigned int idim = DimensionLost; idim < FullDimension; idim++)
            {
                // Copy dimension size and origin
                size[count] = FullLUT->GetLargestPossibleRegion().GetSize()[idim];
                orig[count] = FullLUT->GetLargestPossibleRegion().GetIndex()[idim];
                count++;

                // Load the name of the parameter
                typename TFullLUT::ParameterValuesType values = ParametersValues[idim];

                typename TReducedLUT::ParameterValuesType convertedValues;
                convertedValues.ParameterName = values.ParameterName;

                // Load the associated indices for each parameter (dimension) of the LUT
                unsigned int NbValues = values.ParameterValues.size();
                for (unsigned int j = 0; j < NbValues; j++)
                {

                    convertedValues.ParameterValues.push_back(values.ParameterValues[j]);
                }

                ret->AddParameterValues(convertedValues);
            }

            // ----------------------------------------------------------------
            // Allocate output image
            // ----------------------------------------------------------------
            typename TReducedLUT::RegionType region;
            region.SetSize(size);
            region.SetIndex(orig);

            ret->SetNumberOfComponentsPerPixel(NbBand);
            ret->SetRegions(region);
            ret->Allocate();

            // Copy kept part of the buffer */
            VectorPointType interpPointList;

            // For each band
            for (unsigned int l = 0; l < NbBand; l++)
            {
                PointType interpPoint;
                // Convert physical values into float index,
                // as we do it only once... We save time after ! (instead of interpolating each point on physical values) */
                for (unsigned int i = 0; i < ExtractPointType::PointDimension; i++)
                {
                    interpPoint[i] = FullLUT->FindIndexInParameterValues(i, ReducedPointList.at(l)[i]);
                }
                interpPointList.push_back(interpPoint);
            }

            // Run over all the sub-LUT
            typename TReducedLUT::IteratorType iterator(ret, ret->GetLargestPossibleRegion());

            iterator.GoToBegin();
            while (iterator.IsAtEnd() == false)
            {
                // Get coordinates
                typename TReducedLUT::IndexType index = iterator.GetIndex();
                typename TReducedLUT::PixelType retPix;
                retPix.SetSize(NbBand);

                // For each band
                for (unsigned int l = 0; l < NbBand; l++)
                {
                    // Complete interpolation point in Full LUT
                    for (unsigned int i = DimensionLost; i < FullDimension; i++)
                    {
                        interpPointList.at(l)[i] = index[i - DimensionLost];
                    }

                    // Interpolate in full LUT and set value in reduced one
                    retPix[l] = FullLUT->InterpolateIndex(interpPointList.at(l))[l];
                }
                iterator.Set(retPix);
                ++iterator;
            }

            return ret;
        }

} // End namespace vns

#endif // __vnsVectorLookUpTableExtractor_txx
