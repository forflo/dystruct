#ifndef DSTRU_TEST_FUNCS
#define DSTRU_TEST_FUNCS

/* Required by CUnit. They do nothing */
int init_test_dyn_str(void);
int clean_test_dyn_str(void);

/* Creation and destruction test */
void test_init(void);

/* Tests whether the padding is calculated correctly */
void test_padding_normal(void);
void test_padding_aligned(void);

/* Tests wheter the function dstru_sizeof() works correctly */
void test_sizeof(void);

/* Test for adding voidpointer */
void test_voidp(void);

/* Tests the creation of structures under several circumstances*/
void test_creation_normal1(void);
void test_creation_normal2(void);
void test_creation_aligned(void);
void test_creation_nested(void);

#endif
