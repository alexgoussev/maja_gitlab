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
 * VERSION : 2.1.0 : FA : LAIG-FA-MAJA-157185-CS : 9 mai 2017 : Correction de règles qualité                *
 * VERSION : 2.0.0 : DM : LAIG-DM-MAJA-2240-CNES : 30 mars 2017 : Retrait de log à l'execution de commande  *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/

#ifndef GDAL_LOG_INIT_CXX_
#define GDAL_LOG_INIT_CXX_


#include "cpl_error.h"
#include "vnsLoggers.h"
#include "vnsGDALLogInit.h"

void CPL_STDCALL CPLIPFErrorHandler( CPLErr eErrClass , int nError,
        const char * pszErrorMsg )

{
    if( eErrClass == CE_Debug )
    {
        vnsLogDebugMacro("GDAL Debug "<<nError<<" : "<<pszErrorMsg);
    }
    else
    {
        vnsLogDebugMacro("GDAL Error "<<nError<<" : "<<pszErrorMsg);
    }
}

void GDALInit()
{
    CPLSetErrorHandler(CPLIPFErrorHandler);
}

#endif
