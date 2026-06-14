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
 * @date: 2026-04-18
 * @author: Gregory Nitch
 *
 * @brief: Unit tests for the logger class.
 **********************************************************************************************************************/

/*
************************************************************************************************************************
- - SYSTEM INCLUDES - -
************************************************************************************************************************
*/

#include <cstdlib>
#include <filesystem>
#include <format>
#include <sstream>
#include <string>
#include <unordered_map>

/*
************************************************************************************************************************
- - LOCAL INCLUDES - -
************************************************************************************************************************
*/

#include "logger.hpp"

/*
************************************************************************************************************************
- - TESTS - -
************************************************************************************************************************
*/

int test_default_ctor_and_console()
{
    int out = EXIT_SUCCESS;
    std::stringstream ss;

    {
        libcpp59::logger logger(&ss, &ss);

        logger.log(libcpp59::log_level::INFO, "This is an info message");
        logger.log(libcpp59::log_level::DEBUG, "This debug messaage should not appear");
    }

    if (ss.str().find("[INFO]:") == std::string::npos)
        out = EXIT_FAILURE;

    if (ss.str().find("[DEBUG]:") != std::string::npos)
        out = EXIT_FAILURE;

    return out;
}

int test_set_log_level()
{
    int out = EXIT_SUCCESS;
    std::stringstream ss;

    {
        libcpp59::logger logger(&ss, &ss);

        logger.log(libcpp59::log_level::INFO, "This is an info message");
        logger.set_log_level(libcpp59::log_level::DEBUG);
        logger.log(libcpp59::log_level::DEBUG, "This debug messaage should also appear");
    }

    if (ss.str().find("[INFO]:") == std::string::npos)
        out = EXIT_FAILURE;

    if (ss.str().find("[DEBUG]:") == std::string::npos)
        out = EXIT_FAILURE;

    return out;
}

int test_log_to_file()
{
    int out = EXIT_SUCCESS;

    {
        libcpp59::logger logger("test.log");

        logger.log(libcpp59::log_level::INFO, "This is an info message");
    }

    std::ifstream file("test.log");
    std::string line;
    if (!std::getline(file, line) || line.find("[INFO]:") == std::string::npos)
        out = EXIT_FAILURE;

    return out;
}

int test_set_log_to_stream()
{
    int out = EXIT_SUCCESS;

    {
        libcpp59::logger logger("test.log");
        std::stringstream ss;
        logger.set_log_to_stream(&ss, &ss);

        logger.log(libcpp59::log_level::INFO, "This is an info message");
    }

    std::ifstream file("test.log");
    std::string line;
    if (std::getline(file, line) && line.find("[INFO]:") != std::string::npos)
        out = EXIT_FAILURE;

    return out;
}

int test_set_log_to_file()
{
    int out = EXIT_SUCCESS;
    std::stringstream ss;
    {
        libcpp59::logger logger(&ss, &ss);
        logger.set_log_to_file("test.log");

        logger.log(libcpp59::log_level::INFO, "This is an info message");
    }

    if (ss.str().find("[INFO]:") != std::string::npos)
        out = EXIT_FAILURE;

    return out;
}

int test_constructor_with_file_and_level()
{
    int out = EXIT_SUCCESS;
    {
        libcpp59::logger logger("test.log", libcpp59::log_level::ERR);

        logger.log(libcpp59::log_level::INFO, "This is an info message");
        logger.log(libcpp59::log_level::ERR, "This is an error message");
    }

    std::ifstream file("test.log");
    std::string line;
    if (std::getline(file, line) && line.find("[ERR]:") == std::string::npos)
        out = EXIT_FAILURE;

    return out;
}

/*
************************************************************************************************************************
- - START PROGRAM - -
************************************************************************************************************************
*/

int main()
{
    std::unordered_map<std::string, int (*)(void)> tests = {
        {"test_default_ctor_and_console", test_default_ctor_and_console},
        {"test_set_log_level", test_set_log_level},
        {"test_log_to_file", test_log_to_file},
        {"test_set_log_to_stream", test_set_log_to_stream},
        {"test_set_log_to_file", test_set_log_to_file},
        {"test_constructor_with_file_and_level", test_constructor_with_file_and_level},

    };
    std::unordered_map<std::string, int> results;

    for (const auto& [name, func] : tests)
    {
        std::cout << std::format("Starting test: {}...\n", name);
        int result = func();
        std::filesystem::remove("test.log");
        if (result != EXIT_SUCCESS)
            results[name] = result;
    }

    for (const auto& [name, result] : results)
        std::cerr << "TEST FAILURE: " << name << std::endl;

    if (!results.empty())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
