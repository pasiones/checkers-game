/* Checkers (for one player)
 *
 * Desc:
 *   This program implements a checkers game for one player. The size of
 * the gameboard is 8 x 8, and it will filled with empty spaces and
 * game pieces (character given by the user).
 *   At first, the gameboard is filled with pieces, but there is an
 * empty area of size 4 x 4 in the middle of the gameboard. The aim is to
 * remove pieces such that only one of them is left. A piece can be moved
 * diagonally over another piece, whereupon the piece that was skipped
 * will be removed.
 *   On each round, the user is asked for two points (four coordinates):
 * the piece to be moved and its target position. The program checks if
 * if the move is possible.
 *   The program terminates when there is only one piece left or if the
 * user gives a quitting command ('q' or 'Q'). In such case the program
 * prints the number of moves made and that of pieces left.
 *
 * Program author
 * Name: Dat Minh Lam
 * Student number: 151395774
 * UserID: vhdala
 * E-Mail: datminh.lam@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 * */
#include "gameboard.hh"
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

//A string that split the line
vector<string> split(const string& str,char separator,bool ignore_empty = false) {
    vector<string> parts;
    string current_part;
    for (const char&c : str) {
        if (c == separator) {
            if(!ignore_empty || ! current_part.empty()) {
                parts.push_back(current_part);
            }
            current_part.clear();

        } else {
            current_part += c;
        }
    }

    if (!ignore_empty || !current_part.empty()) {
        parts.push_back(current_part);
    }

    return parts;
}

// Check if a string if a number.
bool isNumber(string s)
{
    for (unsigned int i = 0; i < s.size(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}


int main()
{
    // Initialize the pieces counter and moves counter.
    // Ask the user for gameboard's character input.
    // Print the board at the beginning.
    unsigned int pieces_counter = 48;
    unsigned int moves = 0;
    string character;
    cout << "Enter piece character: ";
    getline(cin, character);
    GameBoard gameboard(character);
    gameboard.print();

    while (true)
    {
        string user_input;
        unsigned int startX = 0, startY = 0, destX = 0, destY = 0;
        cout << "Enter start point (x, y) and destination point (x, y), or q to quit: ";
        getline(cin,user_input);
        vector<string> inputs = split(user_input, ' ');

        // Check if the input is 'q' to quit
        if (user_input == "q" or user_input == "Q")
        {
            cout << moves << " move(s) made." << endl;
            cout << pieces_counter << " piece(s) left." << endl;
            break;
        }

        // Check if the input has more or less than 4 elements.
        if (inputs.size() != 4)
        {
            cout << "Invalid start/destination point." << endl;
            continue;
        }

        // Check if all 4 inputs are integers.
        else if (!isNumber(inputs[0]) || !isNumber(inputs[1])
                   || !isNumber(inputs[2]) || !isNumber(inputs[3]))
        {
            cout << "Invalid start/destination point." << endl;
            continue;
        }

        // Convert all string numbers to integers.
        startX = stoi(inputs[0]);
        startY = stoi(inputs[1]);
        destX = stoi(inputs[2]);
        destY = stoi(inputs[3]);

        // Check if the coordinates are inside the board.
        if (!gameboard.isInsideBoard(startX, startY, destX, destY))
        {
            cout << "Invalid start/destination point." << endl;
            continue;
        }

        // Check if there is a piece at the start point
        // or no piece at destination point. Also check if
        // the start and destination points are in a diagonal
        // and there is a piece at the middle point.
        else if (!gameboard.hasPiece(startX, startY)
                || gameboard.hasPiece(destX, destY)
                || !gameboard.isSameDiagonalWithOnePieceInMiddle(startX, startY, destX, destY))
        {
            cout << "Cannot move from start point to destination point." << endl;
            continue;
        }

        // Move the piece, print the current state of the board,
        // decrement the pieces counter and increment the moves counter.
        gameboard.movePieces(startX, startY, destX, destY, character);
        gameboard.print();
        pieces_counter -= 1;
        moves += 1;
    }
    return 0;
}
