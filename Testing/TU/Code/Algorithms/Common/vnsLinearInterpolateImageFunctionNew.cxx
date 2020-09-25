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
/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkExpandImageFilterTest.cxx,v $
  Language:  C++
  Date:      $Date: 2009-05-19 18:31:17 $
  Version:   $Revision: 1.10 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <iostream>
#include "vnsLinearInterpolateImageFunction.h"
#include "otbVectorImage.h"


int vnsLinearInterpolateImageFunctionNew( int , char** )
{
  typedef double                      PixelType;
  typedef otb::VectorImage<PixelType> ImageType;
  typedef vns::LinearInterpolateImageFunction<ImageType> InterpolatorType;

  InterpolatorType::Pointer interpol = InterpolatorType::New();
  

  return EXIT_SUCCESS;

}
