#include <stdint.h>
#include <stdbool.h>

struct dyn_struct {
	uint8_t *buffer;
	int option;
	int size;
	int elements;
};

/* Returncodes */
#define DYN_S_RC_MEMERR 101
#define DYN_S_RC_PARAM 102
#define DYN_S_RC_SUCCS 103

/* FSLAGS all are mutually exclusive */
#define DYN_FLAG_NONE 0
#define DYN_FLAG_PACKED 1
#define DYN_FLAG_FOO 2

/* Defines */
#define DYN_S_UINT8 1001
#define DYN_S_UINT16 1002
#define DYN_S_UINT32 1000
#define DYN_S_UINT64 1003
#define DYN_S_FLOAT 1004
#define DYN_S_DOUBLE 1005
#define DYN_S_VOIDP 1006
#define DYN_S_STRUCT 1007

/* currently only compatible on AMD64 platforms */
#define DYN_S_AL_UINT8 1
#define DYN_S_AL_UINT16 2
#define DYN_S_AL_UINT32 4
#define DYN_S_AL_UINT64 8
#define DYN_S_AL_FLOAT 4
#define DYN_S_AL_DOUBLE 8
#define DYN_S_AL_VOIDP 8
/* Funktion prototypes */

/* Dispatcher function */
int dstru_add_member(int *rc, int type, void *c, struct dyn_struct *ds);

/* Adds a member to a dynamic structure without respection correct alignment
	Param: *rc: Returncodes from this function
		t: The members type
		c: The members data
		ds: A Pointer to an initialized Struct	
	Return: 0 on success
		-1 on failure*/
int dstru_add_member_packed(int *rc, int type, void *c, struct dyn_struct *ds);

/* Adds a member to a dynamic structure while maintaining the correct alignment 
	Param: *rc: Returncodes from this function
		t: The members type
		c: The members data
		ds: A Pointer to an initialized Struct	
	Return: 0 on success
		-1 on failure*/
int dstru_add_member_aligned(int *rc, int type, void *c, struct dyn_struct *ds);

/* For convenience. All these function use dstru_add_member internally */ 
int dstru_add_int(int *rc, int i, struct dyn_struct *ds);
int dstru_add_short(int *rc, short i, struct dyn_struct *ds);
int dstru_add_double(int *rc, double d, struct dyn_struct *ds);
int dstru_add_float(int *rc, float f, struct dyn_struct *ds);
int dstru_add_char(int *rc, char c, struct dyn_struct *ds);
int dstru_add_voidp(int *rc, void *p, struct dyn_struct *ds);
int dstru_add_long(int *rc, long l, struct dyn_struct *ds);
int dstru_add_bitfield(int *rc, struct dyn_struct *source, struct dyn_struct *dest);

/* Initializes a dynamic structure */
struct dyn_struct *dstru_init();
/* Frees a dynamic structure */
int dstru_free(struct dyn_struct *ds);
