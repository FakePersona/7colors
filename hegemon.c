#include "greedy.h"
#include "tools.h"
#include "7colors.h"

/** Hegemon player **/

int disputed(int x, int y, char player)
{
  if (player == '^')
    {
      if (get_cell(x,y) == 'v')
	return 1;
      else if (get_cell(x,y) == player || get_cell(x,y) == 0)
	return 0;
    }
  else
    {
      if (get_cell(x,y) == '^')
	return 1;
      else if (get_cell(x,y) == player || get_cell(x,y) == 0)
	return 0;
    }
  set_cell(x,y,player);
  return disputed(x+1,y,player) + disputed(x-1,y,player) + disputed(x,y-1,player) + disputed(x,y+1,player);
}

int border(char player)
{
  int i,j,k,bord=0;
  char copie_board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros
  for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
    copie_board[i] = board[i];
  }
  for (i=0;i<BOARD_SIZE;i++)
    {
      for (j=0;j<BOARD_SIZE;j++)
	{
	  bord += (test_border(i,j,player) && disputed(i,j,player));
	  for (k=0;k<BOARD_SIZE * BOARD_SIZE;k++) {
	    board[k] = copie_board[k];
	  }
	}
    }
  return bord;
}


/* Figures out what the Hegemon move is */


void propagate_hegemon(int x, int y, char color, char player, int* occurences) 
{
  occurences[color - 'A']+=3;
  if (x == 0 || x == BOARD_SIZE -1) 
    occurences[color - 'A']-=1;
  if (y == 0 || y == BOARD_SIZE -1) 
    occurences[color - 'A']-=1;
  set_cell(x,y,player);
  /* Propagating */
  if (get_cell(x+1,y) == color)
    propagate_hegemon(x+1,y,color,player,occurences);
  if (get_cell(x-1,y) == color)
    propagate_hegemon(x-1,y,color,player,occurences);
  if (get_cell(x,y+1) == color)
    propagate_hegemon(x,y+1,color,player,occurences);
  if (get_cell(x,y-1) == color)
    propagate_hegemon(x,y-1,color,player,occurences);
  /* Looking for vacancies */
  if (get_cell(x,y-1) == '^' || get_cell(x,y-1) == 'v')
   occurences[color - 'A']-=1;
  if (get_cell(x,y+1) == '^' || get_cell(x,y-1) == 'v')
   occurences[color - 'A']-=1;
  if (get_cell(x+1,y) == '^' || get_cell(x,y-1) == 'v')
   occurences[color - 'A']-=1;
  if (get_cell(x+1,y) == '^' || get_cell(x,y-1) == 'v')
   occurences[color - 'A']-=1;
}


int hegemon_strategy(char player) {
  int position[7] = {0};
  int i,j,played;
  char col1;
  char copie_board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros
  for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
    copie_board[i] = board[i];
  }  
  int count1;
  if (player =='v') 
    count1 = c1;
  else
    count1 = c2;
  for (col1 = 'A'; col1 < 'H'; col1++) {
    played = 0;
    /* restore board to original state */
    if (player == 'v') 
      c1 = count1;
    else
      c2 = count1;
    for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
      board[i] = copie_board[i];
    }  
    /* virtually play one turn */
    for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	{
	  if (get_cell(i,j) == col1 && test_border(i, j, player))
	    {
	      propagate(i,j,col1,player);
	      played+=1;
	    }
	}
    }
    /* store border */
    if (played)
      position[col1 - 'A'] = border(player);
  }
  if (player == 'v') 
    c1 = count1;
  else
    c2 = count1;
  for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
    board[i] = copie_board[i];
  }  
  if (position[max_index(position)])
    return (max_index(position) + 'A');
  else
    return (greedy_strategy(player));
}

/* Glouton turn execution Might want to factorise later on */

void turn_hegemon(char player)
{
  int color_played = hegemon_strategy(player);
  printf("Hegemon played %c \n", color_played);
  play(color_played,player);
  print_board();
  print_occupation();
}
