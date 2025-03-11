#ifndef __TEXTTURE_HEADER__
#define __TEXTTURE_HEADER__

typedef struct image
{
        unsigned char *data;
        unsigned width;
        unsigned height;
        unsigned char byte;
} image;

// allocate an image, load a bmp and fill the image
image *texture_load(const char *filename);

// generate an opengl texture id and upload the picture data to the gpu
unsigned texture_upload(image *);

// free an image and it's member
void texture_free(image *);

#endif // __TEXTTURE_HEADER__
