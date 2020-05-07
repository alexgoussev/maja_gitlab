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
from orchestrator.modules.maja_module import MajaModule
from orchestrator.common.maja_exceptions import *
import orchestrator.common.xml_tools as xml_tools
from orchestrator.common.constants import *
import os
LOGGER = configure_logger(__name__)


class MajaCirrusCorrection(MajaModule):
    """
    classdocs
    """
    NAME = "CirrusCorrection"

    def __init__(self):
        """
        Constructor
        """
        super(MajaCirrusCorrection, self).__init__()
        self.in_keys_to_check = ["Params.Caching", "AppHandler", "Plugin", "L1Reader","L2COMM", "DEM"]
        self.out_keys_to_check = []
        self.out_keys_provided = []
   
    def run(self, dict_of_input, dict_of_output):
        LOGGER.info("Cirrus Correction start")
        cirrus_working = dict_of_input.get("AppHandler").get_directory_manager().get_temporary_directory("CirrusCorrProc_",
                                            do_always_remove=True)
        refres_name = dict_of_input.get("Plugin").CirrusCorrectionReferenceResolution
        refres_idx = 9999
        bands_definition = dict_of_input.get("Plugin").BandsDefinitions
        for i in range(0, len(bands_definition.ListOfL2Resolution)):
            if bands_definition.ListOfL2Resolution[i] == refres_name:
                refres_idx = i
        # TODO test refres_idx
        result = {}
        ref_result = self._gamma_compute_at_res(dict_of_input, dict_of_output, refres_idx, cirrus_working)
        result[bands_definition.ListOfL2Resolution[refres_idx]] = ref_result
        if ref_result[2]:
            l_gammamean = ref_result[3] * ref_result[4]
            l_nbgamma = ref_result[3]
            for i in range(0, len(bands_definition.ListOfL2Resolution)):
                if bands_definition.ListOfL2Resolution[i] != refres_name:
                    res_result = self._gamma_compute_at_res(dict_of_input, dict_of_output, i, cirrus_working)
                    result[bands_definition.ListOfL2Resolution[i]] = res_result
                    l_gammamean = l_gammamean + res_result[3] * res_result[4]
                    l_nbgamma = l_nbgamma + res_result[3]
            l_gammamean = l_gammamean / l_nbgamma
            l_gamma_max = float(dict_of_input.get("L2COMM").get_value("CirrusCorrectionMaxGammaValue"))
            l_gamma_min = float(dict_of_input.get("L2COMM").get_value("CirrusCorrectionMinGammaValue"))
            # Boundary set for gamma
            if l_gammamean > l_gamma_max:
                l_gammamean = l_gamma_max
            if l_gammamean < l_gamma_min:
                l_gammamean = l_gamma_min

            LOGGER.info("Gamma : " + str(l_gammamean))

            # Apply correction
            for i in range(0, len(bands_definition.ListOfL2Resolution)):
                l_res = bands_definition.ListOfL2Resolution[i]
                corrected_toa = os.path.join(cirrus_working, "toac_" + l_res + ".tif")
                l_gammaswir = l_gammamean * float(
                    dict_of_input.get("L2COMM").get_value("CirrusCorrectionSWIRGammaFactor"))
                l_l2bandcodes = bands_definition.get_list_of_l2_band_code(l_res)
                swir_band_list = xml_tools.as_string_list(
                    dict_of_input.get("L2COMM").get_value("CirrusCorrectionSWIRBandCodes"))
                # Param of cirrus apply app
                param_cirrus_apply = {"l2toa": dict_of_output["AtmoAbsIPTOA_" + l_res],
                                      "l2edg": dict_of_input.get("L1Reader").get_value("L2EDGOutputList")[i],
                                      "l2dtm": dict_of_input.get("DEM").ALTList[i],
                                      "l2cirrus": result[l_res][0],
                                      "cirrusmask": result[l_res][1],
                                      "resolution": bands_definition.get_l1_resolution(l_res),
                                      "maxdistance": float(dict_of_input.get("L2COMM").get_value("CirrusCorrectionMaxDistance")),
                                      "thresholdgain": float(
                                          dict_of_input.get("L2COMM").get_value("CirrusMaskThresholdGain")),
                                      "thresholdoffset": float(
                                          dict_of_input.get("L2COMM").get_value("CirrusMaskThresholdOffset")),
                                      "thresholdfactor": float(
                                          dict_of_input.get("L2COMM").get_value("CirrusCorrectionThresholdFactor")),
                                      "gammamean": l_gammamean,
                                      "swirgammafactor": l_gammaswir,
                                      "maxreflectance": float(dict_of_input.get("L2COMM").get_value("CirrusMaxReflectance")),
                                      "bandcodelist": l_l2bandcodes,
                                      "swirbandcodelist": swir_band_list ,
                                      "correctedtoa": corrected_toa
                                      }
                app = OtbAppHandler("CirrusCorrectionApply", param_cirrus_apply, write_output=True)
                del(app)
                dict_of_output["L2TOA_" + l_res] = corrected_toa


        # return cirrus corrected flag
        dict_of_output["CirrusCorrected"] = ref_result[2]
        return ref_result[2]

    def _gamma_compute_at_res(self, dict_of_input, dict_of_output, p_res, p_working):
        bands_definition = dict_of_input.get("Plugin").BandsDefinitions
        l_res = bands_definition.ListOfL2Resolution[p_res]
        LOGGER.info("Cirrus gamma compute at res " + l_res + " start")

        # ---------- Resample L1 Cirrus to resolution ---------------
        l1cirrus_resampled = os.path.join(p_working, "toacirrus_" + l_res + ".tif")
        param_l1cirrus_resample = {"dtm": dict_of_input.get("DEM").ALTList[p_res],
                                   "im": dict_of_input.get("L1Reader").get_value("L1TOACirrusImage"),
                                   "interp": "bco",
                                   "out": l1cirrus_resampled
                                   }
        OtbAppHandler("Resampling", param_l1cirrus_resample, write_output=True)

        # ---------- Resample Cirrus cloud to resolution ---------------
        cld_cirrus_resampled = dict_of_output[CLOUD_MASK_CIRRUS + "_" + l_res]
        # ---------- Resample All cloud to resolution ---------------
        cld_all_resampled = dict_of_output[CLOUD_MASK_ALL + "_" + l_res]
        # ---------- Resample Refl cloud to resolution ---------------
        cld_refl_resampled = dict_of_output[CLOUD_MASK_REFL + "_" + l_res]

        # --------------------- Gamma compute for the resolution
        # construct band list
        gamm_band_list = xml_tools.as_string_list(dict_of_input.get(
            "L2COMM").get_value("CirrusCorrectionGammaBandCodes"))
        l_l2bandcodes = bands_definition.get_list_of_l2_band_code(l_res)
        l_resbandlist = []
        for i in range(0, len(l_l2bandcodes)):
            if l_l2bandcodes[i] in gamm_band_list:
                l_resbandlist.append(str(i))
        cirrus_mask = os.path.join(p_working, "cirrus_corr_mask_" + l_res + ".tif")
        param_gamma_compute = {"l2toa": dict_of_output["AtmoAbsIPTOA_" + l_res],
                               "l2edg": dict_of_input.get("L1Reader").get_value("L2EDGOutputList")[p_res],
                               "l2dtm": dict_of_input.get("DEM").ALTList[p_res],
                               "l2cirrus": param_l1cirrus_resample["out"],
                               "bandlist": l_resbandlist,
                               "cloudcirrus": cld_cirrus_resampled,
                               "cloudall": cld_all_resampled,
                               "cloudrefl": cld_refl_resampled,
                               "cirrusminpixinlist": int(dict_of_input.get("L2COMM").get_value("CirrusCorrectionMinPixInList")),
                               "mask": cirrus_mask + ":uint8"}
        gamma_compute_app = OtbAppHandler("GammaCompute", param_gamma_compute, write_output=True)

        return [l1cirrus_resampled, cirrus_mask, bool(gamma_compute_app.getoutput()["cirrusflag"]), len(l_resbandlist),
                float(gamma_compute_app.getoutput()["gamma"])]
