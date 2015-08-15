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

/**
 * @file
 * @brief Tests for redisCliCs::RedisConnectionStringParser.
 */

#include <gtest/gtest.h>

#include "RedisConnectionStringParser.h"

namespace redisCliCs
{

TEST(RedisConnectionStringParser, EmptyParameterException) {
    EXPECT_THROW(RedisConnectionStringParser::Parse(""), RedisConnectionStringParser::EmptyParameterException);
}

TEST(RedisConnectionStringParser, NoRedisSchemeException) {
    EXPECT_THROW(RedisConnectionStringParser::Parse("foo@bar"), RedisConnectionStringParser::NoRedisSchemeException);
    EXPECT_THROW(RedisConnectionStringParser::Parse("redis:/"), RedisConnectionStringParser::NoRedisSchemeException);
    EXPECT_THROW(RedisConnectionStringParser::Parse("redis:!!!"), RedisConnectionStringParser::NoRedisSchemeException);
    EXPECT_NO_THROW(RedisConnectionStringParser::Parse("redis://"));
    EXPECT_NO_THROW(RedisConnectionStringParser::Parse("redis://foo@bar"));
}

TEST(RedisConnectionStringParser, GetSchemeName) {
    EXPECT_EQ("redis://", RedisConnectionStringParser::Parse("redis://:bar@foobar.com:14578").GetSchemeName());
}

TEST(RedisConnectionStringParser, Parse1) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foo@foobar.com:14578");
    EXPECT_EQ("foo", cs.GetUsername());
    EXPECT_EQ("", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse2) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foo:bar@foobar.com:14578");
    EXPECT_EQ("foo", cs.GetUsername());
    EXPECT_EQ("bar", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse3) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://:bar@foobar.com:14578");
    EXPECT_EQ("", cs.GetUsername());
    EXPECT_EQ("bar", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse4) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://fo:ob:ar@foobar.com:14578");
    EXPECT_EQ("fo", cs.GetUsername());
    EXPECT_EQ("ob:ar", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse5) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://@foobar.com:14578");
    EXPECT_EQ("", cs.GetUsername());
    EXPECT_EQ("", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse6) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foobar.com:14578");
    EXPECT_EQ("", cs.GetUsername());
    EXPECT_EQ("", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse7) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foobar");
    EXPECT_EQ("", cs.GetUsername());
    EXPECT_EQ("", cs.GetPassword());
    EXPECT_EQ("foobar", cs.GetHostname());
    EXPECT_EQ("", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse8) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foobar/2");
    EXPECT_EQ("", cs.GetUsername());
    EXPECT_EQ("", cs.GetPassword());
    EXPECT_EQ("foobar", cs.GetHostname());
    EXPECT_EQ("", cs.GetPort());
    EXPECT_EQ("2", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse9) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://fo:ob:ar@foo@ba@r.com:14578");
    EXPECT_EQ("fo", cs.GetUsername());
    EXPECT_EQ("ob:ar@foo@ba", cs.GetPassword());
    EXPECT_EQ("r.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse10) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foobar@foob@ar.com:14578");
    EXPECT_EQ("foobar@foob", cs.GetUsername());
    EXPECT_EQ("", cs.GetPassword());
    EXPECT_EQ("ar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Pars11) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://:@:/");
    EXPECT_EQ("", cs.GetUsername());
    EXPECT_EQ("", cs.GetPassword());
    EXPECT_EQ("", cs.GetHostname());
    EXPECT_EQ("", cs.GetPort());
    EXPECT_EQ("", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse12) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foo:bar@foobar.com:14578:157/12");
    EXPECT_EQ("foo", cs.GetUsername());
    EXPECT_EQ("bar", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578:157", cs.GetPort());
    EXPECT_EQ("12", cs.GetPath());
}


TEST(RedisConnectionStringParser, Parse13) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foo:bar@foobar.com:14578//");
    EXPECT_EQ("foo", cs.GetUsername());
    EXPECT_EQ("bar", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("/", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse14) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foo:bar@foobar.com:14578/0/");
    EXPECT_EQ("foo", cs.GetUsername());
    EXPECT_EQ("bar", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("0/", cs.GetPath());
}

TEST(RedisConnectionStringParser, Parse15) {
    RedisConnectionString cs = RedisConnectionStringParser::Parse("redis://foo:bar@foobar.com:14578/0/1/2");
    EXPECT_EQ("foo", cs.GetUsername());
    EXPECT_EQ("bar", cs.GetPassword());
    EXPECT_EQ("foobar.com", cs.GetHostname());
    EXPECT_EQ("14578", cs.GetPort());
    EXPECT_EQ("0/1/2", cs.GetPath());
}

}
