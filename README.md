Dystruct
========

Abstract
--------
Dystruct is a little C-Library that lets you easily build your own
C-Structures at runtime.

If you, for example, don't know which kinds of structures you have to pass to a
dynamically called function (with libffi), you'll have to build them on the heap at runtime. This
library does just that while taking care of the correct alignment requirements of the 
members.

Use case
--------
As an use case example, consider the following code:

    struct flat {
        int a;
        double b;
        char c;
    };
    
    [...]
    
    int do_sth(void){
        struct flat *s = malloc(sizeof(struct flat));
        s->a = 42;
        s->b = 424242.424242
        s->c = '*';
        
        return 0;
    }

The structure to which s points now lays on the heap and
looks like this:

    Offset: 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 
    --------+-----------+-----------+-----------------------+
            |    42     |  padding  |    424242.424242      |
    --------+-----------+-----------+-----------------------+
    Offset: 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33
    --------+--+--------+-----------+
            |* |     padding        |
    --------+--+--------+-----------+

Configuration
-------------
The configure script provides the following additional
command line options.

* --enable-uint8-align=[integer] 
* --enable-uint16-align=[integer]
* --enable-uint32-align=[integer]
* --enable-uint64-align=[integer]
* --enable-double-align=[integer]
* --enable-float-align=[integer] 
* --enable-ptr-align=[integer]

With these options you can adjust the platform
specific alignment requirements for the host you'll be using
the library. Notice that you should only use powers of two
as values for [integer]!

Installation
------------
Just use these commands:

    $ ./configure [option=value] ...
    $ make && make check
    $ make install

Build system
============

Development
-----------
After a fresh checkout of the repository, just execute the following command:

    $ autoreconf --install

This will prepare the build system for your usage.

Silent make rules
-----------------
If you rather appreciate silent (or more silent)
build processes, you can run the configure script 
as follows:

    $ ./configure --enable-silent-rules

While this does not completely silence the build, most of the commands executed by make rules
won't be shown anymore. Make will still output cd messages, though.
