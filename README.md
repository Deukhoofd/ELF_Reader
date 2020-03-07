# ELF_Reader

This program uses the output of ``readelf -wi`` on an ELF file built with debug symbols included, and outputs a list of exported functions, including their return types and parameters, and enums in that file in readable json. 

Parameters are:
- ``-f``: a list of files to use as input, i.e. ``-f foobar.so barfoo.so``
- ``-n``: a prefix for which functions to output. If given, only exported functions starting with this prefix will be output. Note that if this prefix is not given, all C library functions are included as well in the output.
- ``-o``: the output file.
