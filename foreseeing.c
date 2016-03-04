#include "7colors.h"
#include "greedy.h"
#include "tools.h"

/** Foreseeing player **/

/* Figures out what the Foreseeing move is */

int foreseeing_strategy(char player) 
{
  int position[7] = {0};
  int i,max_i=0;
  char col1;
  int count1,count2,max_count=0;
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
	count2=c1;
	play(greedy_strategy(player),player);
	position[col1- 'A'] = c1;
      }
    else
      {
        count2=c2;
	play(greedy_strategy(player),player);
	position[col1 - 'A'] = c2;
      }
    if (position[max_i] == position[col1-'A'])
      {
	if (count2 > max_count)
	  {
	    max_i = col1-'A';
	    max_count = count2;
	  }
      }
    if (position[max_i] < position[col1-'A'])
      {
	    max_i = col1-'A';
	    max_count = count2;
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

void turn_foreseeing(char player)
{
  int color_played = foreseeing_strategy(player);
  //printf("Foreseeing played %c \n", color_played);
  play(color_played,player);
  //print_board();
  //  print_occupation();
}

/* Oracle playah !*/

int oracle_strategy(char player,int n) 
{
  int position[7] = {0};
  int i,max_i=0;
  char col1;
  int count1,count2,max_count=0;
  count1 = get_count(player);
  char copie_board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros
  for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
    copie_board[i] = board[i];
  } 
  if (n==2)
    return foreseeing_strategy(player);
    /* Testing the first color */
  for (col1 = 'A'; col1 < 'H'; col1++) { 
    /* playing first turn */
    play(col1,player);
    count2=get_count(player);
    for (i=1;i<n-1;i++)    
      play(oracle_strategy(player,n-i),player);
    play(greedy_strategy(player),player);
    position[col1- 'A'] = get_count(player);
    if (position[max_i] == position[col1-'A'])
      {
	if (count2 > max_count)
	  {
	    max_i = col1-'A';
	    max_count = count2;
	  }
      }
    if (position[max_i] < position[col1-'A'])
      {
	    max_i = col1-'A';
	    max_count = count2;
      }
    /* restoring original board */
    set_count(player,count1);
    for (i=0;i<BOARD_SIZE * BOARD_SIZE;i++) {
      board[i] = copie_board[i];
    } 
  }
return max_i+'A';
}

void turn_oracle(char player, int n)
{
  int color_played = oracle_strategy(player,n);
  //printf("Oracle played %c \n", color_played);
  play(color_played,player);
  //print_board();
  //print_occupation();
}
