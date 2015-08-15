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
CXXFLAGS = -c
INSTALL = install

OUT_FILE = bin/redis-cli-cs

OBJECTS = RedisConnectionStringParser.o main.o
SRC = src

$(OUT_FILE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT_FILE)

RedisConnectionStringParser.o: $(SRC)/RedisConnectionStringParser.cpp
	$(CC) $(CXXFLAGS) $(SRC)/RedisConnectionStringParser.cpp

main.o: $(SRC)/Main.cpp
	$(CC) $(CXXFLAGS) $(SRC)/Main.cpp

clean:
	rm -rf *.o $(OUT_FILE)
	$(MAKE) -C test clean

install:
	$(INSTALL) $(OUT_FILE) /usr/local/bin

tests:
	$(MAKE) -C test
	$(MAKE) -C test run
