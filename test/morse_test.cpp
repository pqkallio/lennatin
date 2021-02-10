#include <gtest/gtest.h>
#include "../morse.h"
#include "../kehapuskuri.h"
#include "../merkit.h"

static KehaPuskuri<char> PUSKURI;

void laitaPuskuriin(const char *merkit)
{
    while (*merkit != '\0')
    {
        PUSKURI.laita(*merkit++);
    }
}

TEST(MorseTesti, ABCDEFG)
{
    laitaPuskuriin(".- -... -.-. -.. . ..-. --.");

    for (char c = 'A'; c <= 'G'; c++)
    {
        EXPECT_EQ(haeKirjain(PUSKURI), c);
    }
}

TEST(MorseTesti, HIJKLMN)
{
    laitaPuskuriin(".... .. .--- -.- .-.. -- -.");

    for (char c = 'H'; c <= 'N'; c++)
    {
        EXPECT_EQ(haeKirjain(PUSKURI), c);
    }
}

TEST(MorseTesti, OPQRSTU)
{
    laitaPuskuriin("--- .--. --.- .-. ... - ..-");

    for (char c = 'O'; c <= 'U'; c++)
    {
        EXPECT_EQ(haeKirjain(PUSKURI), c);
    }
}

TEST(MorseTesti, VWXYZ)
{
    laitaPuskuriin("...- .-- -..- -.-- --..");

    for (char c = 'V'; c <= 'Z'; c++)
    {
        EXPECT_EQ(haeKirjain(PUSKURI), c);
    }
}

TEST(MorseTesti, Skandit)
{
    laitaPuskuriin(".--.- .-.- ---.");

    EXPECT_EQ(haeKirjain(PUSKURI), merkit::AO);
    EXPECT_EQ(haeKirjain(PUSKURI), merkit::AE);
    EXPECT_EQ(haeKirjain(PUSKURI), merkit::OE);
}

TEST(MorseTesti, Numerot)
{
    laitaPuskuriin("----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----.");

    for (char c = '0'; c <= '9'; c++)
    {
        EXPECT_EQ(haeKirjain(PUSKURI), c);
    }
}

TEST(MorseTesti, Erikoismerkit)
{
    laitaPuskuriin("..--.. -..-. -...- ---... .-.-.- --..-- -....- -.--. -.--.-");

    EXPECT_EQ(haeKirjain(PUSKURI), '?');
    EXPECT_EQ(haeKirjain(PUSKURI), '/');
    EXPECT_EQ(haeKirjain(PUSKURI), '=');
    EXPECT_EQ(haeKirjain(PUSKURI), ':');
    EXPECT_EQ(haeKirjain(PUSKURI), '.');
    EXPECT_EQ(haeKirjain(PUSKURI), ',');
    EXPECT_EQ(haeKirjain(PUSKURI), '-');
    EXPECT_EQ(haeKirjain(PUSKURI), '(');
    EXPECT_EQ(haeKirjain(PUSKURI), ')');
}
