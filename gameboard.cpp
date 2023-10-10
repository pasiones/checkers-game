#include "gameboard.hh"
#include <iostream>

GameBoard::GameBoard(std::string fill_character)
    {
    board = std::vector<std::vector<std::string>>
            (SIZE, std::vector<std::string>(SIZE, "  "));
    // Rows 1 and 2
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            board.at(i).at(j) = fill_character + " ";
        }
    }

    // Rows 3 to 6
    for (int i = 2; i < 6; ++i)
    {
        board.at(i).at(0) = fill_character + " ";
        board.at(i).at(1) = fill_character + " ";
        board.at(i).at(6) = fill_character + " ";
        board.at(i).at(7) = fill_character + " ";
    }

    // Rows 7 and 8
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            board.at(i + 6).at(j) = fill_character + " ";
        }
    }
}

bool GameBoard::isInsideBoard(unsigned int startX, unsigned int startY,
                              unsigned int destX, unsigned int destY)
{
    if (startX < 1 || startX > 8
        || startY < 1 || startY > 8 || destX < 1 || destY > 8)
    {
        return false;
    }
    return true;
}

bool GameBoard::hasPiece(unsigned int X, unsigned int Y)
{
    return board.at(Y-1).at(X-1) != "  ";
}

bool GameBoard::isSameDiagonalWithOnePieceInMiddle(unsigned int startX,
            unsigned int startY, unsigned int destX, unsigned int destY)
{
    int dx = destX - startX;
    int dy = destY - startY;

    // Check if the move is diagonal.
    if (abs(dx) != abs(dy)) {
        return false;
    }

    // Determine the direction of the diagonal.
    dx = (dx > 0) ? 1 : -1;
    dy = (dy > 0) ? 1 : -1;

    // Get the coordinate of the middle square.
    unsigned int midX = startX + dx;
    unsigned int midY = startY + dy;

    // Check if there is exactly one piece in the middle of the start and
    // destination points.
    if (!hasPiece(midX, midY))
    {
        return false;
    }
    else if (midX + dx != destX && midY + dy != destY)
    {
        return false;
    }
    return true;
}

void GameBoard::movePieces(unsigned int startX, unsigned int startY,
                           unsigned int destX, unsigned int destY, std::string fill_character)
{
    int dx = destX - startX;
    int dy = destY - startY;

    // Determine the direction of the diagonal.
    dx = (dx > 0) ? 1 : -1;
    dy = (dy > 0) ? 1 : -1;

    // Get the coordinate of the middle square.
    unsigned int midX = startX + dx;
    unsigned int midY = startY + dy;

    // Remove the pieces at the start and middle points.
    // Add piece to destination point.
    board.at(midY - 1).at(midX - 1) = "  ";
    board.at(startY - 1).at(startX - 1) = "  ";
    board.at(destY - 1).at(destX - 1) = fill_character + " ";
}

void GameBoard::print() const
{
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Printing title row
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Printing the actual content of the gameboard
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            std::cout << board.at(i).at(j);
        }
        std::cout << "|" << std::endl;

    // Printing lower border
    }
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}


void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}
