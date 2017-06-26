/* The ARC architecture has selectable endianness.  */

#ifndef _ENDIAN_H
# error "Never use <bits/endian.h> directly; include <endian.h> instead."
#endif

#ifdef __BIG_ENDIAN__
# define __BYTE_ORDER __BIG_ENDIAN
#endif
#ifdef __LITTLE_ENDIAN__
# define __BYTE_ORDER __LITTLE_ENDIAN
#endif
