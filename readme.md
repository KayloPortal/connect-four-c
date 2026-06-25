# Connect Four Game - TUI

## AI Smartness & Game Difficulty
Game's AI comes in three difficulty levels, Easy, Medium and Hard.

### Easy Mode

## Implementation Details

### Board
A 12x12 2D array is used to store the board information, The values R & C which the user defines, determine the boundry of this array which we will be working with. A value 0 in this array represents a vacant place, a value of 1 means a token of the player1 which has the id of 1 is placed there, and a value of 2 represents player 2's token. Player 1 & 2 can be either human, AI, or even an input file which deteremines the moves, what matters is the token.

### Token Customization
The token for both players can be determiened by user, and it can be any character. The game will not break because the game stores the board as an integer 2D array in which the values correspond to player's id which is a constant determined by the game that can not be changed or customized, hence regardless of the token that is chosen, the game can properly determine where the tokens of each player are placed. The game only looks at the user provided character token when the it wants to represent the board at the function BoardConfiguration. At other parts, the choice of the character for token does not change any functionality and have no effect.

### User Independent Engine
The engine simulates the lifecycle of the program and is provided with event handlers. The engine is not hard coded to look at the settings and beahve respectively, instead, it is told what to do on each event. If the game ends, it runs the function that handles this event, if the game continues, it runs the corresponding event handler which it was provided. We do not tell the engine what to do for each setting or gamemode, we give it functions and event handlers to run in different outcomes, and we give it different functions and event handlers based on what gamemode or settings we have. This helps to keep the logic of the engine simple and have a modular, function based, event handler based code while providing a customizable setting and gamemode.

The engine function lifecycle is as below:
- Recieve the parameters, such as the current configuration of the board(it can be any configuration, meaning you can start the game at different starting points, but it needs to be player one's turn, and the board should not be full)
- Run the move functions of the player whos turn is right now to recieve their selection.
- Try to put their token at the selected columns, if faliure, run the wrongColumnHandler to get the new selected column, and continue this until you are given a valid selected column.
- Now that the token is placed, check if the game has ended. If ended, run the end handler function, and break out of the loop, and if not, run the continue handler function
- Repeat this for the other player
- Repeat the process again until the game ends.