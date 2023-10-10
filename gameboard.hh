#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH
#include <string>
#include <vector>
// Size of the gameboard
const unsigned int SIZE = 8;

// Width of the left-most column, needed in printing the gameboard
const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard class
class GameBoard
{
public:
    // Constructor: Gameboard with parameter fill_character to get
    // symbol input from user.
    GameBoard(std::string fill_character);

    // Check if the coordinates given are inside of the board.
    bool isInsideBoard(unsigned int startX, unsigned int startY
                       , unsigned int desX, unsigned int desY);

    // Check if there is a piece at the coordinate given.
    bool hasPiece(unsigned int X, unsigned Y);

    // Check if start point and destination point is in a diagonal,
    // and also if there is a piece in the middle point.
    bool isSameDiagonalWithOnePieceInMiddle(unsigned int startX, unsigned int startY
                                            , unsigned int destX, unsigned int destY);

    // Move the piece at the start point to destination point and
    // remove the piece in the middle point.
    void movePieces(unsigned int startX, unsigned int startY
                    , unsigned int destX, unsigned int destY,
                    std::string fill_character);

    // Prints the gameboard (after you have finished the method).
    void print() const;

private:
    // Prints a line with the given length and fill character.
    void print_line(unsigned int length, char fill_character) const;

    // This is the container that stores pieces of the board.
    std::vector<std::vector<std::string>> board;
};

#endif // GAMEBOARD_HH
