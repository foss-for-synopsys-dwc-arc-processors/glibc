/* ARC specific sigaction and signal restorer
   Copyright (C) 1997-2017 Free Software Foundation, Inc.
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
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/syscall.h>

/*
 * Default sigretrun stub if user doesn't specify SA_RESTORER
 */
static void __default_rt_sa_restorer(void)
{
	INTERNAL_SYSCALL_NCS(__NR_rt_sigreturn, , 0);
}

#define SA_RESTORER	0x04000000

/* If @act is not NULL, change the action for @sig to @act.
   If @oact is not NULL, put the old action for @sig in @oact.  */
int
__libc_sigaction (int sig, const struct sigaction *act, struct sigaction *oact)
{
	struct sigaction kact;
	const struct sigaction *arg;

	/*
	 * SA_RESTORER is only relevant for act != NULL case
	 * (!act means caller only wants to know @oact)
	 */
	if (act && !(act->sa_flags & SA_RESTORER)) {
		kact.sa_restorer = __default_rt_sa_restorer;
		kact.sa_flags = act->sa_flags | SA_RESTORER;

		kact.sa_handler = act->sa_handler;
		kact.sa_mask = act->sa_mask;

		arg = &kact;
	} else {
		arg = act;
	}

	return INLINE_SYSCALL(rt_sigaction, 4,
			sig, arg, oact, _NSIG / 8);
}

libc_hidden_def (__libc_sigaction)

#include <nptl/sigaction.c>
