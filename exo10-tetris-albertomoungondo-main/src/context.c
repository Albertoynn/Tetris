#include "context.h"
#include "board.h"
#include <GL/gl.h>

void context_clear()
{
    // Clear the screen and set up initial OpenGL state
    // This function should:
    // - Set the background color
    // - Clear color and depth buffers
    // - Enable depth testing and set depth function
    // - Enable texturing
    // - Set up the camera projection and position
    glTranslatef(-10.f, 16.5f, -20.0f);
    glRotatef(-10.f, 1.f, 0, 0.f);
}

void render_board(board *b)
{
    // Render the Tetris game board
    // This function should:
    // - Iterate through the board data
    // - Draw cubes for non-empty cells
    // - Use appropriate colors for different piece types
}

void render_piece(piece *p, float x, float y)
{
    // Render a single Tetris piece
    // This function should:
    // - Iterate through the piece data
    // - Draw cubes for non-empty cells of the piece
    // - Position the piece at the given x and y coordinates
}

void context_drawcube(char color, float x, float y, float scale)
{
    // Draw a single colored cube at a specified position
    // This function should:
    // - Set the cube's position and scale
    // - Set the cube's color based on the piece type
    // - Call a function to render the cube geometry
}

void context_cube()
{
    // Render the geometry for a single cube
    // This function should:
    // - Define vertex positions and texture coordinates for a cube
    // - Use appropriate OpenGL calls to render the cube faces
    // You are allowed to use Opengl 1.1
}

void context_image()
{
    // Render a full-screen textured quad
    // This function should:
    // - Set up orthographic projection
    // - Draw a quad covering the entire screen
    // - Apply a texture to the quad
}

void render_box(board *b)
{
    // Render the border around the Tetris game board
    // This function should:
    // - Draw cubes around the perimeter of the game board
    // - Use a specific color or texture for the border
}

const char *GLErrorString(GLenum errorCode)
{
    static const struct
    {
            GLenum code;
            const char *string;
    } errors[] = {
        {GL_NO_ERROR, "no error"},
        {GL_INVALID_ENUM, "invalid enumerant"},
        {GL_INVALID_VALUE, "invalid value"},
        {GL_INVALID_OPERATION, "invalid operation"},
        {GL_STACK_OVERFLOW, "stack overflow"},
        {GL_STACK_UNDERFLOW, "stack underflow"},
        {GL_OUT_OF_MEMORY, "out of memory"},
        {0, nullptr}
    };

    int i;

    for(i = 0; errors[i].string; i++)
        if(errors[i].code == errorCode)
            return errors[i].string;

    return "";
}
