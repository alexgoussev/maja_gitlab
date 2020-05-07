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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 24 mars 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/

#if defined(_MSC_VER)
   //Warning about: identifier was truncated to '255' characters in the debug information (MVC6.0 Debug)
#pragma warning( disable : 4786 )
#endif

#include <iostream>
#include "vnsLookUpTable.h"
#include "otbMath.h"

int vnsLookUpTableLUTInterpolation( int /*argc*/, char * argv[] )
{
    std::cout << "Testing vns::LookUpTable interpolation" << std::endl;

    // Configure Logger
    vns::Loggers::GetInstance()->Initialize(argv[0]);
    vns::Loggers::GetInstance()->SetMinLevel(vns::LoggerBase::DEBUG);

    typedef double TValue;
    typedef vns::LookUpTable<TValue, 3> LUTType;

    LUTType::Pointer R_TestLUT = LUTType::New();


    std::cout << "First parameter : ThetaS" << std::endl;
    LUTType::ParameterValuesType values;
    values.ParameterName = "ThetaS";
    values.ParameterValues.push_back(0.0000);
    values.ParameterValues.push_back(0.0800);
    values.ParameterValues.push_back(0.1600);
    values.ParameterValues.push_back(0.2400);
    R_TestLUT->AddParameterValues(values);

    std::cout << "Second parameter : ThetaV" << std::endl;
    values.ParameterName = "ThetaV";
    values.ParameterValues.clear();
    values.ParameterValues.push_back(0.2500);
    values.ParameterValues.push_back(0.3125);
    values.ParameterValues.push_back(0.3750);
    values.ParameterValues.push_back(0.4375);
    R_TestLUT->AddParameterValues(values);

    std::cout << "Third parameter : DeltaPHI" << std::endl;
    values.ParameterName = "DeltaPHI";
    values.ParameterValues.clear();
    values.ParameterValues.push_back(0.0);
    values.ParameterValues.push_back(30.0);
    values.ParameterValues.push_back(60.0);
    values.ParameterValues.push_back(90.0);
    R_TestLUT->AddParameterValues(values);


    // Load values
    LUTType::ParametersValuesType getValues;
    getValues = R_TestLUT->GetParametersValues();

    int size[getValues.size()];
    for (unsigned int i = 0; i < getValues.size(); i++)
    {
        size[i] = getValues[i].ParameterValues.size();
    }

    // Parcours de la LUT et chargement
    LUTType::IndexType lutIndex;
    for (int i = 0; i < size[0]; i++)
      {
        lutIndex[0] = i;
        for (int j = 0; j < size[1]; j++)
          {
            lutIndex[1] = j;
            for (int k = 0; k < size[2]; k++)
              {
                lutIndex[2] = k;
                // Compute value (constant in miniLUT for test)
                TValue value = 100 * i + 10 * j + k;
                R_TestLUT->SetValue(lutIndex, value);
              }
          }
      }

    lutIndex[0] = 1;
    lutIndex[1] = 2;
    lutIndex[2] = 3;
    std::cout << "Value[1][2][3] = " << R_TestLUT->GetValue(lutIndex) << std::endl;

    // Interpolation
    LUTType::PointType point;
    point[0] = 0.120;
    point[1] = 0.34375;
    point[2] = 45.0;

    TValue interp = R_TestLUT->InterpolateValue(point);
    std::cout << "Value" << point << " = " << interp << std::endl;

    if (vcl_abs(interp - 166.5) > 1e-4)
    {
        std::cout << "ERROR : Value" << point << " = " << interp << " != 166,5" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
