// Anything File related is located here
// file.c V.0.1

#include "gui.h"
#include "files.h"
#include "main.h"
#include "board.h"
#include <graphx.h>

void save_data(void)
{
	ti_CloseAll();
	
	file = ti_OpenVar("TERDATA", "w", TI_APPVAR_TYPE);
	ti_Write(&boards, sizeof(boards), 1, file); // all board names and data are stored here
	
	ti_Close(file);
	return;
}

void load_data(void)
{
	ti_CloseAll();
	
	file = ti_OpenVar("TERDATA", "r", TI_APPVAR_TYPE);
	
	if (file) {
		ti_Read(&boards, sizeof(boards), 1, file); // all board names and data are stored here
	}else return;
	
	ti_Close(file);
	return;
}

void save_board(void)
{
	ti_CloseAll();

	if (BN > -1){
		if (boards[BN].active == true){
			file = ti_OpenVar(boards[BN].name, "w", TI_APPVAR_TYPE);
		}else{ 
			// if there is an error
			return;
		}
	}
	
	ti_Write(&list, sizeof(list), 1, file); // lists are stored here
	// ti_SetArchiveStatus(true, file);
	
	ti_Close(file);
	
	gfx_PopupMessage("Message:","Board data saved.", 1, gfx_green); // Debugging
	return;
}

void load_board(void)
{
	ti_CloseAll();
	
	file = ti_OpenVar(boards[BN].name, "r", TI_APPVAR_TYPE);
	
	if (file) {
		ti_Read(&list, sizeof(list), 1, file);
	} else return;
	// ti_SetArchiveStatus(true, file);
	
	ti_Close(file);
	return;
}