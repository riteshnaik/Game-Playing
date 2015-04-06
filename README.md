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
\*\*\***X**\*\*\*\*  
\*\*\***XX**\*\*\*  
\*\*\***XO**\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  

**Min-Max Output**  
\<next state\>  
\<traverse log\>  
**The Minimax traverse log has 3 columns. Each column is separated by “,”. Three columns are node, depth and value.**    
*Example:*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\***X**\*\*\*\*  
\*\*\***XX**\*\*\*  
\*\*\***XO**\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
Node,Depth,Value  
root,0,-Infinity  
d3,1,Infinity  
c3,2,-3  
d3,1,-3  
e3,2,0  
d3,1,-3  
c5,2,0  
d3,1,-3  
root,0,-3  
c4,1,Infinity  
c3,2,-3  
c4,1,-3  
e3,2,0  
c4,1,-3  
c5,2,0  
c4,1,-3  
root,0,-3  
f5,1,Infinity  
f4,2,0  
f5,1,0  
d6,2,0  
f5,1,0  
f6,2,-3  
f5,1,-3  
root,0,-3  
e6,1,Infinity  
f4,2,0  
e6,1,0  
d6,2,0  
e6,1,0  
f6,2,-3  
e6,1,-3  
root,0,-3  

**Alpha-Beta Output**  
\<next state\>  
\<traverse log\>  
*Example:*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\***X**\*\*\*\*  
\*\*\***XX**\*\*\*  
\*\*\***XO**\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*  
\*\*\*\*\*\*\*\*
Node,Depth,Value,Alpha,Beta  
root,0,-Infinity,-Infinity,Infinity  
d3,1,Infinity,-Infinity,Infinity  
c3,2,-3,-Infinity,Infinity  
d3,1,-3,-Infinity,-3  
e3,2,0,-Infinity,-3  
d3,1,-3,-Infinity,-3  
c5,2,0.0,-Infinity,-3  
d3,1,-3,-Infinity,-3  
root,0,-3,-3,Infinity  
c4,1,Infinity,-3,Infinity  
c3,2,-3,-3,Infinity  
c4,1,-3,-3,-3  
root,0,-3,-3,Infinity  
f5,1,Infinity,-3,Infinity  
f4,2,0,-3,Infinity  
f5,1,0,-3,0  
d6,2,0,-3,0  
f5,1,0,-3,0  
f6,2,-3,-3,0  
f5,1,-3,-3,-3  
root,0,-3,-3,Infinity  
e6,1,Infinity,-3,Infinity  
f4,2,0,-3,Infinity  
e6,1,0,-3,0  
d6,2,0,-3,0  
e6,1,0,-3,0  
f6,2,-3,-3,0  
e6,1,-3,-3,-3  
root,0,-3,-3,Infinity  

