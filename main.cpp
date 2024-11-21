#include <iostream>
#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time()
#include <cctype>  // Для std::tolower

char board[3][3]; // Game board

// Initialize the game board
void initializeBoard() {
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
}

// Print the game board
void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Check for a winner
char checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];

    // Check columns
    for (int i = 0; i < 3; i++)
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    // Check for draw
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return ' '; // Continue the game

    return 'D'; // Draw
}

// Handle player move
bool makeMove(char player, int move) {
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = player;
        return true;
    } else {
        return false;
    }
}

// Simple bot logic - choose a random free cell
int getBotMove() {
    int move;
    do {
        move = rand() % 9 + 1; // Random number between 1 and 9
    } while (!makeMove('O', move)); // Bot is 'O'
    return move;
}

// Main game logic
void playGame(bool vsBot) {
    char player = 'X';
    char winner = ' ';
    int move;

    initializeBoard();

    while (winner == ' ') {
        printBoard();

        if (player == 'X' || !vsBot) { // Player's turn or vs another player
            std::cout << "Player " << player << ", enter the cell number (1-9): ";
            std::cin >> move;

            if (move < 1 || move > 9 || !makeMove(player, move)) {
                std::cout << "Invalid move! Try again.\n";
                continue;
            }
        } else { // Bot's turn
            move = getBotMove();
            std::cout << "Bot chooses cell " << move << std::endl;
        }

        winner = checkWinner();
        player = (player == 'X') ? 'O' : 'X';
    }

    printBoard();

    if (winner == 'D') {
        std::cout << "The game is a draw!" << std::endl;
    } else {
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
}

// Ask the player if they want to replay or exit the game
bool askForReplay() {
    char choice;
    while (true) {
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> choice;
        choice = std::tolower(choice);

        if (choice == 'y') {
            return true;
        } else if (choice == 'n') {
            return false;
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }
}

// Ask the player if they want to play against a bot
bool askForBot() {
    char choice;
    while (true) {
        std::cout << "Do you want to play against the bot? (y/n): ";
        std::cin >> choice;
        choice = std::tolower(choice);

        if (choice == 'y') {
            return true;
        } else if (choice == 'n') {
            return false;
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed

    do {
        bool vsBot = askForBot();
        playGame(vsBot);
    } while (askForReplay());

    std::cout << "Thank you for playing! Goodbye!" << std::endl;
    return 0;
}