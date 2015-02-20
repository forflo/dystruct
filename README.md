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

The structure s pointing to now lays on the heap and
looks like this:

    Offset: 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 
            +-----------+-----------+-----------------------+-
            |    42     |  padding  |    424242.424242      |-
            +-----------+-----------+-----------------------+-
    Offset: 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33
           -+--+--------+-----------+
           -|* |     padding        |
           -+--+--------+-----------+

As you can see, the cells 4 to 7 contain meaningless bytes filling
up the space between the member "a" and "b" of the recently defined structure "flat".
This is because the primitive type double has an alignment requirement
of 8, meaning that a double value can only start at an offset
which is a multiple of 8. The reason for this behaviour is very simple:
Performance! 

If the wordsize of an architecture is, for example, 8 bytes, you wouldn't
want the value of a double type begin at offset 7 and end at 15, because
this would force the processor to load two words (each one 8 bytes big) into some
working registers. However, if all double values were properly aligned,
every access to them could be done in just one cpu cycle.
[see also](http://en.wikipedia.org/wiki/Data_structure_alignment)

Ok, now I know some of the internal mechanisms of data structure alignment. But what
do I need your library for?

A very good question!

Consider the following scenario: 
You are building an interpreter for a programming
language that reads commands from the console and executes them as the user
types enter. (Python is such a programming language for example). 
Now you want
the users of your interpreter to be able to use native C-Functions from within the language. 
This is very possible and there is even a library that
enables you to load and call arbitrary functions at runtime, without compiling and linking
against libraries which contain them. (libffi provides such functionality)
While this would be sufficient for functions taking only values of primitive types, 
you, the programmer of the interpreter, would run into some severe problems when it
comes to functions taking merely a pointer to a structure laying on the heap.
What do you do? You can't use C-Constructs like

    strcut foo *f = malloc(...);
    call_func(funcpointer, f);
    
because you don't have access to the structure definition and thus cannot
rely on the compiler to do the things just right.

This is the point when it comes to this little library.
With it, the code above could be rewritten as follows:

    uint32_t i1 = 42;
    double d = 424242.424242;
    uint8_t c1 = '*'

    struct dstru_struct *ds1;
    
    dstru_add_uint32(DYN_S_UINT32, (void *) &i1, ds1);
    dstru_add_double(DYN_S_DOUBLE, (void *) &d, ds1);
    dstru_add_uint8(DYN_S_UINT8, (void *) &c1, ds1);
    dstru_finalize(ds1) == 0;
    
ds1 contains a member named "buffer", which is just a memory field.
This field now contains the exact same data as the initialized 
structure s in our first example, including both padding byte sections.

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
