#include "align.h"
#include <stdlib.h>
#include <string.h>



/* caluclates the number of required padding bytes
	between a given offset and the start address
	using the following formula
	p = a - (o % a) % a, where p is the number of paddingbytes,
	a is the alignment and o ist the initial address offset 
	Param: t = Datatype
		offset = o
	Return: Number of padding bytes */
static int calc_padding(int t, int offset){
	switch(t){
		case DYN_S_UINT8:
			return  0;
		case DYN_S_UINT16:
			return   (DYN_S_AL_UINT16 - (offset % DYN_S_AL_UINT16)) % 
			DYN_S_AL_UINT16;
		case DYN_S_UINT32:
			return   (DYN_S_AL_UINT32 - (offset % DYN_S_AL_UINT32)) % 
				DYN_S_AL_UINT32;
		case DYN_S_UINT64:
			return   (DYN_S_AL_UINT64 - (offset % DYN_S_AL_UINT64)) % 
			DYN_S_AL_UINT64;
		case DYN_S_FLOAT:
			return   (DYN_S_AL_FLOAT - (offset % DYN_S_AL_FLOAT)) % 
			DYN_S_AL_FLOAT;
		case DYN_S_DOUBLE:
			return   (DYN_S_AL_DOUBLE - (offset % DYN_S_AL_DOUBLE)) % 
			DYN_S_AL_DOUBLE;
		case DYN_S_VOIDP:
			return   (DYN_S_AL_VOIDP - (offset % DYN_S_AL_VOIDP)) % 
			DYN_S_AL_VOIDP;
		default :
			return -1;
	}	
}


/* Adds a member to a dynamic structure while maintaining the correct alignment 
	Param: *rc: Returncodes from this function
		t: The members type
		c: The members data
		ds: A Pointer to an initialized Struct	
	Return: 0 on success
		-1 on failure*/
int dstru_add_member(int *rc, int t, void *c, struct dyn_struct *ds){
	int new_size;
	int *tempI;
	char *tempC;
	double *tempD;
	float *tempF;
	long *tempL;
	short *tempS;
	void *tempV;

	if(ds == NULL || c == NULL){
		if(!(rc == NULL))
			*rc = DYN_S_RC_PARAM;
		return -1;	
	}

	switch(t){
		case DYN_S_STRUCT:
			/* calculates the new size */
			new_size = ds->size + 
				(((struct dyn_struct *) c)->size - (ds->size % ((struct dyn_struct *) c)->size))
				+ ((struct dyn_struct *) c)->size;

			ds->buffer = (void *) realloc(ds->buffer, new_size);
			if(ds->buffer == NULL){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}

			ds->size = new_size;
			ds->elements++;

			/* copies the field into the own buffer */
			if(!memcpy(ds->buffer + (new_size - ((struct dyn_struct *)c)->size),
					((struct dyn_struct *)c)->buffer, ((struct dyn_struct *)c)->size)){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}

			break;
		case DYN_S_UINT32:
			/* Calculates the new size for the dynamic structure */
			new_size = ds->size + calc_padding(t, ds->size) + sizeof(int);

			/* Enlarges buffer properly */
			ds->buffer = (void *) realloc(ds->buffer, new_size); 
			if (ds->buffer == NULL){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}
			/* update the dyn_struct object */
			ds->size = new_size;
			ds->elements++;
			/* Memory has been allocated at this point 
				Copy data from c to the buffer 
			 	Can be understood as.
				1) Get startaddress (new_size - sizeof(int) = number of padding
				2) Cast the address appropriate
				3) Copy the castet content of c into the memory */
			*((int *) (ds->buffer + (new_size - sizeof(int)))) = *((int *) c);
			break;
		case DYN_S_UINT8:
			new_size = ds->size + calc_padding(t, ds->size) + sizeof(char);

			ds->buffer = (void *) realloc(ds->buffer, new_size); 
			if (ds->buffer == NULL){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}
			ds->size = new_size;
			ds->elements++;
			/* Memory has been allocated at this point */
			*((char *) (ds->buffer + (new_size - sizeof(char)))) = *((char *) c);
			break;
		case DYN_S_UINT16:
			new_size = ds->size + calc_padding(t, ds->size) + sizeof(short);

			ds->buffer = (void *) realloc(ds->buffer, new_size); 
			if (ds->buffer == NULL){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}
			ds->size = new_size;
			ds->elements++;
			/* Memory has been allocated at this point */
			*((short *) (ds->buffer + (new_size - sizeof(short)))) = *((short *) c);
			break;
		case DYN_S_UINT64:
			new_size = ds->size + calc_padding(t, ds->size) + sizeof(long);

			ds->buffer = (void *) realloc(ds->buffer, new_size); 
			if (ds->buffer == NULL){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}
			ds->size = new_size;
			ds->elements++;
			/* Memory has been allocated at this point */
			*((long *) (ds->buffer + (new_size - sizeof(long)))) = *((long *) c);
			break;
		case DYN_S_FLOAT:
			new_size = ds->size + calc_padding(t, ds->size) + sizeof(float);

			ds->buffer = (void *) realloc(ds->buffer, new_size); 
			if (ds->buffer == NULL){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}
			ds->size = new_size;
			ds->elements++;
			/* Memory has been allocated at this point */
			*((float *) (ds->buffer + (new_size - sizeof(float)))) = *((float *) c);
			break;
		case DYN_S_DOUBLE:
			new_size = ds->size + calc_padding(t, ds->size) + sizeof(double);

			ds->buffer = (void *) realloc(ds->buffer, new_size); 
			if (ds->buffer == NULL){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}
			ds->size = new_size;
			ds->elements++;
			/* Memory has been allocated at this point */
			*((double *) (ds->buffer + (new_size - sizeof(double)))) = *((double *) c);
			break;
		case DYN_S_VOIDP:
			new_size = ds->size + calc_padding(t, ds->size) + sizeof(void *);

			ds->buffer = (void *) realloc(ds->buffer, new_size); 
			if (ds->buffer == NULL){
				*rc = DYN_S_RC_MEMERR;
				return -1;
			}
			ds->size = new_size;
			ds->elements++;

			/* The tricky bit */
			char *tempv = ds->buffer + (new_size -sizeof(void *));
			char *tempp = (char *) &c;
			int i;
			for (i=0; i< sizeof(void *); i++){
				tempv[i] = tempp[i];
			}
			//*((void *) (ds->buffer + (new_size - sizeof(void *)))) = c;
			break;
		default:
			return -1;
			break;	
	}	
	return 0;
}

/* convenience funktions. 
	These functions provide automatic freeing of 
	needet dynamically allocated variables */
int dstru_add_int(int *rc, int i, struct dyn_struct *ds){
	int *temp = (int *) malloc(sizeof(int));
	int ret;
	*temp = i;
	ret = dstru_add_member(rc, DYN_S_UINT32, (void *) temp, ds);
	free(temp);
	return ret; 
}

int dstru_add_short(int *rc, short i, struct dyn_struct *ds){
	short *temp =  (short *) malloc(sizeof(short));
	int ret;
	*temp = i;
	ret = dstru_add_member(rc, DYN_S_UINT16, (void *) temp, ds);
	free(temp);
	return ret; 
}

int dstru_add_double(int *rc, double d, struct dyn_struct *ds){
	double *temp = (double *) malloc(sizeof(double));
	int ret;
	*temp = d;
	ret = dstru_add_member(rc, DYN_S_DOUBLE, (void *) temp, ds);
	free(temp);
	return ret;	
}

int dstru_add_float(int *rc, float f, struct dyn_struct *ds){
	float *temp = (float *) malloc(sizeof(float));
	int ret;
	*temp = f;
	ret = dstru_add_member(rc, DYN_S_FLOAT, (void *) temp, ds);	
	free(temp);
	return ret; 
}

int dstru_add_char(int *rc, char c, struct dyn_struct *ds){
	char *temp = (char *) malloc(sizeof(char));
	int ret;
	*temp = c;
	ret = dstru_add_member(rc, DYN_S_UINT8, (void *) temp, ds);	
	free(temp);
	return ret;
}

int dstru_add_voidp(int *rc, void *p, struct dyn_struct *ds){
	return dstru_add_member(rc, DYN_S_VOIDP, p, ds);	
}

int dstru_add_long(int *rc, long l, struct dyn_struct *ds){
	long *temp = (long *) malloc(sizeof(long));
	int ret;
	*temp = l;
	ret = dstru_add_member(rc, DYN_S_UINT64, (long *) temp, ds);	
	free(temp);
	return ret;
}

int dstru_add_bitfield(int *rc, struct dyn_struct *source, struct dyn_struct *dest){
	return dstru_add_member(rc, DYN_S_STRUCT, source, dest);
}

/* Returns a newly initialized dyn_struct object 
	Param: void 
	Return: Valid address != NULL on success, NULL on failure */
struct dyn_struct *dstru_init(){
	struct dyn_struct *ret = (struct dyn_struct *) malloc(sizeof(struct dyn_struct) * 1);
	if (ret == NULL)
		return NULL;
	ret->buffer = NULL;
	ret->size = 0;
	ret->elements = 0;
	return ret;
}

/* Destroys a given dyn_struct object 
	Param: ds = Pointer to a valid memory address containing a structure
		of type struct dyn_struct
	Return: 0 on success, -1 on failure */
int dstru_free(struct dyn_struct *ds){
	if(ds == NULL)
		return -1;
	free(ds->buffer);
	free(ds);
	return 0;
}
