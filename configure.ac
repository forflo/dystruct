AC_PREREQ(2.59)

dnl initialize systems
AC_INIT([dynstruct], [0.1], [mayer.florian@web.de])
AM_INIT_AUTOMAKE([1.9 gnu])
LT_INIT dnl initialize libtool

dnl configuration actions
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_CANONICAL_HOST

dnl checks for programs
AC_PROG_CC

dnl check libraries
AC_CHECK_LIB([cunit], 
	[CU_initialize_registry])
dnl [AS_BOX([CUnit is installed])], 
dnl [AC_MSG_ERROR([The library cunit is missing!])])

dnl check functions
AC_FUNC_MALLOC
AC_FUNC_REALLOC

dnl check headers
AC_CHECK_HEADERS([stdio.h, stdlib.h, CUnit/Cunit.h, CUnit/Basic.h])


AC_OUTPUT
