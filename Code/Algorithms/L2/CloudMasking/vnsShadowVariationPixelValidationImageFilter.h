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
 * VERSION : 5-0-0 : DM : LAIG-DM-MAC-982-CNES : 8 janvier 2016 : Modification de l’algorithme de detection **
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: vnsShadowVariationPixelValidationImageFilter.h 10095 2016-01-15 09:42:27Z abricier $                   *
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsShadowVariationPixelValidationImageFilter_h
#define __vnsShadowVariationPixelValidationImageFilter_h

#include "otbPersistentImageFilter.h"
#include "itkNumericTraits.h"
#include "itkArray.h"
#include "itkSimpleDataObjectDecorator.h"
#include "otbPersistentFilterStreamingDecorator.h"
#include "vnsMacro.h"

namespace vns
{

    /** \class PersistentShadowVariationPixelValidationImageFilter
     * \brief
     *
     */
    template<class TInputMask, class TLabelImage>
        class PersistentShadowVariationPixelValidationImageFilter : public otb::PersistentImageFilter<TInputMask, TInputMask>
        {
        public:
            /** Standard Self typedef */
            typedef PersistentShadowVariationPixelValidationImageFilter Self;
            typedef otb::PersistentImageFilter<TInputMask, TInputMask> Superclass;
            typedef itk::SmartPointer<Self> Pointer;
            typedef itk::SmartPointer<const Self> ConstPointer;

            /** Method for creation through the object factory. */
            itkNewMacro(Self)

            /** Runtime information support. */
            itkTypeMacro(PersistentShadowVariationPixelValidationImageFilter, PersistentImageFilter)

            /** Image related typedefs. */
            typedef TInputMask InputMaskType;
            typedef typename TInputMask::Pointer InputMaskPointer;
            typedef TLabelImage LabelImageType;
            typedef typename TLabelImage::Pointer LabelImagePointer;

            typedef typename InputMaskType::PixelType MaskPixelType;
            typedef typename LabelImageType::PixelType LabelPixelType;
            typedef std::map<LabelPixelType, double> LabelPopulationMapType;
            typedef std::map<LabelPixelType, bool> LabelValidityMapType;

            /** Smart Pointer type to a DataObject. */
            typedef typename itk::DataObject::Pointer DataObjectPointer;

            itkStaticConstMacro(InputImageDimension, unsigned int, TInputMask::ImageDimension);
            typedef itk::ImageBase<InputImageDimension> ImageBaseType;
            typedef typename ImageBaseType::RegionType InputImageRegionType;

            /** Type of DataObjects used for scalar outputs */
            typedef itk::SimpleDataObjectDecorator<LabelValidityMapType> LabelValidityMapObjectType;

            /** Set input  D-1 Shadow Mask */
            vnsSetGetInputRawMacro( InputShadow, InputMaskType, 0)

            /** Set input  D-1 Shadow Mask */
            vnsSetGetInputRawMacro( InputShadVar, InputMaskType, 1)

            /** Set input label image */
            vnsSetGetInputRawMacro( InputLabelImage,LabelImageType , 2)

            /** Set/Get validity lower threshold */
            itkSetMacro(LowerValidityThreshold, double);
            itkGetConstReferenceMacro(LowerValidityThreshold, double);

            /** Return the computed Mean for each label in the input label image */
            itkGetConstMacro(LabelValidityStatusMap, LabelValidityMapType)

            /** Make a DataObject of the correct type to be used as the specified
             * output. */
            virtual DataObjectPointer MakeOutput(unsigned int idx);

            /** Pass the input through unmodified. Do this by Grafting in the
             *  AllocateOutputs method.
             */
            void AllocateOutputs();

            virtual void GenerateOutputInformation();

            void Synthetize(void);

            void Reset(void);

            /** Due to heterogeneous input template GenerateInputRequestedRegion must be reimplemented using explicit cast **/
            /** This new implementation is inspired by the one of itk::ImageToImageFilter **/
            void GenerateInputRequestedRegion();

        protected:
            PersistentShadowVariationPixelValidationImageFilter();
            virtual ~PersistentShadowVariationPixelValidationImageFilter()
            {}
            void PrintSelf(std::ostream& os, itk::Indent indent) const;

            /** GenerateData. */
            void GenerateData();

        private:
            PersistentShadowVariationPixelValidationImageFilter(const Self &); //purposely not implemented
            void operator =(const Self&);//purposely not implemented

            LabelPopulationMapType m_LabelTotalPopulation;
            LabelPopulationMapType m_LabelValidPopulation;
            LabelValidityMapType m_LabelValidityStatusMap;
            double m_LowerValidityThreshold;
        }; // end of class

        /*===========================================================================*/

        /** \class ShadowVariationPixelValidationImageFilter
         * \brief
         *
         */

    template<class TInputMask, class TLabelImage>
        class ShadowVariationPixelValidationImageFilter : public otb::PersistentFilterStreamingDecorator<
                PersistentShadowVariationPixelValidationImageFilter<TInputMask, TLabelImage> >
        {
        public:
            /** Standard Self typedef */
            typedef ShadowVariationPixelValidationImageFilter Self;
            typedef otb::PersistentFilterStreamingDecorator<PersistentShadowVariationPixelValidationImageFilter<TInputMask, TLabelImage> > Superclass;
            typedef itk::SmartPointer<Self> Pointer;
            typedef itk::SmartPointer<const Self> ConstPointer;

            /** Type macro */
            itkNewMacro(Self)

            /** Creation through object factory macro */
            itkTypeMacro(ShadowVariationPixelValidationImageFilter, PersistentFilterStreamingDecorator)

            typedef TInputMask MaskType;
            typedef TLabelImage LabelImageType;

            typedef typename Superclass::FilterType::LabelValidityMapType LabelValidityMapType;
            typedef typename Superclass::FilterType::LabelValidityMapObjectType LabelValidityMapObjectType;

            typedef typename Superclass::FilterType::LabelPopulationMapType LabelPopulationMapType;

            /** Set input  D-1 Shadow Mask */
            void
            SetInputShadow(const MaskType * input)
            {
                this->GetFilter()->SetInputShadow(input);
            }

            /** Get input D-1 Shadow Mask */
            const MaskType *
            GetInputShadow()
            {
                return this->GetFilter()->GetInputShadow();
            }

            /** Set input  D-1 Shadow Mask */
            void
            SetInputShadVar(const MaskType * input)
            {
                this->GetFilter()->SetInputShadVar(input);
            }

            /** Get input D-1 ShadVar Mask */
            const MaskType *
            GetInputShadVar()
            {
                return this->GetFilter()->GetInputShadVar();
            }

            /** Set input label image (monoband) */
            void
            SetInputLabelImage(const LabelImageType * input)
            {
                this->GetFilter()->SetInputLabelImage(input);
            }

            /** Get input label image (monoband) */
            const LabelImageType *
            GetInputLabelImage()
            {
                return this->GetFilter()->GetInputLabelImage();
            }

            /** Set input Validity Threshold */
            void
            SetLowerValidityThreshold(const double t)
            {
                this->GetFilter()->SetLowerValidityThreshold(t);
            }

            /** Return the computed Mean for each label */
            LabelValidityMapType
            GetLabelValidityStatusMap() const
            {
                return this->GetFilter()->GetLabelValidityStatusMap();
            }

        protected:
            /** Constructor */
            ShadowVariationPixelValidationImageFilter()
            {
            }
            /** Destructor */
            virtual
            ~ShadowVariationPixelValidationImageFilter()
            {
            }

        private:
            ShadowVariationPixelValidationImageFilter(const Self &); //purposely not implemented
            void
            operator =(const Self&); //purposely not implemented
        };

} // end namespace otb

#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsShadowVariationPixelValidationImageFilter.txx"
#endif

#endif
