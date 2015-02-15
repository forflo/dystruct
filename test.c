#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdint.h>
#include "dstru_funcs.h"
#include "dstru_defines.h"
#include "dstru_types.h"
#include "config.h"

/***************
 Platformdependent to AMD64
***************/

/* unused but required by CUnit */
int init_test_dyn_str(void){ return 0; }
int clean_test_dyn_str(void){ return 0;}

/* Structures used by test drivers */
struct test1 {
	char a;
	int b;
	short c;
};

struct test2 {
	int a;
	double b;
	char c;
};

struct test3 {
	int a;
	int b;
};

struct voip{
	void *a;
};

/* creation and destruction test */
void test_dyn_str(void){
	struct dstru_struct *ds;
	CU_ASSERT(dstru_init(0, &ds) == 0);
	CU_ASSERT(ds != NULL);
	CU_ASSERT(ds->buffer == NULL);
	CU_ASSERT(ds->size == 0 && ds->elem_num == 0);
	dstru_free(ds);
}

/* Test the special case of adding a void pointer
	to a dynamic strucutre */
void test_voidp(void){
	struct dstru_struct *ds;
	CU_ASSERT(dstru_init(0, &ds) == 0);
	CU_ASSERT(ds != NULL);
	int *i = (int *) malloc(sizeof(int));
	dstru_add_member(DYN_S_VOIDP, (void *) i, ds);	
	
	struct voip *v = (struct voip *) ds->buffer;
	CU_ASSERT(v->a == i);
}

/* Main test. Creates different dynamic structures 
	on the heap using the dstru_add_member function . The byte-Buffer
	contained by the dystructs is then casted to a pointer
	with type of one of above specified abstract data types */
void test_struct(void){
	struct dstru_struct *ds1; 
	CU_ASSERT(dstru_init(0, &ds1) == 0);
	struct dstru_struct *ds2;
	CU_ASSERT(dstru_init(0, &ds2) == 0);
	int *i1 = (int *) malloc(sizeof(int)), 
		*i2 = (int *) malloc(sizeof(int)),
		*rc = (int *) malloc(sizeof(int));
	double *d = (double *) malloc(sizeof(double));
	char *c1 = (char *) malloc(sizeof(char)), 
		*c2 = (char *) malloc(sizeof(char));
	short *s1 = (short *) malloc(sizeof(short));;

	CU_ASSERT(i1 != NULL && i2 != NULL && rc != NULL && d != NULL &&
				c1 != NULL && c2 != NULL && s1 != NULL);

	CU_ASSERT(ds1 != NULL);
	CU_ASSERT(ds2 != NULL);

	*i1 = 100123;
	*i2 = 100123;
	*d = 100000.123123;
	*s1 = 600;
	*c1 = 'F';
	*c2 = 'F';
	
	/* ds2 => instance of the test2 structure */
	CU_ASSERT(dstru_add_member(DYN_S_UINT8, (void *) c1, ds1) == 0);
	CU_ASSERT(dstru_add_member(DYN_S_UINT32, (void *) i1, ds1) == 0);	
	CU_ASSERT(dstru_add_member(DYN_S_UINT16, (void *) s1, ds1) == 0);
	
	/* ds1 => instance of the test2 structure*/	
	CU_ASSERT(dstru_add_member(DYN_S_UINT32, (void *) i2, ds2) == 0);
	CU_ASSERT(dstru_add_member(DYN_S_DOUBLE, (void *) d, ds2) == 0);	
	CU_ASSERT(dstru_add_member(DYN_S_UINT8, (void *) c2, ds2) == 0);

	struct test1 *ts1 = (struct test1 *) ds1->buffer;
	struct test2 *ts2 = (struct test2 *) ds2->buffer;

	CU_ASSERT(ts1->a == 'F');
	CU_ASSERT(ts1->b == 100123);
	CU_ASSERT(ts1->c == 600);

	CU_ASSERT(ts2->a == 100123);
	CU_ASSERT(ts2->b == 100000.123123);
	CU_ASSERT(ts2->c == 'F');

	free(i1);
	free(i2);
	free(d);
	free(s1);
	free(c1);
	free(c2);
}

void test_dummy(void){
	struct dstru_struct *ds1;
   	CU_ASSERT(dstru_init(0, &ds1) == 0);
	int *i1 = (int *) malloc(sizeof(int)), 
		*i2 = (int *) malloc(sizeof(int)),
		*rc = (int *) malloc(sizeof(int));

	CU_ASSERT(ds1 != NULL);
	CU_ASSERT(i1 != NULL && i2 != NULL);

	*i1 = 700;
	*i2 = -700;
	CU_ASSERT(dstru_add_member(DYN_S_UINT32, (void *) i1, ds1) == 0);
	CU_ASSERT(dstru_add_member(DYN_S_UINT32, (void *) i2, ds1) == 0);

	struct test3 *t = (struct test3 *) ds1->buffer;
	CU_ASSERT(t->a == 700);
	CU_ASSERT(t->b == -700);
}

/* Tests whether the padding is calculated correctly */
void test_padding(void){
	struct dstru_struct *foo;
	CU_ASSERT(dstru_init(0, &foo) == 0);

	/* INT */
	foo->size = 0;
	CU_ASSERT(dstru_padding(DYN_S_UINT32, foo) == 0);
	foo->size = 1;
	CU_ASSERT(dstru_padding(DYN_S_UINT32, foo) == 3);
	foo->size = 3;
	CU_ASSERT(dstru_padding(DYN_S_UINT32, foo) == 2);
	foo->size = 4;
	CU_ASSERT(dstru_padding(DYN_S_UINT32, foo) == 1);
	/* Short */

	foo->size = 1;
	CU_ASSERT(dstru_padding(DYN_S_UINT16, foo) == 1);
	foo->size = 2;
	CU_ASSERT(dstru_padding(DYN_S_UINT16, foo) == 0);
	/* Char */	
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
		(NULL == CU_add_test(pSuite, "Padding berechnen", test_padding))
	)

	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* misc configuration */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

