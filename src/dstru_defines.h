#ifndef DSTRU_DEFINES
#define DSTRU_DEFINES

/* Returncodes */
#define DYN_S_RC_MEMERR 101
#define DYN_S_RC_PARAM 102
#define DYN_S_RC_SUCCS 103

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

#endif /* DSTRU_DEFINES */
