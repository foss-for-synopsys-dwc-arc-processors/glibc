/* see struct __jmp_buf_tag in generic code.  */
#if defined (__ARC_FLOAT_ABI_HARD__)
#define NUMR 64
#else
#define NUMR 32
#endif

#define JMP_BUF_SIZE		(NUMR + 1 + 2) * sizeof (unsigned long int)
#define SIGJMP_BUF_SIZE		(NUMR + 1 + 2) * sizeof (unsigned long int)
#define JMP_BUF_ALIGN		__alignof__ (unsigned long int)
#define SIGJMP_BUF_ALIGN	__alignof__ (unsigned long int)
#define MASK_WAS_SAVED_OFFSET	(NUMR * sizeof (unsigned long int))
#define SAVED_MASK_OFFSET	((NUMR + 1) * sizeof (unsigned long int))
