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
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 9 avr. 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "vnsProcessingMode.h"

int vnsProcessingModeTest(int /*argc*/, char * /*argv*/ [])
{
    vns::ProcessingMode filter;

    filter.SetMode(vns::ProcessingMode::INIT);
    if (!filter.IsInit()) return EXIT_FAILURE;
    if (filter.IsNotInit()) return EXIT_FAILURE;
    if (filter.IsNominal()) return EXIT_FAILURE;
    if (!filter.IsNotNominal()) return EXIT_FAILURE;
    filter.SetBackwardMode(false);
    if (filter.IsBackward()) return EXIT_FAILURE;
    if (!filter.IsNotBackward()) return EXIT_FAILURE;
    filter.SetBackwardMode(true);
    if (!filter.IsBackward()) return EXIT_FAILURE;
    if (filter.IsNotBackward()) return EXIT_FAILURE;

    filter.SetMode(vns::ProcessingMode::NOMINAL);
    if (filter.IsInit()) return EXIT_FAILURE;
    if (!filter.IsNotInit()) return EXIT_FAILURE;
    if (!filter.IsNominal()) return EXIT_FAILURE;
    if (filter.IsNotNominal()) return EXIT_FAILURE;
    filter.SetBackwardMode(false);
    if (filter.IsBackward()) return EXIT_FAILURE;
    if (!filter.IsNotBackward()) return EXIT_FAILURE;
    filter.SetBackwardMode(true);
    if (!filter.IsBackward()) return EXIT_FAILURE;
    if (filter.IsNotBackward()) return EXIT_FAILURE;


    return EXIT_SUCCESS;
}
