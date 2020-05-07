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

orchestrator.common.directory_manager -- shortdesc

orchestrator.common.directory_manager is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


import tempfile,os,shutil
from fileinput import close


class DirectoryManager(object):
    """
    classdocs
    """

    def __init__(self,working_dir):
        """
        Constructor
        """
        self._working_dir = working_dir
        self._list_of_temp = []
        self._list_of_temp_always = []

    def __del__(self):
        """
        Cleanup at destuction
        """

    def get_temporary_directory(self,module, do_always_remove=False):
        """
        :param module:
        :param working_directory:
        :param do_always_remove:
        :type module:
        :return: a unique working directory
        """
        tmp = tempfile.mkdtemp(prefix="Maja_%s" % module, dir=self._working_dir)
        if do_always_remove:
            self._list_of_temp_always.append(tmp)
        else:
            self._list_of_temp.append(tmp)
        return tmp

    def get_temporary_file(self,module, do_always_remove=False):
        """
        mkstemp returns a tuple of (OS-level handle to an open file, filepath)

        :param module:
        :type module:
        :param working_directory:
        :type working_directory:
        :return: a unique filepath
        """
        tmp = tempfile.mkstemp(prefix="Maja_%s" % module, dir=self._working_dir)
        if do_always_remove:
            self._list_of_temp_always.append(tmp[1])
        else:
            self._list_of_temp.append(tmp[1])
        os.close(tmp[0])
        return tmp[1]

    def clean(self, all=False):
        for f in self._list_of_temp_always:
            if os.path.exists(f):
                if os.path.isdir(f):
                    shutil.rmtree(f, ignore_errors=True)
                else:
                    os.remove(f)
        if all:
            for f in self._list_of_temp:
                if os.path.exists(f):
                    if os.path.isdir(f):
                        shutil.rmtree(f, ignore_errors=True)
                    else:
                        os.remove(f)
