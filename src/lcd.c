#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "lcd.h"

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

static bool is_busy()
{
    enable_com();
    _delay_us(1);

    bool busy = (PIND & _BV(LCD_DB7)) == _BV(LCD_DB7);

    disable_com();
    _delay_us(100);

    return busy;
}

/**
 * Wait for the LCD's busy flag to be 0 before running the task.
 */
static void perform_task(void (*run_task)())
{
    set_address_lines_to_input_mode();

    PORTB = (PORTB & ~_BV(LCD_RS)) | _BV(LCD_RW);

    do
    {
        execute_command();
    } while (is_busy()); // Wait for the busy flag to be zero

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

    PORTD |= _BV(LCD_DB3) | _BV(LCD_DB2) | _BV(LCD_DB1);
    execute_command();
}

static void display_clear()
{
    set_address_lines_to_output_mode();

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    set_zero_address();
    execute_command();

    PORTD |= _BV(LCD_DB0);
    execute_command();

    _delay_us(2000);
}

static void set_entry_mode()
{
    set_address_lines_to_output_mode();

    PORTB &= ~(_BV(LCD_RS) | _BV(LCD_RW));

    set_zero_address();
    execute_command();

    PORTD |= _BV(LCD_DB2) | _BV(LCD_DB1) | _BV(LCD_DB0);
    execute_command();
}

void lcd_init()
{
    // Set control pins as output pins
    DDRB |= _BV(LCD_RS) | _BV(LCD_RW) | _BV(LCD_E);
    disable_com();

    _delay_ms(50);

    init_display();

    perform_task(set_4bit_interface);
    perform_task(set_font_and_display_line_count);
    perform_task(display_on);
    perform_task(display_clear);
    perform_task(set_entry_mode);
}

void lcd_write_char(unsigned char c)
{
}
