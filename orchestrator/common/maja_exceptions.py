# -*- coding: utf-8 -*-
#
# Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
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
orchestrator.common.maja_exceptions -- shortdesc

orchestrator.common.maja_exceptions is a description

It defines classes_and_methods


###################################################################################################
"""

import orchestrator.common.maja_exit_codes as maja_exit_codes


class MajaException(Exception):
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_BASE_ERROR
        super(MajaException, self).__init__(type(self).__name__ + " : " + msg)

    def get_exit_code(self):
        return self._exit_code


class MajaProcessingException(MajaException):
    """
    Exception raised by the main program
    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PROCESSING_ERROR
        super(MajaProcessingException, self).__init__(msg)


class MajaDataException(MajaException):
    """
    Exception raised when there is a problem to find a file
    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_DATA_ERROR
        super(MajaDataException, self).__init__(msg)


class MajaDataMissingAngleException(MajaException):
    """
        Exception raised when there is a problem to find a file
        """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_DATA_MISSING_ANGLES_ERROR
        super(MajaDataMissingAngleException, self).__init__(msg)


class MajaChainException(MajaException):
    """
    Exception raised when there is a problem in a chain
    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_CHAIN_ERROR
        super(MajaChainException, self).__init__(msg)


class MajaModuleException(MajaException):
    """
    Exception raised when there is a problem in a module
    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_MODULE_ERROR
        super(MajaModuleException, self).__init__(msg)


class MajaFactoryException(MajaException):
    """
    Exception raised when there is a problem in a module
    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_FACTORY_ERROR
        super(MajaFactoryException, self).__init__(msg)


class MajaNotYetImplementedException(MajaException):
    """
    Exception raised when entering a not yet implemented functionality
    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_NOT_IMPLEMENTED_ERROR
        super(MajaNotYetImplementedException, self).__init__(msg)


class MajaIOException(MajaDataException):
    """
    Exception raised when there is a problem to read or write a file
    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_IO_ERROR
        super(MajaIOException, self).__init__(msg)


class MajaAlgorithmException(MajaException):
    """
    Exception raised when there is a problem to read or write a file
    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_ALGORITHM_ERROR
        super(MajaAlgorithmException, self).__init__(msg)


class MajaPluginBaseException(MajaException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PLUGIN_BASE_ERROR
        super(MajaPluginBaseException, self).__init__(msg)


class MajaPluginSentinel2Exception(MajaPluginBaseException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PLUGIN_SENTINEL2_ERROR
        super(MajaPluginSentinel2Exception, self).__init__(msg)


class MajaPluginMuscateException(MajaPluginBaseException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PLUGIN_MUSCATE_ERROR
        super(MajaPluginMuscateException, self).__init__(msg)


class MajaPluginEarthExplorerException(MajaPluginBaseException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PLUGIN_EARTH_EXPLORER_ERROR
        super(MajaPluginEarthExplorerException, self).__init__(msg)


class MajaPluginSentinel2MuscateException(MajaPluginMuscateException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PLUGIN_SENTINEL2_MUSCATE_ERROR
        super(MajaPluginSentinel2MuscateException, self).__init__(msg)


class MajaPluginVenusMuscateException(MajaPluginMuscateException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PLUGIN_VENUS_MUSCATE_ERROR
        super(MajaPluginVenusMuscateException, self).__init__(msg)


class MajaPluginVenusException(MajaPluginBaseException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PLUGIN_VENUS_MUSCATE_ERROR
        super(MajaPluginVenusException, self).__init__(msg)


class MajaPluginLandsat8Exception(MajaPluginBaseException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PLUGIN_LANDSAT8_ERROR
        super(MajaPluginLandsat8Exception, self).__init__(msg)


class MajaCotsException(MajaException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_COTS_ERROR
        super(MajaCotsException, self).__init__(msg)


class MajaOTBCotsException(MajaCotsException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_OTB_COTS_ERROR
        super(MajaOTBCotsException, self).__init__(msg)


class MajaOGRCotsException(MajaCotsException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PROCESSING_ERROR
        super(MajaOGRCotsException, self).__init__(msg)


class MajaGDALCotsException(MajaCotsException):
    """

    """
    def __init__(self, msg):
        self._exit_code = maja_exit_codes.MAJA_PROCESSING_ERROR
        super(MajaGDALCotsException, self).__init__(msg)
