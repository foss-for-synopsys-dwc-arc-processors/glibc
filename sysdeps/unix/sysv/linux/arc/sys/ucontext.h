/* struct ucontext definition, ARC version.
   Copyright (C) 2017 Free Software Foundation, Inc.
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

typedef struct
  {
    unsigned long pad;
    struct {
      unsigned long bta, lp_start, lp_end, lp_count;
      unsigned long status32, ret, blink, fp, gp;
      unsigned long r12, r11, r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0;
      unsigned long sp;
    } scratch;
    unsigned long pad2;
    struct {
      unsigned long r25, r24, r23, r22, r21, r20;
      unsigned long r19, r18, r17, r16, r15, r14, r13;
    } callee;
    unsigned long efa;
    unsigned long stop_pc;
    unsigned long r30, r58, r59;
  } mcontext_t;

/* Userlevel context.  */
typedef struct ucontext_t
  {
    unsigned long uc_flags;
    struct ucontext_t *uc_link;
    stack_t uc_stack;
    mcontext_t uc_mcontext;
    sigset_t uc_sigmask;
  } ucontext_t;

#endif /* sys/ucontext.h */
