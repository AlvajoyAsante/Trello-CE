#ifndef MOUSE_H
#define MOUSE_H

#include <tice.h>
#include <keypadc.h>
#include <graphx.h>

// functions
void mouse_loop(void);

void mouse_Enter(void);

int mouse_HoverDetect(void);

void other_keys(void);

void mouse_keys(void);

void Render_Mouse(void);

int mouse_BoardDetect(void);

int mouse_CardDetect(void);

int mouse_ListDetect(void);

int mouse_ButtonDetect(void);

void render_mouse_menu(void);

bool Mouse_Detect_Rect(int ix, int iy, int iw, int ih);


// external Vars 
extern int ext, scrollX, scrollY;

extern int board_amount, display_type;

extern kb_key_t key;

extern gfx_sprite_t *mouse_buff;

struct mouses_t{
	int x;
	int y;
	int spd;
};
extern struct mouses_t mouse;

extern int show_command;
#endif