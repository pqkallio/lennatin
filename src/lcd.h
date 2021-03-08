#ifndef _LCD_H
#define _LCD_H

// Control lines
#define LCD_RS 1
#define LCD_RW 2
#define LCD_E 3

// Address lines
#define LCD_DB0 4
#define LCD_DB1 5
#define LCD_DB2 6
#define LCD_DB3 7
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7

void lcd_init();
void lcd_write_char(unsigned char c);

#endif /* _LCD_H */
