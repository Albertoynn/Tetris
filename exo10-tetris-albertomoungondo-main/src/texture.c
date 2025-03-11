#include <GL/gl.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>

#include "texture.h"
#include "tool.h"

// used to translate the 'bytecount' (1,2,3,4) to opengl format
static GLuint ogl_texture_format[] = {GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA};

#define CTOI(C) (*(int *)&C)

// cf my engine:
// http://sleek-think.ovh/websvn/filedetails.php?repname=sleek-engine&path=%2Fsrc%2Fsleek%2Floader%2Ftexture_bmp.cpp
image *texture_load(const char *filename)
{
    unsigned char header[0x36];
    int colorMode, imagePos;
    long imageSize, imageIdx, m_width, m_height;
    unsigned char m_bitCount;

    FILE *in = fopen(filename, "rb");

    if(!in)
    {
        printf("error: couldn't open \"%s\"!\n", filename);
        return nullptr;
    }

    fread(header, 1, 0x36, in);

    if(header[0] != 'B' || header[1] != 'M')
    {
        printf("error: Can't find BMP headler in \"%s\"!\n", filename);
        return nullptr;
    }

    if(CTOI(header[0x1E]) < 0 || CTOI(header[0x1E]) > 3)
    {
        printf("error: \"%s\" unsuported compressed mode %d!\n", filename, CTOI(header[0x1E]));
        return nullptr;
    }

    printf("Load texture: \"%s\" compressed mode %d\n", filename, CTOI(header[0x1E]));

    m_bitCount = CTOI(header[0x1C]);
    if(m_bitCount == 16)
        colorMode = 3;
    else if(m_bitCount == 24)
        colorMode = 3;
    else if(m_bitCount == 32)
        colorMode = 4;
    else
        colorMode = m_bitCount;

    imagePos = CTOI(header[0x0A]);
    imageSize = CTOI(header[0x22]);

    m_width = CTOI(header[0x12]);
    m_height = CTOI(header[0x16]);

    if(!imageSize)
        imageSize = m_height * m_width * (m_bitCount / 8);
    if(!imagePos)
        imagePos = 0x36;

    fseek(in, imagePos, 0);

    image *bmp = (image *)malloc(sizeof(image));
    bmp->width = m_width;
    bmp->height = m_height;
    bmp->byte = colorMode;
    bmp->data = (unsigned char *)malloc(imageSize);

    if(!bmp->data)
    {
        printf("texture: alocation fail\n");
        return nullptr;
    }

    while(fread(bmp->data, 1, imageSize, in))
        ;

    switch(CTOI(header[0x1E]))
    {
        case 0:
            switch(m_bitCount)
            {
                case 16:
                    for(imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode) // bgr >> rgb
                    {
                        unsigned char colorSwap = bmp->data[imageIdx];
                        bmp->data[imageIdx] = bmp->data[imageIdx + 2];     // 2
                        bmp->data[imageIdx + 1] = bmp->data[imageIdx + 1]; // 1
                        bmp->data[imageIdx + 2] = colorSwap;
                    }
                    break;
                case 24:
                    for(imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode) // bgr >> rgb
                    {
                        unsigned char colorSwap = bmp->data[imageIdx];
                        bmp->data[imageIdx] = bmp->data[imageIdx + 2];     // 2
                        bmp->data[imageIdx + 1] = bmp->data[imageIdx + 1]; // 1
                        bmp->data[imageIdx + 2] = colorSwap;
                    }
                    break;
                case 32:
                    for(imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode) // bgr >> rgb
                    {
                        unsigned char colorSwap = bmp->data[imageIdx];
                        bmp->data[imageIdx] = bmp->data[imageIdx + 2];     // 2
                        bmp->data[imageIdx + 1] = bmp->data[imageIdx + 1]; // 1
                        bmp->data[imageIdx + 3] = bmp->data[imageIdx + 3]; // 3
                        bmp->data[imageIdx + 2] = colorSwap;
                    }
                    break;
            }
            break;
        case 1:
            // decompress8BitRLE(bmp->data, imageSize, m_width, m_height, colorMode);
            break;
        case 2:
            // decompress4BitRLE(bmp->data, imageSize, m_width, m_height, colorMode);
            break;
        case 3:
            switch(m_bitCount)
            {
                case 32:
                    for(imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode) // xrgb -> rgb(a = 255)
                    {
                        unsigned char colorSwap = bmp->data[imageIdx + 2];
                        bmp->data[imageIdx] = bmp->data[imageIdx + 3];
                        bmp->data[imageIdx + 2] = bmp->data[imageIdx + 1];
                        bmp->data[imageIdx + 1] = colorSwap;
                        bmp->data[imageIdx + 3] = 255;
                    }
                    break;
                default:
                    break;
            }
            break;
    }

    return bmp;
}

unsigned texture_upload(image *i)
{
    if(!i)
        return 0;

    GLuint gl;

    // build and bind the new texture (for @glTexParameteri & @glTexImage2D)
    glGenTextures(1, &gl);
    glBindTexture(GL_TEXTURE_2D, gl);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // upload texture data

    glTexImage2D(GL_TEXTURE_2D, 0, i->byte, i->width, i->height, 0, ogl_texture_format[i->byte - 1], GL_UNSIGNED_BYTE, i->data);

    printf("texture uploaded\n");

    return gl;
}

void texture_free(image *i)
{
    free(i->data);
    free(i);
}
