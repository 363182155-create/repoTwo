#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//--------------------------- Colour Coding --------------------------------------

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";
const string YELLOW = "\033[33m";

//-------------------------------------------------------------------------------

struct Square
{
    bool revealed = false; // Indicates whether the square has been revealed (guessed) or not
    int numberNearbyBoats = 0; //how many boats are touching this square if it is a miss
    bool boatPresent = false; // Indicates whether a boat is present in this square
    string display = ""; //what gets printed for this square if it is revealed. X for hit, O for miss, or the square name if not revealed.
};

//-------------------------------------------------------------------------------

struct Player
{
    vector<vector<Square>> board; //Each player has their own board to place their boats on
    vector<vector<Square>> shots; //seperating the board to track where the player has shot
    string name; // Player's name
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
            board[i][j].boatPresent = false; // Initialize the boat presence status of each square to false
        }
    }
}

//-------------------------------------------------------------------------------

void playerSetup(Player& currentPlayer, int playerNumber) // Function to set up a player, including their name and initializing their boards
{
    cout << "Enter name for Player " << playerNumber << ": ";
    cin >> currentPlayer.name;

    currentPlayer.board = vector<vector<Square>>(10, vector<Square>(10)); // Initialize the board for the player
    currentPlayer.shots = vector<vector<Square>>(10, vector<Square>(10)); // Initialize the shots board for the player

    squareSetup(currentPlayer.board); // Set up the player's board
    squareSetup(currentPlayer.shots); // Set up the player's shots board
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

//-------------------------- Overload Version -------------------------------------

void printBoard(const vector<vector<int>>& boatBoard) // Overloaded version for a vector of ints. Shows where the boats are.
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (boatBoard[i][j] == 1)
            {
                cout << GREEN << "X " << RESET << " "; // boat is hit
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

    int row = rand() % 10; //generate a random row index between 0 and 9
    int column = rand() % 10; //generate a random column index between 0 and 9

    if (boatBoard[row][column] == 1)
    {
        placeRandomBoats(boatsPlaced, numberBoats, boatBoard); 
        return;
    }

    boatBoard[row][column] = 1; // Mark the square as having a boat

    cout << "Boat " << boatsPlaced + 1 << ": " << battleShipBoard[row][column] << endl;

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

    // if (columnText.length() == 1 && isdigit(columnText[0])) //is digit checks for digits from only 0-9, if so 
    // {
    //     columnInput = columnText[0] - '0'; //
    // }
    // else if (columnText == "10")
    // {
    //     columnInput = 10;
    // }

    for (int i = 1; i <= 10; i++) //checks if the column input is within 1-10 and if so set the column input to that value
    {
        if (columnText == to_string(i)) //converts the integer i to a string and compares it to the columnText input to see if it is valid and equal to the columnText input
        {
            columnInput = i;
        }
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

void getTarget(const vector<vector<Square>>& squares, int& rowIndex, int& columnIndex)
{
    bool validGuess = false; //set the guess value to false until hit

    while (!validGuess) //loop until the player picks a valid square that hasn't been guessed yet
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

//------------------------------

void placeManually(Player & player, int boatsPlaced, int numberBoats)
{
    int rowIndex;
    int columnIndex;
    bool onBoard = readSquare(rowIndex, columnIndex);
    
    if (boatsPlaced == numberBoats)
    {
        return;
    }

    cout << "\nPlayer " << player.name << ", place boat " << boatsPlaced + 1 << " of " << numberBoats << endl;

    if (!onBoard)
    {
        placeManually(player, boatsPlaced, numberBoats); // ask again
    }
    else if (player.board[rowIndex][columnIndex].boatPresent)
    {
        cout << "I think you already placed a boat at " << battleShipBoard[rowIndex][columnIndex] << ". PICK A DIFFERENT LOCATION.\n";
        placeManually(player, boatsPlaced, numberBoats);
    }
    else
    {
        player.board[rowIndex][columnIndex].boatPresent = true; //
    }
}

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