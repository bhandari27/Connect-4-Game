#include <iostream>
using namespace std;

const int ROWS = 6;
const int COLS = 7;

// ======== Function Declarations ========
void initializeBoard(char board[ROWS][COLS]);
void printBoard(char board[ROWS][COLS]);
bool makeMove(char board[ROWS][COLS], int col, char player);
bool checkWin(char board[ROWS][COLS], char player);
bool checkDirection(char board[ROWS][COLS], int startRow, int startCol, int dRow, int dCol, char player);
bool isBoardFull(char board[ROWS][COLS]);

// ======== Main Function ========
int main() {
    char board[ROWS][COLS];
    initializeBoard(board);

    char currentPlayer = 'X'; // Player 1 is 'X', Player 2 is 'O'
    bool gameWon = false;

    cout << "Welcome to Connect Four!\n";
    printBoard(board);

    while (!gameWon && !isBoardFull(board)) {
        int col;
        cout << "Player " << currentPlayer << ", enter column (1-" << COLS << "): ";
        cin >> col;

        // Validate column
        while (col < 1 || col > COLS || !makeMove(board, col-1, currentPlayer)) {
            cout << "Invalid move. Try again: ";
            cin >> col;
        }

        printBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "🎉 Player " << currentPlayer << " wins!\n";
            gameWon = true;
        } else {
            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    if (!gameWon) {
        cout << "It's a draw! No more moves left.\n";
    }

    return 0;
}

// ======== Function Definitions ========

// Initialize the board with empty spaces
void initializeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = ' ';
}

// Print the current board
void printBoard(char board[ROWS][COLS]) {
    cout << "\n";
    for (int i = 0; i < ROWS; i++) {
        cout << "|";
        for (int j = 0; j < COLS; j++) {
            cout << board[i][j] << "|";
        }
        cout << "\n";
    }
    for (int j = 0; j < COLS; j++) {
        cout << " " << j+1;
    }
    cout << "\n\n";
}

// Place the player's token in the chosen column
bool makeMove(char board[ROWS][COLS], int col, char player) {
    // Check from bottom row upwards
    for (int row = ROWS-1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = player;
            return true;
        }
    }
    return false; // Column full
}

// Check for win in all directions
bool checkWin(char board[ROWS][COLS], char player) {
    // Check horizontal, vertical, and diagonal directions
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (checkDirection(board, row, col, 0, 1, player)) return true; // Horizontal
            if (checkDirection(board, row, col, 1, 0, player)) return true; // Vertical
            if (checkDirection(board, row, col, 1, 1, player)) return true; // Diagonal down-right
            if (checkDirection(board, row, col, 1, -1, player)) return true; // Diagonal down-left
        }
    }
    return false;
}

// Check 4 in a row in a specific direction
bool checkDirection(char board[ROWS][COLS], int startRow, int startCol, int dRow, int dCol, char player) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int r = startRow + i*dRow;
        int c = startCol + i*dCol;
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return false;
        if (board[r][c] == player) count++;
        else break;
    }
    return count == 4;
}

// Check if the board is full (draw)
bool isBoardFull(char board[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == ' ') return false;
    }
    return true;
}
