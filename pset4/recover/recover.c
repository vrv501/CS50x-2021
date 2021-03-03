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
    else
    {
        FILE *file = fopen(argv[1], "r");
        FILE *img = NULL;
        uint8_t bytes[512];
        int i = 0;
        char *filename = malloc((7 + 1));      //Allocate 7 bytes of memory for string (1 extra byte for null terminator)
        while (fread(bytes, 1, 512, file))
        {
            if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)      //If jpeg image found
            {
                if (img != NULL)                            //If its not first jpeg image
                {
                    fclose(img);
                    i++;
                }
                sprintf(filename, "%03i.jpg", i);          //If it's first jpeg image
                img = fopen(filename, "w");
                fwrite(bytes, 1, 512, img);
            }
            else
            {
                if (img != NULL)       //If there's already an image opened
                {
                    fwrite(bytes, 1, 512, img);
                }
            }
        }
        if (img != NULL)
        {
            fclose(img);
        }
        fclose(file);
        free(filename);     //Close all relevant files and free memory
    }
    return 0;
}
