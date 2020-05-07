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
