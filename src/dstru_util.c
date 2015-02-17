#include "dstru_defines.h"
#include "dstru_util_funcs.h"

static const int TYPE_LOOKUP[] = {
	0, DYN_S_UINT8, DYN_S_UINT16, 
	0, DYN_S_UINT32, 0, 0, 0, DYN_S_UINT64
}; 

int dstru_lookup_type(int t){
	return TYPE_LOOKUP[t];
}

int dstru_is_power_of_two(int t){
	return ((t != 0) && !(t & (t - 1)));
}
