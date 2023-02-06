#include <iostream>
#include <tuple>

const int BOARD_SIZE = 3;

void drawBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j];
            if (j != BOARD_SIZE - 1) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
};

std::tuple<int, int> calculateNumberRow(int pos) {
    if (pos <= 3) {
        return std::make_tuple(0, pos - 1);
    }

    else if (pos <= 6) {
        return std::make_tuple(1, pos - 4);
    }

    else {
        return std::make_tuple(2, pos - 7);
    }
};

bool validPosition(char board[BOARD_SIZE][BOARD_SIZE], int pos) {
    auto [row, col] = calculateNumberRow(pos);

    return (board[row][col] == '-') ? true : false;
}

void rotatePlayerTurn(char* playerTurn) {
    *playerTurn = (*playerTurn == 'X') ? 'O' : 'X';
};

void plotPlayerPosition(char board[BOARD_SIZE][BOARD_SIZE], char player, int position) {
    auto [row, col] = calculateNumberRow(position);

    board[row][col] = player;
}

bool checkforWin(char board[BOARD_SIZE][BOARD_SIZE]) {
    // check for row win
    for (int i = 0; i < BOARD_SIZE; i++) {
        int j;
        for (j = 1; j < BOARD_SIZE; j++) {
            if (board[i][j] != board[i][j - 1] || board[i][j] == '-') {
                break;
            }
        }
        if (j == BOARD_SIZE) {
            return true;
        }
    }

    // check for column win
    for (int i = 0; i < BOARD_SIZE; i++) {
        int j;
        for (j = 1; j < BOARD_SIZE; j++) {
            if (board[j][i] != board[j - 1][i] || board[j][i] == '-') {
                break;
            }
        }
        if (j == BOARD_SIZE) {
            return true;
        }
    }

    // check for diagonal win (top left to bottom right)
    int j;
    for (j = 1; j < BOARD_SIZE; j++) {
        if (board[j][j] != board[j - 1][j - 1] || board[j][j] == '-') {
            break;
        }
    }
    if (j == BOARD_SIZE) {
        return true;
    }

    // check for diagonal win (top right to bottom left)
    for (j = 1; j < BOARD_SIZE; j++) {
        if (board[BOARD_SIZE - j - 1][j] != board[BOARD_SIZE - j][j - 1] || board[BOARD_SIZE - j - 1][j] == '-') {
            break;
        }
    }
    if (j == BOARD_SIZE) {
        return true;
    }

    return false;
}


int main() {
	char board[BOARD_SIZE][BOARD_SIZE] = {
		{'-', '-', '-'},
		{'-', '-', '-'},
		{'-', '-', '-'}
	};

    char playerTurn = 'X';

    while (true) {
        drawBoard(board);
        int boardSpot;

        if (playerTurn == 'X') {
            printf("Player 1, choose a spot (1-9): ");
        }

        else if (playerTurn == 'O') {
            printf("Player 2, choose a spot (1-9): ");
        }

        std::cin >> boardSpot;
        if (!validPosition(board, boardSpot)) { continue; }

        plotPlayerPosition(board, playerTurn, boardSpot);
        rotatePlayerTurn(&playerTurn);

        if (checkforWin(board)) {
            std::cout << "Game Over!" << std::endl << std::endl;
            drawBoard(board);
            break;
        }
    }
	return 0;
}