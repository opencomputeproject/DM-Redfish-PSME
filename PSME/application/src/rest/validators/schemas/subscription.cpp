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

#include "psme/rest/validators/schemas/subscription.hpp"
#include "psme/rest/constants/constants.hpp"
#include "psme/rest/eventing/event.hpp"



using namespace psme::rest;
using namespace psme::rest::validators::schema;


const jsonrpc::ProcedureValidator& SubscriptionPatchSchema::get_procedure() {
    static jsonrpc::ProcedureValidator procedure{
        "subscription_patch",
        jsonrpc::PARAMS_BY_NAME,
        constants::Common::NAME, VALID_OPTIONAL(VALID_JSON_STRING),
        constants::EventSubscription::DESTINATION, VALID_OPTIONAL(VALID_JSON_STRING),
        constants::EventSubscription::CONTEXT, VALID_OPTIONAL(VALID_JSON_STRING),
        nullptr
    };
    return procedure;
}
