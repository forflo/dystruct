#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdint.h>
#include "dstru_funcs.h"
#include "dstru_defines.h"
#include "dstru_types.h"
#include "config.h"

/* unused but required by CUnit */
int init_test_dyn_str(void){ 
	return 0; 
}

int clean_test_dyn_str(void){ 
	return 0;
}

/* Structures used by test drivers */
struct test { int a; short c;};

struct test1 { char a; int b; short c; };

struct test2 { int a; double b; char c; };

struct test3 { int a; int b; };

struct voip{ void *a; };

/* creation and destruction test */
void test_dyn_str(void){
	struct dstru_struct *ds;
	CU_ASSERT(dstru_init(0, &ds) == 0);
	CU_ASSERT(ds != NULL);
	CU_ASSERT(ds->buffer == NULL && ds->align == 0);
	CU_ASSERT(ds->size == 0 && ds->elem_num == 0);
	dstru_free(ds);
}

/* Test the special case of adding a void pointer
	to a dynamic strucutre */
void test_voidp(void){
	struct dstru_struct *ds;
	struct voip *v;
	int *i = (int *) malloc(sizeof(int));

	CU_ASSERT(dstru_init(0, &ds) == 0);
	CU_ASSERT(ds != NULL);
	dstru_add_member(DYN_S_VOIDP, (void *) i, ds);	

	v = (struct voip *) ds->buffer;
	CU_ASSERT(v->a == i);
}

/* Main test. Creates different dynamic structures 
	on the heap using the dstru_add_member function . The byte-Buffer
	contained by the dystructs is then casted to a pointer
	with type of one of above specified abstract data types */
void test_struct(void){
	uint32_t i1 = 100123, i2 = -100123;
	double d = 100000.123123;
	uint8_t c1 = 'F', c2 = '\n';
	uint16_t s1 = 0x12FF;

	struct dstru_struct *ds1; 
	struct dstru_struct *ds2;
	struct test1 *ts1;
	struct test2 *ts2;

	CU_ASSERT(dstru_init(0, &ds1) == 0);
	CU_ASSERT(dstru_init(0, &ds2) == 0);

	CU_ASSERT(ds1 != NULL);
	CU_ASSERT(ds2 != NULL);
	
	/* ds2 => instance of the test2 structure */
	CU_ASSERT(dstru_add_member(DYN_S_UINT8, (void *) &c1, ds1) == 0);
	CU_ASSERT(dstru_add_member(DYN_S_UINT32, (void *) &i1, ds1) == 0);	
	CU_ASSERT(dstru_add_member(DYN_S_UINT16, (void *) &s1, ds1) == 0);
	
	/* ds1 => instance of the test2 structure*/	
	CU_ASSERT(dstru_add_member(DYN_S_UINT32, (void *) &i2, ds2) == 0);
	CU_ASSERT(dstru_add_member(DYN_S_DOUBLE, (void *) &d, ds2) == 0);	
	CU_ASSERT(dstru_add_member(DYN_S_UINT8, (void *) &c2, ds2) == 0);

	ts1 = (struct test1 *) ds1->buffer;
	ts2 = (struct test2 *) ds2->buffer;

	CU_ASSERT(ts1->a == c1);
	CU_ASSERT(ts1->b == i1);
	CU_ASSERT(ts1->c == s1);

	CU_ASSERT(ts2->a == i2);
	CU_ASSERT(ts2->b == d);
	CU_ASSERT(ts2->c == c2);
}

void test_add_struct(void){

}

void test_sizeof(void){
	CU_ASSERT(dstru_sizeof(DYN_S_UINT64, NULL) == 8); 
	CU_ASSERT(dstru_sizeof(DYN_S_UINT8, NULL) == 1); 
	CU_ASSERT(dstru_sizeof(DYN_S_UINT16, NULL) == 2); 
	CU_ASSERT(dstru_sizeof(DYN_S_UINT32, NULL) == sizeof(uint32_t)); 
	CU_ASSERT(dstru_sizeof(DYN_S_DOUBLE, NULL) == sizeof(double)); 
}

void test_dummy(void){
	uint32_t i1 = 700;
	uint32_t i2 = -700;

	struct dstru_struct *ds1;
	struct test3 *t;

   	CU_ASSERT(dstru_init(0, &ds1) == 0);
	CU_ASSERT(ds1 != NULL);

	CU_ASSERT(dstru_add_member(DYN_S_UINT32, (void *) &i1, ds1) == 0);
	CU_ASSERT(dstru_add_member(DYN_S_UINT32, (void *) &i2, ds1) == 0);

	t = (struct test3 *) ds1->buffer;

	CU_ASSERT(t->a == i1);
	CU_ASSERT(t->b == i2);
}

/* Tests whether the padding is calculated correctly */
void test_padding(void){
	struct dstru_struct *foo;
	CU_ASSERT(dstru_init(0, &foo) == 0);

	/* uint32 */
	foo->size = 0;
	CU_ASSERT(dstru_padding(DYN_S_UINT32, foo) == 0);
	foo->size = 1;
	CU_ASSERT(dstru_padding(DYN_S_UINT32, foo) == 3);
	foo->size = 2;
	CU_ASSERT(dstru_padding(DYN_S_UINT32, foo) == 2);
	foo->size = 3;
	CU_ASSERT(dstru_padding(DYN_S_UINT32, foo) == 1);

	/* double */
	foo->size = 4;
	CU_ASSERT(dstru_padding(DYN_S_DOUBLE, foo) == 4);

	/* uint16 */
	foo->size = 1;
	CU_ASSERT(dstru_padding(DYN_S_UINT16, foo) == 1);
	foo->size = 2;
	CU_ASSERT(dstru_padding(DYN_S_UINT16, foo) == 0);

	/* uint8 */	
	CU_ASSERT(dstru_padding(DYN_S_UINT8, foo) == 0);
	CU_ASSERT(dstru_padding(DYN_S_UINT8, foo) == 0);

	/* voidpointer */
	foo->size = 4;
	CU_ASSERT(dstru_padding(DYN_S_VOIDP, foo) == 4);
}

/* Required calls to CUnit. Test will be registered  */
int main(int argc, char **argv){
	/* Initialize and build a Testsuite */
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* Creation of the main test suite */
	pSuite = CU_add_suite("Dynamische C-Strukturen", init_test_dyn_str, 
							clean_test_dyn_str); 
	if (NULL == pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Adds tests */
	if((NULL == CU_add_test(pSuite, "Struktur erzeugen", test_dyn_str)) || 
		(NULL == CU_add_test(pSuite, "Member hinzufügen", test_dummy)) ||	
		(NULL == CU_add_test(pSuite, "Voller Test", test_struct)) || 
		(NULL == CU_add_test(pSuite, "Voidpointer Test", test_voidp)) || 
		(NULL == CU_add_test(pSuite, "Sizeof Test", test_sizeof)) ||
		(NULL == CU_add_test(pSuite, "Padding berechnen", test_padding))){

		CU_cleanup_registry();
		return CU_get_error();
	}

	/* misc configuration */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

