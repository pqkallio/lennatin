#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>

static inline void set_address_lines_to_input_mode()
{
    DDRD &= ~0xf0;
}

static inline void set_address_lines_to_output_mode()
{
    DDRD |= 0xf0;
}

static inline void set_zero_address()
{
    PORTD &= ~0xf0;
}

static inline void enable_com()
{
    PORTB |= _BV(LCD_E);
}

static inline void disable_com()
{
    PORTB &= ~_BV(LCD_E);
}

static inline void execute_command()
{
    disable_com();
    _delay_us(1);

    enable_com();
    _delay_us(1);

    disable_com();
    _delay_us(100);
}

static void wait_for_turn()
{
    set_address_lines_to_input_mode();

    PORTB = (PORTB & ~_BV(LCD_RS)) | _BV(LCD_RW);

    for (;;)
    {
        execute_command();

        enable_com();
        _delay_us(1);

        bool busy = (PIND & _BV(LCD_DB7)) == _BV(LCD_DB7);

        disable_com();
        _delay_us(100);

        if (!busy)
            break;
    }
}

/**
 * Wait for the LCD's busy flag to be 0 before running the task.
 */
static void perform_task(void (*run_task)())
{
    wait_for_turn();

    run_task();
}

static void init_display()
{
    set_address_lines_to_output_mode();

    set_zero_address();
    PORTD |= _BV(LCD_DB4) | _BV(LCD_DB5);

    execute_command();
    _delay_us(4500);

    execute_command();
    _delay_us(4500);

    execute_command();
    _delay_us(150);
}

static void set_4bit_interface()
{
    set_address_lines_to_output_mode();

    set_zero_address();
    PORTD |= _BV(LCD_DB5);

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    execute_command();
}

static void set_font_and_display_line_count()
{
    set_4bit_interface();

    set_zero_address();
    PORTD = (PORTD | _BV(LCD_DB3)) & ~_BV(LCD_DB2);

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    execute_command();
}

static void display_on()
{
    set_address_lines_to_output_mode();

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    set_zero_address();
    execute_command();

    PORTD |= _BV(LCD_DB3) | _BV(LCD_DB2) | _BV(LCD_DB0);
    execute_command();
}

void lcd_clear()
{
    set_address_lines_to_output_mode();

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    set_zero_address();
    execute_command();

    PORTD |= _BV(LCD_DB0);
    execute_command();
}

static void set_entry_mode()
{
    set_address_lines_to_output_mode();

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    set_zero_address();
    execute_command();

    PORTD |= _BV(LCD_DB2) | _BV(LCD_DB1);
    execute_command();
}

void lcd_init()
{
    // Set control pins as output pins
    DDRB |= _BV(LCD_RS) | _BV(LCD_RW) | _BV(LCD_E);

    _delay_ms(50);

    init_display();

    perform_task(set_4bit_interface);
    perform_task(set_font_and_display_line_count);
    perform_task(display_on);
    perform_task(lcd_clear);
    perform_task(set_entry_mode);
}

void lcd_write_char(unsigned char c)
{
    wait_for_turn();

    set_address_lines_to_output_mode();

    PORTB = (PORTB & ~_BV(LCD_RW)) | _BV(LCD_RS);

    set_zero_address();
    PORTD |= (0xf0 & c);

    execute_command();

    set_zero_address();
    PORTD |= (c << 4);

    execute_command();
}

void lcd_write_string(char *str)
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++)
    {
        lcd_write_char((unsigned char)str[i]);
    }
}
