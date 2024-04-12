// Copyright 2024 The EA Authors.
// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#pragma once

// Project version
#define CALC_VERSION_MAJOR 0
#define CALC_VERSION_MINOR 3
#define CALC_VERSION_PATCH 0

// Composing the version string from major, minor and patch
#define CALC_CONCATENATE(A, B) CALC_CONCATENATE_IMPL(A, B)
#define CALC_CONCATENATE_IMPL(A, B) A##B
#define CALC_STRINGIFY(a) CALC_STRINGIFY_IMPL(a)
#define CALC_STRINGIFY_IMPL(a) #a

#define CALC_VERSION CALC_STRINGIFY(CALC_CONCATENATE(CALC_VERSION_MAJOR,   \
                 CALC_CONCATENATE(.,CALC_CONCATENATE(CALC_VERSION_MINOR,   \
                                  CALC_CONCATENATE(.,CALC_VERSION_PATCH)))))
                                  