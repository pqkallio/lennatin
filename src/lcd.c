#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

inline void set_address_lines_to_input_mode()
{
    DDRD &= ~0xf0;
}

inline void set_address_lines_to_output_mode()
{
    DDRD |= 0xf0;
}

inline void set_zero_address()
{
    PORTD &= ~0xf0;
}

inline void enable_com()
{
    PORTB |= _BV(LCD_E);
}

inline void disable_com()
{
    PORTB &= ~_BV(LCD_E);
}

inline void execute_command()
{
    enable_com();
    _delay_ms(1);
    disable_com();
}

/**
 * Wait for the LCD's busy flag to be 0 before running the task.
 */
void perform_task(void (*run_task)())
{
    set_address_lines_to_input_mode();

    PORTB = (PORTB & ~_BV(LCD_RS)) | _BV(LCD_RW);

    while ((PIND & _BV(LCD_DB7)) == _BV(LCD_DB7))
        ; // Wait for the busy flag to be zero

    run_task();
}

void set_4bit_interface()
{
    set_address_lines_to_output_mode();

    set_zero_address();
    PORTD |= _BV(LCD_DB5);

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    execute_command();
}

void set_font_and_display_line_count()
{
    set_4bit_interface();

    set_zero_address();
    PORTD = (PORTD | _BV(LCD_DB7)) & ~_BV(LCD_DB6);

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    execute_command();
}

void display_on()
{
    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    set_zero_address();
    execute_command();

    PORTD |= _BV(LCD_DB7) | _BV(LCD_DB6) | _BV(LCD_DB5);
    execute_command();
}

void display_clear()
{
    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    set_zero_address();
    execute_command();

    PORTD |= _BV(LCD_DB0);
    execute_command();
}

void set_entry_mode()
{
    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    set_zero_address();
    execute_command();

    PORTD |= _BV(LCD_DB2) | _BV(LCD_DB1) | _BV(LCD_DB0);
    execute_command();
}

void lcd_init()
{
    // Set control pins as output pins
    DDRB &= ~(_BV(LCD_RS) | _BV(LCD_RW) | _BV(LCD_E));

    perform_task(set_4bit_interface);
    perform_task(set_font_and_display_line_count);
    perform_task(display_on);
    perform_task(display_clear);
    perform_task(set_entry_mode);
}

void lcd_write_char(unsigned char c);
