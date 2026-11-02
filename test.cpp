#include <iostream>
#include <cctype>

#include "headerTest.h"

using namespace std;


int main()
{
    char rowInput = '\0';
    int colInput = 0;
    int boatsFound = 0;

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // vectors for tracking boat placement, hits, misses, and guessed squares
    vector<vector<bool>> occupied(10, vector<bool>(10, false));
    vector<vector<bool>> hitBoard(10, vector<bool>(10, false));
    vector<vector<bool>> missBoard(10, vector<bool>(10, false));
    vector<vector<bool>> guessedBoard(10, vector<bool>(10, false));

    cout << "Battle Ship Board: " << endl; // delete after testing
    cout << "Random boat placement (10 boats):" << endl; // delete after testing

    placeRandomBoats(0, occupied);

    cout << "\nInitial board:\n"; // delete after testing
    printColoredBoard(battleShipBoard, hitBoard, missBoard);

    while (boatsFound < 10)
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

    cout << "\nYou sank all 10 boats! You win!\n";

    return 0;
} 