#
# Copyright 2023 The titan-search Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
###########################################################################
# below are examples, after initialization, modify it to your own.
###########################################################################
###carbin_example
#[[
carbin_cc_library(
        NAMESPACE changeme
        NAME foo
        SOURCES
        foo.cc
        COPTS
        ${CARBIN_CXX_OPTIONS}
        DEPS
        ${CARBIN_DEPS_LINK}
        PUBLIC
)
]]
carbin_cc_library(
        NAMESPACE exodus
        NAME fake
        SOURCES
        fake.cc
        COPTS
        ${CARBIN_CXX_OPTIONS}
        DEPS
        ${CARBIN_DEPS_LINK}
        PUBLIC
)

###carbin_example
if(ENABLE_HS)
    add_subdirectory(hs)
endif()

if(ENABLE_CAL)
    add_subdirectory(cal)
endif()
