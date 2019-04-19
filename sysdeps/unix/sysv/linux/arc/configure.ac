GLIBC_PROVIDES dnl See aclocal.m4 in the top level source directory.
# Local configure fragment for sysdeps/unix/sysv/linux/arc.

arch_minimum_kernel=3.9.0

# Extract "-mcpu=xxx" value from CC to install libs in a separate folder
arc_mcpu=[`echo $CC | grep -Po '\-mcpu=\K[^ ]+'`]

if test "$arc_mcpu" != "" ; then
	LIBC_SLIBDIR_RTLDDIR([lib/${arc_mcpu}], [lib/${arc_mcpu}])
fi
