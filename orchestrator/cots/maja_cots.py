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

orchestrator.cots.maja_cots -- shortdesc

orchestrator.cots.maja_cots is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


from orchestrator.common.system_utils import launch_command
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_exceptions import MajaProcessingError

LOGGER = configure_logger(__name__)


class MajaCots(object):
    """
    classdocs
    """

    def __init__(self, working_directory):
        """
        Constructor
        """
        self.working_directory = working_directory
        self.command_line = []
        self.env = {}
        self.status = 0
        self.output_std = ""
        self.output_err = ""

    def run(self):
        """
        Run self.command_line
        """
        LOGGER.info("Running %s", self.command_line)

        # TODO: TBC use append env or manage entire env for each COTS ?
        self.status = launch_command(self.command_line)

        # TODO: TBC MOve status to post ?
        # TODO: see status management by system command executor
        if self.status != 0:
            raise MajaProcessingError("Error running {}. Exit code {}.".format(self.command_line, self.status))
