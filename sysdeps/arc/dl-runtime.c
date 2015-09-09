/* PLT jump into resolver passes PC of PLTn, while _dl_fixup expects the
   address of corresponding .rela.plt entry */

#ifdef __A7__
#define ARC_PLT_SIZE	12
#else
#define ARC_PLT_SIZE	16
#endif

#define reloc_index					\
({							\
  unsigned long plt0 = D_PTR (l, l_info[DT_PLTGOT]);	\
  unsigned long pltn = reloc_arg;			\
  /* exclude PL0 and PLT1 */				\
  unsigned long idx = (pltn - plt0)/ARC_PLT_SIZE - 2;	\
  idx;							\
})

#define reloc_offset reloc_index * sizeof (PLTREL)

#include <elf/dl-runtime.c>
