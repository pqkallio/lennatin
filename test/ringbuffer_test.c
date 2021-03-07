#include <CUnit/CUnit.h>
#include "ringbuffer_test.h"
#include "ringbuffer.h"

void test_add_to_buffer()
{
  char buffer[255] = {0};
  struct _kehapuskuri b = {.mIndeksi = 0, .mKierrokset = 0, .mLoppu = 0, .mPuskuri = buffer};

  char x = 0;

  do
  {
    CU_ASSERT_TRUE(insertToBuffer(&b, x++));
  } while (x != 0);

  CU_ASSERT_FALSE(insertToBuffer(&b, x));

  takeFromBuffer(&b);

  CU_ASSERT_TRUE(insertToBuffer(&b, x));
  CU_ASSERT_FALSE(insertToBuffer(&b, x));
}

void test_take_from_buffer()
{
  char buffer[255] = {0};
  struct _kehapuskuri b = {.mIndeksi = 0, .mKierrokset = 0, .mLoppu = 0, .mPuskuri = buffer};

  char x = 0;

  CU_ASSERT_FALSE(bufferIsReadable(&b));
  takeFromBuffer(&b);
  CU_ASSERT_FALSE(bufferIsReadable(&b));

  do
  {
    insertToBuffer(&b, x++);
  } while (x != 0);

  for (int i = 0; i < 256; i++, x++)
  {
    CU_ASSERT_TRUE(bufferIsReadable(&b));
    CU_ASSERT_EQUAL(takeFromBuffer(&b), x);
  }

  CU_ASSERT_FALSE(bufferIsReadable(&b));
  CU_ASSERT_EQUAL(takeFromBuffer(&b), x);
}
