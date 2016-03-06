#include "tools.h" 
#include "7colors.h"

/** Random player **/

/* Figures out what the Random move is */

int random_strategy(char player) 
{
  int occurences[7] = {0};
  int possible[7] = {0};
  int possibilities = 0;
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
  for (i=0; i< 7; i++){
    if (occurences[i]) {
      possible[possibilities]=i+'A';
      possibilities++;
    }
  }
  int r = rand() % possibilities;
  return (possible[r]);
}

/* Random turn execution Might want to factorise later on */

void turn_random(char player)
{
  int color_played = random_strategy(player);
  //printf("Random played %c \n", color_played);
  play(color_played,player);
  //print_board();
  //print_occupation();
}
