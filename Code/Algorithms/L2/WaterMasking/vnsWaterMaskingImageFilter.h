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
 * VERSION : 5-1-0 : DM : LAIG-DM-MAC-1514-CNES : 12 juillet 2016 : Amélioration algo ( SRTM loin des côtes)*
 * VERSION : 5-1-0 : FA : LAIG-FA-MAC-145739-CS : 27 juin 2016 : Audit code - Supp de la macro ITK_EXPORT   *
 * VERSION : 5-0-0 : FA : LAIG-FA-MAC-143764-CS : 12 avril 2016 : Mise en forme du code (indentation, etc.) *
 * VERSION : 4-0-0 : DM : LAIG-DM-MAC-517-CNES : 19 décembre 2013 : Améliorations algorithmiques			*
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 20 juil. 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsWaterMaskingImageFilter_h
#define __vnsWaterMaskingImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "vnsPossibleWaterFlagImageFilter.h"
#include "vnsSRTMWaterMaskImproveImageFilter.h"
#include "itkMultiplyImageFilter.h"

namespace vns
{
    /** \class  WaterMaskingImageFilter
     * \brief This class implements .
     *
     *
     *
     * \author CS Systemes d'Information
     *
     * \sa ImageToImageFilter
     *
     * \ingroup L2
     *
     */
    class WaterMaskingImageFilter : public itk::ImageToImageFilter<VNSRealVectorImageType, VNSMaskImageType>
    {
    public:
        /** Standard class typedefs. */
        typedef WaterMaskingImageFilter Self;
        typedef itk::ImageToImageFilter<VNSRealVectorImageType, VNSMaskImageType> Superclass;
        typedef itk::SmartPointer<Self> Pointer;
        typedef itk::SmartPointer<const Self> ConstPointer;

        /** Type macro */
        itkNewMacro(Self)
        /** Creation through object factory macro */
        itkTypeMacro(WaterMaskingImageFilter, ImageToImageFilter )

        /** Some convenient typedefs. */
        typedef Superclass::InputImageType InputImageType;
        typedef InputImageType::ConstPointer InputImageConstPointer;
        typedef InputImageType::RegionType RegionType;
        typedef InputImageType::PixelType InputImagePixelType;
        typedef InputImageType::SizeType SizeType;

        typedef VNSMaskImageType InputMaskType;
        typedef InputMaskType::Pointer InputMaskPointer;
        typedef InputMaskType::ConstPointer InputMaskConstPointer;
        typedef InputMaskType::PixelType InputMaskPixelType;

        typedef VNSMaskVectorImageType VectorMaskType;
        typedef VectorMaskType::Pointer VectorMaskPointer;
        typedef VectorMaskType::ConstPointer VectorMaskConstPointer;
        typedef VectorMaskType::PixelType VectorMaskPixelType;

        typedef VNSMaskImageType SRTMMaskType;
        typedef SRTMMaskType::Pointer SRTMMaskPointer;
        typedef SRTMMaskType::ConstPointer SRTMMaskConstPointer;
        typedef SRTMMaskType::PixelType SRTMMaskPixelType;
        typedef VNSRealImageType SRTMWeighImageType;
        //Typedef for SRTM smoothing
        typedef itk::DiscreteGaussianImageFilter<SRTMMaskType, SRTMWeighImageType> GaussianSRTMMaskFilterType;
        typedef GaussianSRTMMaskFilterType::Pointer                       GaussianSRTMMaskFilterPointer;
        typedef itk::MultiplyImageFilter<SRTMWeighImageType, SRTMMaskType, SRTMWeighImageType> SRTMMultiplyFilterType;
        typedef SRTMMultiplyFilterType::Pointer                       SRTMMultiplyFilterPointer;

        typedef VNSRealImageType ImageType;
        typedef ImageType::Pointer ImageTypePointer;
        typedef ImageType::ConstPointer ImageTypeConstPointer;
        typedef ImageType::PixelType ImageTypePixelType;

        typedef Superclass::OutputImageType OutputImageType;
        typedef OutputImageType::Pointer OutputImagePointer;
        typedef OutputImageType::PixelType OutputImagePixelType;

        /** Pointer Type for data object */
        typedef Superclass::DataObjectPointer DataObjectPointer;

        /** Filters typedef */

        typedef PossibleWaterFlagImageFilter<InputImageType, InputMaskType, ImageType, InputMaskType> PossibleWaterFlagFilterType;
        typedef PossibleWaterFlagFilterType::Pointer PossibleWaterFlagPointerFilterType;

        typedef SRTMWaterMaskImproveImageFilter<InputMaskType, VectorMaskType, SRTMWeighImageType, OutputImageType> SRTMFilterType;
        typedef SRTMFilterType::Pointer SRTMPointerFilterType;

        // Init mode parameter accessors
        itkSetMacro(InitMode, bool)
        itkGetConstReferenceMacro(InitMode, bool)
        // Sunglint flag parameter accessors
        itkSetMacro(SunglintFlag, bool)
        itkGetConstReferenceMacro(SunglintFlag, bool)

        // Red band index accessors for the TOCR
        itkSetMacro(RedBandTOCR, unsigned int)
        itkGetConstReferenceMacro(RedBandTOCR, unsigned int)

        // NIR band index accessors for TOCR
        itkSetMacro(NIRBandTOCR, unsigned int)
        itkGetConstReferenceMacro(NIRBandTOCR, unsigned int)

        // NIR band index accessors for RCR
        itkSetMacro(NIRBandRCR, unsigned int)
        itkGetConstReferenceMacro(NIRBandRCR, unsigned int)

        // Water NDVI threshold accessors
        itkSetMacro(WaterNDVIThreshold, double)
        itkGetConstReferenceMacro(WaterNDVIThreshold, double)

        // Water reflectance variation threshold accessors
        itkSetMacro(WaterReflectanceVariationThreshold, double)
        itkGetConstReferenceMacro(WaterReflectanceVariationThreshold, double)

        // Maximum sunglint reflectance accessors
        itkSetMacro(MaximumSunglintReflectance, double)
        itkGetConstReferenceMacro(MaximumSunglintReflectance, double)

        // SRTM sigma for gaussian accessors
        itkSetMacro(SRTMGaussianSigma, double)
        itkGetConstReferenceMacro(SRTMGaussianSigma, double)

        // Bonus SRTM water mask accessors
        itkSetMacro(SRTMPercent, double)
        itkGetConstReferenceMacro(SRTMPercent, double)

        // Number of water mask accessors
        itkSetMacro(WaterMaskNumber, unsigned int)
        itkGetConstReferenceMacro(WaterMaskNumber, unsigned int)

        // Accessors of minimum percent to declare a pixel as water
        itkSetMacro(MinPercentPossibleWater, double)
        itkGetConstReferenceMacro(MinPercentPossibleWater, double)

        // DEM slope threshold accessors
        itkSetMacro(WaterSlopeThreshold, double)
        itkGetConstReferenceMacro(WaterSlopeThreshold, double)

        // Red reflectance threshold accessors
        itkSetMacro(WaterRedReflectanceThreshold, double)
        itkGetConstReferenceMacro(WaterRedReflectanceThreshold, double)

        vnsMemberAndSetMacro(RealL2NoData, RealNoDataType)

        /** Set the image of the surface reflectance corrected by absorption and rayleigh */
        vnsSetGetInputMacro( IPTOCR, InputImageType, 0)
        /** Set the image of the surface reflectance corrected by absorption and rayleigh
         * of the composite product */
        vnsSetGetInputMacro( L2inRCR, InputImageType, 6)
        /** Set the edge mask of the input product */
        vnsSetGetInputMacro( IPEDG, InputMaskType, 1)
        /** Set the cast shadow mask */
        vnsSetGetInputMacro( IPSHDSub, InputMaskType, 2)
        /** Set the cloud mask (summary mask) */
        vnsSetGetInputMacro( L2CLDSubSummary, InputMaskType, 3)
        /** Set the SRTM water mask */
        vnsSetGetInputMacro( SRTMWAT,SRTMMaskType , 4)
        /** Set the possible water mask */
        vnsSetGetInputMacro( L2inPWA, VectorMaskType, 7)
        /** Set the tested pixel mask */
        vnsSetGetInputMacro( L2inTWA, VectorMaskType, 8)
        /** Set the terrain slope in degrees at L2 coarse resolution */
        vnsSetGetInputMacro( SlopeSub, ImageType, 5)

        /** Get the final water mask */
        OutputImageType*
        GetL2WASOutput()
        {
            return dynamic_cast<OutputImageType*>(this->itk::ProcessObject::GetOutput(0));
        }

        /** Get the updated possible water flag */
        VectorMaskType*
        GetL2PWAOutput()
        {
            return dynamic_cast<VectorMaskType*>(this->itk::ProcessObject::GetOutput(1));
        }

        /** Get the updated tested pixel flag */
        VectorMaskType*
        GetL2TWAOutput()
        {
            return dynamic_cast<VectorMaskType*>(this->itk::ProcessObject::GetOutput(2));
        }

    protected:
        /** Constructor */
        WaterMaskingImageFilter();
        /** Destructor */
        virtual
        ~WaterMaskingImageFilter();
        /** PrintSelf method */
        virtual void
        PrintSelf(std::ostream& os, itk::Indent indent) const;

        /** This is overloaded to create the VectorDistanceMap output image */
        virtual DataObjectPointer
        MakeOutput(unsigned int idx);

        /** Generate output information. */
        virtual void
        GenerateOutputInformation(void);

        /** Composite Filter method. */
        virtual void
        GenerateData(void);

    private:
        WaterMaskingImageFilter(const Self&); //purposely not implemented
        void
        operator=(const Self&); //purposely not implemented

        /** Init_mode option declaration */
        bool m_InitMode;
        /** Sunglint Flag */
        bool m_SunglintFlag;

        /** Red band definition for TOCR */
        unsigned int m_RedBandTOCR;
        /** NIR band definition for TOCR */
        unsigned int m_NIRBandTOCR;
        /** NIR band definition for RCR */
        unsigned int m_NIRBandRCR;

        /** Water NDVI Threshold under which the pixel is probably covered by water */
        double m_WaterNDVIThreshold;
        /** Water reflectance variation threshold over which the pixel is probably covered by water */
        double m_WaterReflectanceVariationThreshold;
        /** Maximum reflectance parameter for which the variation threshold is used */
        double m_MaximumSunglintReflectance;

        /** Gaussian sigma for SRTM smoothing */
        double m_SRTMGaussianSigma;
        /** Bonus SRTM water mask declaration */
        double m_SRTMPercent;
        /** Number of mask available in the PWA and TWA masks (N_WM) */
        unsigned int m_WaterMaskNumber;
        /** Minimum percent of tested times to declare a pixel as water */
        double m_MinPercentPossibleWater;
        /** DEM slope threshold */
        double m_WaterSlopeThreshold;
        /** Red reflectance threshold */
        double m_WaterRedReflectanceThreshold;

        PossibleWaterFlagPointerFilterType m_PossibleWaterFlagFilter;
        SRTMPointerFilterType m_SRTMFilter;
        GaussianSRTMMaskFilterPointer m_SRTMGaussianFilter;
        SRTMMultiplyFilterPointer m_SRTMMultiplyFilter;

    };

} // End namespace vns

#endif /* __vnsWaterMaskingImageFilter_h */
