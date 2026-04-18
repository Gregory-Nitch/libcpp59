/***********************************************************************************************************************
 * MIT License
 *
 * Copyright (c) 2026 Gregory Nitch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @date: 2026-04-13
 * @author: Gregory Nitch
 *
 * @brief: Logger class header.
 **********************************************************************************************************************/

#pragma once

/*
************************************************************************************************************************
- - SYSTEM INCLUDES - -
************************************************************************************************************************
*/

#include <iostream>
#include <string>
#include <mutex>
#include <source_location>
#include <fstream>
#include <memory>

/*
************************************************************************************************************************
- - LOGGER CLASS - -
************************************************************************************************************************
*/

namespace libcpp59 {
    enum class log_level {
        DEBUG,
        INFO,
        WARN,
        ERR,
        OFF
    };

    class logger {
    public:
        logger();
        logger(std::string const & output_path);
        logger(std::string const & output_path, log_level level);

        ~logger() = default;

        logger(const logger&) = delete;
        logger& operator=(const logger&) = delete;

        void log(log_level level, std::string const & message, std::source_location const & location = std::source_location::current());
        void set_log_level(log_level level);
        void set_log_to_console();
        void set_log_to_file(std::string const & output_path);

    private:
        std::ostream* m_output;
        std::unique_ptr<std::ofstream> m_output_file;
        log_level m_log_level = log_level::INFO;
        std::mutex m_mutex;

        void set_log_to_file_internal(std::string const & output_path);
    };
}
