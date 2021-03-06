/*!
 * @copyright
 * Copyright (c) 2015-2017 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file memory.hpp
 *
 * @brief SMBIOS-way of discovering Memory properties
 * */

#pragma once

#include "agent-framework/module/model/system.hpp"
#include "smbios/smbios_parser.hpp"

namespace agent {
namespace compute {
namespace discovery {
namespace smbios {


/*!
 * @brief Discovers Memory modules using the smbios parser
 *
 * @param[in] smbios pointer to smbios parser
 * @param[in] system reference to system model to be populated with BIOS data
 *
 * @return Tuple that tells the caller discovery status and health status to be set on the resource
 */
std::tuple<bool, agent_framework::model::enums::Health> discover_memory_modules(::smbios::parser::SmbiosParser::Ptr smbios,
                                                                              agent_framework::model::System& system);

}
}
}
}
