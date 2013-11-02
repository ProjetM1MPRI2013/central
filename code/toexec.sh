#!/bin/bash

export x=`find -iname *.h | tr "\n" " "` ;
export y=`find -iname *.cc | tr "\n" " "`;
echo "
AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = \${ACLOCAL_FLAGS}
bin_PROGRAMS = sfml
sfml_LDADD = -lsfml-graphics\$(SFML_LIB_SUFFIX) -lsfml-system\$(SFML_LIB_SUFFIX) -lsfml-window\$(SFML_LIB_SUFFIX)
sfml_SOURCES = $x $y
dist_noinst_SCRIPTS = autogen.sh
AM_CPPFLAGS = -Isrc -Isrc/test
" > Makefile.am
