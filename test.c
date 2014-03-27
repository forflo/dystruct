#include <CUnit/Cunit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "align.h"
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
	struct dyn_struct *ds = dstru_init();
	CU_ASSERT(ds != NULL);
	CU_ASSERT(ds->buffer == NULL);
	CU_ASSERT(ds->size == 0 && ds->elements == 0);
	dstru_free(ds);
}

/* Test the special case of adding a void pointer
	to a dynamic strucutre */
void test_voidp(void){
	struct dyn_struct *ds = dstru_init();
	int *rc = (int *) malloc(sizeof(int));
	CU_ASSERT(ds != NULL);
	int *i = (int *) malloc(sizeof(int));
	dstru_add_member(rc, DYN_S_VOIDP, (void *) i, ds);	
	
	struct voip *v = (struct voip *) ds->buffer;
	CU_ASSERT(v->a == i);
}

/* Main test. Creates different dynamic structures 
	on the heap using the dstru_add_member function . The byte-Buffer
	contained by the dystructs is then casted to a pointer
	with type of one of above specified abstract data types */
void test_struct(void){
	struct dyn_struct *ds1 = dstru_init();
	struct dyn_struct *ds2 = dstru_init();
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
	dstru_add_member(rc, DYN_S_CHAR, (void *) c1, ds1);
	dstru_add_member(rc, DYN_S_INT, (void *) i1, ds1);	
	dstru_add_member(rc, DYN_S_SHORT, (void *) s1, ds1);
	
	/* ds1 => instance of the test2 structure*/	
	dstru_add_member(rc, DYN_S_INT, (void *) i2, ds2);
	dstru_add_member(rc, DYN_S_DOUBLE, (void *) d, ds2);	
	dstru_add_member(rc, DYN_S_CHAR, (void *) c2, ds2);

	struct test1 *ts1 = (struct test1 *) ds1->buffer;
	struct test2 *ts2 = (struct test2 *) ds2->buffer;

	CU_ASSERT(ts1->a == 'F');
	CU_ASSERT(ts1->b == 100123);
	CU_ASSERT(ts1->c == 600);

	CU_ASSERT(ts2->a == 100123);
	CU_ASSERT(ts2->b == 100000.123123);
	CU_ASSERT(ts2->c == 'F');
}

void test_dummy(void){
	struct dyn_struct *ds1 = dstru_init();
	int *i1 = (int *) malloc(sizeof(int)), 
		*i2 = (int *) malloc(sizeof(int)),
		*rc = (int *) malloc(sizeof(int));

	CU_ASSERT(ds1 != NULL);
	CU_ASSERT(i1 != NULL && i2 != NULL);

	*i1 = 700;
	*i2 = -700;
	dstru_add_member(rc, DYN_S_INT, (void *) i1, ds1);
	dstru_add_member(rc, DYN_S_INT, (void *) i2, ds1);

	struct test3 *t = (struct test3 *) ds1->buffer;
	CU_ASSERT(t->a == 700);
	CU_ASSERT(t->b == -700);
}

/* Tests whether the padding is calculated correctly */
void test_padding(void){
	/* INT */
	CU_ASSERT(calc_padding(DYN_S_INT, 0) == 0);
	CU_ASSERT(calc_padding(DYN_S_INT, 1) == 3);
	CU_ASSERT(calc_padding(DYN_S_INT, 2) == 2);
	CU_ASSERT(calc_padding(DYN_S_INT, 3) == 1);
	/* Short */
	CU_ASSERT(calc_padding(DYN_S_SHORT, 1) == 1);
	CU_ASSERT(calc_padding(DYN_S_SHORT, 2) == 0);
	/* Char */	
	CU_ASSERT(calc_padding(DYN_S_CHAR, 1) == 0);
	CU_ASSERT(calc_padding(DYN_S_CHAR, 44) == 0);
	/* voidpointer */
	CU_ASSERT(calc_padding(DYN_S_VOIDP, 4) == 4);
	CU_ASSERT(calc_padding(DYN_S_VOIDP, 0) == 0);
	/* double */
	CU_ASSERT(calc_padding(DYN_S_DOUBLE, 4) == 4);
	CU_ASSERT(calc_padding(DYN_S_DOUBLE, 0) == 0);
	CU_ASSERT(calc_padding(DYN_S_DOUBLE, 8) == 0);
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

