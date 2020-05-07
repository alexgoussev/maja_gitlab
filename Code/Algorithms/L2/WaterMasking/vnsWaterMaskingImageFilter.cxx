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
 * VERSION : 2.0.0 : FA : LAIG-FA-MAJA-152790-CS : 21 fevrier 2017 : Correction qualite taux de commentaire *
 * VERSION : 1.0.0 : FA : LAIG-FA-MAC-148399-CS : 19 octobre 2016 : Audit code - Correction qualite         *
 * VERSION : 5-1-0 : DM : LAIG-DM-MAC-1514-CNES : 12 juillet 2016 : Amélioration algo ( SRTM loin des côtes)*
 * VERSION : 5-0-0 : FA : LAIG-FA-MAC-143764-CS : 12 avril 2016 : Mise en forme du code (indentation, etc.) *
 * VERSION : 4-0-0 : FA : LAIG-FA-MAC-120653-CS : 3 avril 2014 : Correction de règles de qualité			*
 * VERSION : 4-0-0 : DM : LAIG-DM-MAC-517-CNES : 19 décembre 2013 : Améliorations algorithmiques			*
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 20 juil. 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/

#include "vnsWaterMaskingImageFilter.h"
#include "vnsMacro.h"
#include "vnsCaching.h"

namespace vns
{

    // Constructor
    WaterMaskingImageFilter::WaterMaskingImageFilter() :
            m_RealL2NoData(0.), m_InitMode(false), m_SunglintFlag(false), m_RedBandTOCR(0), m_NIRBandTOCR(0), m_NIRBandRCR(0), m_WaterNDVIThreshold(
                    0.), m_WaterReflectanceVariationThreshold(0.), m_MaximumSunglintReflectance(0.), m_SRTMGaussianSigma(0.), m_SRTMPercent(
                    0.), m_WaterMaskNumber(0), m_MinPercentPossibleWater(0.), m_WaterSlopeThreshold(0.), m_WaterRedReflectanceThreshold(0.)
    {

        // Input/Output initialization
        this->SetNumberOfIndexedInputs(10);
        this->SetNumberOfRequiredInputs(6);
        this->SetNumberOfIndexedOutputs(3);
        this->SetNumberOfRequiredOutputs(3);

        this->SetNthOutput(0, OutputImageType::New());
        this->SetNthOutput(1, VectorMaskType::New());
        this->SetNthOutput(2, VectorMaskType::New());

        m_PossibleWaterFlagFilter = PossibleWaterFlagFilterType::New();
        m_SRTMFilter = SRTMFilterType::New();
        m_SRTMGaussianFilter = GaussianSRTMMaskFilterType::New();
        m_SRTMMultiplyFilter = SRTMMultiplyFilterType::New();
    }

    // Destructor

    WaterMaskingImageFilter::~WaterMaskingImageFilter()
    {
    }

    //===============  MakeOutput method ===================/
    // This is overloaded to create the VectorDistanceMap output image

    WaterMaskingImageFilter::DataObjectPointer
    WaterMaskingImageFilter::MakeOutput(unsigned int idx)
    {
        if ((idx == 1) || (idx == 2))
        {
            return static_cast<DataObjectPointer>(VectorMaskType::New().GetPointer());
        }
        return Superclass::MakeOutput(idx);
    }

    //===============  Generate output information method ===================/

    void
    WaterMaskingImageFilter::GenerateOutputInformation()
    {
        // Call superclass implementation
        Superclass::GenerateOutputInformation();
        this->GetL2WASOutput()->SetNumberOfComponentsPerPixel(1);

        // If Init mode, no possible water mask and tested pixel flag
        // has been generated before
        if (m_InitMode == true)
        {
            this->GetL2PWAOutput()->SetNumberOfComponentsPerPixel(1);
            this->GetL2TWAOutput()->SetNumberOfComponentsPerPixel(1);
        }
        else
        {
            unsigned int l_NumberOfComponents(0);
            unsigned int l_NumberOfComponents2(0);

            // Check L2inPWA image availability
            if (!this->GetL2inPWAInput())
            {
                vnsExceptionBusinessMacro("Waiting for a possible water mask of previous product, but no one specified. Please set one.");
            }

            // Get the number of possible water mask previously generated (input masks)
            l_NumberOfComponents = this->GetL2inPWAInput()->GetNumberOfComponentsPerPixel();
            l_NumberOfComponents2 = this->GetL2inTWAInput()->GetNumberOfComponentsPerPixel();
            if (l_NumberOfComponents != l_NumberOfComponents2)
            {
                vnsExceptionBusinessMacro(
                        "The number of band of the two input masks (possible water and tested pixel flags) is different !");
            }

            // The number of output possible water mask depends on the
            // number of previous possible water mask generated since
            // init mode (D-1 to D-N_WM).
            // Then, the mask of date D is added to the previous ones.
            if (l_NumberOfComponents < m_WaterMaskNumber)
            {
                this->GetL2PWAOutput()->SetNumberOfComponentsPerPixel(l_NumberOfComponents + 1);
                this->GetL2TWAOutput()->SetNumberOfComponentsPerPixel(l_NumberOfComponents + 1);
            }
            // In this case, the older mask (D-N_WM) is replaced by the new one (date D)
            else
            {
                this->GetL2PWAOutput()->SetNumberOfComponentsPerPixel(m_WaterMaskNumber);
                this->GetL2TWAOutput()->SetNumberOfComponentsPerPixel(m_WaterMaskNumber);
            }
        }

    }

    //====================== Main computation method ======================/

    void
    WaterMaskingImageFilter::GenerateData()
    {
        // Load inputs
        InputImageConstPointer l_IPTOCRPtr = this->GetIPTOCRInput();
        InputMaskConstPointer l_IPEDGPtr = this->GetIPEDGInput();
        InputMaskConstPointer l_IPSHDSubPtr = this->GetIPSHDSubInput();
        SRTMMaskConstPointer l_SRTMWATPtr = this->GetSRTMWATInput();
        InputMaskConstPointer l_L2CLDSubSummaryPtr = this->GetL2CLDSubSummaryInput();
        ImageTypeConstPointer l_SlopeSubPtr = this->GetSlopeSubInput();

        // Initializations of images of the composite
        InputImageConstPointer l_L2inRCRPtr;
        VectorMaskConstPointer l_L2inPWAPtr;
        VectorMaskConstPointer l_L2inTWAPtr;

        // Check inputs
        // In nominal mode
        if (m_InitMode == false)
        {

            // Get the input images of the composite (of date D-1)
            l_L2inRCRPtr = this->GetL2inRCRInput();
            l_L2inPWAPtr = this->GetL2inPWAInput();
            l_L2inTWAPtr = this->GetL2inTWAInput();

            // Check the input images size
            vnsChecking8ImagesSizeMacro(l_L2inRCRPtr, l_L2inPWAPtr, l_L2inTWAPtr, l_L2CLDSubSummaryPtr, l_L2inRCRPtr, l_L2inPWAPtr,
                    l_L2inTWAPtr, l_SlopeSubPtr)

            // L2 input products (composite) exist only in standard mode
            m_PossibleWaterFlagFilter->SetL2inRCRInput(l_L2inRCRPtr);
            m_PossibleWaterFlagFilter->SetNIRBandRCR(m_NIRBandRCR);

            m_SRTMFilter->SetL2inPWAInput(l_L2inPWAPtr);
            m_SRTMFilter->SetL2inTWAInput(l_L2inTWAPtr);

        }
        // Check the input images size in init mode
        else
        {
            vnsChecking6ImagesSizeMacro(l_IPTOCRPtr, l_IPEDGPtr, l_IPSHDSubPtr, l_SRTMWATPtr, l_L2CLDSubSummaryPtr, l_SlopeSubPtr)
        }

        // Compute the possible water flag for image D by detecting low NDVI
        // Set input images
        m_PossibleWaterFlagFilter->SetIPTOCRInput(l_IPTOCRPtr);
        m_PossibleWaterFlagFilter->SetIPEDGInput(l_IPEDGPtr);
        m_PossibleWaterFlagFilter->SetL2CLDSubSummaryInput(l_L2CLDSubSummaryPtr);
        m_PossibleWaterFlagFilter->SetIPSHDSubInput(l_IPSHDSubPtr);
        m_PossibleWaterFlagFilter->SetSlopeSubInput(l_SlopeSubPtr);

        // Set the parameters
        m_PossibleWaterFlagFilter->SetInitMode(m_InitMode);
        m_PossibleWaterFlagFilter->SetSunglintFlag(m_SunglintFlag);
        m_PossibleWaterFlagFilter->SetRedBandTOCR(m_RedBandTOCR);
        m_PossibleWaterFlagFilter->SetNIRBandTOCR(m_NIRBandTOCR);
        m_PossibleWaterFlagFilter->SetWaterNDVIThreshold(m_WaterNDVIThreshold);
        m_PossibleWaterFlagFilter->SetWaterReflectanceVariationThreshold(m_WaterReflectanceVariationThreshold);
        m_PossibleWaterFlagFilter->SetMaximumSunglintReflectance(m_MaximumSunglintReflectance);
        m_PossibleWaterFlagFilter->SetWaterSlopeThreshold(m_WaterSlopeThreshold);
        m_PossibleWaterFlagFilter->SetWaterRedReflectanceThreshold(m_WaterRedReflectanceThreshold);
        m_PossibleWaterFlagFilter->SetRealL2NoData(m_RealL2NoData);

        // Compute the final water flag from the possible water flags
        //Filter the input SRTM with a gaussian
        m_SRTMGaussianFilter->SetInput(l_SRTMWATPtr);
        m_SRTMGaussianFilter->SetVariance(m_SRTMGaussianSigma * m_SRTMGaussianSigma);
        m_SRTMGaussianFilter->SetUseImageSpacingOff();
        m_SRTMGaussianFilter->SetMaximumError(CONST_EPSILON_20);
        m_SRTMGaussianFilter->SetMaximumKernelWidth(static_cast<unsigned int>(10 * m_SRTMGaussianSigma));
        m_SRTMMultiplyFilter->SetInput1(m_SRTMGaussianFilter->GetOutput());
        m_SRTMMultiplyFilter->SetInput2(l_SRTMWATPtr);

        vnsCrocodileClipMacro(SRTMWeighImageType, m_SRTMMultiplyFilter->GetOutput(), "SRTM_lisse.tif")

        // Set input images
        m_SRTMFilter->SetIPPWAInput(m_PossibleWaterFlagFilter->GetIPPWAOutput());
        m_SRTMFilter->SetIPTWAInput(m_PossibleWaterFlagFilter->GetIPTWAOutput());
        m_SRTMFilter->SetSRTMWATInput(m_SRTMMultiplyFilter->GetOutput());

        // Set the parameters
        m_SRTMFilter->SetInitMode(m_InitMode);
        m_SRTMFilter->SetSRTMPercent(m_SRTMPercent);
        m_SRTMFilter->SetMinPercentPossibleWater(m_MinPercentPossibleWater);
        m_SRTMFilter->SetWaterMaskNumber(m_WaterMaskNumber);

        m_SRTMFilter->GraftNthOutput(0, this->GetL2WASOutput());
        m_SRTMFilter->GraftNthOutput(1, this->GetL2PWAOutput());
        m_SRTMFilter->GraftNthOutput(2, this->GetL2TWAOutput());

        m_SRTMFilter->Update();

        // The filter is a composite filter
        // => outputs have to be link with the specific method GraftNthOutput()
        this->GraftNthOutput(0, m_SRTMFilter->GetL2WASOutput());
        this->GraftNthOutput(1, m_SRTMFilter->GetL2PWAOutput());
        this->GraftNthOutput(2, m_SRTMFilter->GetL2TWAOutput());

    }

    // PrintSelf method

    void
    WaterMaskingImageFilter::PrintSelf(std::ostream& os, itk::Indent indent) const
    {
        Superclass::PrintSelf(os, indent);
        os << "m_InitMode :     " << m_InitMode << std::endl;

        // Print the PossibleWaterFlagImageFilter filter
        os << "PossibleWaterFlagImageFilter : " << std::endl;
        // Print the SunglintFlag value
        os << "m_SunglintFlag :         " << Utilities::BoolToLowerString(m_SunglintFlag) << std::endl;
        // Print the TOCR Bands value
        os << "m_RedBandTOCR :          " << m_RedBandTOCR << std::endl;
        os << "m_NIRBandTOCR :          " << m_NIRBandTOCR << std::endl;
        // Print the NIR Band CR value
        os << "m_NIRBandRCR :           " << m_NIRBandRCR << std::endl;
        // Print the Water values
        os << "m_WaterNDVIThreshold :     " << m_WaterNDVIThreshold << std::endl;
        os << "m_WaterSlopeThreshold :     " << m_WaterSlopeThreshold << std::endl;
        os << "m_WaterRedReflectanceThreshold :     " << m_WaterRedReflectanceThreshold << std::endl;
        os << "m_WaterReflectanceVariationThreshold :     " << m_WaterReflectanceVariationThreshold << std::endl;
        // Print the MaximumSunglintReflectance value
        os << "m_MaximumSunglintReflectance :     " << m_MaximumSunglintReflectance << std::endl;

        os << "SRTMWaterMaskImproveImageFilter : " << std::endl;
        // Print the InitMode value
        os << "m_InitMode :                 " << m_InitMode << std::endl;
        // Print the SRTMPercent value
        os << "m_SRTMPercent :              " << m_SRTMPercent << std::endl;
        // Print them_WaterMaskNumber  value
        os << "m_WaterMaskNumber :          " << m_WaterMaskNumber << std::endl;
        // Print the MinPercentPossibleWater value
        os << "m_MinPercentPossibleWater :  " << m_MinPercentPossibleWater << std::endl;
        // Print the RealL2NoData value
        os << "m_SRTMGaussianSigma :        " << m_SRTMGaussianSigma << std::endl;
        // Print the RealL2NoData value
        os << "m_RealL2NoData :             " << m_RealL2NoData << std::endl;

    }

} // End namespace vns
