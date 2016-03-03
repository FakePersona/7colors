
char get_cell(int x,int y);
void set_cell(int x, int y, char color);
void print_board(void);
void init_board(void);
int test_border(int x, int y, char player);
void propagate(int x, int y, char color, char player);
void play(char color, char player);
int finish(void);
void print_occupation(void);
int max_index(int* t);
