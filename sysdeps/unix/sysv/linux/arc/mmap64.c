/* Copyright (C) 2009-2015 Free Software Foundation, Inc.

   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sysdep.h>
#include <unistd.h>

#define MMAP2_PAGE_SHIFT 13	/* 8K page is default for ARC */

__ptr_t
__mmap64 (__ptr_t addr, size_t len, int prot, int flags, int fd, off64_t offset)
{
  if (offset & ((1 << MMAP2_PAGE_SHIFT) - 1))
    {
      __syscall_error (-EINVAL);
      return MAP_FAILED;
    }

  return (__ptr_t) INLINE_SYSCALL (mmap2, 6, addr, len, prot, flags, fd,
                                   (off_t)(offset >> MMAP2_PAGE_SHIFT));
}

weak_alias (__mmap64, mmap64)
