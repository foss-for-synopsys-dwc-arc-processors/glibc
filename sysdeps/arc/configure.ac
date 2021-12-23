GLIBC_PROVIDES dnl See aclocal.m4 in the top level source directory.
# Local configure fragment for sysdeps/arc.

AC_DEFINE(PI_STATIC_AND_HIDDEN)
libc_cv_have_sdata_section=no

# For ARC, historically ; was used for comments and not newline
# Later # also got added to comment list, but ; couldn't be switched to
# canonical newline as there's lots of code out there which will break
libc_cv_asm_line_sep='`'
AC_DEFINE_UNQUOTED(ASM_LINE_SEP, $libc_cv_asm_line_sep)

# For big endian ABI, generate a symbol for selecting right dynamic linker
AC_CACHE_CHECK([for big endian],
  [libc_cv_arc_be],
  [AC_EGREP_CPP(yes,[#ifdef __BIG_ENDIAN__
                      yes
                     #endif
  ], libc_cv_arc_be=yes, libc_cv_arc_be=no)])
if test $libc_cv_arc_be = yes; then
  # For shlib-versions.
  AC_DEFINE(HAVE_ARC_BE)
  LIBC_CONFIG_VAR([default-abi], [arcbe])
else
  LIBC_CONFIG_VAR([default-abi], [arcle])
fi

# For ARC700 ABI, generate a symbol for shlib-versions
AC_CACHE_CHECK([for arc700],
  [libc_cv_arc700],
  [AC_EGREP_CPP(yes,[#ifdef __ARC700__
                      yes
                     #endif
  ], libc_cv_arc700=yes, libc_cv_arc700=no)])
if test $libc_cv_arc700 = yes; then
  AC_DEFINE(HAVE_ARC700)
fi
