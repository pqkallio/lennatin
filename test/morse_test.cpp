#include <gtest/gtest.h>
#include "../morse.h"
#include "../kehapuskuri.h"

static struct _kehapuskuri PUSKURI;

void laitaPuskuriin(const char *merkit)
{
    while (*merkit != '\0')
    {
        insertToBuffer(&PUSKURI, *merkit++);
    }
}

TEST(MorseTesti, ABCDEFG)
{
    laitaPuskuriin(".- -... -.-. -.. . ..-. --.");

    for (char c = 'A'; c <= 'G'; c++)
    {
        EXPECT_EQ(takeFromBuffer(&PUSKURI), c);
    }
}

TEST(MorseTesti, HIJKLMN)
{
    laitaPuskuriin(".... .. .--- -.- .-.. -- -.");

    for (char c = 'H'; c <= 'N'; c++)
    {
        EXPECT_EQ(takeFromBuffer(&PUSKURI), c);
    }
}

TEST(MorseTesti, OPQRSTU)
{
    laitaPuskuriin("--- .--. --.- .-. ... - ..-");

    for (char c = 'O'; c <= 'U'; c++)
    {
        EXPECT_EQ(takeFromBuffer(&PUSKURI), c);
    }
}

TEST(MorseTesti, VWXYZ)
{
    laitaPuskuriin("...- .-- -..- -.-- --..");

    for (char c = 'V'; c <= 'Z'; c++)
    {
        EXPECT_EQ(takeFromBuffer(&PUSKURI), c);
    }
}

TEST(MorseTesti, Skandit)
{
    laitaPuskuriin(".--.- .-.- ---.");

    EXPECT_EQ(takeFromBuffer(&PUSKURI), (unsigned char)0b11000101);
    EXPECT_EQ(takeFromBuffer(&PUSKURI), (unsigned char)0b11000100);
    EXPECT_EQ(takeFromBuffer(&PUSKURI), (unsigned char)0b11010110);
}

TEST(MorseTesti, Numerot)
{
    laitaPuskuriin("----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----.");

    for (char c = '0'; c <= '9'; c++)
    {
        EXPECT_EQ(takeFromBuffer(&PUSKURI), c);
    }
}

TEST(MorseTesti, Erikoismerkit)
{
    laitaPuskuriin("..--.. -..-. -...- ---... .-.-.- --..-- -....- -.--. -.--.-");

    EXPECT_EQ(takeFromBuffer(&PUSKURI), '?');
    EXPECT_EQ(takeFromBuffer(&PUSKURI), '/');
    EXPECT_EQ(takeFromBuffer(&PUSKURI), '=');
    EXPECT_EQ(takeFromBuffer(&PUSKURI), ':');
    EXPECT_EQ(takeFromBuffer(&PUSKURI), '.');
    EXPECT_EQ(takeFromBuffer(&PUSKURI), ',');
    EXPECT_EQ(takeFromBuffer(&PUSKURI), '-');
    EXPECT_EQ(takeFromBuffer(&PUSKURI), '(');
    EXPECT_EQ(takeFromBuffer(&PUSKURI), ')');
}
