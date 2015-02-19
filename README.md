Dystruct
========

Abstract
--------
Dystruct is a little C-Library that lets you easily build your own
C-Structures at runtime.

If you, for example, don't know which kinds of structures you have to pass to a
dynamically called function (libffi) , you have to build them on the heap at runtime. This
Library does just that while taking care about the correct alignment of the 
members. 

Installation
-----------
Just follow the instructions in INSTALL

Development
-----------
After a fresh checkout of the repository, just execute the following command.

    $ autoreconf --install

This will prepare the build system for you usage.

Notice
------
If you rather appreciate silence (or more silence)
build processes, you can run the configure script 
as follows:

    $ ./configure --enable-silent-rules

While this not completely silences the build -
make will still output change directory messages -
almost all of the commands executed by make rules
won't be shown anymore.
