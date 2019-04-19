GLIBC_PROVIDES dnl See aclocal.m4 in the top level source directory.
# Local configure fragment for sysdeps/unix/sysv/linux/arc.

arch_minimum_kernel=3.9.0

# If "-mcpu=xxx" found in passed CC assume we're building for
# non-default CPU and thus we need to install libs in non-default location.
if AC_TRY_COMMAND([echo $CC | grep -F "mcpu" > /dev/null]);
then
	libc_cv_arc_arch=no

	# If this is ARCompact-based core
	AC_EGREP_CPP(yes, [#ifdef __ARC700__
			   yes
			   #endif
	],libc_cv_arc_arch=arc700)

	# If this is ARCv2-based core
	AC_EGREP_CPP(yes, [#ifdef __ARCHS__
			   yes
			   #endif
	],libc_cv_arc_arch=hs)

	if test $libc_cv_arc_arch = no; then
	  AC_MSG_ERROR([Unable to determine ARC architecture])
	fi

	if test $libc_cv_arc_arch = arc700; then
		# NPS400
		AC_EGREP_CPP(yes, [#ifdef __NPS400__
				   yes
				   #endif
		],libc_cv_arc_arch=nps400)
	else
		# Base-line HS38 + HW multiplier
		AC_EGREP_CPP(yes, [#ifdef __ARC_MPY__
				   yes
				   #endif
		],libc_cv_arc_arch=archs)

		# Base-line HS38 + HW quad-multiplier
		AC_EGREP_CPP(yes, [#ifdef __ARC_MPY_QMACW__
				   yes
				   #endif
		],libc_cv_arc_arch=hs38)

		# Base-line HS38 + HW quad-multiplier + FPU
		AC_EGREP_CPP(yes, [#ifdef __ARC_FPU_DP__
				   yes
				   #endif
		],libc_cv_arc_arch=hs38_linux)
	fi

	case $libc_cv_arc_arch in
	arc700)
	  LIBC_SLIBDIR_RTLDDIR([lib/arc700], [lib/arc700])
	  ;;
	nps400)
	  LIBC_SLIBDIR_RTLDDIR([lib/nps400], [lib/nps400])
	  ;;
	hs)
	  LIBC_SLIBDIR_RTLDDIR([lib/hs], [lib/hs])
	  ;;
	archs)
	  LIBC_SLIBDIR_RTLDDIR([lib/archs], [lib/archs])
	  ;;
	hs38)
	  LIBC_SLIBDIR_RTLDDIR([lib/hs38], [lib/hs38])
	  ;;
	hs38_linux)
	  LIBC_SLIBDIR_RTLDDIR([lib/hs38_linux], [lib/hs38_linux])
	  ;;
	esac
fi

