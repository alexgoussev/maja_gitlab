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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 18 mars 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: vnsReadGRIBImage.cxx 2961 2011-05-09 08:58:54Z tfeuvrie $
 *                                                                                                          *
 ************************************************************************************************************/

/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include <fstream>
#include <iostream>

#include "otbGenericRSTransform.h"
#include <ogr_spatialref.h>

int vnsGenericRSTransform(int itkNotUsed(argc), char* argv[])
{
  OGRSpatialReference oSRS;

  typedef otb::GenericRSTransform<>     TransformType;
  typedef TransformType::InputPointType PointType;

  PointType geoPoint;

  geoPoint[0] = atof(argv[1]);
  geoPoint[1] = atof(argv[2]);
  const char * outfname = argv[3];

  // Build wgs ref
  oSRS.SetWellKnownGeogCS("WGS84");
  char * wgsRef = NULL;
  oSRS.exportToWkt(&wgsRef);

  // Build UTM ref
  oSRS.SetProjCS("UTM");
  oSRS.SetUTM(31, true);
  char * utmRef = NULL;
  oSRS.exportToWkt(&utmRef);

  // Build Lambert II ref
  double stdParallel1  = 45.89891944;
  double stdParallel2  = 47.69601389;
  double originLatL2     = 46.8;
  double originLongL2    = 2.33722778;
  double falseEastingL2  = 600000;
  double falseNorthingL2 = 2200000;
  oSRS.SetProjCS("Lambert II ");
  oSRS.SetLCC(stdParallel1, stdParallel2, originLatL2, originLongL2, falseEastingL2, falseNorthingL2);
  char * lambertRef = NULL;
  oSRS.exportToWkt(&lambertRef);

  // Build the Transmercator ref
  double originLatTmt   = 49.83;
  double originLongTmt  = 6.16;

  oSRS.SetProjCS("Transmercator ");
  oSRS.SetWellKnownGeogCS("WGS84");
  oSRS.SetTM(originLatTmt, originLongTmt, 1, 0, 0);
  char * tmtRef = NULL;
  oSRS.exportToWkt(&tmtRef);

  TransformType::Pointer wgs2utm        = TransformType::New();
  wgs2utm->SetInputProjectionRef(wgsRef);
  wgs2utm->SetOutputProjectionRef(utmRef);
  wgs2utm->InstantiateTransform();

  TransformType::Pointer utm2wgs        = TransformType::New();
  wgs2utm->GetInverse(utm2wgs);

  TransformType::Pointer wgs2lambert    = TransformType::New();
  wgs2lambert->SetInputProjectionRef(wgsRef);
  wgs2lambert->SetOutputProjectionRef(lambertRef);
  wgs2lambert->InstantiateTransform();

  TransformType::Pointer lambert2wgs    = TransformType::New();
  wgs2lambert->GetInverse(lambert2wgs);

  TransformType::Pointer wgs2tmt        = TransformType::New();
  wgs2tmt->SetInputProjectionRef(wgsRef);
  wgs2tmt->SetOutputProjectionRef(tmtRef);
  wgs2tmt->InstantiateTransform();

  TransformType::Pointer tmt2wgs        = TransformType::New();
  wgs2tmt->GetInverse(tmt2wgs);

  TransformType::Pointer wgs2wgs        = TransformType::New();
  wgs2wgs->SetInputProjectionRef(wgsRef);
  wgs2wgs->SetOutputProjectionRef(wgsRef);
  wgs2wgs->InstantiateTransform();

  TransformType::Pointer utm2utm        = TransformType::New();
  utm2utm->SetInputProjectionRef(utmRef);
  utm2utm->SetOutputProjectionRef(utmRef);
  utm2utm->InstantiateTransform();

  TransformType::Pointer lambert2lambert = TransformType::New();
  lambert2lambert->SetInputProjectionRef(lambertRef);
  lambert2lambert->SetOutputProjectionRef(lambertRef);
  lambert2lambert->InstantiateTransform();

  TransformType::Pointer tmt2tmt        = TransformType::New();
  tmt2tmt->SetInputProjectionRef(tmtRef);
  tmt2tmt->SetOutputProjectionRef(tmtRef);
  tmt2tmt->InstantiateTransform();

  TransformType::Pointer utm2lambert    = TransformType::New();
  utm2lambert->SetInputProjectionRef(utmRef);
  utm2lambert->SetOutputProjectionRef(lambertRef);
  utm2lambert->InstantiateTransform();

  TransformType::Pointer lambert2utm    = TransformType::New();
  utm2lambert->GetInverse(lambert2utm);

  TransformType::Pointer utm2tmt        = TransformType::New();
  utm2tmt->SetInputProjectionRef(utmRef);
  utm2tmt->SetOutputProjectionRef(tmtRef);
  utm2tmt->InstantiateTransform();

  TransformType::Pointer tmt2utm        = TransformType::New();
  utm2tmt->GetInverse(tmt2utm);

  TransformType::Pointer lambert2tmt    = TransformType::New();
  lambert2tmt->SetInputProjectionRef(lambertRef);
  lambert2tmt->SetOutputProjectionRef(tmtRef);
  lambert2tmt->InstantiateTransform();

  TransformType::Pointer tmt2lambert    = TransformType::New();
  lambert2tmt->GetInverse(tmt2lambert);

  std::ofstream ofs;
  ofs.open(outfname);

  // Set floatfield to format writing properly
  ofs.setf(std::ios::fixed, std::ios::floatfield);
  ofs.precision(10);

  ofs << "Testing geopoint: " << geoPoint << std::endl << std::endl;

  ofs << "Testing wgs84 to wgs84: " << geoPoint << " -> " << wgs2wgs->TransformPoint(geoPoint) << std::endl;

  PointType utmPoint, lambertPoint, tmtPoint;

  utmPoint = wgs2utm->TransformPoint(geoPoint);
  lambertPoint = wgs2lambert->TransformPoint(geoPoint);
  tmtPoint = wgs2tmt->TransformPoint(geoPoint);

  ofs.precision(3);

  ofs << "Testing utm 31 north to utm 31 north: " << utmPoint << " -> " << utm2utm->TransformPoint(utmPoint) <<
  std::endl;
  ofs << "Testing lambert 2 to lambert 2: " << lambertPoint << " -> " <<
  lambert2lambert->TransformPoint(lambertPoint) << std::endl;
  ofs << "Testing transmercator 31 north to transmercator: " << tmtPoint << " -> " <<
  tmt2tmt->TransformPoint(tmtPoint) << std::endl;

  ofs << std::endl << "Testing geo 2 carto ..." << std::endl << std::endl;

  ofs.precision(10);

  ofs << "Testing wgs84 to utm 31 north: " << geoPoint;
  ofs.precision(3);
  ofs << " -> " << utmPoint << std::endl;
  ofs << "Testing utm 31 north to wgs84: " << utmPoint;
  ofs.precision(10);
  ofs << " -> " << utm2wgs->TransformPoint(utmPoint) << std::endl;

  ofs << "Testing wgs84 to lambert 2: " << geoPoint;
  ofs.precision(3);
  ofs << " -> " << lambertPoint << std::endl;
  ofs << "Testing lambert 2 to wgs84: " << lambertPoint;
  ofs.precision(10);
  ofs << " -> " << lambert2wgs->TransformPoint(lambertPoint) << std::endl;

  ofs << "Testing wgs84 to transmeractor: " << geoPoint;
  ofs.precision(3);
  ofs << " -> " << tmtPoint << std::endl;
  ofs << "Testing transmercator to wgs84: " << tmtPoint;
  ofs.precision(10);
  ofs << " -> " << tmt2wgs->TransformPoint(tmtPoint) << std::endl;

  ofs << std::endl << "Testing cross geo ..." << std::endl << std::endl;

  ofs.precision(3);

  ofs << "Testing lambert 2 to utm 31 north: " << lambertPoint << " -> " <<
  lambert2utm->TransformPoint(lambertPoint) << std::endl;
  ofs << "Testing utm 31 north to lambert 2: " << utmPoint << " -> " << utm2lambert->TransformPoint(utmPoint) <<
  std::endl;

  ofs << "Testing lambert 2 to transmercator: " << lambertPoint << " -> " <<
  lambert2tmt->TransformPoint(lambertPoint) << std::endl;
  ofs << "Testing transmercator to lambert 2: " << tmtPoint << " -> " << tmt2lambert->TransformPoint(tmtPoint) <<
  std::endl;

  ofs << "Testing transmercator to utm 31 north: " << tmtPoint << " -> " << tmt2utm->TransformPoint(tmtPoint) <<
  std::endl;
  ofs << "Testing utm 31 north to transmercator: " << utmPoint << " -> " << utm2tmt->TransformPoint(utmPoint) <<
  std::endl;

  ofs.close();

  return EXIT_SUCCESS;
}
