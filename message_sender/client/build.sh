#!/bin/sh

autoscan
aclocal
autoconf
autoheader   #after autoheader , create a Makefile.am then continue execute follow command
automake --add-missing
./configure CXXFLAGS= CFLAGS=
make
