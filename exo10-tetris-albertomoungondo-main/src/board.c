#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_height 4

unsigned min(unsigned i, unsigned j)
{
    // Return the minimum of two unsigned integers
    return 0;
}

unsigned max(unsigned i, unsigned j)
{
    // Return the maximum of two unsigned integers
    return 0;
}

board *board_new(unsigned x, unsigned y)
{
    // Create a new Tetris board with given dimensions
    // Allocate memory for the board structure and its data
    // Initialize the board with empty spaces
    return nullptr;
}

board *board_copy(board *p)
{
    // Create a deep copy of the given board
    // Allocate new memory and copy all data
    return nullptr;
}

void board_print(board *p)
{
    // Print the current state of the board to the console
    // Include borders and use appropriate characters for pieces
}

void board_free(board *p)
{
    // Free all memory associated with the board
    // Including the 2D array of board data
}

bool board_inside(board *b, piece *p, unsigned x, unsigned y)
{
    // Check if a piece is entirely within the board boundaries
    // Return true if inside, false otherwise
    return false;
}

int same(char a, char b)
{
    // Check if two characters represent occupied spaces
    // Return true if both are non-empty
    return false;
}

bool board_intersect(board *b, piece *p, unsigned x, unsigned y)
{
    // Check if a piece intersects with existing pieces on the board
    // or goes out of bounds
    // Return true if there's an intersection, false otherwise
    return false;
}

void board_insert(board *b, piece *p, unsigned x, unsigned y)
{
    // Insert a piece into the board at the specified position
    // Only insert if the piece is entirely within the board
}

int board_clear(board *b)
{
    // Clear any full lines on the board
    // Move all lines above a cleared line down
    // Return the number of lines cleared
    return 0;
}

void board_erase(board *p, unsigned y)
{
    // Erase a specific line from the board
    // Move all lines above it down by one
    // Clear the top line
}

piece *piece_new(unsigned p)
{
    // Create a new Tetris piece based on the given index
    // Initialize the piece's shape and data
    return nullptr;
}

void piece_print(piece *p)
{
    // Print the current shape of the piece to the console
}

piece *piece_copy(piece *p)
{
    // Create a deep copy of the given piece
    // Allocate new memory and copy all data
    return nullptr;
}

void piece_rotate_left(piece *p)
{
    // Rotate the piece 90 degrees counterclockwise
    // Update the piece's dimensions and data accordingly
}

void piece_rotate_right(piece *p)
{
    // Rotate the piece 90 degrees clockwise
    // Update the piece's dimensions and data accordingly
}

void piece_free(piece *p)
{
    // Free all memory associated with the piece
    // Including the 2D array of piece data
}
