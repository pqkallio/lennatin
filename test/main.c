#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "ringbuffer_test.h"
#include "morse_test.h"

CU_SuiteInfo create_test_suite(char *name, CU_TestInfo *tests)
{
    CU_SuiteInfo info = {name, NULL, NULL, NULL, NULL, tests};

    return info;
}

int main()
{
    CU_ErrorCode err = CU_initialize_registry();

    if (err != CUE_SUCCESS)
    {
        return err;
    }

    CU_TestInfo ringbuffer_tests[] = {
        {"Insert to ringbuffer", test_add_to_buffer},
        {"Take from ringbuffer", test_take_from_buffer},
        CU_TEST_INFO_NULL,
    };

    CU_TestInfo morse_tests[] = {
        {"ABCDEFG", test_ABCDEFG},
        {"HIJKLMN", test_HIJKLMN},
        {"OPQRSTU", test_OPQRSTU},
        {"VWXYZ", test_VWXYZ},
        {"Scandics", test_scandics},
        {"Numbers", test_numbers},
        {"Special characters", test_special_characters},
        CU_TEST_INFO_NULL,
    };

    CU_SuiteInfo suites[] = {
        create_test_suite("Ringbuffer", ringbuffer_tests),
        create_test_suite("Morse", morse_tests),
        CU_SUITE_INFO_NULL,
    };

    err = CU_register_suites(suites);

    if (err != CUE_SUCCESS)
    {
        CU_cleanup_registry();

        return err;
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
