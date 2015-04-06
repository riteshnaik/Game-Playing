Game-Playing
============

Implementation of Greedy, Minimax and Alpha-Beta pruning algorithms with positional weight evaluation function to determine the next move for a player in the Reversi game.

The rules of the Reversi game can be found at http://en.wikipedia.org/wiki/Reversi and interactive examples can be found at http://www.samsoft.org.uk/reversi/.

**Input file format:**  
<task#> Greedy = 1, MiniMax = 2, Alpha-beta = 3  
\<your player: X or O\>  
\<cutting off depth \>  
\<current state as follows:\>  
*: blank cell  
X: Black player 
O: White Player  

**Greedy Output**  
\<next state\>  
*Example:*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*X\*\*\*\*  
\*\*\*XX\*\*\*  
\*\*\*XO\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  

**Min-Max Output ** 
\<next state\> 
\<traverse log\>
*Example:*
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*X\*\*\*\*  
\*\*\*XX\*\*\*  
\*\*\*XO\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*
