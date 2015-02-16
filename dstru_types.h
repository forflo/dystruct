#ifndef DSTRU_TYPES
#define DSTRU_TYPES

/* align = 0 => library takes care
 	align in f(x)=2^x => alignment will be f(x) 
 	elem_num = number of first level members
 	embeddet bitfields (e.g. of structs) count as one.
 	size = number of bytes occupied by buffer. 
 	biggest_member = number of bytes of the biggest member */
struct dstru_struct {
	void *buffer;
	int size;
	int elem_num;
	int align;
	int biggest_member;
};

#endif /* DSTRU_TYPES */
