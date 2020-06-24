/* syscall - indirect system call.
   Copyright (C) 2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */

#include <sysdep.h>

ENTRY (syscall)
	MOVR	r8, r0
	MOVR	r0, r1
	MOVR	r1, r2
	MOVR	r2, r3
	MOVR	r3, r4
	MOVR	r4, r5
	MOVR	r5, r6

	ARC_TRAP_INSN
	BRRhi	r0, -4096, L (call_syscall_err)
	j	[blink]
PSEUDO_END (syscall)
