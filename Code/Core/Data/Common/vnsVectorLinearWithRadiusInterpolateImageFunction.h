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
 * $Id: vnsVectorLinearWithRadiusInterpolateImageFunction.h 2406 2011-01-19 15:38:23Z tfeuvrie $
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsVectorLinearWithRadiusInterpolateImageFunction_h
#define __vnsVectorLinearWithRadiusInterpolateImageFunction_h

#include "vnsVectorInterpolateImageFunction.h"
#include "vnsMacro.h"

namespace vns
{

    /**
     * \class VectorLinearWithRadiusInterpolateImageFunction
     * \brief Linearly interpolate a vector image at specified positions.
     *
     * VectorLinearWithRadiusInterpolateImageFunction linearly interpolates a vector
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
        class VectorLinearWithRadiusInterpolateImageFunction : public VectorInterpolateImageFunction<
                TInputImage, TCoordRep>
        {
        public:
            /** Standard class typedefs. */
            typedef VectorLinearWithRadiusInterpolateImageFunction Self;
            typedef VectorInterpolateImageFunction<TInputImage, TCoordRep> Superclass;
            typedef itk::SmartPointer<Self> Pointer;
            typedef itk::SmartPointer<const Self> ConstPointer;

            /** Method for creation through the object factory. */
            itkNewMacro(Self)

            /** Run-time type information (and related methods). */
            itkTypeMacro(VectorLinearWithRadiusInterpolateImageFunction,
                    VectorInterpolateImageFunction)

            /** InputImageType typedef support. */
            typedef typename Superclass::InputImageType InputImageType;
            typedef typename Superclass::PixelType PixelType;
            typedef typename Superclass::ValueType ValueType;
            typedef typename Superclass::RealType RealType;

            vnsMemberAndSetAndGetConstReferenceMacro(Radius, unsigned int)

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
            VectorLinearWithRadiusInterpolateImageFunction();
            virtual
            ~VectorLinearWithRadiusInterpolateImageFunction()
            {
            }
            void
            PrintSelf(std::ostream& os, itk::Indent indent) const;



        private:
            VectorLinearWithRadiusInterpolateImageFunction(const Self&); //purposely not implemented
            void
            operator=(const Self&); //purposely not implemented

            /** Number of neighbors used in the interpolation */
//            static const unsigned long m_Neighbors;

        };

} // end namespace vns

#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsVectorLinearWithRadiusInterpolateImageFunction.txx"
#endif

#endif
