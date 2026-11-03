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

void printColoredBoard(const vector<vector<string>>& board,
                       const vector<vector<bool>>& hit,
                       const vector<vector<bool>>& miss)
{
    for (int i = 0; i < 10; i++)
    {
        for (int c = 0; c < 10; c++)
        {
            if (hit[i][c])
            {
                cout << GREEN << board[i][c] << RESET << " ";
            }
            else if (miss[i][c])
            {
                cout << RED << board[i][c] << RESET << " ";
            }
            else
            {
                cout << board[i][c] << " ";
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

void placeRandomBoats(int boatsPlaced, int numberBoats, vector<vector<bool>>& occupied)
{
    if (boatsPlaced == numberBoats)
    {
        return;
    }

    int row = rand() % 10;
    int col = rand() % 10;

    if (occupied[row][col])
    {
        placeRandomBoats(boatsPlaced, numberBoats, occupied);
        return;
    }

    occupied[row][col] = true;
    cout << "Boat " << boatsPlaced + 1 << ": "
         << battleShipBoard[row][col] << endl;

    placeRandomBoats(boatsPlaced + 1, numberBoats, occupied);
}

//-------------------------------------------------------------------------------

int main()
{
    char rowInput = '\0';
    int colInput = 0;
    int boatsFound = 0;
    int numberBoats = 10; // Default number of boats
    
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // vectors for tracking boat placement, hits, misses, and guessed squares
    vector<vector<bool>> occupied(10, vector<bool>(10, false));
    vector<vector<bool>> hitBoard(10, vector<bool>(10, false));
    vector<vector<bool>> missBoard(10, vector<bool>(10, false));
    vector<vector<bool>> guessedBoard(10, vector<bool>(10, false));

    shipAmount(numberBoats); // Get the number of boats from the user
    
    cout << "Battle Ship Board: " << endl; // delete after testing
    cout << "Random boat placement (" << numberBoats << " boats):" << endl; // delete after testing

    placeRandomBoats(0, numberBoats, occupied);

    cout << "\nInitial board:\n"; // delete after testing

    printColoredBoard(battleShipBoard, hitBoard, missBoard);

    while (boatsFound < numberBoats)
    {
        cout << "\nWhat row would you like to attack? (A-J): ";
        cin >> rowInput;
        cout << "What column would you like to attack? (1-10): ";
        cin >> colInput;

        char normalizedRow = toupper(rowInput);
        int rowIndex = normalizedRow - 'A';
        int colIndex = colInput - 1;

        if (normalizedRow >= 'A' && normalizedRow <= 'J' && colInput >= 1 && colInput <= 10)
        {
            if (guessedBoard[rowIndex][colIndex])
            {
                cout << "You already guessed " << battleShipBoard[rowIndex][colIndex]
                     << ". Pick a different square.\n";
            }
            else
            {
                guessedBoard[rowIndex][colIndex] = true;

                if (occupied[rowIndex][colIndex])
                {
                    if (!hitBoard[rowIndex][colIndex])
                    {
                        hitBoard[rowIndex][colIndex] = true;
                        boatsFound++;
                    }

                    cout << GREEN << "HIT! You hit " << battleShipBoard[rowIndex][colIndex] << RESET << endl;
                }
                else
                {
                    missBoard[rowIndex][colIndex] = true;
                    cout << RED << "MISS! There was no boat at " << battleShipBoard[rowIndex][colIndex] << RESET << endl;
                }

                cout << "\nUpdated board:\n";
                printColoredBoard(battleShipBoard, hitBoard, missBoard);
            }
        }
        else
        {
            cout << "Invalid spot. Please enter a row from A-J and a column from 1-10." << endl;
        }
    }

        cout << "\nYou sank all " << numberBoats << " boats! You win!\n";


    return 0;
} 