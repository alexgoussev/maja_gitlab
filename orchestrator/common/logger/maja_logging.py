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
orchestrator.common.logger.maja_logging -- shortdesc

orchestrator.common.logger.maja_logging is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

import logging.config
import logging
import sys
from orchestrator.common import version


def configure_logger(name, std=sys.stdout, level=logging.DEBUG):
    """
    """
    log = logging.getLogger('MAJA')
    if len(log.handlers) == 0:
        log.setLevel(level)
        handler = logging.StreamHandler(std)
        handler.setLevel(level)
        handler.setFormatter(
            logging.Formatter('%(asctime)s [%(process)d] %(levelname)s %(name)s ' + version.MAJA_VERSION_LOGGER_STRING +
                              ' %(funcName)s:%(lineno)d %(message)s',"%Y-%m-%d %H:%M:%S"))
        log.addHandler(handler)
    """
    Stdout and err redirection
    """
    """stdout_logger = logging.getLogger('STDOUT')
    stream_logger_out = StreamToLogger(stdout_logger, log_level=logging.INFO)
    sys.stdout = stream_logger_out
    stderr_logger = logging.getLogger('STDERR')
    stream_logger_err = StreamToLogger(stderr_logger, log_level=logging.ERROR)
    sys.stderr = stream_logger_err"""
    return log


class StreamToLogger(object):
    """Fake file-like stream object that redirects writes to a logger instance.

    Code from
    `electricmonk <http://www.electricmonk.nl/log/2011/08/14/redirect-\
    stdout-and-stderr-to-a-logger-in-python/>`_
    """

    def __init__(self, logger, log_level=logging.INFO):
        self.logger = logger
        self.log_level = log_level
        self.linebuf = ''

    def write(self, buf):
        """
        :param buf: The buffer to write
        :type buf: [str]
        """
        for line in buf.splitlines():
            line_stripped = line.rstrip()
            if len(line_stripped) > 0:  # Log only non empty lines
                self.logger.log(self.log_level, line_stripped.decode('UTF-8'))
