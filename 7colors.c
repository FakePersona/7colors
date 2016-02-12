/* Template of the 7 wonders of the world of the 7 colors assigment. */

/* Cf. http://people.irisa.fr/Anne-Cecile.Orgerie/teaching2015.html  */

#include <stdio.h>  /* printf */
#include <time.h>
#include <stdlib.h>

/* We want a 30x30 board game by default */
#define BOARD_SIZE 30 

/** Represent the actual current board game 
 * 
 * NOTE: global variables are usually discouraged (plus encapsulation in
 *  an appropriate data structure would also be preferred), but don't worry. 
 *  For this first assignment, no dinosaure will get you if you do that. 
 */
char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros

/** Retrieves the color of a given board cell. If out of bound return 0 */
char get_cell(int x, int y) 
{
  if(x>=0 && x<BOARD_SIZE && y>=0 && y<BOARD_SIZE)
   return board[y*BOARD_SIZE + x];
  else
    return 0;
}

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color) 
{
   board[y*BOARD_SIZE + x] = color;
}
   
/** Prints the current state of the board on screen
 * 
 * Implementation note: It would be nicer to do this with ncurse or even 
 * SDL/allegro, but this is not really the purpose of this assignment.
 */
void print_board() 
{
   int i, j;
   for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	 printf("%c", get_cell(i, j));
      printf("\n");
   }
}
/* init_board with 7 colors and players colors*/
void init_board()
{
  int i,j;
  for(i=0;i<BOARD_SIZE;i++)
    {
      for(j=0;j<BOARD_SIZE;j++)
	{
	  set_cell(i,j,'A' + (rand() % 7));
	}
    }
  set_cell(BOARD_SIZE-1,0,'^');
  set_cell(0,BOARD_SIZE-1,'v');
}

int test_border(int x, int y, char player)
{
  return (get_cell(x-1,y)==player || get_cell(x+1,y)==player || get_cell(x,y-1)==player || get_cell(x,y+1)==player);  
}
void play(char color, char player)  
{
  int i,j,t=1;
  while (t)
    {
      t=0;
      
      for(i=0;i<BOARD_SIZE;i++)
	{
	  for(j=0;j<BOARD_SIZE;j++)
	    {
	      if(get_cell(i,j)==color && test_border(i,j,player))
		{
		  set_cell(i,j,player);
		  t=1;
		}
	    }
	}
    }
}
      


/** Program entry point */
int main() 
{
   printf("\n\n  Welcome to the 7 wonders of the world of the 7 colors\n"
	      "  *****************************************************\n\n"
	 "Current board state:\n\n");
   srand(time(NULL));
   init_board();
   print_board();
   char color_play;
   while (1)
     {
       printf("Joueur 1 ");
       scanf("%c",&color_play);
       play(color_play,'v');
       printf("\n");
       print_board();
       
     }
   return 0; // Everything went well
}
