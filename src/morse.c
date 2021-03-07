#include <stddef.h>
#include "morse.h"

// FINNISH MORSE CODES AS A TREE STRUCTURE
// ---------------------------------------

// BEGINNING WITH A DOT

// Six signals
static const Morse question_mark = {.ch = 0x3f, .dot = NULL, .dash = NULL};
static const Morse dot = {.ch = 0x2e, .dot = NULL, .dash = NULL};

// Five signals
static const Morse five = {.ch = 0x35, .dot = NULL, .dash = NULL};
static const Morse four = {.ch = 0x34, .dot = NULL, .dash = NULL};
static const Morse three = {.ch = 0x33, .dot = NULL, .dash = NULL};
static const Morse question_mark_lead = {.ch = 0x00, .dot = &question_mark, .dash = NULL};
static const Morse two = {.ch = 0x32, .dot = NULL, .dash = NULL};
static const Morse dot_lead = {.ch = 0x00, .dot = NULL, .dash = &dot};
static const Morse AO = {.ch = 0xc5, .dot = NULL, .dash = NULL};
static const Morse one = {.ch = 0x31, .dot = NULL, .dash = NULL};

// Four signals
static const Morse H = {.ch = 0x48, .dot = &five, .dash = &four};
static const Morse V = {.ch = 0x56, .dot = NULL, .dash = &three};
static const Morse F = {.ch = 0x46, .dot = NULL, .dash = NULL};
static const Morse two_lead = {.ch = 0x00, .dot = &question_mark_lead, .dash = &two};
static const Morse L = {.ch = 0x4c, .dot = NULL, .dash = NULL};
static const Morse AE = {.ch = 0xc4, .dot = &dot_lead, .dash = NULL};
static const Morse P = {.ch = 0x50, .dot = NULL, .dash = &AO};
static const Morse J = {.ch = 0x4a, .dot = NULL, .dash = &one};

// Three signals
static const Morse S = {.ch = 0x53, .dot = &H, .dash = &V};
static const Morse U = {.ch = 0x55, .dot = &F, .dash = &two_lead};
static const Morse R = {.ch = 0x52, .dot = &L, .dash = &AE};
static const Morse W = {.ch = 0x57, .dot = &P, .dash = &J};

// Two signals
static const Morse I = {.ch = 0x49, .dot = &S, .dash = &U};
static const Morse A = {.ch = 0x41, .dot = &R, .dash = &W};

// One signal
static const Morse E = {.ch = 0x45, .dot = &I, .dash = &A};

// BEGINNING WITH A DASH

// Six signals
static const Morse dash = {.ch = 0x2d, .dot = NULL, .dash = NULL};
static const Morse right_parenthesis = {.ch = 0x29, .dot = NULL, .dash = NULL};
static const Morse comma = {.ch = 0x2c, .dot = NULL, .dash = NULL};
static const Morse colon = {.ch = 0x3a, .dot = NULL, .dash = NULL};

// Five signals
static const Morse six = {.ch = 0x36, .dot = NULL, .dash = &dash};
static const Morse equal = {.ch = 0x3d, .dot = NULL, .dash = NULL};
static const Morse slash = {.ch = 0x2f, .dot = NULL, .dash = NULL};
static const Morse left_parenthesis = {.ch = 0x28, .dot = NULL, .dash = &right_parenthesis};
static const Morse seven = {.ch = 0x37, .dot = NULL, .dash = NULL};
static const Morse comma_lead = {.ch = 0x00, .dot = NULL, .dash = &comma};
static const Morse eight = {.ch = 0x38, .dot = &colon, .dash = NULL};
static const Morse nine = {.ch = 0x39, .dot = NULL, .dash = NULL};
static const Morse zero = {.ch = 0x30, .dot = NULL, .dash = NULL};

// Four signals
static const Morse B = {.ch = 0x42, .dot = &six, .dash = &equal};
static const Morse X = {.ch = 0x58, .dot = &slash, .dash = NULL};
static const Morse C = {.ch = 0x43, .dot = NULL, .dash = NULL};
static const Morse Y = {.ch = 0x59, .dot = &left_parenthesis, .dash = NULL};
static const Morse Z = {.ch = 0x5a, .dot = &seven, .dash = &comma_lead};
static const Morse Q = {.ch = 0x51, .dot = NULL, .dash = NULL};
static const Morse OE = {.ch = 0xd6, .dot = &eight, .dash = NULL};
static const Morse nine_lead = {.ch = 0x00, .dot = &nine, .dash = &zero};

// Three signals
static const Morse D = {.ch = 0x44, .dot = &B, .dash = &X};
static const Morse K = {.ch = 0x4b, .dot = &C, .dash = &Y};
static const Morse G = {.ch = 0x47, .dot = &Z, .dash = &Q};
static const Morse O = {.ch = 0x4f, .dot = &OE, .dash = &nine_lead};

// Two signals
static const Morse N = {.ch = 0x4e, .dot = &D, .dash = &K};
static const Morse M = {.ch = 0x4d, .dot = &G, .dash = &O};

// One signal
static const Morse T = {.ch = 0x54, .dot = &N, .dash = &M};

// ROOT

static const Morse root = {.ch = 0x00, .dot = &E, .dash = &T};

unsigned char get_char(struct _ringbuffer *buf)
{
    const Morse *morse = &root;

    while (buffer_is_readable(buf) && morse != NULL)
    {
        char ch = take_from_buffer(buf);

        switch (ch)
        {
        case '.':
            morse = morse->dot;
            break;
        case '-':
            morse = morse->dash;
            break;
        default:
            goto END;
        }
    }

END:
    if (morse == NULL)
    {
        return 0x00;
    }

    return morse->ch;
}
