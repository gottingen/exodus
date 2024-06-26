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

#include <dwarf/core/interpreter.h>
#include <collie/nlohmann/json.hpp>
#include <exodus/cal/calc_config.h>
#include <dwarf/core/config.h>

namespace nl = nlohmann;

namespace exodus::cal {
    class DWARF_API interpreter : public dwarf::Interpreter {
    public:

        interpreter() = default;

        virtual ~interpreter() = default;

    private:

        void configure_impl() override;

        nl::json execute_request_impl(int execution_counter,
                                      const std::string &code,
                                      bool silent,
                                      bool store_history,
                                      nl::json user_expressions,
                                      bool allow_stdin) override;

        nl::json complete_request_impl(const std::string &code,
                                       int cursor_pos) override;

        nl::json inspect_request_impl(const std::string &code,
                                      int cursor_pos,
                                      int detail_level) override;

        nl::json is_complete_request_impl(const std::string &code) override;

        nl::json kernel_info_request_impl() override;

        void shutdown_request_impl() override;
    };

    using publish_type = std::function<void(const std::string &name, const std::string &text)>;

    DWARF_API std::string formating_expr(const std::string &expr);

    DWARF_API std::string parse_rpn(const std::string &infix,
                                        publish_type publish = [](const std::string & /*name*/,
                                                                  const std::string & /*text*/) {});

    DWARF_API double compute_rpn(const std::string &expr, publish_type publish = [](const std::string & /*name*/,
                                                                                        const std::string & /*text*/) {});
}
