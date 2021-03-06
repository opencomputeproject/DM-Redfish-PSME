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

if (NOT GTEST_FOUND)
    return()
endif()

 add_gtest(eventing_queue agent-framework
     test_runner.cpp
     eventing_test_queue.cpp
     test_worker_thread.cpp
 )

 target_link_libraries(${test_target}
     ${JSONCXX_LIBRARIES}
     ${AGENT_FRAMEWORK_LIB}

 )

 #add_gtest(eventing_notification agent-framework
 #    test_runner.cpp
 #    eventing_test_notification.cpp
 #)

 #target_link_libraries(${test_target}
 #    ${JSONCXX_LIBRARIES}
 #    ${AGENT_FRAMEWORK_LIB}
 #    ${UUID_LIBRARIES}
 #    ${PCA95XX_LIBRARIES}
 #)

 #target_include_directories(${test_target} PUBLIC
 #    ${AGENT_FRAMEWORK_DIR}/src/state_machine
 #)

 #add_gtest(eventing_subscription agent-framework
 #    test_runner.cpp
 #    eventing_test_subscription.cpp
 #)

 #target_link_libraries(${test_target}
 #    ${JSONCXX_LIBRARIES}
 #    ${AGENT_FRAMEWORK_LIB}
 #    ${UUID_LIBRARIES}
 #    ${PCA95XX_LIBRARIES}
 #)

 #target_include_directories(${test_target} PUBLIC
 #    ${AGENT_FRAMEWORK_DIR}/src/state_machine
 #)
