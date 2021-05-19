//////////////////////////////
// Scratch by Alvajoy123    //
//                          //
// original project from    //
// Scratch ID : Colorgram   //
//////////////////////////////
// Keep these headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

// Standard headers
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Graphic lib's
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <compression.h>
#include <fontlibc.h>

// My headers
#include "main.h"
#include "mouse.h"
#include "gui.h"
#include "decompress.h"
#include "gfx/sprites.h"
#include "files.h"
#include "board.h"

// Variables
int i;
int temp;
char *Temp_Char;
// struct vars_t proj;
uint8_t ikey;

void main(void){
	// Font Setup
	fontlib_SetWindowFullScreen();
    fontlib_SetTransparency(true);
	fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
	
	// Graphic Setup
	gfx_Begin();
	gfx_SetDraw(1);
	gfx_SetTextFGColor(0);
	
	// Data Setup
	splash_screen();
	load_data();
	
	if (!error){
		gfx_SetTextFGColor(0);
		UI_setup();
		gfx_PopupMessage("Quick Update:  ","Pre Alpha v1.0 : Scrolling Released!", 0, gfx_yellow);
		mouse_loop();
		save_data();
	}else{
		// if there is an error run this!!
		while (os_GetCSC());
		gfx_Blit(1);
	}
	
	// Ends
	gfx_End();
	os_ClrHomeFull();
} 


// routines below!!
void vars_init(void){
	int l;
	scrollX = 0;
	scrollY = 0;
	
	// debuging test for lists
	for (i = 0; i < 5; i++){
		boards[i].active = true;
		boards[i].name = "test";
		boards[i].color = randInt(0, 254);
		boards[i].list_amount = 30;
		board_amount++;
		for (l = 0; l < boards[i].list_amount; l++){
			list[i].active = true;
			list[i].name = "test list";
			list[i].cards[l].active = true;
			list[i].cards[l].name = "Hello World";
			list[i].card_amount = 5;
		}
	}
	
	// I think return allows a faster return
	return;
}
	
void Debug(void){
	// for developer only :)
	gfx_SetColor(255);
	gfx_FillRectangle(279,0, 320 - 279, 32);
	
	gfx_SetTextXY(280, 0);
	gfx_PrintInt(scrollY, 2); // Change base on variable I want to debug
	gfx_Blit(1);
	return;
}


void gfx_PopupMessage(const char *header, const char *message, int type, int color){
	// Revamp later
	int x, y, h, w;
	w = fontlib_GetStringWidth(message) + fontlib_GetStringWidth(header);
	if (w > 250) w = 250;
	h = w / 3;
	if (h < 41) h = 50;
	x = 160 - w / 2;
	y = 120 - h / 2;
	
	Temp_Sprite = gfx_MallocSprite(w, h);
	gfx_GetSprite(Temp_Sprite, x, y);
	
	gfx_SetColor(0);
	gfx_FillRectangle(x, y, w, h);
	gfx_SetColor(color);
	gfx_Rectangle(x, y, w, h);
	gfx_Rectangle(x + 1, y + 1, w - 2, h - 2);
	
	fontlib_SetWindow(x + 3, y + 3, w - 6, h - 6);
	fontlib_HomeUp();
	fontlib_SetForegroundColor(255);
	fontlib_DrawString(header);
	fontlib_Newline();
	fontlib_DrawString(message);
	fontlib_Newline();
	
	gfx_Blit(1);
	
	switch (type){
		case 0:
			fontlib_DrawString("Press any key.");
			gfx_Blit(1);
			while(!os_GetCSC());
		break;
		
		case 1:
			wait(10);
		break;
	}
	
	wait(10);
	
	gfx_Sprite(Temp_Sprite, x, y);
	free(Temp_Sprite);
	fontlib_SetWindowFullScreen();
	return;
}

char* Get_LetterInput(const char *text, uint24_t x, uint8_t y, uint8_t max_size){
	const char *U_CHAR = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	const char *L_CHAR = "\0\0\0\0\0\0\0\0\0\0\"wrmh\0\0?[vqlg\0\0:zupkfc\0 ytojeb\0\0xsnida\0\0\0\0\0\0\0\0";
	bool caps = true;
	char buffer[50];
	
	while(ikey != sk_Enter || ikey != sk_2nd) {
		
		gfx_SetColor(gfx_RGBTo1555(244, 245, 247));
		gfx_FillRectangle(x + 2, y + 2, fontlib_GetStringWidth(buffer), 10);
		 
		ikey = os_GetCSC();
		
		if(i != max_size) {
			if (caps == true && U_CHAR[ikey]) buffer[i++] = U_CHAR[ikey];
			if (caps == false && L_CHAR[ikey]) buffer[i++] = L_CHAR[ikey];
		}
		
		if (ikey == sk_Del){
			if (buffer[i] != '\0' && i - 1 >= 0) i -= 1;
			buffer[i] = '\0';
		}
		
		if (ikey == sk_Alpha){
			if (caps == true){
				caps = false;
			}else{
				caps = true;
			}
		}
		
		if (ikey == sk_Clear){
			delay(50);
			return NULL;
		}
		
		fontlib_SetCursorPosition(x + 2, y + 2);
		fontlib_DrawString(buffer);
		
		gfx_Blit(1);
	}
	
	gfx_Sprite(Temp_Sprite, 160 - 100 / 2, 120 - 30 / 2);
	free(Temp_Sprite);
	delay(1000);
	return buffer;
	
}


