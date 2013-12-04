#!/bin/bash

export x=`find . -iname *.h | tr "\n" " "` ;
export y=`find . -iname *.cc | tr "\n" " "`;
export z=`ls -R | grep : |grep src |grep -v widgets| cut -c3- | rev | cut -c2- | rev | sed '1,$ s/^/-I/' | tr "\n" " "`;
echo "

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = \${ACLOCAL_FLAGS}
AM_CXXFLAGS = -Wall -std=c++11
AM_LDFLAGS = -ltgui -lsfml-audio\$(SFML_LIB_SUFFIX) -lsfml-graphics\$(SFML_LIB_SUFFIX) -lsfml-system\$(SFML_LIB_SUFFIX) -lsfml-window\$(SFML_LIB_SUFFIX) -lboost_system\$(BOOS_LIB_SUFFIX) -lpthread -std=c++11
bin_PROGRAMS = game
game_LDADD = -ltgui -lsfml-audio\$(SFML_LIB_SUFFIX) -lsfml-graphics\$(SFML_LIB_SUFFIX) -lsfml-system\$(SFML_LIB_SUFFIX) -lsfml-window\$(SFML_LIB_SUFFIX) -lboost_system\$(BOOS_LIB_SUFFIX) -lpthread
game_CFLAGS = -std=c++11
game_LDFLAGS =
game_SOURCES = $x $y
dist_noinst_SCRIPTS = autogen.sh
AM_CPPFLAGS = $z
" > Makefile.am
