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
orchestrator.common.file_utils -- shortdesc

orchestrator.common.file_utils is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from orchestrator.common.maja_utils import get_test_mode
import os
import shutil
from orchestrator.cots.otb.algorithms.otb_write_images import write_images
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_exceptions import MajaIOError

LOGGER = configure_logger(__name__)


# Copy a file to the directory
def otb_copy_file_to_directory(sourceFilename, destinationDir):
    destinationFilename = os.path.join(destinationDir, os.path.basename(sourceFilename))
    if not get_test_mode():
        if type(sourceFilename).__name__ == "SwigPyObject":
            write_images([sourceFilename], [destinationFilename])
        else:
            shutil.copyfile(sourceFilename, destinationFilename)
    else:
        with open(destinationFilename, 'a'):
            os.utime(destinationFilename, None)
    return destinationFilename


def otb_copy_image_to_file(source, dest, raise_exceptions=True):
    if not get_test_mode():
        if type(source).__name__ == "SwigPyObject":
            write_images([source], [dest])
        else:
            LOGGER.debug("source : " + source + " , dest : " + dest)
            try:
                shutil.copyfile(source, dest)
            except IOError as err:
                if raise_exceptions:
                    raise MajaIOError(err)
                else:
                    LOGGER.warn("Copy failed !!!")

    else:
        with open(dest, 'a'):
            os.utime(dest, None)
