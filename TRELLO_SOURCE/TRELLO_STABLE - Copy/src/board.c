#include "main.h"
#include "gui.h"
#include "mouse.h"
#include "board.h"
#include "files.h"

// Need for sprites
#include <compression.h>
#include "decompress.h"
#include "gfx/sprites.h"

int BN; // board #
struct data_board_t boards[28]; // data in broad
struct data_list_t list[30]; // list
int x, y, len;

void Board_UIsetup(const int num)
{
	BN = num;
	display_type = 7;
	GUI_Header(boards[num].name, 1, boards[num].color);
	// load_board();
	Board_UIBody(boards[num].color);
	return;
}

void Board_UIBody(const int color)
{
	display_type = 7;
	gfx_SetColor(color + 2);
	gfx_FillRectangle(0, 23, 320, 217);
	render_list();
	Render_Scroll_Bar(3, 237, 1);
	return;
}

void render_cards(void)
{
	int l;
	y = 48;
	for (l = 0; l < list[i].card_amount; l++){		

		if (list[i].cards[l].active == true){
			gfx_SetColor(gfx_RGBTo1555(244, 245, 247));
			gfx_FillRectangle(x + 2 + scrollX, y, 77, 25);
			
			len = fontlib_GetStringWidth(list[i].cards[l].name);
			if ((x + 5) + scrollX + len < 315 && (x + 5) + scrollX > 0){
				fontlib_SetCursorPosition(x + 4 + scrollX, y + 7 );
				fontlib_DrawStringL(list[i].cards[l].name, 10);
			}
		}
		
		y += 28;
	}
}

void render_list(void){
	x = 7;
	fontlib_SetForegroundColor(0);
	
	for (i = 0; i < boards[BN].list_amount; i++){
		if (list[i].active == true){
			len = fontlib_GetStringWidth(list[i].name);
			gfx_SetColor(255);
			gfx_FillRectangle(x + scrollX, 30, 81, (list[i].card_amount * 28) + 29);  // list  is drawn here
		
			if ((x + 5) + scrollX + len < 315 && (x + 5) + scrollX > 0){
				fontlib_SetCursorPosition(x + 5 + scrollX, 32 );
				fontlib_DrawStringL(list[i].name, 15);
			}
		
			render_cards();
		
			gfx_SetColor(gfx_RGBTo1555(244, 245, 247));
			gfx_FillRectangle(x + 2 + scrollX, 59 + (list[i].card_amount * 28) - 11, 77, 9);
			
			len = fontlib_GetStringWidth("+ Add Card");
			if ((x + 16) + scrollX + len < 315 && (x + 16) + scrollX > 0){
				fontlib_SetCursorPosition(x + 16 + scrollX, 59 + (list[i].card_amount * 28) - 11);
				fontlib_DrawString("+ Add Card");
			}
			
			x += 98;
		}
	}
	
	gfx_SetColor(255);
	gfx_FillRectangle(x + scrollX, 30, 81, 12);
	
	len = fontlib_GetStringWidth("+ Add List");
	if ((x + 16) + scrollX + len > 0 && x + 16 + scrollX + len < 300){
		fontlib_SetCursorPosition(x + 18 + scrollX, 32);
		fontlib_DrawString("+ Add List");
	}
	return;
}

void render_scrollY_Card(void){	
}

/*
**
**
**
**
*/
