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

orchestrator.common.interfaces.maja_xml_input -- shortdesc

orchestrator.common.interfaces.maja_xml_input is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


from lxml import etree as ET

from orchestrator.common.logger.maja_logging import configure_logger
LOGGER = configure_logger(__name__)


class MajaInternalXmlInput(object):
    """
    classdocs
    """

    def __init__(self, output_filename):
        """
        Constructor
        """
        if output_filename == "":
            self.only_print = True
        else:
            self.only_print = False
        self.output_filename = output_filename

    def write(self, root):
        """
        write method common to all internal interfaces
        """
        tree = ET.ElementTree(root)

        if self.only_print:
            LOGGER.info(ET.tostring(tree, pretty_print=True, xml_declaration=True, standalone='No',
                                    encoding="UTF-8").decode("utf-8"))
            return
        f = open(self.output_filename, "w")
        f.write(ET.tostring(tree, pretty_print=True, xml_declaration=True, standalone='No',
                            encoding="UTF-8").decode("utf-8"))
        f.close()
