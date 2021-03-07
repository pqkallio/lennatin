#include <CUnit/CUnit.h>
#include "ringbuffer_test.h"
#include "ringbuffer.h"

void test_add_to_buffer()
{
  char buffer[255] = {0};
  struct _ringbuffer b = {.idx = 0, .rounds = 0, .end = 0, .buffer = buffer};

  char x = 0;

  do
  {
    CU_ASSERT_TRUE(insert_into_buffer(&b, x++));
  } while (x != 0);

  CU_ASSERT_FALSE(insert_into_buffer(&b, x));

  take_from_buffer(&b);

  CU_ASSERT_TRUE(insert_into_buffer(&b, x));
  CU_ASSERT_FALSE(insert_into_buffer(&b, x));
}

void test_take_from_buffer()
{
  char buffer[255] = {0};
  struct _ringbuffer b = {.idx = 0, .rounds = 0, .end = 0, .buffer = buffer};

  char x = 0;

  CU_ASSERT_FALSE(buffer_is_readable(&b));
  take_from_buffer(&b);
  CU_ASSERT_FALSE(buffer_is_readable(&b));

  do
  {
    insert_into_buffer(&b, x++);
  } while (x != 0);

  for (int i = 0; i < 256; i++, x++)
  {
    CU_ASSERT_TRUE(buffer_is_readable(&b));
    CU_ASSERT_EQUAL(take_from_buffer(&b), x);
  }

  CU_ASSERT_FALSE(buffer_is_readable(&b));
  CU_ASSERT_EQUAL(take_from_buffer(&b), x);
}
