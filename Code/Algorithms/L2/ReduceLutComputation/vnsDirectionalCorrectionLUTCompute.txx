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
 ************************************************************************************************************/
#ifndef __vnsDirectionalCorrectionLUTCompute_txx
#define __vnsDirectionalCorrectionLUTCompute_txx

#include "vnsDirectionalCorrectionLUTCompute.h"
#include "vnsLoggers.h"

namespace vns
{

    // Constructor
    DirectionalCorrectionLUTCompute::DirectionalCorrectionLUTCompute() :
    	m_SolarZenith(0.), m_SolarAzimuth(0.), m_RefZenith(0.), m_RefAzimuth(0.)
    {
    }

    // Destructor
	
    DirectionalCorrectionLUTCompute::~DirectionalCorrectionLUTCompute()
    {
    }

    // Get sunglint distance
	
    void
    DirectionalCorrectionLUTCompute::ComputeDirectionalCoeffs()
    {
    	// Check LUT availability
		if (m_LUT.IsNull() == true)
		{
			vnsExceptionBusinessMacro("Waiting for a LUT, but no one specified. Please set one.");
		}

		// Get the number of band
        const unsigned int numberOfBand(m_MeanViewingZenithAngles.size());

		//Lut ExtractPoint
        ReducedLutPointType point;
        ReducedLutPointType pointRef;
        pointRef.Fill(0);

        point[0] = m_SolarZenith;
        point[1] = m_RefZenith;
        point[2] = m_RefAzimuth;
		pointRef[0] = m_SolarZenith;

		ReducedLutPixelType interpRefValue = m_LUT->InterpolateValue(pointRef);

		// Band loop
		for (unsigned int i = 0; i < numberOfBand; i++)
			{
			point[1] = m_MeanViewingZenithAngles[i];
			// Get the relative azimuth angle
			double deltaPhi = m_SolarAzimuth - m_MeanViewingAzimuthAngles[i];
            if (deltaPhi < 0.)
                {
                deltaPhi = -deltaPhi;
                }
            if (deltaPhi > 180.)
                {
                deltaPhi = 360 - deltaPhi;
                }

            point[2] = deltaPhi;

            ReducedLutPixelType interpValue = m_LUT->InterpolateValue(point);

            const float l_dirNorm = interpRefValue[i] / interpValue[i];

            // Set directional correction coefficients
            m_CorrCoefs.push_back(l_dirNorm) ;
			}
    }

	// PrintSelf method
	
	void
	DirectionalCorrectionLUTCompute::PrintSelf(std::ostream& os, itk::Indent indent) const
	{
		Superclass::PrintSelf(os, indent);

		os << "Solar Zenith value: " << m_SolarZenith << std::endl;
		os << "Solar Azimuth value: " << m_SolarAzimuth << std::endl;
		os << "Ref Zenith value: " << m_RefZenith << std::endl;
		os << "Ref Azimuth value: " << m_RefAzimuth << std::endl;

	}

} // End namespace vns

#endif /* __vnsDirectionalCorrectionLUTCompute_txx */
