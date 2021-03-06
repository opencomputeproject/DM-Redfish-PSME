/*!
 * @copyright
 * Copyright (c) 2016-2017 Intel Corporation
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
 * @file requests/network/delete_acl_port.cpp
 *
 * @brief Network request DeleteAclPort implementation
 * */

#include "agent-framework/module/requests/network/delete_acl_port.hpp"
#include "agent-framework/module/constants/network.hpp"
#include "agent-framework/module/constants/common.hpp"
#include <json/json.h>

using namespace agent_framework::model::requests;
using namespace agent_framework::model::literals;

DeleteAclPort::DeleteAclPort(const std::string& acl, const Ports& ports,
                       const Oem& oem)
    : m_acl(acl), m_ports(ports), m_oem(oem) {}

Json::Value DeleteAclPort::to_json() const {
    Json::Value value;
    value[Acl::ACL] = m_acl;
    value[Acl::PORTS] = m_ports.to_json();
    value[Acl::OEM] = m_oem.to_json();
    return value;
}

DeleteAclPort DeleteAclPort::from_json(const Json::Value& json) {
    return DeleteAclPort{json[Acl::ACL].asString(),
        Ports::from_json(json[Acl::PORTS]),
        Oem::from_json(json[Acl::OEM])
    };
}
