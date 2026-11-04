#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//-------------------------------------------------------------------------------

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";
const string YELLOW = "\033[33m";

//-------------------------------------------------------------------------------

struct Square
{
    bool revealed = false; // Indicates whether the square has been revealed (guessed) or not
    int numberNearbyBoats = 0; //how many boats are touching this square if it is a miss
    string display = ""; //what gets printed for this square if it is revealed. X for hit, O for miss, or the square name if not revealed.
};

//-------------------------------------------------------------------------------

vector<vector<string>> battleShipBoard =
{
    {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10"},
    {"B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10"},
    {"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10"},
    {"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10"},
    {"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10"},
    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10"},
    {"G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9", "G10"},
    {"H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10"},
    {"I1", "I2", "I3", "I4", "I5", "I6", "I7", "I8", "I9", "I10"},
    {"J1", "J2", "J3", "J4", "J5", "J6", "J7", "J8", "J9", "J10"}
};

//-------------------------------------------------------------------------------

void squareSetup(vector<vector<Square>>& board)
{
    for (int i = 0; i < 10; i++) // Loop through each row of the board
    {
        for (int j = 0; j < 10; j++) // Loop through each column of the board
        {
            board[i][j].revealed = false; // Initialize the revealed status of each square to false
            board[i][j].numberNearbyBoats = 0; // Initialize the number of nearby boats for each square to 0
            board[i][j].display = battleShipBoard[i][j]; // Initialize the display string for each square to its position
        }
    }
}

//-------------------------------------------------------------------------------

void printBoard(const vector<vector<Square>>& squares) // Prints the board the attacking player sees
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << squares[i][j].display << " "; // Print the display string for each square
        }
        cout << endl;
    }
}

//-------------------------------------------------------------------------------

void printBoard(const vector<vector<int>>& boatBoard) // Overloaded version for a vector of ints. Shows where the boats are.
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (boatBoard[i][j] == 1)
            {
                cout << GREEN << "X " << RESET << " "; // a boat is here
            }
            else
            {
                cout << battleShipBoard[i][j] << " "; // empty square, show its name
            }
        }
        cout << endl;
    }
}

//-------------------------------------------------------------------------------

void hideScreen() // Pushes the last player's boats off the screen so the other player can't see them
{
    for (int i = 0; i < 50; i++)
    {
        cout << endl;
    }
}

//-------------------------------------------------------------------------------

void shipAmount(int& numberBoats)  //let the user select how many ships they want to play with. 1-100. 10 is default.
{
    cout << "How many ships would you like to play with? (1-100, default is 10): ";
    cin >> numberBoats;

    if (numberBoats < 1 || numberBoats > 100)
    {
        cout << "Invalid input. Defaulting to 10 ships." << endl;
        numberBoats = 10;
    }
}

//-------------------------------------------------------------------------------

// Asks for a row and column. Returns true if it's a real square on the board,
// and puts the square's position into rowIndex and columnIndex.
bool readSquare(int& rowIndex, int& columnIndex)
{
    string rowText;
    string columnText;

    cout << "Row (A-J): ";
    cin >> rowText;

    cout << "Column (1-10): ";
    cin >> columnText;

    char normalizedRow = toupper(rowText[0]); // first character of what they typed

    // Turn the column text into a number. Anything that isn't 1-10 stays 0 (invalid).
    int columnInput = 0;
    if (columnText.length() == 1 && isdigit(columnText[0]))
    {
        columnInput = columnText[0] - '0';
    }
    else if (columnText == "10")
    {
        columnInput = 10;
    }

    if (rowText.length() != 1 || normalizedRow < 'A' || normalizedRow > 'J' || columnInput < 1 || columnInput > 10)
    {
        cout << "Invalid spot. Please enter a row from A-J and a column from 1-10." << endl;
        return false;
    }

    rowIndex = normalizedRow - 'A';
    columnIndex = columnInput - 1;
    return true;
}

//-------------------------------------------------------------------------------

void placeRandomBoats(int boatsPlaced, int numberBoats, vector<vector<int>>& boatBoard)
{
    if (boatsPlaced == numberBoats)
    {
        return;
    }

    int row = rand() % 10;
    int column = rand() % 10;

    if (boatBoard[row][column] == 1)
    {
        placeRandomBoats(boatsPlaced, numberBoats, boatBoard);
        return;
    }

    boatBoard[row][column] = 1;
    cout << "Boat " << boatsPlaced + 1 << ": "
         << battleShipBoard[row][column] << endl;

    placeRandomBoats(boatsPlaced + 1, numberBoats, boatBoard);
}

//-------------------------------------------------------------------------------

// Lets a player pick where each of their boats goes, one at a time, using recursion.
// Boats can't go on a square that already has a boat or has already been guessed.
void placeBoatsManually(int player, int boatsPlaced, int numberBoats, vector<vector<int>>& boatBoard, const vector<vector<Square>>& squares)
{
    if (boatsPlaced == numberBoats)
    {
        return;
    }

    cout << "\nPlayer " << player << ", place boat " << boatsPlaced + 1 << " of " << numberBoats << ".\n";

    int rowIndex = 0;
    int columnIndex = 0;
    bool onBoard = readSquare(rowIndex, columnIndex);

    if (!onBoard)
    {
        placeBoatsManually(player, boatsPlaced, numberBoats, boatBoard, squares); // invalid spot, ask again
    }
    else if (boatBoard[rowIndex][columnIndex] == 1 || squares[rowIndex][columnIndex].revealed)
    {
        cout << "You can't place a boat there. Pick a different square.\n";
        placeBoatsManually(player, boatsPlaced, numberBoats, boatBoard, squares); // taken, ask again
    }
    else
    {
        boatBoard[rowIndex][columnIndex] = 1;
        printBoard(boatBoard); // show the player their boats so far
        placeBoatsManually(player, boatsPlaced + 1, numberBoats, boatBoard, squares); // next boat
    }
}

//-------------------------------------------------------------------------------

int nearbyBoats(int row, int column, const vector<vector<int>>& boatBoard, int spot = 0)
{
    if (spot == 9)
    {
        return 0;
    }

    int rowOffset = row + (spot / 3) - 1;
    int colOffset = column + (spot % 3) - 1;

    if (spot != 4 && rowOffset >= 0 && rowOffset < 10 && colOffset >= 0 && colOffset < 10)
    {
        if (boatBoard[rowOffset][colOffset] == 1)
        {
            return 1 + nearbyBoats(row, column, boatBoard, spot + 1);
        }
    }

    return nearbyBoats(row, column, boatBoard, spot + 1);
}

//-------------------------------------------------------------------------------

// Keeps asking until the player picks a real square that hasn't been guessed yet.
void getGuess(const vector<vector<Square>>& squares, int& rowIndex, int& columnIndex)
{
    bool validGuess = false;

    while (!validGuess)
    {
        cout << "Pick a square to attack.\n";
        bool onBoard = readSquare(rowIndex, columnIndex);

        if (onBoard && squares[rowIndex][columnIndex].revealed)
        {
            cout << battleShipBoard[rowIndex][columnIndex] << " has already been guessed. Pick a different square.\n";
        }
        else if (onBoard)
        {
            validGuess = true;
        }
    }
}

//-------------------------------------------------------------------------------

// Reveals one square, changes what it displays, and prints HIT or MISS.
// Returns 1 for a hit and 0 for a miss, so it can be added to the boats found.
int revealSquare(vector<vector<Square>>& squares, const vector<vector<int>>& boatBoard, int rowIndex, int columnIndex)
{
    squares[rowIndex][columnIndex].revealed = true;

    if (boatBoard[rowIndex][columnIndex] == 1)
    {
        squares[rowIndex][columnIndex].display = GREEN + "X " + RESET;
        cout << GREEN << "HIT! There was a boat at " << battleShipBoard[rowIndex][columnIndex] << RESET << endl;
        return 1;
    }

    squares[rowIndex][columnIndex].numberNearbyBoats = nearbyBoats(rowIndex, columnIndex, boatBoard);

    if (squares[rowIndex][columnIndex].numberNearbyBoats > 0)
    {
        squares[rowIndex][columnIndex].display = YELLOW + to_string(squares[rowIndex][columnIndex].numberNearbyBoats) + " " + RESET; // miss, shows how many boats are touching
    }
    else
    {
        squares[rowIndex][columnIndex].display = RED + "O " + RESET; // miss, no boats nearby
    }

    cout << RED << "MISS! There was no boat at " << battleShipBoard[rowIndex][columnIndex] << RESET << endl;
    cout << "Boats touching that square: " << YELLOW << squares[rowIndex][columnIndex].numberNearbyBoats << RESET << endl;
    return 0;
}

//-------------------------------------------------------------------------------

// Counts the squares where a new boat could still go (no boat there and not guessed yet).
int freeSquares(const vector<vector<int>>& boatBoard, const vector<vector<Square>>& squares)
{
    int count = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (boatBoard[i][j] == 0 && !squares[i][j].revealed)
            {
                count++;
            }
        }
    }

    return count;
}

//-------------------------------------------------------------------------------

// Called when both players sink the last boat on the same turn.
// Returns true if the game keeps going, or false if there's no room left and both players lose.
bool handleDraw(int numberBoats, vector<vector<int>>& boatBoard1, const vector<vector<Square>>& squares1,
                vector<vector<int>>& boatBoard2, const vector<vector<Square>>& squares2)
{
    cout << "\nIt's a draw! Both players sank their last boat on the same turn.\n";

    if (freeSquares(boatBoard1, squares1) < numberBoats || freeSquares(boatBoard2, squares2) < numberBoats)
    {
        cout << "There is no room left on the board for new boats. You both lose!\n";
        return false;
    }

    cout << "Both players place new boats and keep playing!\n";

    placeBoatsManually(1, 0, numberBoats, boatBoard1, squares1);
    hideScreen();
    placeBoatsManually(2, 0, numberBoats, boatBoard2, squares2);
    hideScreen();

    return true;
}

//-------------------------------------------------------------------------------

// The original one player game, with boats placed randomly.
void playSinglePlayer()
{
    int boatsFound = 0;
    int numberBoats = 10;

    vector<vector<int>> boatBoard(10, vector<int>(10, 0));
    vector<vector<Square>> squares(10, vector<Square>(10));

    shipAmount(numberBoats);

    cout << "Battle Ship Board: " << endl;
    cout << "Random boat placement (" << numberBoats << " boats):" << endl;

    placeRandomBoats(0, numberBoats, boatBoard);
    squareSetup(squares);

    cout << "\nInitial board:\n";
    printBoard(squares);     // Square version

    while (boatsFound < numberBoats)
    {
        int rowIndex = 0;
        int columnIndex = 0;

        cout << endl;
        getGuess(squares, rowIndex, columnIndex);
        boatsFound += revealSquare(squares, boatBoard, rowIndex, columnIndex);

        cout << "\nUpdated board:\n";
        printBoard(squares);
    }

    cout << "\nYou sank all " << numberBoats << " boats! You win!\n";

    cout << "\nBoat Locations Were:\n";
    printBoard(boatBoard);   // int version
}

//-------------------------------------------------------------------------------

// Two player game. Each player places their own boats, then both pick a square
// and the two shots are revealed at the same time.
void playTwoPlayer()
{
    int numberBoats = 10;
    int boatsFound1 = 0;    // how many of player 2's boats player 1 has sunk
    int boatsFound2 = 0;    // how many of player 1's boats player 2 has sunk
    bool gameOver = false;

    vector<vector<int>> boatBoard1(10, vector<int>(10, 0));   // where player 1's boats are
    vector<vector<int>> boatBoard2(10, vector<int>(10, 0));   // where player 2's boats are
    vector<vector<Square>> squares1(10, vector<Square>(10));  // player 1's board, as player 2 sees it
    vector<vector<Square>> squares2(10, vector<Square>(10));  // player 2's board, as player 1 sees it

    shipAmount(numberBoats);
    squareSetup(squares1);
    squareSetup(squares2);

    placeBoatsManually(1, 0, numberBoats, boatBoard1, squares1);
    hideScreen();
    placeBoatsManually(2, 0, numberBoats, boatBoard2, squares2);
    hideScreen();

    while (!gameOver)
    {
        int row1 = 0;
        int column1 = 0;
        int row2 = 0;
        int column2 = 0;

        cout << "\n--- Player 1's turn. Player 2's board: ---\n";
        printBoard(squares2);
        getGuess(squares2, row1, column1);

        cout << "\n--- Player 2's turn. Player 1's board: ---\n";
        printBoard(squares1);
        getGuess(squares1, row2, column2);

        // Both shots are revealed at the same time
        cout << "\nPlayer 1 fired at " << battleShipBoard[row1][column1] << ": ";
        boatsFound1 += revealSquare(squares2, boatBoard2, row1, column1);

        cout << "\nPlayer 2 fired at " << battleShipBoard[row2][column2] << ": ";
        boatsFound2 += revealSquare(squares1, boatBoard1, row2, column2);

        if (boatsFound1 == numberBoats && boatsFound2 == numberBoats)
        {
            gameOver = !handleDraw(numberBoats, boatBoard1, squares1, boatBoard2, squares2);
            boatsFound1 = 0;
            boatsFound2 = 0;
        }
        else if (boatsFound1 == numberBoats)
        {
            cout << "\nPlayer 1 sank all of Player 2's boats! Player 1 wins!\n";
            gameOver = true;
        }
        else if (boatsFound2 == numberBoats)
        {
            cout << "\nPlayer 2 sank all of Player 1's boats! Player 2 wins!\n";
            gameOver = true;
        }
    }
}

//-------------------------------------------------------------------------------

int main()
{
    string mode;

    srand(static_cast<unsigned int>(time(0)));

    cout << "Choose a mode (1 = single player, 2 = two player): ";
    cin >> mode;

    if (mode == "2")
    {
        playTwoPlayer();
    }
    else
    {
        playSinglePlayer();
    }

    return 0;
}