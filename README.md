Dystruct
========

Abstract
--------
Dystruct is a little C-Library that lets you easily build your own
C-Structures at runtime.

If you, for example, don't know which kinds of structures you have to pass to a
dynamically called function (with libffi), you'll have to build them on the heap at runtime. This
library does just that while taking care about the correct alignment requirements of the 
members. 

Installation
-----------
The configure script provides the following additional
command line options.

* --enable-uint8-align=[integer] 
* --enable-uint16-align=[integer]
* --enable-uint32-align=[integer]
* --enable-uint64-align=[integer]
* --enable-double-align=[integer]
* --enable-float-align=[integer] 

With these options you can adjust the platform
specific alignment requirements for the host you'll be using
the library. Notice that you should only use powers of two
as value for [integer]!

Build system
============

Development
-----------
After a fresh checkout of the repository, just execute the following command.

    $ autoreconf --install

This will prepare the build system for you usage.

Silent make rules
-----------------
If you rather appreciate silence (or more silence)
build processes, you can run the configure script 
as follows:

    $ ./configure --enable-silent-rules

While this does not completely silence the build,
- make will still output cd messages -
most of the commands executed by make rules
won't be shown anymore. 
