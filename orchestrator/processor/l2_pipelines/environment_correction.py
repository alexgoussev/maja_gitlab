# -*- coding: utf-8 -*-
"""
###################################################################################################
#
#                        o     o
#                        oo   oo   oo        o   oo        ,-.
#                        o o o o  o  o       o  o  o       \_/
#                        o  o  o o    o      o o    o     {|||)<
#                        o     o oooooo      o oooooo      / \
#                        o     o o    o o    o o    o      `-^
#                        o     o o    o  oooo  o    o
#
###################################################################################################

orchestrator.processor.base_processor -- shortdesc

orchestrator.processor.base_processor is the base of all processors

It defines method mandatory for a processor

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.cots.otb.algorithms.otb_extract_roi import extract_roi
from orchestrator.cots.otb.algorithms.otb_write_images import write_images
from orchestrator.modules.maja_module import MajaModule
from orchestrator.common.maja_exceptions import *
import os
LOGGER = configure_logger(__name__)


class MajaEnvCorr(MajaModule):
    """
    classdocs
    """

    NAME = "EnvironmentCorrection"

    def __init__(self):
        """
        Constructor
        """
        super(MajaEnvCorr, self).__init__()
        self.in_keys_to_check = ["Params.Caching", "AppHandler", "Plugin", "L1Reader","L2COMM", "DEM",
                                 "L2DIRT", "L2DIFT", "L2ALBD", "Params.RealL2NoData"]
        self.out_keys_to_check = ["TOC_sub", "AOT_Sub"]
        self.out_keys_provided = ["SRE_List"]

    def run(self, dict_of_input, dict_of_output):
        LOGGER.info("Environment Correction start")
        env_working = dict_of_input.get("AppHandler").get_directory_manager().get_temporary_directory("EnvoCorrProc_",
                                            do_always_remove=True)
        l_envcorradius = dict_of_input.get("L2COMM").get_value_f("EnvCorrRadius")
        l_envcorsize = (2 * l_envcorradius + 1) * (2 * l_envcorradius + 1)
        caching = dict_of_input.get("Params").get("Caching")
        # Compute rho env sub
        rhoenv_sub_image = os.path.join(env_working, "rhoenv_sub.tif")
        param_computerho = {"toc": dict_of_output["TOC_sub"],
                            "edg": dict_of_input.get("L1Reader").get_value("IPEDGSubOutput"),
                            "radius": l_envcorradius,
                            "filtercoeff": 1.0 / l_envcorsize,
                            "rhoenv": rhoenv_sub_image}
        computerho_app = OtbAppHandler("ComputeRhoEnv", param_computerho, write_output=True)

        # Interpolate for env
        tdif_filename = os.path.join(env_working, "tdif_sub.tif")
        tdir_filename = os.path.join(env_working, "tdir_sub.tif")
        albd_filename = os.path.join(env_working, "albd_sub.tif")
        param_interpolate = {"luttdir": dict_of_input.get("L2DIRT"),
                             "luttdif": dict_of_input.get("L2DIFT"),
                             "lutalbd": dict_of_input.get("L2ALBD"),
                             "aot": dict_of_output["AOT_Sub"],
                             "dtm": dict_of_input.get("DEM").ALC,
                             "edg": dict_of_input.get("L1Reader").get_value("IPEDGSubOutput"),
                             "thetav": dict_of_input.get(
                                 "L1Info").ListOfViewingZenithAnglesPerBandAtL2CoarseResolution,
                             "tdir": tdir_filename,
                             "tdif": tdif_filename,
                             "albd": albd_filename
                             }
        interpolate_app = OtbAppHandler("InterpolateForEnvCorr", param_interpolate, write_output=True)
        tdif_image = interpolate_app.getoutput()["tdif"]
        tdir_image = interpolate_app.getoutput()["tdir"]
        albd_image = interpolate_app.getoutput()["albd"]
        # Compute env corr for each l2 resolution
        bands_definition = dict_of_input.get("Plugin").BandsDefinitions
        l_nbRes = len(bands_definition.ListOfL2Resolution)
        sre_list = []
        for r in range(0, l_nbRes):
            l_res = bands_definition.ListOfL2Resolution[r]
            l_l2bandcodes = bands_definition.get_list_of_l2_band_code(l_res)
            l_l2bandidx = [bands_definition.get_band_id_in_l2_coarse(b) for b in l_l2bandcodes]
            tdifl2_filename = os.path.join(env_working, "tdif_" + l_res + ".tif")
            tdirl2_filename = os.path.join(env_working, "tdir_" + l_res + ".tif")
            albdl2_filename = os.path.join(env_working, "albd_" + l_res + ".tif")
            rhoenvl2_filename= os.path.join(env_working, "rhoenv_extract_" + l_res + ".tif")
            # Extract tdif
            tdifl2_image_app = extract_roi(tdif_image, l_l2bandidx, tdifl2_filename, write_output=False)
            # Extract tdir
            tdirl2_image_app = extract_roi(tdir_image, l_l2bandidx, tdirl2_filename, write_output=False)
            # Extract albd
            albdl2_image_app = extract_roi(albd_image, l_l2bandidx, albdl2_filename, write_output=False)
            # Extract rhoenv_sub
            rhoenvl2_image_app = extract_roi(rhoenv_sub_image, l_l2bandidx, rhoenvl2_filename, write_output=False)

            rhoenv_image = os.path.join(env_working, "rhoenv_" + l_res + ".tif")
            sre_image = os.path.join(env_working, "sre_" + l_res + ".tif")

            # Compute env correction
            param_envcorr = {"tdir": tdirl2_image_app.getoutput()["out"],
                             "tdif": tdifl2_image_app.getoutput()["out"],
                             "albd": albdl2_image_app.getoutput()["out"],
                             "rhoenvsub": rhoenvl2_image_app.getoutput()["out"],
                             "nodata": dict_of_input.get("Params").get("RealL2NoData"),
                             "ram": str(OtbAppHandler.ram_to_use/4),
                             "toc": dict_of_output["TOC_" + l_res],
                             "edg": dict_of_input.get("L1Reader").get_value("L2EDGOutputList")[r],
                             "sre": sre_image,
                             "rhoenv": rhoenv_image
                             }
            envcorr_app = OtbAppHandler("EnvCorrection", param_envcorr, write_output=False)
            write_images([envcorr_app.getoutput().get("sre"), envcorr_app.getoutput().get("rhoenv")],
                         [sre_image, rhoenv_image])
            dict_of_output["SRE_" + l_res] = sre_image
            dict_of_output["RhoEnv_" + l_res] = rhoenv_image
            sre_list.append(sre_image)
        dict_of_output["SRE_List"] = sre_list

