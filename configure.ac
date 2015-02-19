AC_PREREQ(2.69)

dnl initialize systems
AC_INIT([dynstruct], [0.3], [mayerflorian@me.com])
LT_INIT
AM_INIT_AUTOMAKE

##
# Some custom helper vars
##
CUNIT_NOTF="
	CUnit/Cunit.h or CUnit/CUnit.h not found!
	Please install the dev package of cunit.
"

CUNIT_BASIC_NOTF="
	CUnit/Basic.h not found!
	Please install the dev package of cunit.
"

dnl checks for programs
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_CXX
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

dnl check libraries
AC_SEARCH_LIBS([CU_initialize_registry], 
	[cunit], 
	[have_lib_cunit=yes],
	[have_lib_cunit=no])

if test "x${have_lib_cunit}" = xno; then
	AC_MSG_ERROR([
	The unit testing framework cunit
	could not be found! Please do
	install it before you build this
	project.
	], [1])
fi

dnl check headers
AC_CHECK_HEADERS([stdio.h stdlib.h])


AC_CHECK_HEADER([CUnit/CUnit.h],
	[AC_DEFINE([CUINT_K1], [1], [CUnit/CUnit.h])], 
	[have_cunit_k1=no])

AC_CHECK_HEADER([CUnit/Cunit.h],
	[AC_DEFINE([CUINT_K2], [1], 
	[CUnit/Cunit.h])], 
	[have_cunit_k2=no])

if test "x${have_cunit_k1}" = xno; then
	if test "x${have_cunit_k2}" = xno; then
		AC_MSG_ERROR([$CUNIT_NOTF], [1])
	fi
fi

AC_CHECK_HEADER([CUnit/Basic.h],
	[AC_DEFINE([CUNIT_BASIC], [1], [CUnit/Basic.h])],
	[AC_MSG_ERROR([$CUNIT_BASIC_NOTF], [1])])

dnl Adds various commandline options
dnl to the resulting configure script
AC_ARG_ENABLE([uint8-align],
	[AS_HELP_STRING([--enable-uint8-align=<integer>], 
		[custom uint8 alignment])], 
	[AC_DEFINE_UNQUOTED([DSTRU_UINT_8_AL], 
		[${enableval}], 
		[UINT8 alignment adjustment])],
	[])

AC_ARG_ENABLE([uint16-align],
	[AS_HELP_STRING([--enable-uint16-align=<integer>], 
		[custom uint16 alignment])], 
	[AC_DEFINE_UNQUOTED([DSTRU_UINT_16_AL], 
		[${enableval}], 
		[UINT16 alignment adjustment])],
	[])

AC_ARG_ENABLE([uint32-align],
	[AS_HELP_STRING([--enable-uint32-align=<integer>], 
		[custom uint32 alignment])], 
	[AC_DEFINE_UNQUOTED([DSTRU_UINT_32_AL], 
		[${enableval}], 
		[UINT32 alignment adjustment])],
	[])

AC_ARG_ENABLE([uint64-align],
	[AS_HELP_STRING([--enable-uint64-align=<integer>], 
		[custom uint64 alignment])], 
	[AC_DEFINE_UNQUOTED([DSTRU_UINT_64_AL], 
		[${enableval}], 
		[UINT64 alignment adjustment])],
	[])

AC_ARG_ENABLE([double-align],
	[AS_HELP_STRING([--enable-double-align=<integer>], 
		[custom double alignment])], 
	[AC_DEFINE_UNQUOTED([DSTRU_DOUBLE_AL], 
		[${enableval}], 
		[DOUBLE alignment adjustment])],
	[])

AC_ARG_ENABLE([float-align],
	[AS_HELP_STRING([--enable-float-align=<integer>], 
		[custom float alignment])], 
	[AC_DEFINE_UNQUOTED([DSTRU_FLOAT_AL], 
		[${enableval}], 
		[FLOAT alignment adjustment])],
	[])

dnl check for types
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

dnl check functions
AC_FUNC_MALLOC
AC_FUNC_REALLOC

dnl configuration actions
AC_CONFIG_HEADERS([config.h])
dnl specifies the .in Files to process 
AC_CONFIG_FILES([Makefile:Makefile.in
	src/Makefile:src/Makefile.in
	test/Makefile:test/Makefile.in
	])

AC_OUTPUT

AC_MSG_NOTICE([

Summary:
--------
${PACKAGE_NAME} Version ${PACKAGE_VERSION}

Prefix: ${prefix}.
Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}

Now type: 
$ make && make install
])
