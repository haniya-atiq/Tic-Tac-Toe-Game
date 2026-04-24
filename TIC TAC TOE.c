#include <stdio.h>
#include <stdlib.h>

void displayBoard(char *board);
int checkWinner(char *board);
void saveGame(char *board, const char *filename, const char *result);

int main() {
    char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char *boardPtr = board;  // Pointer to the board array
    int player = 1, choice, gameStatus = 0;
    char mark;

    FILE *file;
    file = fopen("game_log.txt", "w");  // Open file to log moves
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "Tic Tac Toe Game Log:\n\n");
    fclose(file);

    while (gameStatus == 0) {
        displayBoard(boardPtr);
        player = (player % 2) ? 1 : 2;
        mark = (player == 1) ? 'X' : 'O';

        printf("Player %d, enter your choice: ", player);
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 9 && board[choice - 1] == '1' + (choice - 1)) {
            board[choice - 1] = mark;

            // Log move to file
            file = fopen("game_log.txt", "a");
            fprintf(file, "Player %d placed %c at position %d\n", player, mark, choice);
            fclose(file);
        } else {
            printf("Invalid move! Try again.\n");
            player--;
        }

        gameStatus = checkWinner(boardPtr);
        player++;
    }

    displayBoard(boardPtr);

    if (gameStatus == 1) {
        printf("==> Player %d wins!\n", --player);
        saveGame(boardPtr, "game_result.txt", player == 1 ? "Player 1 (X) Wins!" : "Player 2 (O) Wins!");
    } else {
        printf("==> Game Draw!\n");
        saveGame(boardPtr, "game_result.txt", "Draw!");
    }

    return 0;
}

// Function to display the board
void displayBoard(char *board) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n\n", board[6], board[7], board[8]);
}

// Function to check for a winner
int checkWinner(char *board) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i + 3] && board[i] == board[i + 6]) return 1;  // Columns
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3] == board[i * 3 + 2]) return 1;  // Rows
    }
    if (board[0] == board[4] && board[0] == board[8]) return 1;  // Main diagonal
    if (board[2] == board[4] && board[2] == board[6]) return 1;  // Anti-diagonal

    // Check for a draw (no empty spaces)
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') return 0;
    }

    return -1;  // Draw
}

// Function to save the final board and result to a file
void saveGame(char *board, const char *filename, const char *result) {
    FILE *file = fopen("game_log.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving game result!\n");
        return;
    }

    fprintf(file, "Final Board:\n");
    fprintf(file, " %c | %c | %c \n", board[0], board[1], board[2]);
    fprintf(file, "---|---|---\n");
    fprintf(file, " %c | %c | %c \n", board[3], board[4], board[5]);
    fprintf(file, "---|---|---\n");
    fprintf(file, " %c | %c | %c \n\n", board[6], board[7], board[8]);
    fprintf(file, "Result: %s\n", result);

    fclose(file);
}

