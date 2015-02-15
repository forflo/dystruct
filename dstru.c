#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "dstru_funcs.h"
#include "dstru_defines.h"
#include "dstru_types.h"
#include "config.h"

static const int TYPE_LOOKUP[] = {
	0, 
	DYN_S_UINT8, 
	DYN_S_UINT16, 
	0, 
	DYN_S_UINT32, 
	0, 
	0, 
	0, 
	DYN_S_UINT64
}; 

static int is_power_of_two(int t){
	return ((t != 0) && !(t & (t - 1)));
}

int dstru_sizeof(int type, struct dstru_struct *content){
	switch(type){
		case DYN_S_UINT8 : return sizeof(uint8_t);
		case DYN_S_UINT16: return sizeof(uint16_t);
		case DYN_S_UINT32: return sizeof(uint32_t);
		case DYN_S_UINT64: return sizeof(uint64_t);
		case DYN_S_FLOAT : return sizeof(float);
		case DYN_S_DOUBLE: return sizeof(double);
		case DYN_S_VOIDP : return sizeof(void*);
		case DYN_S_STRUCT: return content->size;
		default: return 1;
	}
}

/* caluclates the number of required padding bytes
	between a given offset and the start address
	using the following formula
	p = a - (o % a) % a, where p is the number of paddingbytes,
	a is the alignment and o ist the initial address offset 
	Param: t = Datatype
		offset = o
	Return: Number of padding bytes */
int dstru_padding(int type, struct dstru_struct *s){
	/* Packing enabled. Use t as x in pack(x).
	 	Alignment is t-bytes */
	if(s->align == 1){
		return 0; 
	} else if (s->align >= 1){
		return (s->align - (s->size % s->align)) % s->align;
	/* no packing. Alignment follows the DYN_S_AL_* Defines*/
	} else {
		switch(type){
			case DYN_S_UINT8:
				return  0;
			case DYN_S_UINT16:
				return   (DYN_S_AL_UINT16 - (s->size % DYN_S_AL_UINT16)) % 
				DYN_S_AL_UINT16;
			case DYN_S_UINT32:
				return   (DYN_S_AL_UINT32 - (s->size % DYN_S_AL_UINT32)) % 
				DYN_S_AL_UINT32;
			case DYN_S_UINT64:
				return   (DYN_S_AL_UINT64 - (s->size % DYN_S_AL_UINT64)) % 
				DYN_S_AL_UINT64;
			case DYN_S_FLOAT:
				return   (DYN_S_AL_FLOAT - (s->size % DYN_S_AL_FLOAT)) % 
				DYN_S_AL_FLOAT;
			case DYN_S_DOUBLE:
				return   (DYN_S_AL_DOUBLE - (s->size % DYN_S_AL_DOUBLE)) % 
				DYN_S_AL_DOUBLE;
			case DYN_S_VOIDP:
				return   (DYN_S_AL_VOIDP - (s->size % DYN_S_AL_VOIDP)) % 
				DYN_S_AL_VOIDP;
			default :
				return -1;
		}	
	}
}

/* adds final padding to the buffer of dest */
int dstru_finalize(struct dstru_struct *dest){
	int new_size;
	if ((!is_power_of_two(dest->align) && (dest->align != 0)) || dest == NULL)
		return 1;

	new_size = dest->size + dstru_padding(TYPE_LOOKUP[dest->biggest_member], dest);

	dest->buffer = realloc(dest->buffer, new_size);
	if(dest->buffer == NULL)
		return 1;

	dest->size = new_size;
	
	return 0;
}

int dstru_add_member(int type, void *content, struct dstru_struct *dest){
	int pad_size, new_size;
	uint8_t *tempv, *tempp;
	int vi;

	if (!is_power_of_two(dest->align) && (dest->align != 0))
		return 1;

	if(dest == NULL || content == NULL){
		return 1;	
	}

	/* element adding logic begins here */
	new_size = dest->size + dstru_padding(type, dest) + dstru_sizeof(type, content);
	pad_size = new_size - dstru_sizeof(type, content);

	dest->buffer = realloc(dest->buffer, new_size);
	if(dest->buffer == NULL)
		return 1;

	dest->size = new_size;
	dest->elem_num++;

	/* update the biggest_member field if the new field 
	 	will be bigger than every other field before (dest->buffer) */
	if (dest->biggest_member < dstru_sizeof(type,content)){
		dest->biggest_member = dstru_sizeof(type,content);
	}

	/* type dependent adding logic */
	switch(type){
		case DYN_S_STRUCT:
			/* copies the field into the own buffer */
			if(!memcpy(((uint8_t *) dest->buffer) + pad_size, ((struct dstru_struct *)content)->buffer, 
						((struct dstru_struct *)content)->size))
				return 1;
			break;
		case DYN_S_UINT32:
			/* Memory has been allocated at this point 
				Copy data from c to the buffer 
			 	Can be understood as.
				1) Get startaddress (new_size - sizeof(int) = number of padding
				2) Cast the address appropriate
				3) Copy the castet content of c into the memory */
			*((uint32_t *) (((uint8_t *) dest->buffer) + pad_size)) = *((uint32_t *) content);
			break;
		case DYN_S_UINT8:
			/* Memory has been allocated at this point */
			*((uint8_t *) (((uint8_t *) dest->buffer) + pad_size)) = *((uint8_t *) content);
			break;
		case DYN_S_UINT16:
			/* Memory has been allocated at this point */
			*((uint16_t *) (((uint8_t *) dest->buffer) + pad_size )) = *((uint16_t *) content);
			break;
		case DYN_S_UINT64:
			/* Memory has been allocated at this point */
			*((uint64_t *) (((uint8_t *) dest->buffer) + pad_size)) = *((uint64_t *) content);
			break;
		case DYN_S_FLOAT:
			/* Memory has been allocated at this point */
			*((float *) (((uint8_t *) dest->buffer) + pad_size )) = *((float *) content);
			break;
		case DYN_S_DOUBLE:
			/* Memory has been allocated at this point */
			*((double *) (((uint8_t *) dest->buffer) + pad_size )) = *((double *) content);
			break;
		case DYN_S_VOIDP:
			/* The tricky bit */
			tempv = ((uint8_t *) dest->buffer) + (new_size - dstru_sizeof(type, content));
			tempp = (uint8_t *) &content;
			for (vi=0; vi< dstru_sizeof(type, content); vi++){
				tempv[vi] = tempp[vi];
			}
			break;
		default:
			return 1;
	}	
	return 0;
} 

/* convenience funktions. 
	These functions provide automatic freeing of 
	needet dynamically allocated variables */
int dstru_add_uint16(uint16_t i, struct dstru_struct *ds){
	return dstru_add_member(DYN_S_UINT16, (void *) &i, ds);
}

int dstru_add_uint32(uint32_t i, struct dstru_struct *ds){
	return dstru_add_member(DYN_S_UINT32, (void *) &i, ds);
}

int dstru_add_double(double i, struct dstru_struct *ds){
	return dstru_add_member(DYN_S_DOUBLE, (void *) &i, ds);
}

int dstru_add_float(float i, struct dstru_struct *ds){
	return dstru_add_member(DYN_S_FLOAT, (void *) &i, ds);	
}

int dstru_add_char(uint8_t i, struct dstru_struct *ds){
	return dstru_add_member(DYN_S_UINT8, (void *) &i, ds);	
}

int dstru_add_voidp(void *i, struct dstru_struct *ds){
	return dstru_add_member(DYN_S_VOIDP, i, ds);	
}

int dstru_add_long(uint64_t i, struct dstru_struct *ds){
	return dstru_add_member(DYN_S_UINT64, (long *) &i, ds);	
}

int dstru_add_bitfield(struct dstru_struct *source, struct dstru_struct *dest){
	return dstru_add_member(DYN_S_STRUCT, source, dest);
}

/* Returns a newly initialized dstru_struct object 
	Param: void 
	Return: Valid address != NULL on success, NULL on failure */
int dstru_init(int align, struct dstru_struct **s){
	struct dstru_struct *ret = malloc(sizeof(struct dstru_struct));
	if (ret == NULL)
		return 1;

	ret->buffer = NULL;
	ret->size = 0;
	ret->elem_num = 0;
	ret->align = 0;
	ret->biggest_member = 0;

	*s = ret;

	return 0;
}

/* Destroys a given dstru_struct object 
	Param: ds = Pointer to a valid memory address containing a structure
		of type struct dstru_struct
	Return: 0 on success, -1 on failure */
int dstru_free(struct dstru_struct *s){
	if (s == NULL)
		return 1;

	free(s->buffer);
	free(s);
	return 0;
}
