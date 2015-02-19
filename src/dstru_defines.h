#ifndef DSTRU_DEFINES
#define DSTRU_DEFINES

#include "config.h"

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

/* Alignment configuration */

#ifndef DSTRU_UINT_8_AL
#	define DYN_S_AL_UINT8 1
/* todo add more platforms */
#else
#	define DYN_S_AL_UINT8 DSTRU_UINT_8_AL
#endif

#ifndef DSTRU_UINT_16_AL
#	define DYN_S_AL_UINT16 2
/* todo add more platforms */
#else
#	define DYN_S_AL_UINT16 DSTRU_UINT_16_AL
#endif

#ifndef DSTRU_UINT_32_AL
#	define DYN_S_AL_UINT32 4
#else
#	define DYN_S_AL_UINT32 DSTRU_UINT_32_AL
#endif

#ifndef DSTRU_UINT_64_AL
#	define DYN_S_AL_UINT64 8
#else
#	define DYN_S_AL_UINT64 DSTRU_UINT_64_AL
#endif

#ifndef DSTRU_FLOAT_AL
#	define DYN_S_AL_FLOAT 4
#else
#	define DYN_S_AL_FLOAT DSTRU_FLOAT_AL
#endif

#ifndef DSTRU_DOUBLE_AL
#	define DYN_S_AL_DOUBLE 8
#else
#	define DYN_S_AL_DOUBLE DSTRU_DOUBLE_AL
#endif

#ifndef DSTRU_PTR_AL
#	define DYN_S_AL_VOIDP 8
#else
#	define DYN_S_AL_VOIDP DSTRU_PTR_AL
#endif

#endif /* DSTRU_DEFINES */
