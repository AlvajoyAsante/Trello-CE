// everything mouse related is in here!!
#include "mouse.h"
#include "gui.h"
#include "main.h"
#include "board.h"
#include "files.h"

// Needed for sprites
#include <compression.h>
#include "decompress.h"
#include "gfx/sprites.h"

kb_key_t key;
gfx_sprite_t *mouse_buff, *cursor_buff;
struct mouses_t mouse;
int ext = 0, scrollX, scrollY, timerX;
int board_amount, display_type = 0;

void mouse_loop(void){
	mouse.x = LCD_WIDTH / 2;
	mouse.y = LCD_HEIGHT / 2;
	mouse.spd = 4;
	scrollX = 0;
	scrollY = 0;
	
	// Copies Sprite BG to behind sprite
	gfx_SetTransparentColor(0xF0);
	mouse_buff = gfx_MallocSprite(17, 22);
	gfx_GetSprite(mouse_buff, mouse.x, mouse.y);
	
	while (ext != 1){
		kb_Scan();
		key = kb_Data[7];

		gfx_Sprite(mouse_buff, mouse.x, mouse.y);
		
		other_keys();
		
		if (display_type <= 6){
			gfx_SetColor(gfx_RGBTo1555(244, 245, 247));
			fontlib_SetForegroundColor(0);
			gfx_PrintTime(6, 228);
			if (timerX == 30000) gfx_BatteryStatus(69, 218); 
			timerX += 1;	
		}
		
		mouse_keys();
		
		gfx_GetSprite(mouse_buff, mouse.x, mouse.y);
		Render_Mouse();

		gfx_Blit(1);
			
	} 
	// free allocated data
	free(mouse_buff);
	return;
}

void mouse_Enter(void){
	// When user clicks enter
	
	if (display_type <= 6){
		// Header
		if (mouse.x > 256 && mouse.x < 269 && mouse.y > 5 && mouse.y < 18){
			temp = Render_Add_Menu();
			switch (temp){
				case 1:
					Centered_Dialog_Box("Add Board", 120, 100);
				break;
				
				case 0:
					Centered_Dialog_Box("Add Card", 120, 100);
				break;
				
				case 2:
					return;
				break;
			}
			
			
		}
	
		// Menu
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 25 && mouse.y < 40){
		GUI_Menu(0);
		UI_setup();
	}
	
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 41 && mouse.y < 56) GUI_Menu(1);
		
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 72 && mouse.y < 87) GUI_Menu(2);
	
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 87 && mouse.y < 102) GUI_Menu(3);
		
		// Help section (need to revamp)
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 101 && mouse.y < 116){
		GUI_Menu(4);
		Render_Menu_Help();
	}
	
		// if user clicks on board.
		if (mouse_BoardDetect() != 404 && display_type == 0){
			temp = mouse_BoardDetect();
			scrollX = 0;
			scrollY = 0;
			Board_UIsetup(temp);
		}
	}
}

int mouse_HoverDetect(void){
	if (display_type <= 6){ // only when menu is beening displayed
		// Header
		if (mouse.x > 256 && mouse.x < 269 && mouse.y > 5 && mouse.y < 18) return 1;
	
		if (mouse.x > 278 && mouse.x < 291 && mouse.y > 5 && mouse.y < 18) return 1;
	
		if (mouse.x > 300 && mouse.x < 313 && mouse.y > 5 && mouse.y < 18) return 1;
	
		// menu
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 25 && mouse.y < 40) return 1;
	
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 41 && mouse.y < 56) return 1;
		
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 72 && mouse.y < 87) return 1;
	
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 87 && mouse.y < 102) return 1;
	
		if (mouse.x > 0 && mouse.x < 84 && mouse.y > 101 && mouse.y < 116) return 1;
		
		if (!display_type){
			if (mouse_BoardDetect() != 404) return 1;
		}
	}
	
	if (display_type == 7){ // for board info
		if (mouse_CardDetect() != 404) return 1;
		
		if (mouse_ListDetect() != 404) return 1;
	}
	
	// returns 0 if there is no hover
	return 0;
}

int mouse_BoardDetect(void){
	// Need to be revamped
	int x = 87, y = 42;
	for (i = 0; i < 28; i++){
		if (boards[i].active == true){ // Check if the board is active else move on
			if (mouse.x > 84 && mouse.x < 84 + 236 && mouse.y > 38 && mouse.y < 38 + 202){
				if (mouse.x >= x && mouse.x <= x + 113 && mouse.y >= y + scrollY && mouse.y <= y + scrollY + 77) return i;
			}
			
			if (x != 202){
				x = 202;
			}else{
				x = 87;
				y += 91;
			}
		}
	}
	// returns error error code
	return 404;
}

int mouse_CardDetect(void){
	int l, i;
	int x = 7, y = 48; // Starting X and Y for lists
	for (i = 0; i < boards[BN].list_amount; i++){ 
		for (l = 0; l < list[i].card_amount; l++){
			if ( Mouse_Detect_Rect(x + 2 + scrollX, y, 77, 25) ) return l; // Returns l amount (l amout is the list or card position)
			y += 28;
		}
		x += 98;
		y = 48;
	}
	// Return 404 if there was an error.
	return 404;
}

int mouse_ListDetect(void){
	int x = 7, y;
	if (boards[BN].list_amount != 0){
		for (i = 0; i < boards[BN].list_amount; i++){
			if (list[i].active){
				if (Mouse_Detect_Rect(x + scrollX, 30, 81, (list[i].card_amount * 28) + 29)) return i; // Detects The list itself
			}
			if (Mouse_Detect_Rect(x + scrollX, 30, 81, (list[i].card_amount * 28) + 29 - 11)) return list[i].card_amount + 1; // Detects Add card
			x += 98;
		}
	}
	if (Mouse_Detect_Rect(x + scrollX, 30, 81, 12)) return boards[BN].list_amount + 1; // Detects Add list
	
	// Return 404 if there was an error
	return 404;
}

int mouse_ButtonDetect(void){
	// This allow the mouse to detect buttons based on its index number and xy. and width and height
	for (i = 0; i < 100; i++){
		if (buttons[i].active){ // makes sure the button index is in use
			if (Mouse_Detect_Rect(buttons[i].x, buttons[i].y, buttons[i].w, buttons[i].y)) return i; // Returns Data Pos
		}
	}
	
	// Returns 404 if there is an error
	return 404;
}

void Render_Mouse(void){
	if (!mouse_HoverDetect()){ // Checks hover data
			// Still dont know why am not using a unintended sprite.
			cursor_buff = gfx_MallocSprite(cursorA_width, cursorA_height);
			zx7_Decompress(cursor_buff, cursorA_compressed);
			gfx_TransparentSprite(cursor_buff, mouse.x, mouse.y);
			free(cursor_buff);
		}else{
			cursor_buff = gfx_MallocSprite(cursorB_width, cursorB_height);
			zx7_Decompress(cursor_buff, cursorB_compressed);
			gfx_TransparentSprite(cursor_buff, mouse.x, mouse.y);
			free(cursor_buff);
	}
}

void mouse_keys(void){
	// Mouse movement key belong here :)
	if (kb_IsDown(kb_KeyAlpha) && kb_IsDown(kb_KeyUp)){
		if (display_type == 0){
			if (scrollY > (-(board_amount/2)*79)){
				scrollY -= 10;
				Render_Body();
			}
		}
		return;
	}
	
	if (kb_IsDown(kb_KeyAlpha) && kb_IsDown(kb_KeyLeft)){
		if (display_type == 7){
			if (scrollX > (-81 * boards[BN].list_amount)){
				scrollX -= 10;
				Board_UIBody(boards[BN].color);
			}
		}
		return;
	}
		
	if (kb_IsDown(kb_KeyAlpha) && kb_IsDown(kb_KeyDown)){
		if (display_type == 0){
			if (scrollY != 0){
				scrollY += 10;
				Render_Body();
			}
		}
		return;
	}
	
	if (kb_IsDown(kb_KeyAlpha) && kb_IsDown(kb_KeyRight)){
		if (display_type == 7){
			if (scrollX != 0) scrollX += 10;
			Board_UIBody(boards[BN].color);
		}
		return;
	}
	
	switch (key){
		case kb_Down:
			if (mouse.y + mouse.spd < LCD_HEIGHT) mouse.y += mouse.spd;
		break;
	
		case kb_Up:
			if (mouse.y - mouse.spd > 0) mouse.y -= mouse.spd;
		break;
			
		case kb_Left:
			if (mouse.x - mouse.spd > 0) mouse.x -= mouse.spd;
		break;

		case kb_Right:
			if (mouse.x + mouse.spd < LCD_WIDTH) mouse.x += mouse.spd;
		break;
	}
		
	if (kb_IsDown(kb_KeyUp) && kb_IsDown(kb_KeyRight)){
		if (mouse.y - mouse.spd > 0) mouse.y -= mouse.spd;
		if (mouse.x + mouse.spd < LCD_WIDTH) mouse.x += mouse.spd;
	}
		
	if (kb_IsDown(kb_KeyUp) && kb_IsDown(kb_KeyLeft)){
		if (mouse.y - mouse.spd > 0) mouse.y -= mouse.spd;
		if (mouse.x - mouse.spd > 0) mouse.x -= mouse.spd;
	}
		
	if (kb_IsDown(kb_KeyDown) && kb_IsDown(kb_KeyRight)){
		if (mouse.y + mouse.spd < LCD_HEIGHT) mouse.y += mouse.spd;
		if (mouse.x + mouse.spd < LCD_WIDTH) mouse.x += mouse.spd;
	}
		
	if (kb_IsDown(kb_KeyDown) && kb_IsDown(kb_KeyLeft)){
		if (mouse.y + mouse.spd < LCD_HEIGHT) mouse.y += mouse.spd;
		if (mouse.x - mouse.spd > 0) mouse.x -= mouse.spd;
	}
}

void other_keys(void){
// any other key presses will be scripted here
	// exit key
	if (kb_Data[6] == kb_Clear){
			// main
			if (display_type <= 6) ext = 1;
			
			// board
			if (display_type > 6){
				save_board();
				scrollX = 0;
				scrollY = 0;
				UI_setup();
			}
		}
	
	// Enter keys
	if (kb_Data[6] == kb_Enter || kb_Data[1] == kb_2nd){
			wait(5);
			mouse_Enter();
		}
	
	//Speed up mouse
	if (kb_IsDown(kb_KeyMode) && kb_IsDown(kb_KeyUp)){
			if (mouse.spd != 10) mouse.spd += 1;
			gfx_PopupMessage("Message: ","Speed increased. +1 ", 1, gfx_yellow);
		}
	
	// Slow down mouse
	if (kb_IsDown(kb_KeyMode) && kb_IsDown(kb_KeyDown)){
			if (mouse.spd != 1) mouse.spd -= 1;
			gfx_PopupMessage("Message: ","Speed decreased. -1", 1, gfx_yellow);
		}
	
	// Mouse Menu
	if (kb_Data[1] == kb_Alpha){
		
	}
	return;
}

void Render_Mouse_Menu(void){
	// paused for later
}

bool Mouse_Detect_Rect(int ix, int iy, int iw, int ih){
	// check if the mouse is x and y pos is in given x,y,x+w,y+h 
	if ( mouse.x > ix && mouse.x < ix + iw && mouse.y > iy && mouse.y < iy + ih ) return true;
	return false;
}

