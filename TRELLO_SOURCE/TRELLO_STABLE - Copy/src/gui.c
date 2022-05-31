//  Everything GUI Related is in here!!
#include "main.h"
#include "gui.h"
#include "mouse.h"
#include "board.h"

// Need for sprites
#include <compression.h>
#include "decompress.h"
#include "gfx/sprites.h"

int8_t ver_type = 0;
int8_t ver_maj = 1;
int8_t ver_min = 0;
fontlib_font_pack_t *my_font_pack;
fontlib_font_t *my_font;
ti_var_t file;
uint8_t error;
string_t *Ans_Data;
int checkDate;
int main_color = 0x11;
int body_color = gfx_RGBTo1555(244, 245, 247);
gfx_UninitedSprite(GUI_buff, 50, 50);
struct buttons_data_t buttons[100];

void splash_screen(void){
	gfx_FillScreen(255);
	gfx_SetTextFGColor(254);
	
	//version
	show_ver();
	
	// By / Criedit 
	gfx_SetTextFGColor(0);
	gfx_PrintStringXY("Ported by Alvajoy123", 1, 230);
	zx7_Decompress(GUI_buff, boards_compressed);
	
	gfx_SetTransparentColor(0xF0);
	gfx_ScaledTransparentSprite_NoClip(GUI_buff, 160 - ((13*5)/2), 120 - ((13*5)/2), 5, 5);
	gfx_Blit(1);
	
	gfx_SetTextFGColor(224); // Red
	ti_CloseAll();
	
	// Looks for font data
	file = ti_Open("TREFONT", "r");
	my_font_pack = ti_GetDataPtr(file);
	
	if (!my_font_pack){ // Appvar was found
		gfx_PrintStringXY("'TREFONT' Font Appvar not found!", 1, 10);
		error = 1;
		return;
	}
	
	ti_Close(file);
	
	my_font = fontlib_GetFontByIndexRaw(my_font_pack, 0);
	if (!my_font){
		gfx_PrintStringXY("'SCRFONT' Font Appvar not invalid!", 1, 10);
		error = 2;
		return;
	}else{
		fontlib_SetFont(my_font, 0);
	}
	
	vars_init();
	
	gfx_SetColor(255);
	gfx_loading(152, (120 + 60), 40);
	return;
	
}

void show_ver(void){
	gfx_SetTextFGColor(0);
	gfx_SetTextXY(1, 1);

	switch (ver_type){
		case 0:
			gfx_PrintString("pre a");
		break;
		
		case 1:
			gfx_PrintString("a v.");
		break;
		
		case 2:
			gfx_PrintString("b v.");
		break;
		
		case 3:
			gfx_PrintString("v.");
		break;
	}
	
	gfx_PrintInt(ver_maj, 1);
	gfx_PrintString(".");
	gfx_PrintInt(ver_min, 1);
}

void UI_setup(void){
	display_type = 0;
	gfx_FillScreen(255);
	gfx_SetTransparentColor(0xF0);
	gfx_SetTextFGColor(0);
	// header
	GUI_Header("Boards", 0, main_color);
	GUI_Menu(0);
	GUI_Body("Personal Boards");
	// version
	show_ver();
	
	// battery
	gfx_BatteryStatus(69, 218);
	gfx_SetColor(gfx_RGBTo1555(244, 245, 247));
	fontlib_SetForegroundColor(0);
	gfx_PrintTime(6, 228);
	gfx_PrintDate(6, 216);
	
	
	fontlib_SetForegroundColor(74);
	fontlib_SetCursorPosition(92, 47);
	fontlib_DrawString("No boards where found please make one.");
	
	Render_Body();
}

void GUI_Header(const char *name, int type, int color){
	gfx_SetColor(color);
	gfx_FillRectangle(0, 0, 320, 23);
	
	fontlib_SetForegroundColor(255);
	fontlib_SetCursorPosition(6, 8);
	fontlib_DrawString(name);
	
	gfx_SetTransparentColor(0xF0);
	if (type == 0){
		zx7_Decompress(GUI_buff, create_compressed);
		gfx_TransparentSprite(GUI_buff, 256, 5);
	}
	
	zx7_Decompress(GUI_buff, search_compressed);
	gfx_TransparentSprite(GUI_buff, 278, 5);
	
	zx7_Decompress(GUI_buff, notifications_compressed);
	gfx_TransparentSprite(GUI_buff, 300, 5);
	
	show_ver();
}

void GUI_Menu(const int selected){
	gfx_SetColor(gfx_RGBTo1555(244, 245, 247));
	gfx_FillRectangle(0, 23, 84, 217);
	display_type = selected;
	
	gfx_SetColor(255);
	switch (selected){
		case 0:
			gfx_FillRectangle(0, 25, 84, 15);
		break;
		
		case 1:
			gfx_FillRectangle(0, 41, 84, 15);
		break;
		
		case 2:
			gfx_FillRectangle(0, 72, 84, 15);
		break;
		
		case 3:
			gfx_FillRectangle(0, 87, 84, 15);
		break;
		
		case 4:
			gfx_FillRectangle(0, 101, 84, 15);
		break;
	}
	
	fontlib_SetForegroundColor(0);
	gfx_SetTransparentColor(0xF0);
	zx7_Decompress(GUI_buff, boards_compressed);
	gfx_TransparentSprite(GUI_buff, 4, 26);
	
	fontlib_SetCursorPosition(21, 29);
	fontlib_DrawString("Boards");	
	
	zx7_Decompress(GUI_buff, home_compressed);
	gfx_TransparentSprite(GUI_buff, 4, 43);
	
	fontlib_SetCursorPosition(21, 44);
	fontlib_DrawString("Home");
	
	zx7_Decompress(GUI_buff, cards_compressed);
	gfx_TransparentSprite(GUI_buff, 4, 73);
	
	gfx_SetColor(74);
	gfx_FillRectangle(0, 60, 84, 3);
	
	fontlib_SetCursorPosition(22, 74);
	fontlib_DrawString("My Cards");
	
	zx7_Decompress(GUI_buff, settings_compressed);
	gfx_TransparentSprite(GUI_buff, 4, 87);
	
	fontlib_SetCursorPosition(21, 89);
	fontlib_DrawString("Settings");
	
	zx7_Decompress(GUI_buff, help_compressed);
	gfx_TransparentSprite(GUI_buff, 4, 102);
	
	fontlib_SetCursorPosition(21, 104);
	fontlib_DrawString("Help");
	
	gfx_BatteryStatus(69, 218);
	gfx_SetColor(gfx_RGBTo1555(244, 245, 247));
	fontlib_SetForegroundColor(0);
	gfx_PrintTime(6, 228);
	gfx_PrintDate(6, 216);
}

void GUI_Body(const char *name){
	// gfx_SetColor(255);
	// gfx_FillRectangle(84, 23, 235, 217);
	
	gfx_SetColor(gfx_RGBTo1555(244, 245, 247));
	gfx_FillRectangle(85, 23, 234, 15);
	
	fontlib_SetForegroundColor(0);
	fontlib_SetCursorPosition(92, 27);
	fontlib_DrawString(name);
}

void GUI_Clear_Body(uint8_t color){
	gfx_SetColor(color);
	gfx_FillRectangle(0, 23, 320, 217);
}

void Render_Menu_Help(void){
	display_type = 5;
	gfx_SetColor(255);
	gfx_FillRectangle(84, 23, 235, 217);
	
	GUI_Body("Help");
	fontlib_SetWindow(87, 39, 233, 199);
	fontlib_HomeUp();
	fontlib_SetForegroundColor(0);
	fontlib_DrawString("Trello CE!");
	fontlib_Newline();
	fontlib_DrawString("Trello Board Manager. Manage board and card, stay on top of your team.");
	fontlib_Newline();
	fontlib_DrawString("Ported By Alvajoy123");
	fontlib_Newline();
	fontlib_Newline();
	fontlib_DrawString("Key Binds:");
	fontlib_Newline();
	fontlib_DrawString("[Alpha] + [+] :: Scroll Up");
	fontlib_Newline();
	fontlib_DrawString("[Alpha] + [-] :: Scroll Down");
	fontlib_Newline();
	fontlib_DrawString("[up] [down] [left] [right] :: Move Mouse");
	gfx_Blit(1);
	fontlib_SetWindowFullScreen();
}

void Render_Menu_Settings(void){
	
}

void Render_Menu_MyCards(void){
	
}

void Render_Menu_Home(void){
	
}

int Render_Button(const char *text, int x, int y, int w, int h, int index){
	if (!buttons[index].active){
		gfx_FillRectangle(x, y, w, h);
		gfx_PrintStringXY(text, (w / 2) - x, (h / 2) - y);
		buttons[index].active = true;
		buttons[index].x = x;
		buttons[index].y = y;
		buttons[index].w = w;
		buttons[index].h = h;
	}
	return 0;
}

void Render_Body(void){
	Render_Board();
	GUI_Header("Board", 0, main_color);
	GUI_Body("Personal Boards");	
	Render_Scroll_Bar(316, 42, 0);
}

void Render_Board(void){
	int x = 87, y = 42;
	if (!board_amount) return;
	gfx_SetColor(255);
	gfx_FillRectangle(84, 23, 235, 217);

	for (i = 0; i < board_amount; i++){
		if (boards[i].active == true){
			gfx_SetColor(boards[i].color);
			gfx_FillRectangle(x, y + scrollY, 113, 77);
			gfx_SetColor(0);
			gfx_FillRectangle(x , (y + 64) + scrollY, 113, 13);
			
			fontlib_SetForegroundColor(255);
			fontlib_SetCursorPosition(x + 2, (y + 67) + scrollY);
			if ((y + 67) + scrollY < 235 && (y + 67) + scrollY > 0){
				fontlib_DrawStringL(boards[i].name, 10);
			}
			if (x != 202){
				x = 202;
			}else{
				x = 87;
				y += 91;
			}
		}
	}
}

void gfx_PrintTime(int x, int y){
	uint8_t sec = 0, min = 0, hur = 0;
	const char *time_ind[2] = {" AM", " PM"};
	
	boot_GetTime(&sec, &min, &hur);
	
	gfx_FillRectangle(x, y, 42, 8);
	
	if (hur == 24){ // date update
		temp = 1;
		if (temp != checkDate){
			gfx_PrintDate(6, 218);
			checkDate = 1;
		}
	}else{
		temp = 0;
		checkDate = 0;
	}
	
	if (hur == 0) hur = 12;
	
	if (hur > 12) hur -= 12;
	
	fontlib_SetCursorPosition(x, y);
	
	fontlib_DrawInt((unsigned int)hur, 2);
	fontlib_DrawString(" : ");
	fontlib_DrawInt((unsigned int)min, 2);
	fontlib_DrawString(time_ind[(uint8_t)boot_IsAfterNoon()]);
}

void gfx_PrintDate(int x, int y){
	uint8_t day = 0, month = 0;
	uint16_t year;
	
	boot_GetDate(&day, &month, &year);
	
	gfx_FillRectangle(x, y, 57, 8);
	
	fontlib_SetCursorPosition(x, y);
	
	fontlib_DrawInt((unsigned int)month, 2);
	fontlib_DrawString("/");
	fontlib_DrawInt((unsigned int)day, 2);
	fontlib_DrawString("/");
	fontlib_DrawInt((unsigned int)year, 4);
}

int Render_Add_Menu(void){
	// true == add board && false == add card :)
	int out = 1;
	Temp_Sprite = gfx_MallocSprite(59, 28);
	gfx_GetSprite(Temp_Sprite, 256, 26);
	
	while (key != sk_Enter && key != sk_2nd){
		gfx_SetColor(255);
		gfx_FillRectangle(256, 26, 59, 28);
		
		key = os_GetCSC();
		
		if (key == sk_Down){
			out = 0;
		}
		
		if (key == sk_Up){
			out = 1;
		}
		
		if (out){
			gfx_SetColor(body_color);
			gfx_FillRectangle(256, 26, 59, 14);
		}else{
			gfx_SetColor(body_color);
			gfx_FillRectangle(256, 40, 59, 14);
		}
		
		if (key == sk_Clear){
			delay(200);
			return 2;
			break;
		}
		
		fontlib_SetCursorPosition(259, 30);
		fontlib_DrawString("New Board");
		fontlib_SetCursorPosition(260, 43);
		fontlib_DrawString("New Card");
		gfx_SetColor(0);
		gfx_Rectangle(256, 26, 59, 28);
		gfx_Blit(1);
	}
	free(Temp_Sprite);
	return out;
}

void gfx_BatteryStatus(int x, int y){
	temp = boot_GetBatteryStatus();
	gfx_SetColor(0);
	gfx_FillRectangle(x + 2, y - 2, 4, 2);
	gfx_FillRectangle(x, y, 8, 18);
	
	gfx_SetColor(255);
	gfx_FillRectangle(x + 2, y, 5, 17);
	
	if (temp > 1){
		gfx_SetColor(7); //light gren
	}else{
		gfx_SetColor(224);
	}
	
	if (temp > 3) gfx_FillRectangle(x + 1, y, 6, 8);
	
	if (temp > 1) gfx_FillRectangle(x + 1, y + 6, 6, 6);
	
	if (temp >= 0) gfx_FillRectangle(x + 1, y + 12, 6, 5);
}

void gfx_loading(int x, int y, int time){
	for (i = 0; i < time; i++){
		gfx_FillRectangle(x, y, loading_width, loading_height);
		zx7_Decompress(GUI_buff, loading_compressed);
		gfx_RotatedTransparentSprite_NoClip(GUI_buff, x, y, i * 8);
		gfx_Blit(1);
	}
}

void Render_Scroll_Bar(int x, int y, int type){	
	gfx_SetColor(0);
	switch (type){
		case 0:
			gfx_FillRectangle(x, y + abs(scrollY), 2, y - (board_amount/2) - 8);
			return;			
		break;
		
		case 1:
			gfx_FillRectangle(x + abs(scrollX), y, x - (boards[BN].list_amount/2) - 8, 2);
			return;
		break;
	}
}

void Centered_Dialog_Box(const char *name, uint24_t iw, uint8_t ih){
	// need to revamp and remove from main.c
	int dx, dy;
	
	// Creates Difference X and Y. 
	dx = 160 - iw / 2;
	dy = 120 - ih / 2;
	
	Temp_Sprite = gfx_MallocSprite(iw, ih);
	gfx_GetSprite(Temp_Sprite, dx, dy);
	
	gfx_SetColor(main_color);
	gfx_FillRectangle(dx, dy, iw, 15);
	fontlib_SetCursorPosition(dx + 2, dy + 2);
	fontlib_SetForegroundColor(255);
	fontlib_DrawString(name);
	
	gfx_SetColor(body_color);
	gfx_FillRectangle(dx, dy + 15, iw, ih - 15);
	// gfx_Rectangle(dx, dy, width, height);
	
	
	return;
}