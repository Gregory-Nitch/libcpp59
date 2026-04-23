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

#include <string>
#include <unordered_map>
#include <cstdlib>
#include <sstream>

/*
************************************************************************************************************************
- - LOCAL INCLUDES - -
************************************************************************************************************************
*/

#include "logger.hpp"

/*
************************************************************************************************************************
- - HELPERS - -
************************************************************************************************************************
*/

/***********************************************************************************************************************
 * @console_output_redirector
 * @brief: Redirects std::cout to a stringstream for capturing output.
 *
 * @ss: The stringstream used to capture output.
 * @out_cout_buff: The original buffer of std::cout.
 **********************************************************************************************************************/
class logger_output_redirector {
public:
    logger_output_redirector() : out_cout_buff(std::cout.rdbuf()) {}

    ~logger_output_redirector() {
        std::cout.rdbuf(out_cout_buff); // Restore original buffer
    }

    // Redirect std::cout to a stringstream
    void redirect() {
        std::cout.rdbuf(ss.rdbuf());
    }

    // Get the captured output
    std::string get_output() const {
        return ss.str();
    }

private:
    std::stringstream ss;
    std::streambuf* out_cout_buff;
};

/*
************************************************************************************************************************
- - TESTS - -
************************************************************************************************************************
*/

int test_default_ctor_and_console(char const * test_name)
{
    logger_output_redirector redirector;
    redirector.redirect();
    int out = EXIT_SUCCESS;

    libcpp59::logger logger;

    logger.log(libcpp59::log_level::INFO, "This is an info message");
    logger.log(libcpp59::log_level::DEBUG, "This debug messaage should not appear");

    std::string output = redirector.get_output();

    if (output.find("[INFO]: This is an info message") == std::string::npos)
        out = EXIT_FAILURE;

    return out;
}

int test_set_log_level(char const * test_name)
{
    int out = EXIT_SUCCESS;
    return out;
}

int test_log_to_file(char const * test_name)
{
    int out = EXIT_SUCCESS;
    return out;
}

int test_set_log_to_console(char const * test_name)
{
    int out = EXIT_SUCCESS;
    return out;
}

int test_set_log_to_file(char const * test_name)
{
    int out = EXIT_SUCCESS;
    return out;
}

int test_constructor_with_file_and_level(char const * test_name)
{
    int out = EXIT_SUCCESS;
    return out;
}

/*
************************************************************************************************************************
- - START PROGRAM - -
************************************************************************************************************************
*/

int main()
{
    std::unordered_map<std::string, int(*)(char const *)> tests =
        {
            {"test_default_ctor_and_console", test_default_ctor_and_console},
            {"test_set_log_level", test_set_log_level},
            {"test_log_to_file", test_log_to_file},
            {"test_set_log_to_console", test_set_log_to_console},
            {"test_set_log_to_file", test_set_log_to_file},
            {"test_constructor_with_file_and_level", test_constructor_with_file_and_level},

        };
    std::unordered_map<std::string, int> results;

    for (const auto& [name, func] : tests)
    {
        std::cout << "Running test: " << name << std::endl;
        int result = func(name.c_str());
        if (result != EXIT_SUCCESS)
            results[name] = result;
    }

    for (const auto& [name, result] : results)
        std::cerr << "TEST FAILURE: " << name << std::endl;

    if(!results.empty())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
