#!/bin/bash

export x=`find . -iname *.h | tr "\n" " "` ;
export y=`find . -iname *.cc | tr "\n" " "`;
export z=`ls -R | grep : | grep src | cut -c3- | rev | cut -c2- | rev | sed '1,$ s/^/-I/' | tr "\n" " "`;
echo "
AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = \${ACLOCAL_FLAGS}
bin_PROGRAMS = game
game_LDADD = -lsfml-graphics\$(SFML_LIB_SUFFIX) -lsfml-system\$(SFML_LIB_SUFFIX) -lsfml-window\$(SFML_LIB_SUFFIX)
game_SOURCES = $x $y
dist_noinst_SCRIPTS = autogen.sh
AM_CPPFLAGS = $z
" > Makefile.am
