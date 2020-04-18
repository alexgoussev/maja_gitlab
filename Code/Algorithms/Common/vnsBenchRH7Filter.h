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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 11 mai 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsBenchRH7_h
#define __vnsBenchRH7_h

#include "itkImageSource.h"
#include "vnsMacro.h"

namespace vns
{
/** \class  MultiplyByScalarToVectorImageFilter
 * \brief Multiply each component of a vector image by a given scalar
 *
 *
 * \author CS Systemes d'Information
 *
 * \sa ImageToImageFilter
 * \sa BenchRH7
 *
 *
 */
template <class TInputImage, class TOutputImage>
class BenchRH7
{
public:
    /** Standard class typedefs. */
    typedef BenchRH7                              Self;

    /** Some convenient typedefs. */
    typedef TInputImage                  InputImageType;
    typedef typename InputImageType::ConstPointer InputImageConstPointer;
    typedef typename InputImageType::RegionType   RegionType;
    typedef typename InputImageType::PixelType    InputImagePixelType;
    typedef typename InputImageType::SizeType     SizeType;
    typedef TOutputImage  OutputImageType;
    typedef typename OutputImageType::Pointer     OutputImagePointer;
    typedef typename OutputImageType::PixelType   OutputImagePixelType;
    typedef typename OutputImageType::InternalPixelType   OutputImageInternalPixelType;

    void Update();

    /** Constructor */
    BenchRH7(const unsigned int nbThreads, const unsigned int nbBands, const unsigned int nbPixels);

    /** Destructor */
    virtual ~BenchRH7();

private:
    BenchRH7(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented

    /** Scalar factor top apply */
    unsigned int m_nbThreads;
    unsigned int m_nbBands;
    unsigned int m_nbPixels;

    /** Static function used as a "callback" by the MultiThreader.  The threading
     * library will call this routine for each thread, which will delegate the
     * control to ThreadedGenerateData(). */
    static ITK_THREAD_RETURN_TYPE ThreaderCallback(void *arg);
};

} // End namespace vns
#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsBenchRH7Filter.txx"
#endif

#endif /* __vnsMultiplyByScalarVectorImageFilter_h */
