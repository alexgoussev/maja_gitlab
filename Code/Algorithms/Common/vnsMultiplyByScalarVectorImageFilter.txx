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
 * VERSION : 1.0.0 : FA : LAIG-FA-MAC-1988-CNES : 21 octobre 2016 : Correction qualite (code mort)          *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 11 mai 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsMultiplyByScalarVectorImageFilter_txx
#define __vnsMultiplyByScalarVectorImageFilter_txx

#include "vnsMultiplyByScalarVectorImageFilter.h"

#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkNumericTraits.h"

namespace vns
{

    /** Constructor */
    template<class TInputImage, class TOutputImage>
        MultiplyByScalarVectorImageFilter<TInputImage, TOutputImage>::MultiplyByScalarVectorImageFilter() : m_Coeff(1.0)
        {
        }

    /** Destructor */
    template<class TInputImage, class TOutputImage>
        MultiplyByScalarVectorImageFilter<TInputImage, TOutputImage>::~MultiplyByScalarVectorImageFilter()
        {
        }

    template<class TInputImage, class TOutputImage>
        void
        MultiplyByScalarVectorImageFilter<TInputImage, TOutputImage>::GenerateOutputInformation()
        {
            // Call to the superclass implementation
            Superclass::GenerateOutputInformation();

            typename Superclass::InputImageConstPointer inputPtr = this->GetInput();
            typename Superclass::OutputImagePointer outputPtr = this->GetOutput();

            // initialize the number of channels of the output image
            outputPtr->SetNumberOfComponentsPerPixel(inputPtr->GetNumberOfComponentsPerPixel());
        }

    template<class TInputImage, class TOutputImage>
        void
        MultiplyByScalarVectorImageFilter<TInputImage, TOutputImage>::ThreadedGenerateData(
                const RegionType& outputRegionForThread, itk::ThreadIdType /*threadId*/)
        {
            // Grab the input and output
            typename Superclass::OutputImagePointer outputPtr = this->GetOutput();
            typename Superclass::InputImageConstPointer inputPtr = this->GetInput();

            // Define the iterators
            itk::ImageRegionConstIterator<InputImageType> inputIt(inputPtr, outputRegionForThread);
            itk::ImageRegionIterator<OutputImageType> outputIt(outputPtr, outputRegionForThread);


            // Iterator initialization
            inputIt.GoToBegin();
            outputIt.GoToBegin();

            OutputImagePixelType outputVectorValue;

            outputVectorValue.SetSize(inputPtr->GetNumberOfComponentsPerPixel());
            outputVectorValue.Fill(itk::NumericTraits<OutputImageInternalPixelType>::Zero);
            const unsigned int nbValue = outputVectorValue.GetSize();

            // Pixel loop
            while (inputIt.IsAtEnd() == false)
            {
                const InputImagePixelType& inputValue = inputIt.Get();

                // Band loop

                for (unsigned int j = 0 ; j < nbValue ; j++)
                {
                    // Set to one the bit to the associated band
                    outputVectorValue[j] = static_cast<OutputImageInternalPixelType> (m_Coeff * inputValue[j]);
                }

                // Set the output pixel value
                outputIt.Set(static_cast<OutputImagePixelType> (outputVectorValue));

                ++inputIt;
                ++outputIt;
            }
        }

    /** PrintSelf method */
    template<class TInputImage, class TOutputImage>
        void
        MultiplyByScalarVectorImageFilter<TInputImage, TOutputImage>::PrintSelf(std::ostream& os, itk::Indent indent) const
        {
            Superclass::PrintSelf(os, indent);
        }

} // End namespace vns

#endif /* __vnsMultiplyByScalarVectorImageFilter_txx */
