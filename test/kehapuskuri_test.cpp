#include <gtest/gtest.h>
#include "../kehapuskuri.h"

TEST(KehaPuskuriTesti, PuskuriinLisaaminen)
{
    KehaPuskuri<char> puskuri{};

    char x = 0;

    do
    {
        EXPECT_TRUE(puskuri.laita(x++));
    } while (x != 0);

    EXPECT_FALSE(puskuri.laita(x));

    puskuri.ota();

    EXPECT_TRUE(puskuri.laita(x));
    EXPECT_FALSE(puskuri.laita(x));
}

TEST(KehaPuskuriTesti, PuskuristaOttaminen)
{
    KehaPuskuri<char> puskuri{};

    char x = 0;

    EXPECT_FALSE(puskuri.luettavissa());
    puskuri.ota();
    EXPECT_FALSE(puskuri.luettavissa());

    do
    {
        puskuri.laita(x++);
    } while (x != 0);

    for (int i = 0; i < 256; i++, x++)
    {
        EXPECT_TRUE(puskuri.luettavissa());
        EXPECT_EQ(puskuri.ota(), x);
    }

    EXPECT_FALSE(puskuri.luettavissa());
    EXPECT_EQ(puskuri.ota(), x);
}
