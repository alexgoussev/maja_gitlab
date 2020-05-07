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
 * VERSION : 5-1-0 : FA : LAIG-FA-MAC-145739-CS : 27 juin 2016 : Audit code - Supp de la macro ITK_EXPORT   *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 10 avril 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsVectorLinearInterpolateImageFunction_h
#define __vnsVectorLinearInterpolateImageFunction_h

#include "vnsVectorInterpolateImageFunction.h"

namespace vns
{

    /**
     * \class VectorLinearInterpolateImageFunction
     * \brief Linearly interpolate a vector image at specified positions.
     *
     * VectorLinearInterpolateImageFunction linearly interpolates a vector
     * image intensity non-integer pixel position. This class is templated
     * over the input image type and the coordinate representation type.
     *
     * This function works for N-dimensional images.
     *
     * \warning This function work only for Vector images. For
     * scalar images use LinearInterpolateImageFunction.
     *
     * \ingroup ImageFunctions ImageInterpolators
     *
     */
    template<class TInputImage, class TCoordRep = double>
        class VectorLinearInterpolateImageFunction : public VectorInterpolateImageFunction<
                TInputImage, TCoordRep>
        {
        public:
            /** Standard class typedefs. */
            typedef VectorLinearInterpolateImageFunction Self;
            typedef VectorInterpolateImageFunction<TInputImage, TCoordRep> Superclass;
            typedef itk::SmartPointer<Self> Pointer;
            typedef itk::SmartPointer<const Self> ConstPointer;

            /** Method for creation through the object factory. */
            itkNewMacro(Self)

            /** Run-time type information (and related methods). */
            itkTypeMacro(VectorLinearInterpolateImageFunction,
                    VectorInterpolateImageFunction)

            /** InputImageType typedef support. */
            typedef typename Superclass::InputImageType InputImageType;
            typedef typename Superclass::PixelType PixelType;
            typedef typename Superclass::ValueType ValueType;
            typedef typename Superclass::RealType RealType;

            /** Dimension underlying input image. */
            itkStaticConstMacro(ImageDimension, unsigned int,Superclass::ImageDimension);

            /** Index typedef support. */
            typedef typename Superclass::IndexType IndexType;

            /** ContinuousIndex typedef support. */
            typedef typename Superclass::ContinuousIndexType ContinuousIndexType;

            /** Output type is Vector<double,Dimension> */
            typedef typename Superclass::OutputType OutputType;

            /** Evaluate the function at a ContinuousIndex position
             *
             * Returns the linearly interpolated image intensity at a
             * specified point position. No bounds checking is done.
             * The point is assume to lie within the image buffer.
             *
             * ImageFunction::IsInsideBuffer() can be used to check bounds before
             * calling the method. */
            virtual OutputType
            EvaluateAtContinuousIndex(const ContinuousIndexType & index) const;

        protected:
            VectorLinearInterpolateImageFunction();
            virtual
            ~VectorLinearInterpolateImageFunction()
            {
            }
            void
            PrintSelf(std::ostream& os, itk::Indent indent) const;

        private:
            VectorLinearInterpolateImageFunction(const Self&); //purposely not implemented
            void
            operator=(const Self&); //purposely not implemented

            /** Number of neighbors used in the interpolation */
            static const unsigned long m_Neighbors;

        };

} // end namespace vns

#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsVectorLinearInterpolateImageFunction.txx"
#endif

#endif
