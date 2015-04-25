#!/bin/sh

autoscan  #scan all sub-program , justify which libraries program will need
	  #configure.scan 
cp  configure.scan configure.in 
aclocal
autoconf
autoheader
automake --add-missing
./configure CXXFLAGS= CFLAGS=
make



