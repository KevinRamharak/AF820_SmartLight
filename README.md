# AF820_SmartLight
Version 2 of an C++ implementation that can communicate with the '[AF820 SmartLight](http://www.vstarcam.com/AF820-Smart-Light-141.html)'.

## Introduction
This is the result of a rewrite of [this project](https://github.com/KevinRamharak/af820-smartlight).
The old project was written with very limited knowledge of C/C++ and I have learned a lot since then.
Therefore this project was born, where I try to write a more general aproach to a command line application that should work out of the box.
Furthermore I will also try to provide scripts (probably Python) that can configure an 'AF820 SmartLight' from out of the (literal) box.

## Todo list:
- [x] Port the old struct/classes into new C++ classes with correct inheritance
- [ ] Write a simple and non-blocking UDP/IP abstraction to send and receive packets
- [ ] Create a (decent) API so it can be used for other programs than the command line application
- [ ] Daemonize the command line application
- [ ] Write helper scripts to connect to a new 'AF820 SmartLight' and configure it
- [ ] Debug more of the protocol :
  + [ ] Find out how the remote registration/spying service works and if it is possible to disable it
  + [ ] Write some helper scripts to quickly manipulate existing packets into new ones and store the results
  + [ ] Do analysis on the above generated data
- [ ] Port the program to different languages :
  + [ ] JavaScript Node
    * [ ] as JS module
    * [ ] (?) as a C++ extension
  + [ ] Python (3)
    * [ ] as a Python module
    * [ ] (?) as a C extension
  + [ ] PHP
    * [ ] as a PHP Library
    * [ ] (?) as a C/C++ extension
  + [ ] C
    * [ ] Library

## Purpose
Main focus and goal of this project is Fun/Education. The more i know about low level programming the more i love it.
There is something exiting and engaging about manipulating a (proprietary) byte protocol on actual byte level.

## External / Sources
### Info about what information i used and where i got it
- Most of the protocol information is from this guys [MQTT implementation](https://gitlab.com/iot/af820smartlight)
- For the C socket programming i used (Beej's networking guide](http://beej.us/guide/bgnet/)

## Notes
### `UDP::send` vs `UDP::Connection`
So I could just implement a 'simple' function `send`. This would take an IP Adress, Port, a byte pointer and a length and then send it over the wire.

Or I could implement a `Connection` class that would be initialised with an IP Adress and Port. And could sends byte buffers (and maybe `Protocol::*` instances) over the wire. Buy `Connection` implies some sort of duplex stream. This could be implemented with the `Protocol::Standard::sequence_number` bytes but that would be only specific for this custom protocol.

So I will probably implement `send` since it would be a nice and simple abstraction that has its uses in this application. Maybe implement `Connection` if this can be shaped for something usefull and non reliant on the custom `Protocol::*` classes.
