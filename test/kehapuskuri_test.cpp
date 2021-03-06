#include <gtest/gtest.h>
#include "../kehapuskuri.h"

TEST(KehaPuskuriTesti, PuskuriinLisaaminen)
{
    char x = 0;

    do
    {
        EXPECT_TRUE(insertToBuffer(x++));
    } while (x != 0);

    EXPECT_FALSE(insertToBuffer(x));

    takeFromBuffer();

    EXPECT_TRUE(insertToBuffer(x));
    EXPECT_FALSE(insertToBuffer(x));
}

TEST(KehaPuskuriTesti, PuskuristaOttaminen)
{
    char x = 0;

    EXPECT_FALSE(bufferIsReadable());
    takeFromBuffer();
    EXPECT_FALSE(bufferIsReadable());

    do
    {
        insertToBuffer(x++);
    } while (x != 0);

    for (int i = 0; i < 256; i++, x++)
    {
        EXPECT_TRUE(bufferIsReadable());
        EXPECT_EQ(takeFromBuffer(), x);
    }

    EXPECT_FALSE(bufferIsReadable());
    EXPECT_EQ(takeFromBuffer(), x);
}
