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

namespace libcpp59
{
    /***********************************************************************************************************************
     * @log_level
     * @brief: log level used by the logger class.
     **********************************************************************************************************************/
    enum class log_level
    {
        DEBUG,
        INFO,
        WARN,
        ERR,
        OFF // No logs will be output.
    };

    /***********************************************************************************************************************
     * @logger
     * @brief: Simple logger that logs the message and source information based on log level and passed severity, can
     * target files and can target the console.
     *
     * @m_output: Pointer to the current output stream.
     * @m_err_output: Pointer to the current error output stream. If a file is used it points to the same file as m_output.
     * @m_output_file: Unique pointer to an output file, nullptr if pointing to std::cout.
     * @m_log_level: Current log level threshold for logging messages.
     * @m_mutex: Mutex for thread-safe logging.
     **********************************************************************************************************************/
    class logger
    {
    public:
        /***********************************************************************************************************************
        * @brief: Default logger constructor
        **********************************************************************************************************************/
        logger();

        /***********************************************************************************************************************
        * @brief: Logger constructor which takes an output stream and an error output stream.
        *
        * @param[in] output: Pointer to the output stream (e.g., std::cout or a file stream).
        * @param[in] err_output: Pointer to the error output stream (e.g., std::cerr or a file stream).
        **********************************************************************************************************************/
        logger(std::ostream* output, std::ostream* err_output);

        /***********************************************************************************************************************
         * @brief: Constructor which takes a file output path to the constructor.
         *
         * @param[in] output_path: Path to the target log file..
         **********************************************************************************************************************/
        logger(std::string const & output_path);

        /***********************************************************************************************************************
         * @brief: Constructor which takes both a log target file and a log level.
         *
         * @param[in] output_path: Path to the target log file.
         * @param[in] level: The log level to set the logger to.
         **********************************************************************************************************************/
        logger(std::string const & output_path, log_level level);

        /***********************************************************************************************************************
         * @brief: Deconstructor, flushes output aswell.
         **********************************************************************************************************************/
        ~logger();

        /***********************************************************************************************************************
         * @brief: Deleted copy constructor.
         **********************************************************************************************************************/
        logger(const logger&) = delete;

        /***********************************************************************************************************************
         * @brief: Deleted assignment operator.
         **********************************************************************************************************************/
        logger& operator=(const logger&) = delete;

        /***********************************************************************************************************************
         * @brief: Logs a message.
         *
         * @param[in] level: Level of the message.
         * @param[in] message: The message to log.
         * @param[in] location: The location of the trace.
         **********************************************************************************************************************/
        void log(log_level level, std::string const & message, std::source_location const & location = std::source_location::current());

        /***********************************************************************************************************************
         * @brief: Used to manualy flush the log, helps prevent data loss at determined areas.
         **********************************************************************************************************************/
        void flush();

        /***********************************************************************************************************************
         * @brief: Updates the logger to the passed log level.
         *
         * @param[in] level: New log level to set.
         **********************************************************************************************************************/
        void set_log_level(log_level level);

        /***********************************************************************************************************************
         * @brief: Sets the logger to log to the console. This also clears the current held log file information if any.
         **********************************************************************************************************************/
        void set_log_to_console();

        /***********************************************************************************************************************
         * @brief: Sets the logger to log to a file. This also clears the current held console log information if any.
         *
         * @param[in] output_path: Path to the target log file.
         **********************************************************************************************************************/
        void set_log_to_file(std::string const & output_path);

    private:
        std::ostream* m_output; // Log target stream (console or file).
        std::ostream* m_err_output; // Log target stream for error messages (console or file).
        std::unique_ptr<std::ofstream> m_output_file; // Log target file stream, may be null if logging to console.
        log_level m_log_level = log_level::INFO;
        std::mutex m_mutex;

        /***********************************************************************************************************************
         * @brief: Internal logger function to set the loger to log to the passed target file.
         *
         * @param[in] output_path: Path to the target log file.
         **********************************************************************************************************************/
        void set_log_to_file_internal(std::string const & output_path);

        /***********************************************************************************************************************
         * @brief: Internal flusher, used in deconstructor to ensure output.
         **********************************************************************************************************************/
        void flush_internal();
    };
}
