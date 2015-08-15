# Redis CLI CS
A C++ Redis CLI client connection string (URI) connector.

Basically the program parses its first parameter/argument which is a connection string (URI) to a Redis server, then launches the redis-cli program with the proper parameters to connect to a Redis server.

# Install
The program works on UNIX systems where the redis-cli (redis-tools) client is avaiable. You have to compile the source code. You need the [g++](https://gcc.gnu.org/) compiler, and the [GNU make](https://www.gnu.org/software/make/).

If you want to compile and run the unit tests you need the [GoogleTest](https://code.google.com/p/googletest/) lib.

First you have to clone the repository:
```
git clone https://github.com/Anubisss/redis-cli-cs
```

Then you compile the source and install the program:
```
cd redis-cli-cs
make
sudo make install
```

``Make install`` copies the redis-cli-cs executable program to the /usr/local/bin directory.

So if you want to "uninstall" the program just delete the executable:``
rm /usr/local/bin/redis-cli-cs``

# Documentation
To get HTML documentation into the docs directory, just use [Doxygen](http://doxygen.org/) in the source root directory.
```
doxygen Doxyfile
```

# Test, develop
If you want to just test or develop the code you can use a [Vagrant](https://www.vagrantup.com/) box.

Start a Vagrant box and SSH into it:
```
vagrant up
vagrant ssh
```

Compiles the source, runs unit tests, test the client, generates docs:
```
cd /vagrant
make
make tests
make install
redis-cli-cs redis://test.com
doxygen Doxyfile
```

# How to use
If you want to connect to the Redis server which parameters are the following:
* hostname: localhost
* port: 12345
* pasword: passw
* db index: 6

You have to use this command:
```
redis-cli-cs redis://:passw@localhost:12345/6
```

Which will execute the following command: ``redis-cli -a "passw" -h "localhost" -p "12345" -n "6"``

If you want to pass params to redis-cli: ``redis-cli-cs redis://:passw@localhost:12345/6 --bigkeys --latency-history``

Will execute this: ``redis-cli -a "passw" -h "localhost" -p "12345" -n "6" --bigkeys --latency-history``

**The redis-cli program have to be in your PATH to make redis-cli-cs workable.**

# License
The MIT License (MIT)
