# -*- coding: utf-8 -*-
#
# Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES), CS-SI, CESBIO - All Rights Reserved
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
from datetime import datetime as dt


def datetimeToString(timestamp):
    """
    @brief Convert datetime to string %Y-%m-%dT%H:%M:%S.%f
    """
    return timestamp.strftime("%Y-%m-%dT%H:%M:%S.%f")[:-3] + "Z"


def datetimeToStringShort(timestamp):
    """
    @brief Convert datetime to string YYYYMMDD
    """
    return timestamp.strftime("%Y%m%d")


def datetimeToStringName(timestamp):
    """
    @brief Convert datetime to string YYYYMMDD
    """
    return timestamp.strftime("%Y%m%d-%H%M%S-%f")[:-3]


def stringToDatetime(s):
    """
    @brief Convert string of format YYYYMMDD or %Y-%m-%dT%H:%M:%S.%f to datetime
    """
    if(len(s) == 24):
        return dt.strptime(s[:-1], "%Y-%m-%dT%H:%M:%S.%f")
    if(len(s) == 8):
        return dt.strptime(s, "%Y%m%d")
    raise ValueError("Unknown datetime string {0}".format(s))
