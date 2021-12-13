AC_INIT([mocin], [0.1.0])

AC_PREREQ([2.59c])
AC_CANONICAL_SYSTEM
AC_CONFIG_SRCDIR([src/main.cc])
AM_INIT_AUTOMAKE([gnu])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CXX

# Check for openssl (ssl)
AC_CHECK_LIB([ssl], [OPENSSL_init_ssl], [],
	     [AC_MSG_FAILURE([can't find openssl! (ssl)])])

# Check for openssl (crypto)
AC_CHECK_LIB([crypto], [EVP_EncryptInit], [],
	     [AC_MSG_FAILURE([can't find openssl! (crypto)])])

# Check for libprotobuf
PKG_CHECK_MODULES([PROTOBUF], [protobuf >= 3.5.0])

# Check for the actual protobuf compiler (protoc)
AC_ARG_WITH([protoc],
    [AS_HELP_STRING([--with-protoc=/path/of/protoc],
        [Location of protoc (Protocol Buffer Compiler), Default is on path.])],
    [PROTOC="$withval"],
    [ AS_IF([test "x${PROTOC}" == "x"],
        [AC_PATH_PROG([PROTOC], [protoc], [no])])
    ]
)

AS_IF([test "${PROTOC}" == "no"], [AC_MSG_ERROR([protoc (Protocol Buffer Compiler) not found.])])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

# Check for profile builds
AC_ARG_ENABLE([profile],
    AS_HELP_STRING([--enable-profile], [Enable profiling (WARNING: Output is verbose!)]))

AS_IF([test "x$enable_profile" = "xyes"], [
	AC_SUBST([mocind_CPPFLAGS], [-fsanitize=undefined])
	AC_SUBST([mocind_LDFLAGS], [-fsanitize=undefined])
	AC_DEFINE([PROFILE], [1], [Profiling is enabled])
])

AC_OUTPUT

