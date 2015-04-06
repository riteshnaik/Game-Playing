Game-Playing
============

Implementation of **Greedy, Minimax and Alpha-Beta pruning algorithms** with **positional weight evaluation function** to determine the next move for a player in the **Reversi game**.

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

**MiniMax Output**  
\<next state\>  
\<traverse log\>  

**MiniMax Traverse Log Description:**  
The Minimax traverse log has 3 columns. Each column is separated by “,”. Three columns are **node, depth and value.**  
**Node:** is the node name which refers to the move that is made by the agent.There are two **special node names:** **root** and **pass**. **root** is the name for the root node. **pass** is the name for the special move **pass**. Agent can make the pass move only when it cannot make any valid move.  
**Depth:** is the depth of the node. The root node has depth zero.  
**Value:** is the value of the node. The value is initialized to **-Infinity** for the max node and **Infinity** for the min node. The value will be updated when its children return the value to the node. The value of leaf nodes is the
evaluated value.  

**Alpha-Beta Output**  
\<next state\>  
\<traverse log\>  

**Alpha-Beta Traverse Log Description:**  
The Alpha-Beta traverse log has 5 columns. Each column is separated by “,”. Five columns are **node, depth, value,alpha, and beta.** The description is same with the Minimax log.  
