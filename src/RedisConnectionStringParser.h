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
#include <stdexcept>

#include "RedisConnectionString.h"

namespace redisCliCs
{

/// The Redis scheme name.
#define URI_REDIS_SCHEME "redis://"
/// Separates the user info (username + password) from the hostname + port + path.
#define URI_USER_INFO_SEPARATOR "@"
/// Separates the username and the password.
#define URI_PASSWORD_SEPARATOR ":"
/// Separates the hostname and the port.
#define URI_PORT_SEPARATOR ":"
/// Separates the path from the hostname or from the port.
#define URI_PATH_SEPARATOR "/"

/**
 * @brief Parses a Redis connection string (URI).
 */
class RedisConnectionStringParser {
public:
    /**
     * @brief Represents an exception which is thrown when the
     *        Redis connection string (URI) is empty.
     */
    class EmptyParameterException : public std::runtime_error
    {
    public:
        EmptyParameterException() : std::runtime_error("Empty Redis connection string.") {}
    };

    /**
     * @brief Represents an exception which is thrown when the
     *        Redis connection string (URI) doesn't have the
     *        proper Redis scheme (redis://).
     */
    class NoRedisSchemeException : public std::runtime_error
    {
    public:
        NoRedisSchemeException() : std::runtime_error("Redis connection string have to start " \
                                                      "with the Redis URI scheme (redis://).") {}
    };

public:
    /**
     * @brief Parses the raw Redis connection string (URI) to a structured format.
     *
     * @param connectionString The raw Redis connection string (URI) which will be parsed.
     * @return                 The parsed and structured format of the Redis connection
     *                         string (URI), RedisConnectionString.
     *
     * @throws EmptyParameterException When the Redis connection string (URI) is empty.
     * @throws NoRedisSchemeException  When the Redis connection string (URI) doesn't have the
     *                                 proper Redis scheme (redis://).
     */
    static RedisConnectionString Parse(std::string connectionString);

private:
    /**
     * @brief Checks that the Redis connection string (URI) starts
     *        with required Redis scheme name.
     *
     * @param connectionString The raw Redis connection string (URI) which will be parsed.
     * @return                 True if the connection string starts with the proper scheme
     *                         or else false.
     */
    static bool StartsWithRedisScheme(std::string connectionString);

    /**
     * @brief Gets the userinfo from a Redis connection string (URI) without scheme.
     *
     * @param connectionStringWithoutScheme Redis connection string (URI) without scheme.
     * @return                              The userinfo of the Redis connection
     *                                      string (URI), may be empty string.
     */
    static std::string GetUserInfo(std::string connectionStringWithoutScheme);
    /**
     * @brief Gets the username from the userinfo of the Redis connection string (URI).
     *
     * @param userInfo The userinfo of the Redis connection string (URI).
     * @return         Username of the Redis connection string (URI), may be empty string.
     */
    static std::string GetUsername(std::string userInfo);
    /**
     * @brief Gets the password from the userinfo of the Redis connection string (URI).
     *
     * @param userInfo The userinfo of the Redis connection string (URI).
     * @return         Pasword of the Redis connection string (URI), may be empty string.
     */
    static std::string GetPassword(std::string userInfo);

    /**
     * @brief Gets hostname, port and path from a Redis connection string (URI) without scheme.
     *
     * @param connectionStringWithoutScheme Redis connection string (URI) without scheme.
     * @return                              Hostname, port and path of the Redis connection
     *                                      string (URI), may be empty string.
     */
    static std::string GetHostnamePortPath(std::string connectionStringWithoutScheme);

    /**
     * @brief Gets the hostname and the port from a Redis connection
     *        string (URI) without scheme and userinfo.
     *
     * @param hostnamePortPath Redis connection string (URI) without scheme and userinfo.
     * @return                 Hostname and port of the Redis connection string (URI),
     *                         may be empty string.
     */
    static std::string GetHostnamePort(std::string hostnamePortPath);
    /**
     * @brief Gets the hostname from the hostname + port of the Redis connection string (URI).
     *
     * @param hostnamePort The hostname + port of the Redis connection string (URI).
     * @return             Hostname of the Redis connection string (URI), may be empty string.
     */
    static std::string GetHostname(std::string hostnamePort);
    /**
     * @brief Gets the port from the hostname + port of the Redis connection string (URI).
     *
     * @param hostnamePort The hostname + port of the Redis connection string (URI).
     * @return             Port of the Redis connection string (URI), may be empty string.
     */
    static std::string GetPort(std::string hostnamePort);

    /**
     * @brief Gets the path from a Redis connection string (URI) without scheme and userinfo.
     *
     * @param hostnamePortPath Redis connection string (URI) without scheme and userinfo.
     * @return                 Path of the Redis connection string (URI), may be empty string.
     */
    static std::string GetPath(std::string hostnamePortPath);
};

}
