#ifndef GUI_H
#define GUI_H

#include <tice.h>
#include <fontlibc.h>
#include <fileioc.h>
#include <string.h>

// External variables 
extern int8_t ver_type;
extern int8_t ver_maj;
extern int8_t ver_min;

extern fontlib_font_pack_t *my_font_pack;
extern fontlib_font_t *my_font;

extern ti_var_t file;

extern uint8_t error;

extern int newsprt_x;

struct buttons_data_t{
	bool active;
	int x;
	int y;
	int w;
	int h;
};

extern struct buttons_data_t buttons[100];

// Function
void gfx_BatteryStatus(int x, int y);
void gfx_PrintTime(int x, int y);
void gfx_PrintDate(int x, int y);

void splash_screen(void);
void show_ver(void);
void UI_setup(void);
void GUI_Header(const char *name, int type, int color);
void GUI_Menu(const int selected);
void GUI_Body(const char *name);
void GUI_Clear_Body(uint8_t color);

void Render_Menu_Help(void);
void Render_Menu_Settings(void);
void Render_Menu_MyCards(void);
void Render_Menu_Home(void);
int Render_Button(const char *text, int x, int y, int w, int h, int index);
int Render_Add_Menu(void);

void Render_Board(void);
void Render_Body(void);
void gfx_loading(int x, int y, int time);
void Render_Scroll_Bar(int x, int y, int type);

void Centered_Dialog_Box(const char *name, uint24_t iw, uint8_t ih);
#endif
