/* see struct __jmp_buf_tag in generic code.  */
#define JMP_BUF_SIZE		(32 + 1 + 2) * sizeof (unsigned long int)
#define SIGJMP_BUF_SIZE		(32 + 1 + 2) * sizeof (unsigned long int)
#define JMP_BUF_ALIGN		__alignof__ (unsigned long int)
#define SIGJMP_BUF_ALIGN	__alignof__ (unsigned long int)
#define MASK_WAS_SAVED_OFFSET	(32 * sizeof (unsigned long int))
#define SAVED_MASK_OFFSET	(33 * sizeof (unsigned long int))
