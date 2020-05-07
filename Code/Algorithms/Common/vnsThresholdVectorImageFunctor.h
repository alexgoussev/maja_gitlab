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
 * VERSION : 2.1.0 : DM : LAIG-DM-MAJA-157814-CS : 17 mai 2017 : Refactoring plus de unary                  *
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsThresholdVectorImageFunctor_h
#define __vnsThresholdVectorImageFunctor_h

namespace vns
{
  /** \class  ThresholdVectorImageFunctor
   * \brief This class applies a threshold to an image and generates the associated mask.
   *
   * For each band, it tests if the value of the input pixel is greater than a threshold value.
   * If it is true, this functor sets the value of the output pixel to m_OutputValue,
   * else it sets the value of the output pixel to m_InsideValue.
   * The output image is a vector image ( one mask for each band ).
   *
   * \author CS Systemes d'Information
   *
   * \ingroup L2
   *
   */
  namespace Functor
  {
    template<class TInputPixel, class TOutputPixel>
      class ThresholdVectorImageFunctor
    {
    public:
      typedef ThresholdVectorImageFunctor<TInputPixel, TOutputPixel>
	ThresholdVectorImageFunctorType;
		
    ThresholdVectorImageFunctor(void) : m_ThresholdValue (0), m_InsideValue(0), m_OutputValue(1), m_OutputSize(1)
	{
	}
                
		
      virtual ~ThresholdVectorImageFunctor(void)
	{
	}
                
		
      typedef TInputPixel InputPixelType;
      typedef TOutputPixel OutputPixelType;
      typedef typename InputPixelType::ValueType  InputInternalPixelType;
      typedef typename OutputPixelType::ValueType OutputInternalPixelType;
		
      /** Get the threshold value */
      InputInternalPixelType

	GetThresholdValue(void)
      {
	return m_ThresholdValue;
      }
      /** Set the threshold value */
      void
	SetThresholdValue(InputInternalPixelType val)
      {
	m_ThresholdValue = val;
      }
      
      /** Get the inside value set to the output mask*/
      OutputInternalPixelType
	GetInsideValue(void)
      {
	return m_InsideValue;
      }
      /** Set the inside value set to the output mask */
      void
	SetInsideValue(OutputInternalPixelType val)
      {
	m_InsideValue = val;
      }
      
      /** Get the output value set to the output mask*/
      OutputInternalPixelType
	GetOutputValue(void)
      {
	return m_OutputValue;
      }
      /** Set the output value set to the output mask */
      void
	SetOutputValue(OutputInternalPixelType val)
      {
	m_OutputValue = val;
      }
      
      /** Get the output size of the output mask*/
      unsigned int
	GetOutputSize(void)
      {
	return m_OutputSize;
      }
      /** Set the output size of the output mask */
      void
	SetOutputSize(unsigned int val)
      {
	m_OutputSize = val;
      }
      
      inline OutputPixelType
	operator()(InputPixelType inPix) const
	{
	  OutputPixelType outPix;
	  const unsigned int l_size = inPix.Size();
	  // Set output pixel dimension
	  outPix.SetSize(l_size);

	  // Set the inside value to the pixel of the output mask for all bands
	  outPix.Fill(m_InsideValue);

	  // Band Loop
	  for (unsigned int bd = 0; bd < l_size; bd++)
	    {
	      if ( vcl_abs(inPix[bd]) > m_ThresholdValue)
		{
		  outPix[bd] = m_OutputValue;
		}
	    }

	  return outPix;
	}

    protected:
      /** Threshold value declaration */
      InputInternalPixelType m_ThresholdValue;
      /** Mask inside value declaration */
      OutputInternalPixelType m_InsideValue;
      /** Mask output value declaration */
      OutputInternalPixelType m_OutputValue;
      /** Output image dimension declaration */
      unsigned int m_OutputSize;

    };

  } // end namespace functor

} // End namespace vns

#endif /* __vnsThresholdVectorImageFunctor_h */
