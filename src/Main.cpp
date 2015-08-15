/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 David Vas <anuka|Anubisss>, http://anuka.me/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>

#include "RedisConnectionStringParser.h"

// The Redis CLI client program.
#define REDIS_CLI "redis-cli"

int main(int argc, char* argv[])
{
    // Some help.
    if (argc <= 1 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        std::cout << "redis-cli-cs" << std::endl;
        std::cout << "  Redis CLI client connection string (URI) connector." << std::endl;
        std::cout << std::endl;
        std::cout << "Usage: redis-cli-cs redis_connection_string [custom params to redis-cli]" << std::endl;
        std::cout << "Examples:" << std::endl;
        std::cout << "  " << "redis-cli-cs redis://:foobar@example.com:37890/11" << std::endl;
        std::cout << "  " << "redis-cli-cs redis://:foobar@example.com:37890/11 --bigkeys --latency-history" << std::endl;
        return 0;
    }

    redisCliCs::RedisConnectionString cs;
    try
    {
        // Try to parse the given Redis connection string (URI).
        cs = redisCliCs::RedisConnectionStringParser::Parse(argv[1]);
    }
    // Error happened.
    catch (std::runtime_error e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    // Extracts the data from the connection string (URI).
    std::string password = cs.GetPassword();
    std::string hostname = cs.GetHostname();
    std::string port = cs.GetPort();
    std::string db = cs.GetPath();

    std::stringstream redisCommand;
    redisCommand << REDIS_CLI;

    if (!password.empty())
        redisCommand << " -a " << "\"" << password << "\"";
    if (!hostname.empty())
        redisCommand << " -h " << "\"" << hostname << "\"" ;
    if (!port.empty())
        redisCommand << " -p " << "\"" << port << "\"" ;
    if (!db.empty())
        redisCommand << " -n " << "\"" << db << "\"" ;

    // If any custom params given appends to the command.
    for (int i = 2; i < argc; ++i)
    {
        // Gets the custom param.
        std::string param = argv[i];
        redisCommand << " ";
        // If the param contains space.
        if (param.find_first_of(" ") != std::string::npos)
            redisCommand << "\"";
        redisCommand << param;
        if (param.find_first_of(" ") != std::string::npos)
            redisCommand << "\"";
    }

    std::cout << "Executing... " << redisCommand.str() << std::endl;
    std::system(redisCommand.str().c_str());
    return 0;
}
