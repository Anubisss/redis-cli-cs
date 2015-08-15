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

#include "RedisConnectionStringParser.h"

namespace redisCliCs
{

RedisConnectionString RedisConnectionStringParser::Parse(std::string connectionString)
{
    // Empty connection string.
    if (connectionString.empty())
        throw EmptyParameterException();
    // The connection string doesn't start with the required Redis scheme.
    if (!StartsWithRedisScheme(connectionString))
        throw NoRedisSchemeException();

    // The function parses the connection string to this object.
    RedisConnectionString cs;
    // No exception was thrown, so this is constant.
    cs.SetSchemeName(URI_REDIS_SCHEME);

    // Removes the scheme from the connection string.
    std::string connectionStringWithoutScheme = connectionString.substr(std::string(URI_REDIS_SCHEME).length());

    // Gets the userinfo part of the connection string.
    std::string connectionStringUserInfo = GetUserInfo(connectionStringWithoutScheme);
    cs.SetUsername(GetUsername(connectionStringUserInfo));
    cs.SetPassword(GetPassword(connectionStringUserInfo));

    // Gets the hostname + port + path part of the connection string.
    std::string hostnamePortPath = GetHostnamePortPath(connectionStringWithoutScheme);
    // Gets the hostname + port part of the connection string.
    std::string hostnamePort = GetHostnamePort(hostnamePortPath);

    cs.SetHostname(GetHostname(hostnamePort));
    cs.SetPort(GetPort(hostnamePort));

    cs.SetPath(GetPath(hostnamePortPath));

    return cs;
}

bool RedisConnectionStringParser::StartsWithRedisScheme(std::string connectionString)
{
    // Too short, so can't contain the required Redis scheme.
    if (connectionString.length() < std::string(URI_REDIS_SCHEME).length())
        return false;
    // Doesn't contain or may contain but not at the start of the connection string.
    if (connectionString.substr(0, std::string(URI_REDIS_SCHEME).length()) != std::string(URI_REDIS_SCHEME))
        return false;
    // OK, should contain.
    return true;
}

std::string RedisConnectionStringParser::GetUserInfo(std::string connectionStringWithoutScheme)
{
    // Gets the last position of the userinfo separator.
    std::size_t userinfoSeparatorPos = connectionStringWithoutScheme.find_last_of(URI_USER_INFO_SEPARATOR);
    // No separator, so no userinfo.
    if (userinfoSeparatorPos == std::string::npos)
        return "";
    return connectionStringWithoutScheme.substr(0, userinfoSeparatorPos);
}

std::string RedisConnectionStringParser::GetUsername(std::string userInfo)
{
    // Gets the first position of the password separator.
    std::size_t usernameSeparatorPos = userInfo.find_first_of(URI_PASSWORD_SEPARATOR);
    // No separator, so no password, so the username is the full userinfo.
    if (usernameSeparatorPos == std::string::npos)
        return userInfo;
    return userInfo.substr(0, usernameSeparatorPos);
}

std::string RedisConnectionStringParser::GetPassword(std::string userInfo)
{
    // Gets the first position of the password separator.
    std::size_t usernameSeparatorPos = userInfo.find_first_of(URI_PASSWORD_SEPARATOR);
    // No separator, so no password.
    if (usernameSeparatorPos == std::string::npos)
        return "";
    return userInfo.substr(usernameSeparatorPos + std::string(URI_PASSWORD_SEPARATOR).length());
}

std::string RedisConnectionStringParser::GetHostnamePortPath(std::string connectionStringWithoutScheme)
{
    // Gets the last position of the userinfo separator.
    std::size_t userinfoSeparatorPos = connectionStringWithoutScheme.find_last_of(URI_USER_INFO_SEPARATOR);
    // No separator, so no userinfo, so the hostname + port + path are the full connection string.
    if (userinfoSeparatorPos == std::string::npos)
        return connectionStringWithoutScheme;
    return connectionStringWithoutScheme.substr(userinfoSeparatorPos + std::string(URI_USER_INFO_SEPARATOR).length());
}

std::string RedisConnectionStringParser::GetHostnamePort(std::string hostnamePortPath)
{
    // Gets the first position of the path separator.
    std::size_t pathSeparatorPos = hostnamePortPath.find_first_of(URI_PATH_SEPARATOR);
    // No separator, so no path, so the hostname + port are the full hostname + port + path string.
    if (pathSeparatorPos == std::string::npos)
        return hostnamePortPath;
    return hostnamePortPath.substr(0, pathSeparatorPos);
}

std::string RedisConnectionStringParser::GetHostname(std::string hostnamePort)
{
    // Gets the first position of the port separator.
    std::size_t hostnameSeparatorPos = hostnamePort.find_first_of(URI_PORT_SEPARATOR);
    // No separator, so no port, so the hostname is the full hostname + port string.
    if (hostnameSeparatorPos == std::string::npos)
        return hostnamePort;
    return hostnamePort.substr(0, hostnameSeparatorPos);
}

std::string RedisConnectionStringParser::GetPort(std::string hostnamePort)
{
    // Gets the first position of the port separator.
    std::size_t hostnameSeparatorPos = hostnamePort.find_first_of(URI_PORT_SEPARATOR);
    // No separator, so no port.
    if (hostnameSeparatorPos == std::string::npos)
        return "";
    return hostnamePort.substr(hostnameSeparatorPos + std::string(URI_PORT_SEPARATOR).length());
}

std::string RedisConnectionStringParser::GetPath(std::string hostnamePortPath)
{
    // Gets the first position of the path separator.
    std::size_t pathSeparatorPos = hostnamePortPath.find_first_of(URI_PATH_SEPARATOR);
    // No separator, so no path.
    if (pathSeparatorPos == std::string::npos)
        return "";
    return hostnamePortPath.substr(pathSeparatorPos + std::string(URI_PATH_SEPARATOR).length());
}

}
