#ifndef DSTRU_TEST_TYPES
#define DSTRU_TEST_TYPES

/* Flat structures */
struct flat_3 { 
	char a; 
	int b; 
	short c; 
};

struct flat_2 { 
	int a; 
	double b; 
	char c; 
};

struct flat_1 { 
	int a; 
	int b; 
};

struct flat_4 {
	void *a;
};

/* Nested structures and their components */
struct nested_1 { 
	int a; 
	int b; 
	short c;
	struct { 
		double d1; 
		uint16_t s; 
		double d2;
	} anon; 
};

struct nested_2 {
	struct { 
		int a; 
		int b; 
		short c; 
	} anon1; 

	struct { 
		double d1; 
		uint16_t s; 
		double d2; 
	} anon2; 

	struct { 
		uint8_t string[32]; 
		int arr[4]; 
	} anon3;
};

struct nested_3_part_1 {
	uint32_t a;
	double b;
};

struct nested_3_part_2 {
	uint8_t name[8];
	uint8_t addr[8];	
};

struct nested_3 {
	struct nested_3_part_1 a;
	struct nested_3_part_2 b;
};

#endif
