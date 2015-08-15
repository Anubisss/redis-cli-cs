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

#pragma once

#include <string>

namespace redisCliCs
{

/**
 * @brief Represents a parsed Redis connection string (URI).
 */
class RedisConnectionString
{
public:
    RedisConnectionString() : _schemeName(""),
                              _username(""),
                              _password(""),
                              _hostname(""),
                              _port(""),
                              _path("") {}

    std::string GetSchemeName() const { return _schemeName; }
    void SetSchemeName(std::string schemeName) { _schemeName = schemeName; }

    std::string GetUsername() const { return _username; }
    void SetUsername(std::string username) { _username = username; }

    std::string GetPassword() const { return _password; }
    void SetPassword(std::string password) { _password = password; }

    std::string GetHostname() const { return _hostname; }
    void SetHostname(std::string hostname) { _hostname = hostname; }

    std::string GetPort() const { return _port; }
    void SetPort(std::string port) { _port = port; }

    std::string GetPath() const { return _path; }
    void SetPath(std::string path) { _path = path; }

private:
    /// Scheme name of the connection string.
    std::string _schemeName;
    /// Username.
    std::string _username;
    /// Password.
    std::string _password;
    /// Hostname (or IP address).
    std::string _hostname;
    /// Port.
    std::string _port;
    /// Path which is a DB index in Redis.
    std::string _path;
};

}
