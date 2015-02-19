/*
Copyright (c) 2014 Florian Mayer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

----------------------------------------------------------------------------
This license differs slightly from the original MIT license.

* Sublicensing is not allowed.
* Alteration of the packages license is not allowed.
*/


#ifndef DSTRU_FUNCS
#define DSTRU_FUNCS

#include "dstru_types.h"

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
