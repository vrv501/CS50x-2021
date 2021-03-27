#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s image\n", argv[0]);      //No command-line input
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    FILE *img = NULL;
    uint8_t imgContent[512];
    int imgNum = 0;

    // Allocate 7 bytes of memory for string (1 extra byte for null terminator)
    // imgName here is 001.jpg - 7 characters + 1 null terminator
    char *imgName = malloc((7 + 1));

    while (fread(imgContent, 1, 512, file))
    {
        // If new jpeg image found
        if (imgContent[0] == 0xff && imgContent[1] == 0xd8 && imgContent[2] == 0xff && (imgContent[3] & 0xf0) == 0xe0)
        {
            //If an image is already opened, then close it
            if (img != NULL)
            {
                fclose(img);
                imgNum++;
            }

            // Open a new image and write into it
            sprintf(imgName, "%03i.jpg", imgNum);
            img = fopen(imgName, "w");
            fwrite(imgContent, 1, 512, img);
        }

        else
        {
            //If there's already an image opened, then write into it
            if (img != NULL)
            {
                fwrite(imgContent, 1, 512, img);
            }
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(file);
    free(imgName);

    return 0;
}
