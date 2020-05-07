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
 * VERSION : 1-0-3 : DM : 310 : 13 septembre 2011 : Creation                                                *
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id: vnsUtilitiesUTCDate.cxx 3205 2011-09-14 17:16:24Z tfeuvrie $
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsUtilities.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "vcl_cmath.h"
#include <iterator>
#include <algorithm>

int
vnsUtilitiesTesting(int /*argc*/, char * /*argv*/[])
{
//    if (argc < 3)
//    {
//        std::cout << "Usage   : " << argv[0] << " UTCDate outputJulianDay" << std::endl;
//        return EXIT_FAILURE;
//    }

    vns::Utilities::SetEnv("TOTO", "DEDE");
    std::cout << vns::Utilities::GetEnv("TOTO")<< std::endl;

    vns::Utilities::ListOfStrings l_LTCProductMHAFilename;
    vns::Utilities::ListOfStrings l_LTCProductMHAFilenameInDisc;

    l_LTCProductMHAFilenameInDisc.push_back("1");
    l_LTCProductMHAFilenameInDisc.push_back("2");
    l_LTCProductMHAFilenameInDisc.push_back("3");
    l_LTCProductMHAFilenameInDisc.push_back("8");
    l_LTCProductMHAFilenameInDisc.push_back("7");
    l_LTCProductMHAFilenameInDisc.push_back("0");
    l_LTCProductMHAFilenameInDisc.push_back("9");

    l_LTCProductMHAFilename.push_back("3");
    l_LTCProductMHAFilename.push_back("8");
    l_LTCProductMHAFilename.push_back("7");


    std::sort(l_LTCProductMHAFilename.begin(),  l_LTCProductMHAFilename.end());
    std::sort(l_LTCProductMHAFilenameInDisc.begin(),  l_LTCProductMHAFilenameInDisc.end());
    vns::Utilities::ListOfStrings l_DeltaMha;
    std::set_difference(l_LTCProductMHAFilenameInDisc.begin(),  l_LTCProductMHAFilenameInDisc.end(), l_LTCProductMHAFilename.begin(),  l_LTCProductMHAFilename.end(), std::back_inserter(l_DeltaMha));

    vns::Utilities::PrintVector("l_LTCProductMHAFilename", l_LTCProductMHAFilename, std::cout);
    vns::Utilities::PrintVector("l_LTCProductMHAFilenameInDisc", l_LTCProductMHAFilenameInDisc, std::cout);
    vns::Utilities::PrintVector("l_DeltaMha", l_DeltaMha, std::cout);

    return EXIT_SUCCESS;
}
