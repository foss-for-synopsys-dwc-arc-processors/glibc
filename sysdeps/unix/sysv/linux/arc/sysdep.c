/* Wrapper for setting errno.
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1 or later, see the file COPYING.LIB in this tarball.
 */

#include <sysdep.h>
#include <errno.h>

/* All syscall handler come here to avoid generated code bloat due to
 * GOT reference  to errno_location or it's equivalent
 */
int __syscall_error(int err_no)
{
	__set_errno(-err_no);
	return -1;
}

#if IS_IN (libc)
hidden_def (__syscall_error)
#endif
