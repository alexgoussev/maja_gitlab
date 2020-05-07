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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 20 août 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: vnsInternalSlopeCorrectionImageFilterNew.cxx 3726 2012-01-26 08:20:23Z tfeuvrie $
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsLoggers.h"
#include "otbImageFileReader.h"
#include "vnsIncidenceAngleFunctor.h"
#include "itkBinaryFunctorImageFilter.h"


int vnsIncidenceAngleFunctorNew(int argc, char * argv [])
{
    if (argc != 1)
    {
        return EXIT_FAILURE;
    }

    // Configure Logger
    vns::Loggers::GetInstance()->Initialize(argv[0]);
    vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);


    typedef otb::Image<double,2>                        InputImageType;
    typedef InputImageType::PixelType                   InputImagePixelType;

    typedef otb::Image<double, 2>                       InternalIncidenceAngleImageType;
    typedef InternalIncidenceAngleImageType::PixelType  InternalIncidenceAnglePixelType;

    typedef vns::Functor::IncidenceAngleFunctor< InputImagePixelType, InputImagePixelType, InternalIncidenceAnglePixelType > IncidenceAngleFunctorType;
    typedef itk::BinaryFunctorImageFilter< InputImageType, InputImageType, InternalIncidenceAngleImageType, IncidenceAngleFunctorType> IncidenceAngleFilterType;
    typedef IncidenceAngleFilterType::Pointer IncidenceAngleFilterPointer;

    IncidenceAngleFilterPointer l_IncidenceAngleFilter = IncidenceAngleFilterType::New();

    return EXIT_SUCCESS;
}
