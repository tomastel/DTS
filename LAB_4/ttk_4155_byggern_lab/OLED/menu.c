#include "menu.h"

uint8_t num_options_in_menu;
uint16_t menu_option_value;
uint8_t arrow_on_line;

void this_end()
{
	print_uart("sug pikk");
}

void back()
{
	//enter_menu(current_menu.parent_menu);
}

menu_struct sub_menu_back = {
	"Back",
	0,
	back,
	NULL
};

menu_struct sub_menu_1_1_1 = {
	"Submenu 1.1.1",
	0,
	this_end,
	NULL
};

menu_struct sub_menu_1_1 = {
	"Submenu 1.1",
	1,
	NULL,
	{&sub_menu_1_1_1}
};

menu_struct sub_menu_1 = {
	"Submenu 1",
	1,
	NULL,
	{&sub_menu_1_1}
};

menu_struct sub_menu_2 = {
	"Submenu 2",
	1,
	NULL,
	NULL
};


menu_struct main_menu = {
	"Main Menu",
	2,
	NULL,
	{&sub_menu_1, &sub_menu_2}
};

menu_struct current_menu;

void enter()
{
	enter_menu(current_menu.submenu[arrow_on_line-1]);
	if (num_options_in_menu != 0)
	{
		menu_struct *temp = current_menu.submenu[arrow_on_line-1];
		memcpy(&current_menu, &temp, sizeof(current_menu));
	}
}

void enter_menu(menu_struct* menu)
{
	menu_struct* temp_menu = menu;
	const char *this_title = temp_menu->title;
	
	oled_reset();
	oled_goto_line(0);
	oled_goto_column(40);
	print_oled(this_title);
	
	uint8_t temp_num = temp_menu->num_options;
	char* num = temp_num + '0';
	print_uart(&num);
	print_uart("\r\n");
	
	if(temp_num == 0)
	{
		print_uart("fsaffsafsa");
		num_options_in_menu = 0;
		menu->command();
		
		return;
	}
	print_uart("her");
	for(uint8_t i = 0; i < temp_menu->num_options; i++)
	{
		menu_struct* temp_submenu = temp_menu->submenu[i];
		char *tit = temp_submenu->title;
		oled_goto_line(i+1);
		oled_goto_column(8);
		print_oled(tit);
	}
	num_options_in_menu = menu->num_options;
	oled_pos(FIRST_LINE_MENU, 0);
	print_arrow();
	arrow_on_line = FIRST_LINE_MENU;
}

void menu_init()
{
	current_menu = main_menu;
	enter_menu(&current_menu);
}

void menu_navigate()
{	
	static dir_t last_dir;
	dir_t dir = dir_read(pos_read());
	
	
	if(dir == DOWN && dir != last_dir){
		move_arrow_down();
	}
	else if(dir == UP && dir != last_dir){
		move_arrow_up();
	}
	last_dir = dir;
}


void print_arrow()
{
	oled_write_data(0x18);
	oled_write_data(0x18);
	oled_write_data(0x7E);
	oled_write_data(0x3C);
	oled_write_data(0x18);
}

void clear_arrow()
{
	for(uint8_t i = 0; i < 5; i++) oled_write_data(0x00);
}

void move_arrow_up()
{
	if(arrow_on_line > FIRST_LINE_MENU && arrow_on_line <= num_options_in_menu)
	{
		oled_goto_line(arrow_on_line);
		oled_goto_column(0);
		clear_arrow();
		arrow_on_line--;
		menu_option_value--;
		oled_goto_line(arrow_on_line);
		oled_goto_column(0);
		print_arrow();
	}
}

void move_arrow_down()
{
	if(arrow_on_line >= FIRST_LINE_MENU && arrow_on_line < num_options_in_menu)
	{
		oled_goto_line(arrow_on_line);
		oled_goto_column(0);
		clear_arrow();
		arrow_on_line++;
		menu_option_value++;
		oled_goto_line(arrow_on_line);
		oled_goto_column(0);
		print_arrow();
	}
}