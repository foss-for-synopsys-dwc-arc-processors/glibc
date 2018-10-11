/* Create new context for ARC
   Copyright (C) 2015-2018 Free Software Foundation, Inc.
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
#include <stdarg.h>
#include <stdint.h>
#include <sys/ucontext.h>

void
__makecontext (ucontext_t *ucp, void (*func) (void), int argc, ...)
{
  extern void __startcontext (void) attribute_hidden;
  unsigned long sp, *r;
  va_list vl;
  int i, reg_args, stack_args;

  sp = ((unsigned long) ucp->uc_stack.ss_sp + ucp->uc_stack.ss_size) & ~7;

  ucp->uc_mcontext.scratch.sp = sp;
  ucp->uc_mcontext.scratch.fp = 0;

  /* __startcontext is sort of trampoline to invoke @func
   *  From setcontext() pov, the resume address is __startcontext,
   *  set it up in BLINK place holder*/
  ucp->uc_mcontext.scratch.blink = (unsigned long) &__startcontext;

  /* __startcontext passed 2 types of args
   *    - args to @func setup in canonical r0-r7
   *    - @func itself in r9, and next function in r10
   */
  ucp->uc_mcontext.callee.r13 = (unsigned long) func;
  ucp->uc_mcontext.callee.r14 = (unsigned long) ucp->uc_link;

  r = &ucp->uc_mcontext.scratch.r0;

  va_start (vl, argc);

  reg_args = argc > 8 ? 8 : argc;
  for (i = 0; i < reg_args; i++) {
      *r-- = va_arg(vl, unsigned long);
  }

  stack_args = argc - reg_args;

  if (__glibc_unlikely(stack_args > 0)) {

    sp -=  stack_args * sizeof (unsigned long);
    ucp->uc_mcontext.scratch.sp = sp;
    r = (unsigned long *)sp;

    for (i = 0; i < stack_args; i++) {
        *r++ = va_arg(vl, unsigned long);
    }
  }

  va_end (vl);
}

weak_alias (__makecontext, makecontext)
