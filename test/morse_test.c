#include <CUnit/CUnit.h>
#include "morse_test.h"
#include "morse.h"
#include "ringbuffer.h"

static char ARR[255] = {0};
struct _kehapuskuri BUF = {.mIndeksi = 0, .mLoppu = 0, .mKierrokset = 0, .mPuskuri = ARR};

void insert_into_buffer(const char *str)
{
    while (*str)
    {
        insertToBuffer(&BUF, *str++);
    }
}

void test_ABCDEFG()
{
    insert_into_buffer(".- -... -.-. -.. . ..-. --.");

    for (char c = 'A'; c <= 'G'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_HIJKLMN()
{
    insert_into_buffer(".... .. .--- -.- .-.. -- -.");

    for (char c = 'H'; c <= 'N'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_OPQRSTU()
{
    insert_into_buffer("--- .--. --.- .-. ... - ..-");

    for (char c = 'O'; c <= 'U'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_VWXYZ()
{
    insert_into_buffer("...- .-- -..- -.-- --..");

    for (char c = 'V'; c <= 'Z'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_scandics()
{
    insert_into_buffer(".--.- .-.- ---.");

    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)0xc5);
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)0xc4);
    CU_ASSERT_EQUAL(get_char(&BUF), (unsigned char)0xd6);
}

void test_numbers()
{
    insert_into_buffer("----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----.");

    for (char c = '0'; c <= '9'; c++)
    {
        CU_ASSERT_EQUAL(get_char(&BUF), c);
    }
}

void test_special_characters()
{
    insert_into_buffer("..--.. -..-. -...- ---... .-.-.- --..-- -....- -.--. -.--.-");

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
