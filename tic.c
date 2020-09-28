#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int getRandomNumber() {
    return rand() % 3;
}

void showGameTable(char gameTable[3][3]) {
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            if (j == 2) printf("%c\n", gameTable[i][j]);
            else printf("%c ", gameTable[i][j]);
        }
    }
}

int main(void) {
    int playerMoveLine, playerMoveColumn, computerWon = 0, moves = 0, computerMoveLine, computerMoveColumn;

    char gameTable[3][3];
    int markedSegments[3][3];

    //initialize arrays
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            gameTable[i][j] = '-';
            markedSegments[i][j] = 0;
        }
    }

    while (computerWon == 0 && moves < 9) {
        if (moves <= 2) { //first two moves must be in random corners of the gameTable
            do {
                srand(time(0));
                computerMoveLine = getRandomNumber();
                computerMoveColumn = getRandomNumber();
            } while ((computerMoveLine == 1 || computerMoveColumn == 1) || markedSegments[computerMoveLine][computerMoveColumn] == 1);

            //assign random move
            gameTable[computerMoveLine][computerMoveColumn] = 'x';
            markedSegments[computerMoveLine][computerMoveColumn] = 1;
        } else { //next moves will block the player or win the game for the computer
            //check for winning in rows
            for (int k = 0; k <= 2; k++) {
                if (gameTable[k][0] == 'x' && gameTable[k][1] == 'x' && markedSegments[k][2] == 0) {
                    gameTable[k][2] = 'x';
                    computerWon = 1;
                    break;
                } else if (gameTable[k][0] == 'x' && gameTable[k][2] == 'x' && markedSegments[k][1] == 0) {
                    gameTable[k][1] = 'x';
                    computerWon = 1;
                    break;
                } else if (gameTable[k][1] == 'x' && gameTable[k][2] == 'x' && markedSegments[k][0] == 0) {
                    gameTable[k][0] = 'x';
                    computerWon = 1;
                    break;
                }
            }

            if (computerWon == 0) {
                //check for winning in columns
                for (int k = 0; k <= 2; k++) {
                    if (gameTable[0][k] == 'x' && gameTable[1][k] == 'x' && markedSegments[2][k] == 0) {
                        gameTable[2][k] = 'x';
                        computerWon = 1;
                        break;
                    } else if (gameTable[0][k] == 'x' && gameTable[2][k] == 'x' && markedSegments[1][k] == 0) {
                        gameTable[1][k] = 'x';
                        computerWon = 1;
                        break;
                    } else if (gameTable[1][k] == 'x' && gameTable[2][k] == 'x' && markedSegments[0][k] == 0) {
                        gameTable[0][k] = 'x';
                        computerWon = 1;
                        break;
                    }
                }
            }

            if (computerWon == 0) {
                //check for winning diagonal
                if (gameTable[0][0] == 'x' && gameTable[1][1] == 'x' && markedSegments[2][2] == 0) {
                    gameTable[2][2] = 'x';
                    computerWon = 1;
                } else if (gameTable[0][0] == 'x' && gameTable[2][2] == 'x' && markedSegments[1][1] == 0) {
                    gameTable[1][1] = 'x';
                    computerWon = 1;
                } else if (gameTable[1][1] == 'x' && gameTable[2][2] == 'x' && markedSegments[0][0] == 0) {
                    gameTable[0][0] = 'x';
                    computerWon = 1;
                } else if (gameTable[0][2] == 'x' && gameTable[1][1] == 'x' && markedSegments[2][0] == 0) {
                    gameTable[2][0] = 'x';
                    computerWon = 1;
                } else if (gameTable[2][0] == 'x' && gameTable[1][1] == 'x' && markedSegments[0][2] == 0) {
                    gameTable[0][2] = 'x';
                    computerWon = 1;
                } else if (gameTable[2][0] == 'x' && gameTable[0][2] == 'x' && markedSegments[1][1] == 0) {
                    gameTable[1][1] = 'x';
                    computerWon = 1;
                }
            }

            int computerBlock = 0;

            if (computerBlock == 0 && computerWon == 0) {
                //check for blocking in rows
                for (int k = 0; k <= 2; k++) {
                    if (gameTable[k][0] == 'o' && gameTable[k][1] == 'o' && markedSegments[k][2] == 0) {
                        gameTable[k][2] = 'x';
                        markedSegments[k][2] = 1;
                        computerBlock = 1;
                        break;
                    } else if (gameTable[k][0] == 'o' && gameTable[k][2] == 'o' && markedSegments[k][1] == 0) {
                        gameTable[k][1] = 'x';
                        markedSegments[k][1] = 1;
                        computerBlock = 1;
                        break;
                    } else if (gameTable[k][1] == 'o' && gameTable[k][2] == 'o' && markedSegments[k][0] == 0) {
                        gameTable[k][0] = 'x';
                        markedSegments[k][0] = 1;
                        computerBlock = 1;
                        break;
                    }
                }
            }

            if (computerBlock == 0 && computerWon == 0) {
                //check for blocking in columns
                for (int k = 0; k <= 2; k++) {
                    if (gameTable[0][k] == 'o' && gameTable[1][k] == 'o' && markedSegments[2][k] == 0) {
                        gameTable[2][k] = 'x';
                        markedSegments[2][k] = 1;
                        computerBlock = 1;
                        break;
                    } else if (gameTable[0][k] == 'o' && gameTable[2][k] == 'o' && markedSegments[1][k] == 0) {
                        gameTable[1][k] = 'x';
                        markedSegments[1][k] = 1;
                        computerBlock = 1;
                        break;
                    } else if (gameTable[1][k] == 'o' && gameTable[2][k] == 'o' && markedSegments[0][k] == 0) {
                        gameTable[0][k] = 'x';
                        markedSegments[0][k] = 1;
                        computerBlock = 1;
                        break;
                    }
                }
            }

            if (computerBlock == 0 && computerWon == 0) {
                //check for blocking in diagonal
                if (gameTable[0][0] == 'o' && gameTable[1][1] == 'o' && markedSegments[2][2] == 0) {
                    gameTable[2][2] = 'x';
                    markedSegments[2][2] = 1;
                    computerBlock = 1;
                } else if (gameTable[0][0] == 'o' && gameTable[2][2] == 'o' && markedSegments[1][1] == 0) {
                    gameTable[1][1] = 'x';
                    markedSegments[1][1] = 1;
                    computerBlock = 1;
                } else if (gameTable[1][1] == 'o' && gameTable[2][2] == 'o' && markedSegments[0][0] == 0) {
                    gameTable[0][0] = 'x';
                    markedSegments[0][0] = 1;
                    computerBlock = 1;
                } else if (gameTable[0][2] == 'o' && gameTable[1][1] == 'o' && markedSegments[2][0] == 0) {
                    gameTable[2][0] = 'x';
                    markedSegments[2][0] = 1;
                    computerBlock = 1;
                } else if (gameTable[2][0] == 'o' && gameTable[1][1] == 'o' && markedSegments[0][2] == 0) {
                    gameTable[0][2] = 'x';
                    markedSegments[0][2] = 1;
                    computerBlock = 1;
                } else if (gameTable[2][0] == 'o' && gameTable[0][2] == 'o' && markedSegments[1][1] == 0) {
                    gameTable[1][1] = 'x';
                    markedSegments[1][1] = 1;
                    computerBlock = 1;
                }
            }


            if (computerBlock == 0 && computerWon == 0) {
                if (moves == 8) {
                    //if the last move is not winning or blocking assign the last element to x, so random do while loop is not executed 
                    for (int i = 0; i <= 2; i++) {
                        for (int j = 0; j <= 2; j++) {
                            if (markedSegments[i][j] == 0) gameTable[i][j] = 'x';
                        }
                    }
                } else {
                    //get random move from the computer if no winning or blocking sequence was found 
                    do {
                        srand(time(0));
                        computerMoveLine = getRandomNumber();
                        computerMoveColumn = getRandomNumber();
                    } while (markedSegments[computerMoveLine][computerMoveColumn] == 1);

                    //assign random move
                    gameTable[computerMoveLine][computerMoveColumn] = 'x';
                    markedSegments[computerMoveLine][computerMoveColumn] = 1;
                }
            }
        }

        //incrementing moves
        moves++;

        //showing the gameTable
        showGameTable(gameTable);

        //checking for the player to give correct input for his move, no need to check if player wins
        if (computerWon == 0 && moves <= 7) {
            do {
                scanf("%d", &playerMoveLine);
                scanf("%d", &playerMoveColumn);
            } while (markedSegments[playerMoveLine][playerMoveColumn] == 1 || playerMoveLine < 0 || playerMoveLine > 2 || playerMoveColumn < 0 || playerMoveColumn > 2);

            //assign player move
            gameTable[playerMoveLine][playerMoveColumn] = 'o';
            markedSegments[playerMoveLine][playerMoveColumn] = 1;

            //incrementing moves
            moves++;
        }
    }

    //showing the results of the game
    if (computerWon == 1) printf("Congratulations computer you have defeated the human");
    else printf("Friendship between computer and human has won");

    return 0;
}