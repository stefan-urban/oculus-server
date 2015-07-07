
Oculus Rift - eDVS Robot - Server Software
==========================================

#Requirements
Tested with Ubuntu 14.04 and Ubuntu 15.04 with Nouveau graphics drivers.<br>
Does not work with Intel graphic adapters!

Install the following packages from the repository:
- git
- libboost-system1.55-dev
- libboost-thread1.55-dev
- qt5-qmake

All in one command:<br>
- `sudo apt install git libboost-system1.55-dev libboost-thread1.55-dev qt5-qmake`

# Building

1. clone this repository and make sure to get the submodules<br>`git clone https://github.com/stefan-urban/oculus-server.git && cd oculus-server`<br>`git submodule update --init`
2. `mkdir build && cd build`
3. `qmake ..`
4. `make`

# Starting

Run application with `./oculus-server`

