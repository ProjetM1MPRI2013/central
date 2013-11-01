AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
bin_PROGRAMS = sfml
sfml_LDADD = -lsfml-graphics$(SFML_LIB_SUFFIX) -lsfml-system$(SFML_LIB_SUFFIX) -lsfml-window$(SFML_LIB_SUFFIX)
sfml_SOURCES = src/main.cc src/test/test.h src/test/test.cc
dist_noinst_SCRIPTS = autogen.sh
AM_CPPFLAGS = -Isrc -Isrc/test
