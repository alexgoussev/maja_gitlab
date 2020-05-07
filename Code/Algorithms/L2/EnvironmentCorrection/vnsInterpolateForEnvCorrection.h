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
 * VERSION : 5-1-0 : FA : LAIG-FA-MAC-144674-CS : 2 mai 2016 : Correction warning, qualite, etc             *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 1 septembre 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsInterpolateForEnvCorrection_h
#define __vnsInterpolateForEnvCorrection_h

#include "itkImageToImageFilter.h"
#include "vnsMacro.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"



namespace vns
{
/** \class  InterpolateForEnvCorrection
 * \brief This class computes Tdir, Tdif and T, images of direct transmission, diffuse transmission
 *  and the sum of these two.
 *
 * To do this, we proceed interpolations on two LUTs with h_dtm_sub, thetaS and AOT smoothed image.
 * \author CS Systemes d'Information
 *
 * \sa ImageToImageFilter
 *
 * \ingroup L2
 *
 */
template <class TInputImage, class TInputMask, class TInputDTM, class TLUT3D, class TLUT2D, class TOutputVectorImage>
class InterpolateForEnvCorrection : public itk::ImageToImageFilter<TInputImage,TOutputVectorImage>
{
public:
    /** Standard class typedefs. */
    typedef InterpolateForEnvCorrection                             Self;
    typedef itk::ImageToImageFilter<TInputImage,TOutputVectorImage>      Superclass;
    typedef itk::SmartPointer<Self>                                Pointer;
    typedef itk::SmartPointer<const Self>                          ConstPointer;

    /** Type macro */
    itkNewMacro(Self);
    /** Creation through object factory macro */
    itkTypeMacro(InterpolateForEnvCorrection, ImageToImageFilter );

    /** Some convenient typedefs. */
    typedef TInputImage                                     InputImageType;
    typedef typename InputImageType::ConstPointer           InputImageConstPointerType;
    typedef typename InputImageType::Pointer                InputImagePointerType;
    typedef typename InputImageType::RegionType             InputImageRegionType;
    typedef typename InputImageType::PixelType              InputImagePixelType;
    typedef typename InputImageType::InternalPixelType      InternalPixelType;
    typedef typename InputImageType::IndexType              IndexType;
    typedef typename InputImageType::SizeType               SizeType;
    typedef typename InputImageType::OffsetType             OffsetType;

    typedef TInputMask                                      InputMaskType;
    typedef typename InputMaskType::Pointer                 InputMaskPointerType;
    typedef typename InputMaskType::ConstPointer            InputMaskConstPointerType;
    typedef typename InputMaskType::PixelType               InputMaskPixelType;
    typedef typename InputMaskType::InternalPixelType       InputMaskInternalPixelType;

    typedef TInputDTM                                       InputDTMType;
    typedef typename InputDTMType::Pointer                  InputDTMPointerType;
    typedef typename InputDTMType::ConstPointer             InputDTMConstPointerType;
    typedef typename InputDTMType::PixelType                InputDTMPixelType;
    typedef typename InputDTMType::InternalPixelType        InputDTMInternalPixelType;

    typedef TLUT3D                                          LUT3DType;
    typedef typename LUT3DType::Pointer                     LUT3DPointerType;
    typedef typename LUT3DType::PixelType                   LUT3DPixelType;
    typedef typename LUT3DType::ParameterValuesType         LUT3DParameterValuesType;
    typedef typename LUT3DType::PointType                   LUT3DPointType;
    typedef typename LUT3DPointType::ValueType              LUT3DPointValueType;

    typedef TLUT2D                                          LUT2DType;
    typedef typename LUT2DType::Pointer                     LUT2DPointerType;
    typedef typename LUT2DType::PixelType                   LUT2DPixelType;
    typedef typename LUT2DType::ParameterValuesType         LUT2DParameterValuesType;
    typedef typename LUT2DType::PointType                   LUT2DPointType;
    typedef typename LUT2DPointType::ValueType              LUT2DPointValueType;

    typedef TOutputVectorImage                              OutputVectorImageType;
    typedef typename OutputVectorImageType::Pointer         OutputVectorImagePointerType;
    typedef typename OutputVectorImageType::RegionType      OutputVectorImageRegionType;
    typedef typename OutputVectorImageType::PixelType       OutputVectorImagePixelType;
    typedef typename OutputVectorImageType::IndexType       OutputVectorImageIndexType;
    typedef typename OutputVectorImageType::SizeType        OutputVectorImageSizeType;


    /** Iterators */
    typedef typename itk::ImageRegionConstIterator<InputDTMType>            DTMRegionConstIteratorType;
    typedef typename itk::ImageRegionConstIterator<InputImageType>          ImageRegionConstIteratorType;
    typedef typename itk::ImageRegionConstIterator<InputMaskType>           MaskRegionConstIteratorType;

    typedef typename itk::ImageRegionIterator<OutputVectorImageType>        VectorImageRegionIteratorType;


    // Input 0 -> transmitted to InternalSlopeCorrection
    vnsSetGetInputRawMacro( IPAOTS, InputImageType, 0)
    vnsSetGetInputRawMacro( DTMSub, InputDTMType, 1)
    vnsSetGetInputRawMacro( IPEDG, InputMaskType, 2)

    // Output
    OutputVectorImageType* GetTdir();

    // Output 1
    OutputVectorImageType* GetTdif();

    // Output 2
    OutputVectorImageType* GetT();

    // Output 3
    OutputVectorImageType* GetSatm();

    // LUTs accessors
    itkSetObjectMacro(LUT_Tdir,LUT3DType);
    itkSetObjectMacro(LUT_Tdif,LUT3DType);
    itkSetObjectMacro(LUT_Satm,LUT2DType);

    // Angle
    itkSetMacro(ThetaV, double);
    itkGetConstReferenceMacro(ThetaV, double);

    // NbOfBands
    itkSetMacro(NbOfBands, unsigned int);
    itkGetConstReferenceMacro(NbOfBands, unsigned int);


protected:
    /** Constructor */
    InterpolateForEnvCorrection();
    /** Destructor */
    virtual ~InterpolateForEnvCorrection();
    /** Validate the presence of all inputs. If at least one input
     * is missing, it throws an exception. */
    void BeforeThreadedGenerateData();
    /** Multi-thread version GenerateData. */
    void ThreadedGenerateData (const InputImageRegionType& outputRegionForThread, itk::ThreadIdType threadId);
    /** PrintSelf method */
    virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

private:
    InterpolateForEnvCorrection(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented


    // Direct Transmission LUT (3D)
    LUT3DPointerType m_LUT_Tdir;
    // Diffuse Transmission LUT (3D)
    LUT3DPointerType m_LUT_Tdif;
    // Atmorspheric albedo LUT (2D)
    LUT2DPointerType m_LUT_Satm;


    // Angle Theta V in degree
    double m_ThetaV;

    unsigned int m_NbOfBands;


};

} // End namespace vns
#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsInterpolateForEnvCorrection.txx"
#endif

#endif /* __vnsInterpolateForEnvCorrection_h */
