#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//holds x, o or - if not assigned
char gameTable[3][3] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

//getting random number between 0-2
int getRandomNumber() {
    return rand() % 3;
}

//get a free column in a row
int getFreeColumnInRow(int row, char sign) {
    if (gameTable[row][0] == sign && gameTable[row][1] == sign && gameTable[row][2] == '-') return 2;
    else if (gameTable[row][0] == sign && gameTable[row][2] == sign && gameTable[row][1] == '-') return 1;
    else if (gameTable[row][1] == sign && gameTable[row][2] == sign && gameTable[row][0] == '-') return 0;

    return -1;
}

//get a free row in a column
int getFreeRowInColumn(int column, char sign) {
    if (gameTable[0][column] == sign && gameTable[1][column] == sign && gameTable[2][column] == '-') return 2;
    else if (gameTable[0][column] == sign && gameTable[2][column] == sign && gameTable[1][column] == '-') return 1;
    else if (gameTable[1][column] == sign && gameTable[2][column] == sign && gameTable[0][column] == '-') return 0;

    return -1;
}

//showing the game table in a grid
void showGameTable() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", gameTable[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int row, column, computerWon = 0, moves = 0;

    //game loop
    while (computerWon == 0 && moves < 9) {
        if (moves <= 2) {  //first two moves must be in random corners of the gameTable
            //get random line and column
            do {
                srand(time(0));
                row = getRandomNumber();
                column = getRandomNumber();
            } while (row == 1 || column == 1 || gameTable[row][column] != '-');

            //assign random move
            gameTable[row][column] = 'x';
        } else {  //next moves will block the player or win the game for the computer
            //check for winning in rows
            for (int k = 0; k < 3; k++) {
                int freeColumnInRow = getFreeColumnInRow(k, 'x');

                if (freeColumnInRow == -1) continue;

                gameTable[k][freeColumnInRow] = 'x';
                computerWon = 1;
                break;
            }

            if (computerWon == 0) {
                //check for winning in columns
                for (int k = 0; k < 3; k++) {
                    int freeRowInColumn = getFreeRowInColumn(k, 'x');

                    if (freeRowInColumn == -1) continue;

                    gameTable[freeRowInColumn][k] = 'x';
                    computerWon = 1;
                    break;
                }
            }

            if (computerWon == 0) {
                //check for winning diagonals
                if (gameTable[0][0] == 'x' && gameTable[1][1] == 'x' && gameTable[2][2] == '-') {
                    gameTable[2][2] = 'x';
                    computerWon = 1;
                } else if (gameTable[0][0] == 'x' && gameTable[2][2] == 'x' && gameTable[1][1] == '-') {
                    gameTable[1][1] = 'x';
                    computerWon = 1;
                } else if (gameTable[1][1] == 'x' && gameTable[2][2] == 'x' && gameTable[0][0] == '-') {
                    gameTable[0][0] = 'x';
                    computerWon = 1;
                } else if (gameTable[0][2] == 'x' && gameTable[1][1] == 'x' && gameTable[2][0] == '-') {
                    gameTable[2][0] = 'x';
                    computerWon = 1;
                } else if (gameTable[2][0] == 'x' && gameTable[1][1] == 'x' && gameTable[0][2] == '-') {
                    gameTable[0][2] = 'x';
                    computerWon = 1;
                } else if (gameTable[2][0] == 'x' && gameTable[0][2] == 'x' && gameTable[1][1] == '-') {
                    gameTable[1][1] = 'x';
                    computerWon = 1;
                }
            }

            int computerBlock = 0;

            if (computerWon == 0) {
                //check for blocking in rows
                for (int k = 0; k < 3; k++) {
                    int freeColumnInRow = getFreeColumnInRow(k, 'o');

                    if (freeColumnInRow == -1) continue;

                    gameTable[k][freeColumnInRow] = 'x';
                    computerBlock = 1;
                    break;
                }
            }

            if (computerBlock == 0 && computerWon == 0) {
                //check for blocking in columns
                for (int k = 0; k < 3; k++) {
                    int freeRowInColumn = getFreeRowInColumn(k, 'o');

                    if (freeRowInColumn == -1) continue;

                    gameTable[freeRowInColumn][k] = 'x';
                    computerBlock = 1;
                    break;
                }
            }

            if (computerBlock == 0 && computerWon == 0) {
                //check for blocking in diagonals
                if (gameTable[0][0] == 'o' && gameTable[1][1] == 'o' && gameTable[2][2] == '-') {
                    gameTable[2][2] = 'x';
                    computerBlock = 1;
                } else if (gameTable[0][0] == 'o' && gameTable[2][2] == 'o' && gameTable[1][1] == '-') {
                    gameTable[1][1] = 'x';
                    computerBlock = 1;
                } else if (gameTable[1][1] == 'o' && gameTable[2][2] == 'o' && gameTable[0][0] == '-') {
                    gameTable[0][0] = 'x';
                    computerBlock = 1;
                } else if (gameTable[0][2] == 'o' && gameTable[1][1] == 'o' && gameTable[2][0] == '-') {
                    gameTable[2][0] = 'x';
                    computerBlock = 1;
                } else if (gameTable[2][0] == 'o' && gameTable[1][1] == 'o' && gameTable[0][2] == '-') {
                    gameTable[0][2] = 'x';
                    computerBlock = 1;
                } else if (gameTable[2][0] == 'o' && gameTable[0][2] == 'o' && gameTable[1][1] == '-') {
                    gameTable[1][1] = 'x';
                    computerBlock = 1;
                }
            }


            if (computerBlock == 0 && computerWon == 0) {
                if (moves == 8) {
                    //if the last move is not winning or blocking assign the last element to x, so random do while loop is not executed 
                    for (int i = 0; i <= 2; i++) {
                        for (int j = 0; j <= 2; j++) {
                            if (gameTable[i][j] == '-') gameTable[i][j] = 'x';
                        }
                    }
                } else {
                    //get random move from the computer if no winning or blocking sequence was found 
                    do {
                        srand(time(0));
                        row = getRandomNumber();
                        column = getRandomNumber();
                    } while (gameTable[row][column] != '-');

                    //assign random move
                    gameTable[row][column] = 'x';
                }
            }
        }

        //incrementing moves
        moves++;

        //showing the gameTable
        showGameTable(gameTable);

        //checking for the player to give correct input for his move
        if (computerWon == 0 && moves <= 7) {
            do {
                scanf("%d", &row);
                scanf("%d", &column);
            } while (gameTable[row][column] != '-' || row < 0 || row > 2 || column < 0 || column > 2);

            //assign player move
            gameTable[row][column] = 'o';

            //incrementing moves
            moves++;
        }
    }

    //showing the results of the game
    if (computerWon == 1) printf("Congratulations computer you have defeated the human");
    else printf("Friendship between computer and human has won");

    return 0;
}