#include "givenA2.h"

#define XSCORE 1
#define OSCORE 4


int  getComputerMove(char board[N][N], int* computerRow, int* computerCol, int userRow, int userCol) {

    int winningSpot = 0;

    winningSpot = computerPlaysToWin(board, computerRow, computerCol);


     //if the computer does not find a winning spot, then it either play randomly or blocks


    if (!winningSpot)
    {
        // comment the next line if you are attempting the 2% functionality
        //computerPlaysRandom(computerRow, computerCol);

        // uncomment the next few  lines if you are attempting the 2% functionality
        int blocked = 0;

        blocked = computerPlaysToBlock(board, computerRow, computerCol);
        if (blocked == 0) {
           computerPlaysRandom(computerRow, computerCol);
        }
        return blocked;
    }

    return winningSpot;
}

void createInitialBoard(char board[N][N])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '?';
        }
    }
    printCurrentBoard(board);
}

void printCurrentBoard(char board[N][N])
{
    printf("Current board now is:\n\n");
    printf("   1   2   3\n\n");
        for (int i = 0; i < 3; i++)
        {
          printf("%d ", i+1);
          for (int j = 0; j < 2; j++)
          {
            printf(" %c |",board[i][j]);
          }
          if(i<2)
          {
            printf(" %c\n  -----------\n", board[i][2]);
          }
          else
          {
            printf(" %c\n",board[2][2]);
          }
        }
    printf("\n");
}

int isBoardFull(char board[N][N])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j]=='?')
            {
                return 0;
            }
        }
    }
    return 1;
}

int isInputValid(int entered, int min, int max)
{
    if (entered <= max && entered >= min)
    {
        return 1;
    }
    return 0;
}

void readUserMove(int* userRow, int* userCol, int* stepsWon)
{
    printf("Your move - enter numbers between 1 and 3\n");
    printf("Enter row number: ");
    scanf("%d",userRow);
    printf("Enter column number: ");
    scanf("%d", userCol);
     if( isInputValid(*userRow, 1,3) && isInputValid(*userCol, 1,3) )
    {
      *stepsWon += 1;
     }
}

void all_sums(char board[N][N], int sumR[N], int sumC[N], int* sumLD, int* sumRD)
{
    //initializing row and column scores
    for (int k = 0; k < N; k++)
    {
        sumR[k] = 0;
        sumC[k] = 0;
    }

    //summing row and column scores
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int value = 0;
            if (board[i][j] == 'X') { value = XSCORE; }
            else if (board[i][j] == 'O') { value = OSCORE; }

            sumR[i] += value;
            sumC[j] += value;
        }
    }

    //left and right diagonal score
    int sumld = 0, sumrd = 0;
    for (int i = 0; i < N; i++)
    {
        int value = 0;
        if (board[i][i] == 'X') { value = XSCORE; }
        else if (board[i][i] == 'O') { value = OSCORE; }
        sumld += value;

        value = 0;
        if (board[i][N - 1 - i] == 'X') { value = XSCORE; }
        else if (board[i][N - 1 - i] == 'O') { value = OSCORE; }
        sumrd += value;
    }
    *sumLD = sumld;
    *sumRD = sumrd;
}

int gameWon(char board[N][N], char c)
{
    int checkSum = 0;
    if (c == 'X') { checkSum = 3; }
    else if (c == 'O') { checkSum = 12; }

    int sumR[N];
    int sumC[N];
    int sumLD = 0, sumRD = 0;
    all_sums(board, sumR,sumC, &sumLD,&sumRD);

    for (int i = 0; i < N; i++)
    {
        if (sumR[i] == checkSum || sumC[i] == checkSum) { return 1; }
    }

    if (sumLD == checkSum || sumRD == checkSum) { return 1; }

    return 0;
}

int computerPlaysToWin(char board[N][N], int* computerRow, int* computerCol)
{
    int checkSum = 2 * OSCORE;
    int sumR[N];
    int sumC[N];
    int sumLD = 0, sumRD = 0;
    all_sums(board, sumR, sumC, &sumLD, &sumRD);

    for (int i = 0; i < N; i++)
    {
        if (sumR[i] == checkSum)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == '?')
                {
                    *computerRow = i ;
                    *computerCol = j ;
                    board[i][j] = 'O';
                    return 1;
                }
            }
        }
    }

    for (int j = 0; j < N; j++)
    {
        if (sumC[j] == checkSum)
        {
            for (int i = 0; i < N; i++)
            {
                if (board[i][j] == '?')
                {
                    *computerRow = i ;
                    *computerCol = j ;
                    board[i][j] = 'O';
                    return 1;
                }
            }
        }
    }

    if (sumLD == checkSum)
    {
        for (int i = 0; i < N; i++)
        {
            if (board[i][i] == '?')
            {
                *computerRow = i ;
                *computerCol = i ;
                board[i][i] = 'O';
                return 1;
            }
        }
    }

    if (sumRD == checkSum)
    {
        for (int i = 0; i < N; i++)
        {
            if (board[i][N-1-i] == '?')
            {
                *computerRow = i ;
                *computerCol = N-i-1;
                board[i][N-i-1] = 'O';
                return 1;
            }
        }
    }
    return 0;
}

int computerPlaysToBlock(char board[N][N], int* computerRow, int* computerCol)
{
    int checkSum = 2 * XSCORE;
    int sumR[N];
    int sumC[N];
    int sumLD = 0, sumRD = 0;
    all_sums(board, sumR, sumC, &sumLD, &sumRD);

    for (int i = 0; i < N; i++)
    {
        if (sumR[i] == checkSum)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == '?')
                {
                    *computerRow = i;
                    *computerCol = j;
                    board[i][j] = 'O';
                    return 1;
                }
            }
        }
    }

    for (int j = 0; j < N; j++)
    {
        if (sumC[j] == checkSum)
        {
            for (int i = 0; i < N; i++)
            {
                if (board[i][j] == '?')
                {
                    *computerRow = i;
                    *computerCol = j;
                    board[i][j] = 'O';
                    return 1;
                }
            }
        }
    }

    if (sumLD == checkSum)
    {
        for (int i = 0; i < N; i++)
        {
            if (board[i][i] == '?')
            {
                *computerRow = i;
                *computerCol = i;
                board[i][i] = 'O';
                return 1;
            }
        }
    }

    if (sumRD == checkSum)
    {
        for (int i = 0; i < N; i++)
        {
            if (board[i][N - 1 - i] == '?')
            {
                *computerRow = i;
                *computerCol = N - i - 1;
                board[i][N-i-1] = 'O';
                return 1;
            }
        }
    }
    return 0;
}

void computerPlaysRandom(int* computerRow, int* computerCol)
{
    *computerRow = (rand()) % 3;
    *computerCol = (rand()) % 3;
}

int memberOf(int value, int someArray[N])
{
    for (int i = 0; i < N; i++)
    {
        if (someArray[i] == value) { return 1; }
    }
    return 0;
}