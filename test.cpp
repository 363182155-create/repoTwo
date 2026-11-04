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

struct player
{
    vector<vector<Square>> board;
    vector<vector<Square>> shots;
    string name;
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

void printBoard(const vector<vector<Square>>& squares) // Function to print the current state of the board
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

// void printColoredBoard(const vector<vector<string>>& board,
//                        const vector<vector<bool>>& hit,
//                        const vector<vector<bool>>& miss,
//                        const vector<vector<int>>& nearbyBoatsCount)
// {
//     for (int i = 0; i < 10; i++)
//     {
//         for (int c = 0; c < 10; c++)
//         {
//             if (hit[i][c])
//             {
//                 cout << GREEN << board[i][c] << RESET << " ";
//             }
//             else if (miss[i][c])
//             {
//                 cout << RED << nearbyBoatsCount[i][c] << RESET << " ";
//             }
//             else
//             {
//                 cout << board[i][c] << " ";
//             }
//         }
//         cout << endl;
//     }
// }

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

bool readSquare(int &rowIndex, int &columnIndex)
{
    string rowText;
    string columnText;

    char normalizedRow = toupper(rowText[0]);
    int columnInput = 0;

    cout << "Enter row (A-J): ";
    cin >> rowText;

    cout << "Enter column (1-10): ";
    cin >> columnText;

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
        cout << "Invalid spot sir. Please enter a row from A-J and a column from 1-10." << endl;
        return false;
    }

    rowIndex = normalizedRow - 'A';
    columnIndex = columnInput - 1;
    return true;
}
//-------------------------------------------------------------------------------

// void placeManually(int player, int boatsPlaced, int numberBoats, vector<vector<int>>& boatBoard, vector<vector<Square>>& squares)
// {
//     if (boatsPlaced == numberBoats)
//     {
//         return;
//     }

//     cout << "Player " << playerNumber << ", place boat " << boatsPlaced + 1 << " of " << numberBoats << endl;

//     char rowInput;
//     int columnInput;
//     bool onBoard = readSquare(rowIndex, columnIndex);

//     if (!onBoard)
//     {
//         placeManually(player, boatsPlaced, numberBoats, boatBoard, squares); // ask again
//     }
// }

//-------------------------------------------------------------------------------

void printBoard(const vector<vector<int>>& boatBoard)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (boatBoard[i][j] == 1)
            {
                cout << GREEN << "X " << RESET << " ";
            }
            else
            {
                cout << battleShipBoard[i][j] << " ";
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

void singlePlayer()
{

}

//-------------------------------------------------------------------------------

void twoPlayer()
{

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

int main()
{
    char rowInput = '\0';
    int columnInput = 0;
    int boatsFound = 0;
    int numberBoats = 10;

    srand(static_cast<unsigned int>(time(0)));

    vector<vector<int>> boatBoard(10, vector<int>(10, 0));
    vector<vector<Square>> squares(10, vector<Square>(10));

//-------------------------------------------------------------------------------

    shipAmount(numberBoats);

    cout << "Battle Ship Board: " << endl;
    cout << "Random boat placement (" << numberBoats << " boats):" << endl;

    placeRandomBoats(0, numberBoats, boatBoard);
    squareSetup(squares);

    cout << "\nInitial board:\n";

    printBoard(squares);

//-------------------------------------------------------------------------------

    while (boatsFound < numberBoats)
    {
        cout << "\nWhat row would you like to attack? (A-J): ";
        cin >> rowInput;

        cout << "What column would you like to attack? (1-10): ";
        cin >> columnInput;

        char normalizedRow = toupper(rowInput);
        int rowIndex = normalizedRow - 'A';
        int columnIndex = columnInput - 1;

        if (normalizedRow < 'A' || normalizedRow > 'J' || columnInput < 1 || columnInput > 10)
        {
            cout << "Invalid spot. Please enter a row from A-J and a column from 1-10." << endl;
        }
        else if (squares[rowIndex][columnIndex].revealed)
        {
            cout << battleShipBoard[rowIndex][columnIndex]
                 << " has already been guessed. Pick a different square.\n";
        }
        else if (boatBoard[rowIndex][columnIndex] == 1)
        {
            squares[rowIndex][columnIndex].revealed = true;
            squares[rowIndex][columnIndex].display = GREEN + "X " + RESET;
            boatsFound++;

            cout << GREEN << "HIT! You hit " << battleShipBoard[rowIndex][columnIndex] << RESET << endl;
            cout << "\nUpdated board:\n";
            printBoard(squares);
        }
        else
        {
            squares[rowIndex][columnIndex].revealed = true;
            squares[rowIndex][columnIndex].numberNearbyBoats = nearbyBoats(rowIndex, columnIndex, boatBoard);

            if (squares[rowIndex][columnIndex].numberNearbyBoats > 0)
            {
                squares[rowIndex][columnIndex].display = YELLOW + to_string(squares[rowIndex][columnIndex].numberNearbyBoats) + " " + RESET;
            }
            else
            {
                squares[rowIndex][columnIndex].display = RED + "O " + RESET;
            }


            cout << RED << "\nMISS! There was no boat at " << battleShipBoard[rowIndex][columnIndex] << RESET << endl;
            cout << "Boats touching that square: " << YELLOW << squares[rowIndex][columnIndex].numberNearbyBoats << RESET << endl;
            cout << "\nUpdated board:\n";
            printBoard(squares);

        }
    }

    cout << "\nYou sank all " << numberBoats << " boats! You win!\n";

    cout << "\nBoat Locations Were:\n";
    printBoard(boatBoard);

    return 0;
}