# -*- coding: utf-8 -*-
"""
###################################################################################################

                        o     o
                        oo   oo   oo        o   oo        ,-.
                        o o o o  o  o       o  o  o       \_/
                        o  o  o o    o      o o    o     {|||D
                        o     o oooooo      o oooooo      / \
                        o     o o    o o    o o    o      `-^
                        o     o o    o  oooo  o    o

###################################################################################################

orchestrator.tests.plugins.test_maja_sentinel2_l1_pimage_file_reader -- shortdesc

orchestrator.tests.plugins.test_maja_sentinel2_l1_pimage_file_reader is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from __future__ import absolute_import
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.gipp_utils import *

import glob

def set_input_l2_writer(input_dir, dict_img):

    # Set input images
    sre_list = []
    fre_list = []
    l2sat_list = []
    l2stl_list = []
    l2tgs_list = []
    l2aot_list = []
    l2tao_list = []
    l2vap_list = []
    l2iwc_list = []
    l2pix_list = []
    l2edg_list = []
    l2cld_list = []
    dfp_list = []

    os.chdir(input_dir)

    for file in os.listdir(input_dir):
        if file.endswith('.mha') :
            dict_img["ltc"] = os.path.join(input_dir, file)
            break
        else:
            dict_img["ltc"] = None

    if os.path.isfile(os.path.join(input_dir, 'apTuCLAImage.tif')):
        dict_img["cla"] = os.path.join(input_dir + 'apTuCLAImage.tif')
    else:
        dict_img["cla"] = None

    if os.path.isfile(os.path.join(input_dir, 'apTuSNWImage.tif')):
        dict_img["snow"] = os.path.join(input_dir + 'apTuSNWImage.tif')
    else:
        dict_img["snow"] = None

    if os.path.isfile(os.path.join(input_dir, 'apTuSHDImage.tif')):
        try:
            dict_img["dtm_shd"] = os.path.join(input_dir + 'apTuSHDImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuSHDImageList.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuHIDImage.tif')):
        try:
            dict_img["dtm_hid"] = os.path.join(input_dir + 'apTuHIDImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuHIDImage.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuWASImage.tif')):
        try:
            dict_img["was"] = os.path.join(input_dir + 'apTuWASImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuWASImage.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuPWAImage.tif')):
        try:
            dict_img["pwa"] = os.path.join(input_dir + 'apTuPWAImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuPWAImage.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuTWAImage.tif')):
        try:
            dict_img["twa"] = os.path.join(input_dir + 'apTuTWAImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuTWAImage.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuRTAImage.tif')):
        try:
            dict_img["rta_composite"] = os.path.join(input_dir + 'apTuRTAImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuRTAImage.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuRTCImage.tif')):
        try:
            dict_img["rtc_composite"] = os.path.join(input_dir + 'apTuRTCImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuRTCImage.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuRCRImage.tif')):
        try:
            dict_img["rcr_composite"] = os.path.join(input_dir + 'apTuRCRImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuRCRImage.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuSTOImage.tif')):
        try:
            dict_img["sto_composite"] = os.path.join(input_dir + 'apTuSTOImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuSTOImage.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuPXDImage.tif')):
        try:
            dict_img["pxd_composite"] = os.path.join(input_dir + 'apTuPXDImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuPXDImage.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuNDTImage.tif')):
        try:
            dict_img["ndt_composite"] = os.path.join(input_dir + 'apTuNDTImage.tif')
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuNDTImage.tif')) + "doesn't exist ! ")

    l2cld_img_R1 = [os.path.join(input_dir, 'apTuL2CLDImage_R1_1.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R1_2.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R1_3.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R1_4.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R1_5.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R1_6.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R1_7.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R1_8.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R1_9.tif')]

    l2cld_img_R2 = [os.path.join(input_dir, 'apTuL2CLDImage_R2_1.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R2_2.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R2_3.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R2_4.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R2_5.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R2_6.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R2_7.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R2_8.tif'),
                    os.path.join(input_dir, 'apTuL2CLDImage_R2_9.tif')]

    if all(os.path.isfile(l2cld_img_R1[i]) for i in range(0, len(l2cld_img_R1) - 1)):
        try:
            l2cld_list.append(l2cld_img_R1)
            if all(os.path.isfile(l2cld_img_R2[i]) for i in range(0, len(l2cld_img_R2) - 1)):
                l2cld_list.append(l2cld_img_R2)

        except FileNotFoundError:
            LOGGER.debug("Missing one image of L2 CLD image list ! ")


    tmp_cld = [os.path.join(input_dir, 'apTuCLDImage_1.tif'),
                   os.path.join(input_dir, 'apTuCLDImage_2.tif'),
                   os.path.join(input_dir, 'apTuCLDImage_3.tif'),
                   os.path.join(input_dir, 'apTuCLDImage_4.tif'),
                   os.path.join(input_dir, 'apTuCLDImage_5.tif'),
                   os.path.join(input_dir, 'apTuCLDImage_6.tif'),
                   os.path.join(input_dir, 'apTuCLDImage_7.tif'),
                   os.path.join(input_dir, 'apTuCLDImage_8.tif'),
                   os.path.join(input_dir, 'apTuCLDImage_9.tif')]
    if all(os.path.isfile(tmp_cld[i]) for i in range(0, len(tmp_cld) - 1)):
        try:
            dict_img["CLD_List"] = tmp_cld
        except FileNotFoundError:
            LOGGER.debug("Missing one image of CLD image list ! ")



    if os.path.isfile(os.path.join(input_dir, 'apTuSREImageList_R1.tif')):
        try:
            sre_list.append(os.path.join(
                input_dir, 'apTuSREImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuSREImageList_R2.tif')):
                sre_list.append(os.path.join(
                    input_dir, 'apTuSREImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuSREImageList.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuFREImageList_R1.tif')):
        try:
            fre_list.append(os.path.join(
                input_dir, 'apTuFREImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuFREImageList_R2.tif')):
                fre_list.append(os.path.join(
                    input_dir, 'apTuFREImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuFREImageList.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuL2SATImageList_R1.tif')):
        try:
            l2sat_list.append(os.path.join(
                input_dir, 'apTuL2SATImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2SATImageList_R2.tif')):
                l2sat_list.append(os.path.join(
                    input_dir, 'apTuL2SATImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuSATImageList.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuL2STLImageList_R1.tif')):
        try:
            l2stl_list.append(os.path.join(
                input_dir, 'apTuL2STLImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2STLImageList_R2.tif')):
                l2stl_list.append(os.path.join(
                    input_dir, 'apTuL2STLImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuSTLImageList.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuL2TGSImageList_R1.tif')):
        try:
            l2tgs_list.append(os.path.join(
                input_dir, 'apTuL2TGSImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2TGSImageList_R2.tif')):
                l2tgs_list.append(os.path.join(
                    input_dir, 'apTuL2TGSImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuTGSImageList.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuL2AOTImageList_R1.tif')):
        try:
            l2aot_list.append(os.path.join(
                input_dir, 'apTuL2AOTImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2AOTImageList_R2.tif')):
                l2aot_list.append(os.path.join(
                    input_dir, 'apTuL2AOTImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuL2AOTImageList_R1.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuL2TAOImageList_R1.tif')):
        try:
            l2tao_list.append(os.path.join(
                input_dir, 'apTuL2TAOImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2TAOImageList_R2.tif')):
                l2tao_list.append(os.path.join(
                    input_dir, 'apTuL2TAOImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuL2TAOImageList_R1.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuL2VAPImageList_R1.tif')):
        try:
            l2vap_list.append(os.path.join(
                input_dir, 'apTuL2VAPImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2VAPImageList_R2.tif')):
                l2vap_list.append(os.path.join(
                    input_dir, 'apTuL2VAPImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuL2VAPImageList_R1.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuL2IWCImageList_R1.tif')):
        try:
            l2iwc_list.append(os.path.join(
                input_dir, 'apTuL2IWCImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2IWCImageList_R2.tif')):
                l2iwc_list.append(os.path.join(
                    input_dir, 'apTuL2IWCImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuL2IWCImageList_R1.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuL2PIXImageList_R1.tif')):
        try:
            l2pix_list.append(os.path.join(
                input_dir, 'apTuL2PIXImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2PIXImageList_R2.tif')):
                l2pix_list.append(os.path.join(
                    input_dir, 'apTuL2PIXImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuL2PIXImageList_R1.tif')) + "doesn't exist ! ")


    if os.path.isfile(os.path.join(input_dir, 'apTuL2EDGImageList_R1.tif')):
        try:
            l2edg_list.append(os.path.join(
                input_dir, 'apTuL2EDGImageList_R1.tif'))
            if os.path.isfile(os.path.join(input_dir, 'apTuL2EDGImageList_R2.tif')):
                l2edg_list.append(os.path.join(
                    input_dir, 'apTuL2EDGImageList_R2.tif'))
        except FileNotFoundError:
            LOGGER.debug("The file " + os.path.basename(
                os.path.join(input_dir, 'apTuL2EDGImageList_R1.tif')) + "doesn't exist ! ")

    if os.path.isfile(os.path.join(input_dir, 'apTuL2DFPImageList_R1.tif')):
        dfp_list.append(os.path.join(
            input_dir, 'apTuL2DFPImageList_R1.tif'))
        if os.path.isfile(os.path.join(input_dir, 'apTuL2DFPImageList_R2.tif')):
            dfp_list.append(os.path.join(
                    input_dir, 'apTuL2DFPImageList_R2.tif'))

    dict_img["SRE_List"] = sre_list
    dict_img["FRE_List"] = fre_list
    dict_img["L2SAT_List"] = l2sat_list
    dict_img["L2STL_List"] = l2stl_list
    dict_img["L2TGS_List"] = l2tgs_list
    dict_img["L2AOT_List"] = l2aot_list
    dict_img["L2TAO_List"] = l2tao_list
    dict_img["L2VAP_List"] = l2vap_list
    dict_img["L2IWC_List"] = l2iwc_list
    dict_img["L2PIX_List"] = l2pix_list
    dict_img["L2EDG_List"] = l2edg_list
    dict_img["L2CLD_List"] = l2cld_list
    dict_img["L2DFP_List"] = dfp_list

    LOGGER.debug(dict_img["SRE_List"] )
    LOGGER.debug(dict_img["FRE_List"])
    LOGGER.debug(dict_img["L2SAT_List"])
    LOGGER.debug(dict_img["L2STL_List"])
    LOGGER.debug(dict_img["L2TGS_List"])
    LOGGER.debug(dict_img["L2AOT_List"])
    LOGGER.debug(dict_img["L2VAP_List"])
    LOGGER.debug(dict_img["L2IWC_List"])
    LOGGER.debug(dict_img["L2PIX_List"])
    LOGGER.debug(dict_img["L2EDG_List"])
    LOGGER.debug(dict_img["L2CLD_List"])
    LOGGER.debug(dict_img["L2DFP_List"])



