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
orchestrator.launcher.maja -- shortdesc

orchestrator.launcher.maja is the entry point of Maja

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

import shutil
from orchestrator.launcher.app_handler import AppHandler
from orchestrator.processor.base_processor import BaseProcessor
from orchestrator.processor.l2_init_processor import L2InitProcessor
from orchestrator.processor.l2_nominal_processor import L2NominalProcessor
from orchestrator.processor.l2_backward_processor import L2BackwardProcessor
from orchestrator.plugins.common.factory.plugin_activate import register_all
from orchestrator.common.maja_exceptions import MajaProcessingError
from orchestrator.common.logger.maja_logging import configure_logger
LOGGER = configure_logger(__name__)
import subprocess


def main():
    register_all()

    app_handler = AppHandler()
    app_handler.initialize()

    processorName = app_handler.get_processor_name()
    if processorName == AppHandler.MAJA_L2_INIT_CHAIN:
        lprocessor = L2InitProcessor(app_handler)
    elif processorName == AppHandler.MAJA_L2_NOMINAL_CHAIN:
        lprocessor = L2NominalProcessor(app_handler)
    elif processorName == AppHandler.MAJA_L2_BACKWARD_CHAIN:
        lprocessor = L2BackwardProcessor(app_handler)
    elif processorName == AppHandler.MAJA_L3_CHAIN:
        lprocessor = BaseProcessor(app_handler)
    elif processorName == AppHandler.MAJA_L1_CHECKTOOL_CHAIN:
        lprocessor = BaseProcessor(app_handler)
    elif processorName == AppHandler.MAJA_L2_CHECKTOOL_CHAIN:
        lprocessor = BaseProcessor(app_handler)
    elif processorName == AppHandler.MAJA_L3_CHECKTOOL_CHAIN:
        lprocessor = BaseProcessor(app_handler)
    else:
        raise MajaProcessingError(
            "Error during initialization of the DataApplication handler : The processor name <%s> is incorrect !" %
            processorName)

    LOGGER.info("Launching processor : " + lprocessor.get_name())

    lprocessor.pre_processing()
    lprocessor.scientific_processing()
    lprocessor.post_processing()

    if app_handler.get_user_conf().get_Computing().get_EnableCleaningTemporaryDirectory():
        LOGGER.info("Cleaning Temporary datas ...")

        app_handler.get_directory_manager().clean(all=True)
        subprocess.call(
            ["lsof", "+D", str(app_handler.get_working_directory())])

        shutil.rmtree(app_handler.get_working_directory())
        LOGGER.info("Cleaning Temporary datas : Done")

    LOGGER.info("Process ok")
    return


if __name__ == "__main__":
    main()
