/*
* Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
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
 * VERSION : 4-0-0 : DM : LAIG-DM-MAC-517-CNES : 11 février 2014 : Améliorations algorithmiques (Spec v2.1)	*
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: DirectionalCorrectionLUTCompute.h 2406 2011-01-19 15:38:23Z tfeuvrie $
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __DirectionalCorrectionLUTCompute_h
#define __DirectionalCorrectionLUTCompute_h

#include "itkObject.h"
#include "itkObjectFactory.h"

#include "otbMath.h"

#include "vnsMacro.h"
#include "vnsVectorLookUpTable.h"

namespace vns
{
/** \class  DirectionalCorrectionLUTCompute
 *
 * \author CS Systemes d'Information
 *
 * \sa Object
 *
 * \ingroup L2
 *
 */

class DirectionalCorrectionLUTCompute : public itk::Object
{
public:
    /** Standard class typedefs. */
    typedef DirectionalCorrectionLUTCompute                                Self;
    typedef itk::Object                                            Superclass;
    typedef itk::SmartPointer<Self>                                Pointer;
    typedef itk::SmartPointer<const Self>                          ConstPointer;

	typedef VNSLUT3DType                                    LUTType;
    typedef typename LUTType::ConstPointer                  ReducedLutConstPointerType;
    typedef typename LUTType::Pointer                       ReducedLutPointerType;
    typedef typename LUTType::PixelType                     ReducedLutPixelType;
	typedef typename LUTType::PointType           			ReducedLutPointType;
	typedef typename ReducedLutPointType::ValueType     	ReducedLutPointValueType;

	typedef std::vector<double>                      		DoubleVectType;

    /** Type macro */
    itkNewMacro(Self);
    /** Creation through object factory macro */
    itkTypeMacro(DirectionalCorrectionLUTCompute, Object );


    /**  Set the Solar Zenith value. */
    vnsSetMacro(SolarZenith, double)
    /**  Get the Solar Zenith value. */
    vnsGetConstMacro(SolarZenith, double)

    /**  Set the Solar Azimuth value. */
	vnsSetMacro(SolarAzimuth, double)
	/**  Get the Solar Azimuth value. */
	vnsGetConstMacro(SolarAzimuth, double)

	/**  Set the Reference Solar Zenith value. */
	vnsSetMacro(RefZenith, double)
	/**  Get the Reference Solar Zenith value. */
	vnsGetConstMacro(RefZenith, double)

	/**  Set the Reference Solar Azimuth value. */
	vnsSetMacro(RefAzimuth, double)
	/**  Get the Reference Solar Azimuh value. */
	vnsGetConstMacro(RefAzimuth, double)

	/** Set the LUT image */
	itkSetObjectMacro(LUT, LUTType)

	/** Set/Get the Viewing Zenith angles values */
	vnsSetMacro(MeanViewingZenithAngles, DoubleVectType)
	vnsGetConstMacro(MeanViewingZenithAngles, DoubleVectType)
	/** Set/Get the Viewing Azimuth angles values */
	vnsSetMacro(MeanViewingAzimuthAngles, DoubleVectType)
	vnsGetConstMacro(MeanViewingAzimuthAngles, DoubleVectType)

	/** Get the Directional correction coefficients */
	vnsGetConstMacro(CorrCoefs, DoubleVectType)

    void ComputeDirectionalCoeffs();


protected:
    /** Constructor */
    DirectionalCorrectionLUTCompute();
    /** Destructor */
    virtual ~DirectionalCorrectionLUTCompute();

    /** PrintSelf method */
    virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

private:
    DirectionalCorrectionLUTCompute(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented

    /**  Solar Zenith value */
    double m_SolarZenith;
    /**  Solar Azimuth value */
    double m_SolarAzimuth;
    /**  Ref Solar Zenith value */
	double m_RefZenith;
	/**  Ref Solar Azimtuh value */
	double m_RefAzimuth;

	/** Surface reflectance LUT */
	ReducedLutPointerType m_LUT;

	/** Viewing Zenith angles */
	DoubleVectType m_MeanViewingZenithAngles;
	/** Viewing Azimuth angles */
	DoubleVectType m_MeanViewingAzimuthAngles;
	/** Directional correction coefficients */
	DoubleVectType m_CorrCoefs;

};

} // End namespace vns

#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsDirectionalCorrectionLUTCompute.txx"
#endif

#endif /* __vnsDirectionalCorrectionLUTCompute_h */
