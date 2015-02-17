#include "dstru_types.h"

#ifndef DSTRU_FUNCS
#define DSTRU_FUNCS

/* Adds a member to a dynamic structure without respection correct alignment
	Param: *rc: Returncodes from this function
		t: The members type
		c: The members data
		ds: A Pointer to an initialized Struct	
	Return: 0 on success
		-1 on failure*/
int dstru_add_member(int type, void *content, struct dstru_struct *ds);

/* fills the buffer with the required number of padding bytes */
int dstru_finalize(struct dstru_struct *ds);

/* For convenience. All these function use dstru_add_member internally */ 
int dstru_add_uint8(uint8_t i, struct dstru_struct *ds);
int dstru_add_uint16(uint16_t i, struct dstru_struct *ds);
int dstru_add_uint32(uint32_t i, struct dstru_struct *ds);
int dstru_add_uint64(uint64_t i, struct dstru_struct *ds);
int dstru_add_float(float i, struct dstru_struct *ds);
int dstru_add_double(double i, struct dstru_struct *ds);
int dstru_add_voidp(void *i, struct dstru_struct *ds);
int dstru_add_bitfield(struct dstru_struct *source, struct dstru_struct *dest);

/* Initializes a dynamic structure */
int dstru_init(int align, struct dstru_struct **s);
/* Frees a dynamic structure */
int dstru_free(struct dstru_struct *s);

int dstru_padding(int type, struct dstru_struct *s);
int dstru_sizeof(int type, struct dstru_struct *s);

#endif
