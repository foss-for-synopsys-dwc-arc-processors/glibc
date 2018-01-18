/* Machine-dependent definitions for profiling support.  ARC version.
   Copyright (C) 1996-2018 Free Software Foundation, Inc.
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
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <sysdep.h>

#define _MCOUNT_DECL(frompc, selfpc)
static void __attribute_used__ __mcount_internal (u_long frompc, u_long selfpc)

/* mcount is not really supported, there are better tools now */
#define MCOUNT						\
  asm (".globl __mcount\n\t"				\
       ".type __mcount,@function\n\t"			\
       "__mcount:\n\t"					\
       "flag 1	\n\t"					\
       ".size __mcount, . - __mcount\n\t"		\
       );
