/* Low-level functions for atomic operations. ARC version.
   Copyright (C) 2012-2017 Free Software Foundation, Inc.
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

#ifndef _ARC_BITS_ATOMIC_H
#define _ARC_BITS_ATOMIC_H 1

#include <stdint.h>

typedef int32_t atomic32_t;
typedef uint32_t uatomic32_t;
typedef int_fast32_t atomic_fast32_t;
typedef uint_fast32_t uatomic_fast32_t;

typedef intptr_t atomicptr_t;
typedef uintptr_t uatomicptr_t;
typedef intmax_t atomic_max_t;
typedef uintmax_t uatomic_max_t;

#define __HAVE_64B_ATOMICS 0
#define USE_ATOMIC_COMPILER_BUILTINS 0
#define ATOMIC_EXCHANGE_USES_CAS 1

#define __arch_compare_and_exchange_val_8_acq(mem, newval, oldval)	\
  (abort (), (__typeof (*mem)) 0)
#define __arch_compare_and_exchange_val_16_acq(mem, newval, oldval)	\
  (abort (), (__typeof (*mem)) 0)
#define __arch_compare_and_exchange_val_64_acq(mem, newval, oldval)	\
  (abort (), (__typeof (*mem)) 0)

#define __arch_compare_and_exchange_bool_8_acq(mem, newval, oldval)	\
  (abort (), 0)
#define __arch_compare_and_exchange_bool_16_acq(mem, newval, oldval)	\
  (abort (), 0)
#define __arch_compare_and_exchange_bool_64_acq(mem, newval, oldval)	\
  (abort (), 0)

#define __arch_compare_and_exchange_val_32_acq(mem, newval, oldval)	\
  ({									\
	__typeof(*(mem)) prev;						\
									\
	__asm__ __volatile__(						\
	"1:	llock   %0, [%1]	\n"				\
	"	brne    %0, %2, 2f	\n"				\
	"	scond   %3, [%1]	\n"				\
	"	bnz     1b		\n"				\
	"2:				\n"				\
	: "=&r"(prev)							\
	: "r"(mem), "ir"(oldval),					\
	  "r"(newval) /* can't be "ir". scond can't take limm for "b" */\
	: "cc", "memory");						\
									\
	prev;								\
  })

# define atomic_exchange_acq(mem, newvalue) \
  ({									\
	__typeof(*(mem)) __val = (newvalue);				\
									\
	__asm__ __volatile__(						\
	"1:	ex   %0, [%1]	\n"					\
	: "+r"(__val)							\
	: "r"(mem)							\
	: "memory");							\
									\
	__val;								\
  })

#define atomic_full_barrier()  ({ asm volatile ("dmb 3":::"memory"); })

#endif /* _ARC_BITS_ATOMIC_H */
