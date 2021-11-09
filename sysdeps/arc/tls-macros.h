/* Macros to support TLS testing in times of missing compiler support.  ARC version.
   Copyright (C) 2020-2021 Free Software Foundation, Inc.

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
   <https://www.gnu.org/licenses/>.  */

#include <sysdep.h>
#include "dl-tls.h"

/* For now.  */
#define TLS_LD(x)	TLS_IE(x)

#define TLS_GD(x)					\
  ({ void *__result;					\
     __asm__ ("ADDR %0, pcl, @" #x "@tlsgd \n"		\
	      ".tls_gd_ld " #x "\n"			\
	      : "=r" (__result));			\
	  __tls_get_addr(__result);			\
	  })

#define TLS_LE(x)					\
  ({ void *__result;					\
     void *tp = __builtin_thread_pointer ();		\
     __asm__ ("ADDR %0, %1, @" #x "@tpoff   \n"		\
	  : "=r" (__result) : "r"(tp));	        	\
     __result; })

#define TLS_IE(x)					\
  ({ void *__result;					\
     void *tp = __builtin_thread_pointer ();		\
     __asm__ ("LDR %0, pcl, @" #x "@tlsie       \n"     \
	  "ADDR %0, %1, %0                      \n"	\
	  : "=&r" (__result) : "r" (tp));		\
     __result; })
