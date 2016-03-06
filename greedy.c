#include "7colors.h"
#include "tools.h" 
/** Glouton player **/

/* Figures out what the glouton move is */

/* int greedy_strategy(char player) 
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
*/

int greedy_strategy(char player) 
{
  int position[7] = {0};
  int i,max_i=0;
  char col1;
  int count1;
  if (player =='v') 
    count1 = c1;
  else
    count1 = c2;
  char copie_board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros
  for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
    copie_board[i] = board[i];
  } 
    /* Testing the first color */
  for (col1 = 'A'; col1 < 'H'; col1++) { 
    /* playing first turn */
    play(col1,player);
    if (player == 'v') 
      {
	position[col1- 'A'] = c1;
      }
    else
      {
	position[col1 - 'A'] = c2;
      }
    if (position[max_i] < position[col1-'A'])
      {
	    max_i = col1-'A';
      }
    /* restoring original board */
    if (player == 'v') 
      c1 = count1;
    else
      c2 = count1;
    for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
      board[i] = copie_board[i];
    } 
  }
return max_i+'A';
}


/* Glouton turn execution Might want to factorise later on */

void turn_greedy(char player)
{
  int color_played = greedy_strategy(player);
  //printf("Glouton played %c \n", color_played);
  play(color_played,player);
  //print_board();
  //print_occupation();
}
