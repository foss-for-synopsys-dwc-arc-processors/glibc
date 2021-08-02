#define ARC_NUMREG		32
#define ARC_NUMSIGW		(64 / (8 * sizeof (unsigned long int)))

/* see struct __jmp_buf_tag in generic code.  */
#define JMP_BUF_SIZE		(ARC_NUMREG + 1 + ARC_NUMSIGW) * sizeof (unsigned long int)
#define SIGJMP_BUF_SIZE		(ARC_NUMREG + 1 + ARC_NUMSIGW) * sizeof (unsigned long int)
#define JMP_BUF_ALIGN		__alignof__ (unsigned long int)
#define SIGJMP_BUF_ALIGN	__alignof__ (unsigned long int)
#define MASK_WAS_SAVED_OFFSET	(ARC_NUMREG * sizeof (unsigned long int))
#define SAVED_MASK_OFFSET	((ARC_NUMREG + 1) * sizeof (unsigned long int))
