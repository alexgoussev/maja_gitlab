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
orchestrator.common.maja_exceptions -- shortdesc

orchestrator.common.maja_exceptions is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


class MajaException(Exception):

    def __init__(self, msg):
        super(MajaException, self).__init__(msg)


class MajaDriverException(MajaException):
    """
    Exception raised by an error reading a product with maja drivers
    """
    pass


class MajaDataException(MajaException):
    """
    Exception raised when there is a problem to read or write a file
    """
    pass


class MajaModuleException(MajaException):
    """
    Exception raised when there is a problem to read or write a file
    """
    pass


class MajaNotYetImplemented(NotImplementedError):
    """
    Exception raised when entering a not yet implemented functionality
    """
    pass


class MajaProcessingError(MajaException):
    """
    Exception raised when process crashed during run
    """
    pass


class MajaIOError(IOError):
    """
    Exception raised when there is a problem to read or write a file
    """
    pass


class MajaExceptionAlgorithm(ArithmeticError):
    """
    Exception raised when there is a problem to read or write a file
    """
    pass



class MajaExceptionPluginBase(MajaException):
    """

    """
    pass


class MajaExceptionPluginSentinel2(MajaExceptionPluginBase):
    """

    """
    pass


class MajaExceptionPluginSentinel2Muscate(MajaExceptionPluginBase):
    """

    """
    pass


class MajaExceptionPluginVenus(MajaExceptionPluginBase):
    """

    """
    pass



class MajaExceptionPluginMuscate(MajaExceptionPluginBase):
    """

    """
    pass


class MajaBusinessException(MajaException):
    """

    """
    pass


class MajaChainException(MajaException):
    """

    """
    pass


class MajaOgrException(MajaException):
    """

    """
    pass
