/*!
 * @section LICENSE
 *
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
 * @section DESCRIPTION
 *
 * Edgecore DeviceManager
 * Copyright 2020-2021 Edgecore Networks, Inc.
 *
 * This product includes software developed at
 * Edgecore Networks Inc. (http://www.edge-core.com/).
 *
 * @file command_json_server.cpp
 *
 * @brief Command JSON server implementation
 * */

#include "agent-framework/command/command_json_server.hpp"
#include "agent-framework/exceptions/exception.hpp"
#include "agent-framework/logger_ext.hpp"			
using namespace jsonrpc;
using namespace agent_framework;
using namespace agent_framework::command;

CommandJsonServer::CommandJsonServer(AbstractServerConnector& connector,
        serverVersion_t type) :
            m_connection(connector),
            m_handler(RequestHandlerFactory::createProtocolHandler(type, *this)),
            m_methods({}) {

    connector.SetHandler(m_handler.get());
}

void CommandJsonServer::start() {
    m_connection.StartListening();
}

void CommandJsonServer::stop() {
    m_connection.StopListening();
}

void CommandJsonServer::HandleMethodCall(Procedure& proc,
        const Json::Value& input, Json::Value& output) {

    try {
        m_methods[proc.GetProcedureName()](input, output);
    }
    catch (const JsonRpcException&) {
        throw;
    }
    catch (const std::exception& e) {
        throw JsonRpcException(static_cast<int>(exceptions::ErrorCode::UNKNOWN_ERROR),
                               e.what());
    }
    catch (...) {
        throw JsonRpcException(static_cast<int>(exceptions::ErrorCode::UNKNOWN_ERROR),
                               "Unknown exception occurred in JSON command method.");
    }
}

void CommandJsonServer::HandleNotificationCall(Procedure& proc,
        const Json::Value& input) {

    try {
        Json::Value dummy;
        m_methods[proc.GetProcedureName()](input, dummy);
    }
    catch (const JsonRpcException&) {
        throw;
    }
    catch (const std::exception& e) {
        throw JsonRpcException(static_cast<int>(exceptions::ErrorCode::UNKNOWN_ERROR),
                               e.what());
    }
    catch (...) {
        throw JsonRpcException(static_cast<int>(exceptions::ErrorCode::UNKNOWN_ERROR),
                               "Unknown exception occurred in JSON command method.");
    }
}

void CommandJsonServer::add(const Procedure& proc,
                            const method_function_t& method) {

    if (RPC_METHOD != proc.GetProcedureType()) {
        return;
    }

    auto& method_name = proc.GetProcedureName();

    if (m_methods.end() != m_methods.find(method_name)) {
        return;
    }

    m_handler->AddProcedure(proc);
    m_methods[method_name] = method;
}

void CommandJsonServer::add(const Procedure& proc,
                            const notification_function_t& notification) {

    if(RPC_NOTIFICATION != proc.GetProcedureType()) {
        return;
    }

    auto& method_name = proc.GetProcedureName();

    if (m_methods.end() != m_methods.find(method_name)) {
        return;
    }

    using std::placeholders::_1;

    m_handler->AddProcedure(proc);
    m_methods[method_name] = std::bind(notification, _1);
}


void CommandJsonServer::add(const CommandFactory::CommandsJsonVector& command_vector) {
    using std::placeholders::_1;
    using std::placeholders::_2;

    for (const auto& command : command_vector) {
        add(command->get_procedure(), static_cast<method_function_t>(
                    std::bind(&CommandJson::method, command.get(), _1, _2)));
        add(command->get_procedure(), static_cast<notification_function_t>(
                    std::bind(&CommandJson::notification, command.get(), _1)));
    }
}

void CommandJsonServer::add(const command_ref::Registry::Commands& commands) {
    using std::placeholders::_1;
    using std::placeholders::_2;

    for (const auto& command : commands) {
        add(command.get()->get_procedure(), static_cast<method_function_t>(
                std::bind(&command_ref::CommandBase::method, command.get(), _1, _2)));
        add(command.get()->get_procedure(), static_cast<notification_function_t>(
                std::bind(&command_ref::CommandBase::notification, command.get(), _1)));
    }
}


CommandJsonServer::~CommandJsonServer() { }
