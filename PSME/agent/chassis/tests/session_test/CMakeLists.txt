# <license_header>
#
# Copyright (c) 2015-2017 Intel Corporation
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
# Edgecore DeviceManager
# Copyright 2020-2021 Edgecore Networks, Inc.
#
# This product includes software developed at
# Edgecore Networks Inc. (http://www.edge-core.com/).
#
# </license_header>

if (NOT GTEST_FOUND)
    return()
endif()

add_gtest(session psme-chassis
    session_test.cpp
    test_runner.cpp
)

target_link_libraries(${test_target}
    ${AGENT_CHASSIS_LIBRARIES}
    chassis-utils
    chassis-ecrf_pal
    ${AGENT_FRAMEWORK_LIBRARIES}
    ${UUID_LIBRARIES}
    ${LOGGER_LIBRARIES}
    ${SAFESTRING_LIBRARIES}
    ${CONFIGURATION_LIBRARIES}
    ${JSONCXX_LIBRARIES}
    ${BASE64_LIBRARIES}
    jsoncpp
)
