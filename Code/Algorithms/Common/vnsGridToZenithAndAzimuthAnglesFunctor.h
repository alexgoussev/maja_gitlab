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
 * HISTORIQUE                                                                                               *
 *                                                                                                          *
 * VERSION : 1.0.0 : FA : LAIG-FA-MAC-148399-CS : 03 novembre 2016 : Audit code - Correction qualite        *
 * MOD : VERSION : 1-0-0  : 23 nov. 2011 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id:
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsGridToZenithAndAzimuthAnglesFunctor_h
#define __vnsGridToZenithAndAzimuthAnglesFunctor_h

#include "vnsMath.h"

namespace vns
{
    /** \class  GridToZenithAndAzimuthAnglesFunctor
     * \brief This class implements .
     *
     *
     *
     * \author CS Systemes d'Information
     *
     * \sa ImageToImageFilter
     *
     * \ingroup L2
     * \ingroup L3
     * \ingroup Checktool
     *
     */
    namespace Functor
    {
        template<class TInputPixel, class TOutputPixel>
            class GridToZenithAndAzimuthAnglesFunctor
            {
            public:
                typedef GridToZenithAndAzimuthAnglesFunctor<TInputPixel, TOutputPixel> GridToZenithAndAzimuthAnglesFunctorType;

                GridToZenithAndAzimuthAnglesFunctor()
                {
                }

                virtual
                ~GridToZenithAndAzimuthAnglesFunctor()
                {
                }

                typedef TInputPixel InputPixelType;
                typedef TOutputPixel OutputPixelType;
                typedef typename OutputPixelType::ValueType OutputValueType;

                inline OutputPixelType
                operator()(InputPixelType inputPix) const
                {
                    // Set the output pixel value
                    OutputPixelType outPix;
                    outPix.SetSize(2);

                    // Computes the dv values
                    const double dv_x = static_cast<double> (inputPix[0]);
                    const double dv_y = static_cast<double> (inputPix[1]);

                    // Declares and init angles phi and theta
                    double phi(0.);
                    double theta(0.);

                    // If dv_y "zero"
                    if (vnsDifferentDoubleMacro(dv_y, 0.0) == true)
                    {
                        // Computes phi
                        phi = vcl_atan(dv_x / dv_y);
                        if (dv_y < 0.)
                        {
                            phi = phi + otb::CONST_PI;
                        }
                        if (phi < 0.)
                        {
                            phi = phi + otb::CONST_2PI;
                        }
                        // Computes theta
                        theta = vcl_atan(dv_y / vcl_cos(phi));
                        // Set the output pixel value
                        outPix[0] = static_cast<OutputValueType> (theta);
                        outPix[1] = static_cast<OutputValueType> (phi);
                    }
                    // dv_y non zero
                    else
                    {
                        if (vnsDifferentDoubleMacro(dv_x, 0.0) == true)
                        {
                            // Computes phi
                            if (dv_x > 0)
                            {
                                phi = otb::CONST_PI_2;
                            }
                            else
                            {
                                phi = -otb::CONST_PI_2;
                            }
                            // To keep phi between [0; 360]
                            if (phi < 0.)
                            {
                                phi = phi + otb::CONST_2PI;
                            }
                            // Computes theta
                            theta = vcl_atan(vcl_abs(dv_x));

                            // Set the output pixel value
                            outPix[0] = static_cast<OutputValueType> (theta);
                            outPix[1] = static_cast<OutputValueType> (phi);
                        }
                        else
                        {
                            // Set the output pixel value to default value
                            outPix[0] = 0;
                            outPix[1] = 0;
                        }
                    }

                    return outPix;
                }
            };
    }// end namespace functor

} // End namespace vns


#endif /* __vnsGridToZenithAndAzimuthAnglesFunctor_h */
