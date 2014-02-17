struct dyn_struct {
	char *buffer;
	int size;
	int elements;
};

/* Returncodes */
#define DYN_S_RC_MEMERR 101
#define DYN_S_RC_PARAM 102
#define DYN_S_RC_SUCCS 103

/* Defines */
#define DYN_S_INT 1000
#define DYN_S_CHAR 1001
#define DYN_S_SHORT 1002
#define DYN_S_LONG 1003
#define DYN_S_FLOAT 1004
#define DYN_S_DOUBLE 1005
#define DYN_S_VOIDP 1006

/* currently only compatible on AMD64 platforms */
#define DYN_S_AL_CHAR 1
#define DYN_S_AL_SHORT 2
#define DYN_S_AL_INT 4
#define DYN_S_AL_LONG 8
#define DYN_S_AL_FLOAT 4
#define DYN_S_AL_DOUBLE 8
#define DYN_S_AL_VOIDP 8
/* Funktion prototypes */

/* Convenience functions */
int dstru_add_int(int *rc, int i, struct dyn_struct *ds);
int dstru_add_short(int *rc, short i, struct dyn_struct *ds);
int dstru_add_double(int *rc, double d, struct dyn_struct *ds);
int dstru_add_float(int *rc, float f, struct dyn_struct *ds);
int dstru_add_char(int *rc, char c, struct dyn_struct *ds);
int dstru_add_voidp(int *rc, void *p, struct dyn_struct *ds);
int dstru_add_long(int *rc, long l, struct dyn_struct *ds);

/* Adds a member of given Type */
int dstru_add_member(int *rc,int type, void *c, struct dyn_struct *ds);
/* Initializes a dynamic structure */
struct dyn_struct *dstru_init();
/* Frees a dynamic structure */
int dstru_free(struct dyn_struct *ds);
/* calculates the number of required padding bytes */
int calc_padding(int t, int offset);
