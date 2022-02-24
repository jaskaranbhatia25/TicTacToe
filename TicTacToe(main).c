
int main()
{
    int userRow, userCol, computerRow, computerCol;
    int taken;
    int count = 1;
    int stepsWon = 0;
    char board[N][N];
    char winner = 'N';
    srand((int)time(0));
    printf("This tic-tac-toe board is of size %d by %d\n", N, N);
    printf("You are using symbol X and the computer program is using symbol O\n");
    printf("Here is the board - spaces are indicated by a ?\n");
    createInitialBoard(board);
    while ((winner != 'Y') && !(isBoardFull(board)))
    {
        taken = 0;
        while (!(taken))
        {
            readUserMove(&userRow, &userCol, &stepsWon);
            printf("You chose row %d and column %d \n", userRow, userCol);
            while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))
            {
                printf("That's is an invalid row or column number - try again\n");
                readUserMove(&userRow, &userCol, &stepsWon);
                printf("You chose row %d and column %d \n", userRow, userCol);
            }
            if (board[userRow - 1][userCol - 1] == '?')
            {
                board[userRow - 1][userCol - 1] = 'X';
                taken = 1;
                count++;
            }
            else
            {
                taken = 0;
                printf("That spot is taken - please try another one\n");
            }
        }
        if (gameWon(board, 'X'))   //user won
        {
            printf("Congrats - you won against the computer :) in %d steps\n", stepsWon);
            winner = 'Y';
        }
        else  if (!(isBoardFull(board)))            //check computer's move if the board is not yet full
        {
            taken = 0;
            while (!(taken))
            {
                taken = getComputerMove(board, &computerRow, &computerCol, userRow - 1, userCol - 1);
                if (taken) {
                    break;
                }
                if (board[computerRow][computerCol] == '?')
                {
                    board[computerRow][computerCol] = 'O';
                    taken = 1;
                }
                else
                {
                    taken = 0;
                    //printf("That spot is taken - computer - try another one\n");
                }
            }
            printf("Computer chose row %d and column %d \n", computerRow + 1, computerCol + 1);
            if (gameWon(board, 'O'))
            {
                printf("Oh the computer won this time :(( think hard next time\n");
                winner = 'Y';
            }
        }
        printCurrentBoard(board);
        if (winner != 'Y') {
            printf("Enter to continue \n");
        }
    } //end of while
    if (winner != 'Y') {
        printf("Game was a tie - no winner!\n\n");
    }
    return 0;
}
