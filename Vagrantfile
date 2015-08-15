Vagrant.configure(2) do |config|
  config.vm.box = "ubuntu/trusty64"

  config.vm.provision "shell", inline: <<-SHELL
    sudo apt-get update -y
    sudo apt-get install -y g++ unzip doxygen redis-tools
    wget https://googletest.googlecode.com/files/gtest-1.7.0.zip
    unzip gtest-1.7.0.zip
    cd gtest-1.7.0
    ./configure
    make
    cp -a include/gtest /usr/include
    cp -a lib/.libs/* /usr/lib/
    SHELL
end
