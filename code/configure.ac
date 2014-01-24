
AC_INIT([Chaos simulator], [0.5], [matthieu.journault@free.fr],
        [main_cc], [])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define silent-rules])
AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN],
[test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([docs/Doxyfile])])
AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([SFML/Graphics.hpp])
AC_LANG_POP([C++])
AC_PROG_CXX
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
