#
# The MIT License (MIT)
#
# Copyright (c) 2015 David Vas <anuka|Anubisss>, http://anuka.me/
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

CC = g++
CXXFLAGS = -c -pedantic -Wall -Wextra -Weffc++

OUT_FILE = bin/test

OBJECTS = RedisConnectionStringParser.o RedisConnectionStringParserTests.o Main.o
SRC = ../src
SRC_TEST = .
INCLUDES = -I$(SRC)/

$(OUT_FILE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT_FILE) -lgtest -lpthread

RedisConnectionStringParser.o: $(SRC)/RedisConnectionStringParser.cpp
	$(CC) $(CXXFLAGS) $(SRC)/RedisConnectionStringParser.cpp

RedisConnectionStringParserTests.o: $(SRC_TEST)/RedisConnectionStringParserTests.cpp
		$(CC) $(CXXFLAGS) $(INCLUDES) $(SRC_TEST)/RedisConnectionStringParserTests.cpp

Main.o: $(SRC_TEST)/Main.cpp
	$(CC) $(CXXFLAGS) $(SRC_TEST)/Main.cpp

run:
	./$(OUT_FILE)

clean:
	rm -rf *.o $(OUT_FILE)
