/*
 * oled_drv.c
 *
 * Created: 22.09.2022 10:09:07
 *  Author: haavarok
 */ 

#include "oled_drv.h"

uint16_t oled_cursor_counter = 0;

void oled_write_cmd(char command)
{
	volatile char *oled_cmd_reg = (char *) 0x1000;
	oled_cmd_reg[0] = command;
}

void oled_init()
{
	oled_write_cmd(0xae); // display off
	oled_write_cmd(0xa1); //segment remap
	oled_write_cmd(0xda); //common pads hardware: alternative
	oled_write_cmd(0x12);
	oled_write_cmd(0xc8); //common output scan direction:com63~com0
	oled_write_cmd(0xa8); //multiplex ration mode:63
	oled_write_cmd(0x3f);
	oled_write_cmd(0xd5); //display divide ratio/osc. freq. mode
	oled_write_cmd(0x80);
	oled_write_cmd(0x81); //contrast control
	oled_write_cmd(0xFF);
	oled_write_cmd(0xd9); //set pre-charge period
	oled_write_cmd(0x21);
	oled_write_cmd(0x20); //Set Memory Addressing Mode (Horizontal)
	oled_write_cmd(0x00);
	oled_write_cmd(0xdb); //VCOM deselect level mode
	oled_write_cmd(0x30);
	oled_write_cmd(0xad); //master configuration
	oled_write_cmd(0x00);
	oled_write_cmd(0xa4); //out follows RAM content
	oled_write_cmd(0xa6); //set normal display
	oled_write_cmd(0xaf); // display on
	
	oled_write_cmd(0b00100001); // Set Column Address
	oled_write_cmd(0b00000000);
	oled_write_cmd(0b11111111);
	
	oled_write_cmd(0b00100010); // Set Page Address
	oled_write_cmd(0b00000000);
	oled_write_cmd(0b11111111);
	
	oled_reset(); // Set all pixels low
}

void oled_reset()
{
	for(int i = 0; i < OLED_RES; i++) {
		oled_write_data(0x00);
	}
}

void oled_home()
{
	uint16_t to_move = OLED_RES - oled_cursor_counter;
	
	for(int i=0; i<to_move; i++){
		oled_write_data(0x00);
	}
	
	oled_reset();
	oled_cursor_counter = 0;
}

void oled_goto_line(/*line*/)
{
	
}

void oled_goto_column();

void oled_clear_line(/*line*/)
{
	
}

void oled_pos(/*row, column*/)
{
	
}

void oled_write_data(char data) // Volatile
{
	volatile char *oled_data_reg = (char *) 0x1200;
	oled_data_reg[0] = data;
	oled_cursor_counter++;
}

void oled_print(/*char**/)
{
	
}

void oled_set_brightness(uint8_t lvl_percent)
{
	uint8_t lvl = lvl_percent * 255 / 100;
	oled_write_cmd(0x81); //contrast control
	oled_write_cmd(lvl);
}

void oled_testingtesting()
{
	for(int i = 0; i < 50; i++){
		oled_write_data(0b00011000); // Write arrow
		oled_write_data(0b00011000);
		oled_write_data(0b01111110);
		oled_write_data(0b00111100);
		oled_write_data(0b00011000);
		_delay_ms(50);
	}
	oled_home();
}





