#include "7colors.h"
#include "tools.h" 
#include "random.h"
#include "greedy.h"
#include "hegemon.h"
#include "foreseeing.h"

/** Represent the actual current board game 
 * 
 * NOTE: global variables are usually discouraged (plus encapsulation in
 *  an appropriate data structure would also be preferred), but don't worry. 
 *  For this first assignment, no dinosaure will get you if you do that. 
 */
char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros
int c1=1,c2=1;


/** Program entry point */
int main() 
{
  int i,player,score=0;
  srand(time(NULL));
  printf("\n\n  Welcome to the 7 wonders of the world of the 7 colors\n"
	      "  *****************************************************\n\n"
	 "Current board state:\n\n");
   srand(time(NULL));
   init_board();
   print_board();
      for (i=0;i<100;i++)
     {
       init_board();
       c1=1;
       c2=1;
       player = rand () % 2;
       while (42)
	 {
	   if (player == 0)
	     {
	       turn_greedy('v');
	       player = 1;
	     }
	   else
	     {
	       turn_random('^');
	       player = 0;
	     }
	   if(finish())
	     break;
	 }
       if (finish()==1)
	 {
	   score +=1;
	   printf("Joueur 'v' a gagné\n");
	 }
       else
	 printf("Joueur '^' a gagné\n");
     }
   printf("Joueur 'v' a gagne %d fois",score);
   return 0; // Everything went well
}
