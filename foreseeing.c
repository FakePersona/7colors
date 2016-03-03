#include "7colors.h"
#include "greedy.h"
#include "tools.h"

/** Foreseeing player **/

/* Figures out what the Foreseeing move is */

int foreseeing_strategy(char player) 
{
  int position[7] = {0};
  int i,j,done;
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
    done = 0;
    /* restoring original board */
    if (player == 'v') 
      c1 = count1;
    else
      c2 = count1;
    for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
      board[i] = copie_board[i];
    }  
    /* playing first turn */
    for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	{
	  if (get_cell(i,j) == col1 && test_border(i, j, player))
	    {
	      propagate(i,j,col1,player);
	    }
	}
    }    
    for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	{
	  if (test_border(i, j, player))
	    {
	      done +=1;
	    }
	}
    }
    if (done)
      play(greedy_strategy(player),player);
    if (player == 'v') 
      position[col1- 'A'] = c1;
    else
      position[col1 - 'A'] = c2;
  }
if (player == 'v') 
  c1 = count1;
 else
   c2 = count1;
for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
  board[i] = copie_board[i];
 }  
return (max_index(position) + 'A');
}


/* Glouton turn execution Might want to factorise later on */

void turn_foreseeing(char player)
{
  int color_played = foreseeing_strategy(player);
  //  printf("Foreseeing played %c \n", color_played);
  play(color_played,player);
  //print_board();
  //print_occupation();
}

/* Oracle playah !*/

int oracle_strategy(char player, int n) 
{
  int position[7] = {0};
  int i,j,done;
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
  if (n==2)
    return foreseeing_strategy(player);
    /* Testing the first color */
  for (col1 = 'A'; col1 < 'H'; col1++) {
    done = 0;
    /* restoring original board */
    if (player == 'v') 
      c1 = count1;
    else
      c2 = count1;
    for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
      board[i] = copie_board[i];
    }  
    /* playing first turn */
    for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	{
	  if (get_cell(i,j) == col1 && test_border(i, j, player))
	    {
	      propagate(i,j,col1,player);
	    }
	}
    }
    for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	{
	  if (test_border(i, j, player))
	    {
	      done +=1;
	    }
	}
    }
    if (done)
      play(oracle_strategy(player,n-1),player);
    if (player == 'v') 
      position[col1- 'A'] = c1;
    else
      position[col1 - 'A'] = c2;
  }
if (player == 'v') 
  c1 = count1;
 else
   c2 = count1;
for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
  board[i] = copie_board[i];
 }  
return (max_index(position) + 'A');
}

void turn_oracle(char player, int n)
{
  int color_played = oracle_strategy(player,n);
  //printf("Oracle played %c \n", color_played);
  play(color_played,player);
  //print_board();
  //print_occupation();
}
