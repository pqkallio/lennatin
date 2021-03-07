#include <CUnit/CUnit.h>
#include "morse_test.h"
#include "morse.h"
#include "ringbuffer.h"

static char ARR[255] = {0};
struct _ringbuffer BUF = {.idx = 0, .end = 0, .rounds = 0, .buffer = ARR};

void set_buffer_content(const char *str)
{
    while (*str)
    {
        insert_into_buffer(&BUF, *str++);
    }
}

void test_ABCDEFG()
{
    set_buffer_content(".- -... -.-. -.. . ..-. --.");

    for (char c = 'A'; c <= 'G'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_HIJKLMN()
{
    set_buffer_content(".... .. .--- -.- .-.. -- -.");

    for (char c = 'H'; c <= 'N'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_OPQRSTU()
{
    set_buffer_content("--- .--. --.- .-. ... - ..-");

    for (char c = 'O'; c <= 'U'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_VWXYZ()
{
    set_buffer_content("...- .-- -..- -.-- --..");

    for (char c = 'V'; c <= 'Z'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_scandics()
{
    set_buffer_content(".--.- .-.- ---.");

    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)0xc5);
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)0xc4);
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)0xd6);
}

void test_numbers()
{
    set_buffer_content("----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----.");

    for (char c = '0'; c <= '9'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_special_characters()
{
    set_buffer_content("..--.. -..-. -...- ---... .-.-.- --..-- -....- -.--. -.--.-");

    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)'?');
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)'/');
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)'=');
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)':');
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)'.');
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)',');
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)'-');
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)'(');
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)')');
}
