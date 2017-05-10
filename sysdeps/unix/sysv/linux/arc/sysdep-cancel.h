/* Assembler macros with cancellation support, ARC version.
   Copyright (C) 2003-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <sysdep.h>
#include <tls.h>
#ifndef __ASSEMBLER__
# include <nptl/pthreadP.h>
#endif

#if IS_IN (libc)
#define BR_ERRNO_SETTER	        b PLTJMP(HIDDEN_JUMPTARGET(__syscall_error))
#else
#define BR_ERRNO_SETTER	        b PLTJMP(__syscall_error)
#endif

#if IS_IN (libc) || IS_IN (libpthread) || IS_IN (librt)

#ifdef __ASSEMBLER__

# undef PSEUDO
# define PSEUDO(name, syscall_name, nargs)				\
   /* vanilla version */				ASM_LINE_SEP	\
   ENTRY(name##_nocancel)				ASM_LINE_SEP	\
      DO_CALL (__NR_##syscall_name)			ASM_LINE_SEP	\
      jls  [blink]					ASM_LINE_SEP	\
      BR_ERRNO_SETTER					ASM_LINE_SEP	\
   END(name##_nocancel)					ASM_LINE_SEP	\
   /* thread cancellation variant */			ASM_LINE_SEP	\
   ENTRY(name)			    			ASM_LINE_SEP	\
      SINGLE_THREAD_P					ASM_LINE_SEP	\
      bz name##_nocancel				ASM_LINE_SEP	\
      DOCARGS_##nargs  /* stash syscall args */		ASM_LINE_SEP	\
      CENABLE          /* call enable_asynccancel */	ASM_LINE_SEP	\
      mov r9, r0       /* Safe-keep mask */ 		ASM_LINE_SEP	\
      UNDOCARGS_##nargs	/* restore syscall args */	ASM_LINE_SEP	\
      DO_CALL (__NR_##syscall_name)			ASM_LINE_SEP	\
      PUSH  r0         /* save syscall return value */	ASM_LINE_SEP	\
      mov   r0, r9  /* mask for disable_asynccancel */  ASM_LINE_SEP	\
      CDISABLE						ASM_LINE_SEP	\
      POP  r0       /* get syscall ret value back */	ASM_LINE_SEP	\
      POP  blink    /* UNDOCARGS left blink on stack */	ASM_LINE_SEP	\
      cmp  r0, -1024					ASM_LINE_SEP	\
      jls  [blink]					ASM_LINE_SEP	\
      BR_ERRNO_SETTER					ASM_LINE_SEP	\
   END(name)

#undef	PSEUDO_END
#define	PSEUDO_END(name)	\

# if IS_IN (libpthread)
#  define CENABLE	bl PLTJMP(__pthread_enable_asynccancel)
#  define CDISABLE	bl PLTJMP(__pthread_disable_asynccancel)
# elif IS_IN (libc)
#  define CENABLE	bl PLTJMP(__libc_enable_asynccancel)
#  define CDISABLE	bl PLTJMP(__libc_disable_asynccancel)
# elif IS_IN (librt)
#  define CENABLE	bl PLTJMP(__librt_enable_asynccancel)
#  define CDISABLE	bl PLTJMP(__librt_disable_asynccancel)
# else
#  error Unsupported library
# endif

#undef DO_CALL
#define DO_CALL(num)				\
	mov r8, num		ASM_LINE_SEP	\
	ARC_TRAP_INSN		ASM_LINE_SEP	\
	cmp r0, -1024

.macro PUSH reg
	st.a \reg, [sp, -4]
	cfi_adjust_cfa_offset (4)
	cfi_rel_offset (\reg, 0)
.endm

.macro POP reg
	ld.ab \reg, [sp, 4]
	cfi_adjust_cfa_offset (-4)
	cfi_restore (\reg)
.endm

#define DOCARGS_0	PUSH blink
/* don't pop blink at this point */
#define UNDOCARGS_0	ld   blink, [sp]

#define DOCARGS_1	DOCARGS_0  ASM_LINE_SEP	PUSH r0
#define UNDOCARGS_1	POP  r0    ASM_LINE_SEP	UNDOCARGS_0

#define DOCARGS_2	DOCARGS_1  ASM_LINE_SEP	PUSH r1
#define UNDOCARGS_2	POP  r1    ASM_LINE_SEP	UNDOCARGS_1

#define DOCARGS_3	DOCARGS_2  ASM_LINE_SEP	PUSH r2
#define UNDOCARGS_3	POP  r2    ASM_LINE_SEP	UNDOCARGS_2

#define DOCARGS_4	DOCARGS_3  ASM_LINE_SEP	PUSH r3
#define UNDOCARGS_4	POP  r3    ASM_LINE_SEP	UNDOCARGS_3

#define DOCARGS_5	DOCARGS_4  ASM_LINE_SEP	PUSH r4
#define UNDOCARGS_5	POP  r4    ASM_LINE_SEP	UNDOCARGS_4

#define DOCARGS_6	DOCARGS_5  ASM_LINE_SEP	PUSH r5
#define UNDOCARGS_6	POP  r5    ASM_LINE_SEP	UNDOCARGS_5

#define DOCARGS_7	DOCARGS_6  ASM_LINE_SEP	PUSH r6
#define UNDOCARGS_7	POP  r6    ASM_LINE_SEP	UNDOCARGS_6

#  define SINGLE_THREAD_P 					\
    THREAD_SELF r9     				ASM_LINE_SEP	\
    ld	   r10, [r9, MULTIPLE_THREADS_OFFSET]	ASM_LINE_SEP	\
    cmp    r10, 0

#else /* !__ASSEMBLER__ */

/* TBD: Can use @__local_multiple_threads for libc/libpthread like ARM */
#   define SINGLE_THREAD_P	\
    __glibc_likely(THREAD_GETMEM (THREAD_SELF, header.multiple_threads) == 0)

#endif	/* !__ASSEMBLER__ */

#elif !defined __ASSEMBLER__

# define SINGLE_THREAD_P 1
# define NO_CANCELLATION 1

#endif

#ifndef __ASSEMBLER__
# define RTLD_SINGLE_THREAD_P \
  __glibc_likely (THREAD_GETMEM (THREAD_SELF, header.multiple_threads) == 0)
#endif
