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
# </license_header>

set(SOURCES
    status_manager.cpp
    module_software_status.cpp
    module_hardware_status.cpp
    state_machine_action.cpp
    system_power_state_thread.cpp
    system_boot_options_thread.cpp
    gpio/gpio_status.cpp
    icmp/icmp.cpp
    smbios/smbios_checksum.cpp
)

set_source_files_properties(module_software_status.cpp PROPERTIES COMPILE_FLAGS
    "-Wno-old-style-cast")

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    # GCC bug. In C++11 initializtion with {} is correct
    set_source_files_properties(module_hardware_status.cpp PROPERTIES
        COMPILE_FLAGS "-Wno-missing-field-initializers")
endif()

add_library(compute-status-impl OBJECT ${SOURCES})
