#include <tice.h>
#include <graphx.h>

// Functions
void Board_UIsetup(const int num);

void Board_UIBody(const int color);

void render_cards(void);

void render_list(void);

void render_scrollY_Card(void);


// extern int 

extern int BN;

// extern struct
struct data_board_t{
	bool active;
	char *name;
	int color;
	int list_amount;
};
extern struct data_board_t boards[28];

struct data_check_list_t{
	bool active;
	char list_name;
	bool checked;
	char check_name;
};

struct data_card_t{
	bool active;
	// int list_num;
	char *name;
	bool active_due_date;
	int date[3];
	int label_num[5];
}; 

struct data_list_t{
	bool active;
	char *name;
	int card_amount;
	struct data_card_t cards[10];
	int scrollY;
};
extern struct data_list_t list[30];

struct data_labels_t{
	// bool active;
	char *name;
	int color;
	// int num;
};
extern struct data_labels_t labels[5];


