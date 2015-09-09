/* struct ucontext definition, ARC version.
   Copyright (C) 2017-2018 Free Software Foundation, Inc.
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

/* System V/ARC ABI compliant context switching support.  */

#ifndef _SYS_UCONTEXT_H
#define _SYS_UCONTEXT_H	1

#include <features.h>

#include <bits/types/sigset_t.h>
#include <bits/types/stack_t.h>

#ifdef __USE_MISC
# define __ctx(fld) fld
#else
# define __ctx(fld) __ ## fld
#endif

typedef struct
  {
    unsigned long __ctx(pad);
    struct {
      unsigned long __ctx(bta);
      unsigned long __ctx(lp_start), __ctx(lp_end), __ctx(lp_count);
      unsigned long __ctx(status32), __ctx(ret), __ctx(blink);
      unsigned long __ctx(fp), __ctx(gp);
      unsigned long __ctx(r12), __ctx(r11), __ctx(r10), __ctx(r9), __ctx(r8);
      unsigned long __ctx(r7), __ctx(r6), __ctx(r5), __ctx(r4), __ctx(r3);
      unsigned long __ctx(r2), __ctx(r1), __ctx(r0);
      unsigned long __ctx(sp);
    } __ctx(scratch);
    unsigned long __ctx(pad2);
    struct {
      unsigned long __ctx(r25), __ctx(r24), __ctx(r23), __ctx(r22), __ctx(r21);
      unsigned long __ctx(r20), __ctx(r19), __ctx(r18), __ctx(r17), __ctx(r16);
      unsigned long __ctx(r15), __ctx(r14), __ctx(r13);
    } __ctx(callee);
    unsigned long __ctx(efa);
    unsigned long __ctx(stop_pc);
    unsigned long __ctx(r30), __ctx(r58), __ctx(r59);
  } mcontext_t;

/* Userlevel context.  */
typedef struct ucontext_t
  {
    unsigned long __ctx(uc_flags);
    struct ucontext_t *uc_link;
    stack_t uc_stack;
    mcontext_t uc_mcontext;
    sigset_t uc_sigmask;
  } ucontext_t;

#undef __ctx

#endif /* sys/ucontext.h */
