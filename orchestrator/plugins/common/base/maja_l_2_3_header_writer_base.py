# -*- coding: utf-8 -*-
"""
###################################################################################################
#
#                        o     o
#                        oo   oo   oo        o   oo        ,-.
#                        o o o o  o  o       o  o  o       \_/
#                        o  o  o o    o      o o    o     |||)<
#                        o     o oooooo      o oooooo      / \
#                        o     o o    o o    o o    o      `-^
#                        o     o o    o  oooo  o    o
#
###################################################################################################

orchestrator.plugins.maja_dataset -- shortdesc

orchestrator.plugins.maja_dataset is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
from orchestrator.common.maja_exceptions import MajaNotYetImplemented
from orchestrator.common.logger.maja_logging import configure_logger

LOGGER = configure_logger(__name__)


class L23HeaderWriterBase(object):

    def __init__(self):
        self.plugin = None
        self.apphandler = None
        self.checkxmlfileswithschema = False
        self.outputfileclass = ""
        self.nodatavalue = ""
        self.creator = ""
        self.system = ""
        self.notes = ""
        self.listofgippsfilenames = []
        self.quicklookredbandcode = ""
        self.quicklookgreenbandcode = ""
        self.quicklookbluebandcode = ""
        self.adjacencyeffectsandslopecorrection = False
        self.cirruscorrection = False
        self.productisvalid = False
        self.reflectancequantificationvalue = 0

    def write(self):
        raise MajaNotYetImplemented("Could not instanciate base class")
