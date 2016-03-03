#include "7colors.h"
#include "tools.h" 
/** Glouton player **/

/* Figures out what the glouton move is */

int glouton_strategy(char player) 
{
  int occurences[7] = {0};
  int i, j;
  for (i=0; i<BOARD_SIZE; i++) {
    for (j=0; j<BOARD_SIZE; j++) 
      {
	if (test_border(i,j,player))
	  {
	    (occurences[get_cell(i,j)-'A'])++;
	  }
      }
  }
  return (max_index(occurences) + 'A');
}

/* Glouton turn execution Might want to factorise later on */

void turn_glouton(char player)
{
  int color_played = glouton_strategy(player);
  printf("Glouton played %c \n", color_played);
  play(color_played,player);
  print_board();
  print_occupation();
}
