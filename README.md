
Oculus Rift - eDVS Robot - Server Software
==========================================

#Requirements
Tested with Ubuntu 13.10, Ubuntu 14.04 and Ubuntu 15.04.<br>

Install the following packages from the repository:
- git
- libboost-system-dev
- libboost-thread-dev
- qt5-qmake

All in one command:<br>
- `sudo apt install git libboost-system-dev libboost-thread-dev qt5-qmake`

# Building

1. clone this repository and make sure to get the submodules<br>`git clone https://github.com/stefan-urban/oculus-server.git && cd oculus-server`<br>`git submodule update --init`
2. `mkdir build && cd build`
3. `qmake ..`
4. `make`

# Starting

Running the application with `./oculus-server` will open a server at port `4000`.



#License

Copyright (C) 2015  Stefan Urban

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.<br>
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.<br>
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

