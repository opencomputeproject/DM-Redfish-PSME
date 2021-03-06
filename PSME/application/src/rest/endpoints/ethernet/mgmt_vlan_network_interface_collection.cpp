/*
* Edgecore DeviceManager
* Copyright 2020-2021 Edgecore Networks, Inc.
 *
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#include "agent-framework/module/requests/network/add_port_vlan.hpp"
#include "agent-framework/module/responses/network/add_port_vlan.hpp"

#include "psme/core/agent/agent_manager.hpp"
#include "psme/rest/constants/constants.hpp"
#include "psme/rest/endpoints/ethernet/mgmt_vlan_network_interface_collection.hpp"
#include "psme/rest/model/handlers/handler_manager.hpp"
#include "psme/rest/model/handlers/generic_handler_deps.hpp"
#include "psme/rest/model/handlers/generic_handler.hpp"
#include "psme/rest/server/error/error_factory.hpp"
#include "psme/rest/validators/json_validator.hpp"
#include "psme/rest/validators/schemas/vlan_network_interface_collection.hpp"
#include "configuration/configuration.hpp"
#include "ecsys_helper/ecsys_helper.hpp"
#include "psme/rest/utils/ec_common_utils.hpp"
using namespace psme::rest::utils;
using namespace psme::rest;
using namespace psme::rest::constants;
using namespace psme::rest::validators;
using namespace psme::rest::endpoint;
using namespace ecsys_helper;

namespace
{
json::Value make_prototype()
{
    json::Value r(json::Value::Type::OBJECT);

    r[Common::ODATA_CONTEXT] =
        "/redfish/v1/$metadata#VLanNetworkInterfaceCollection.VLanNetworkInterfaceCollection";
    r[Common::ODATA_ID] = json::Value::Type::NIL;
    r[Common::ODATA_TYPE] = "#VLanNetworkInterfaceCollection.v1_0_0.VLanNetworkInterfaceCollection";
    r[Common::NAME] = "VLAN Network Interface Collection";
    r[Common::DESCRIPTION] = "Collection of VLAN Network Interfaces";
    r[Collection::ODATA_COUNT] = json::Value::Type::NIL;
    r[Collection::MEMBERS] = json::Value::Type::ARRAY;
    return r;
}

} // namespace

Mgmt_VlanNetworkInterfaceCollection::Mgmt_VlanNetworkInterfaceCollection(const std::string& path) : EndpointBase(path) {}
Mgmt_VlanNetworkInterfaceCollection::~Mgmt_VlanNetworkInterfaceCollection() {}

void Mgmt_VlanNetworkInterfaceCollection::get(const server::Request &req, server::Response &res)
{
    auto r = ::make_prototype();
    r[Common::ODATA_ID] = PathBuilder(req).build();

    char resultA[HT_BUFFER_LEN] = {0};
    char command[HT_BUFFER_LEN] = {0};
    const json::Value config = configuration::Configuration::get_instance().to_json();
    const auto& nic_name = config["server"]["network-interface-name"].as_string();

    sprintf(command, "mgmt_vlan.sh get vlan_port_count %s" ,  nic_name.c_str());
    memset(resultA,0x0, sizeof(resultA));
    EcCommonUtils::exec_shell(command, resultA, 0);

    if(strlen(resultA) != 0)
    {
        int icount = std::stoi(resultA);
        int i =0;
        r[Collection::ODATA_COUNT] = static_cast<std::uint32_t>(icount);

	 for (i = 0; i < icount ; i++) 
        {
            json::Value link_elem(json::Value::Type::OBJECT);
    
            sprintf(command, "mgmt_vlan.sh get vlan_port_value %s  %d",nic_name.c_str(),  i);
            memset(resultA,0x0, sizeof(resultA));
            EcCommonUtils::exec_shell(command, resultA, 0);
    
           if(strlen(resultA) != 0)
           {
               link_elem[Common::ODATA_ID] = PathBuilder(req).append(atoi(resultA)).build();
               r[Collection::MEMBERS].push_back(std::move(link_elem));
           }
        }	
    }
    else	
        r[Collection::ODATA_COUNT] = 0;	
	
    set_response(res, r);
}
