#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BLOCK_SIZE = 512;
int fileNumber = 0;
int openFile = 0;

typedef uint8_t BYTE;

FILE *JPEG = NULL;

int main(int argc, char *argv[])
{
    char *fileName = malloc(8);
    //check for argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //remember mounted image
    char *image = argv[1];

    //open mounted image
    FILE *card = fopen(image, "r");
    if (card == NULL)
    {
        printf("Could not open %s\n.", image);
        free(fileName);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];


    //Repeat untill the end
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, card) == BLOCK_SIZE)
    //Read 512 bytes into buffer
    {
        //If you find JPEG start new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(fileName, "%03i.jpg", fileNumber);
            JPEG = fopen(fileName, "w");
            if (JPEG == NULL)
            {
                printf("Could not open file.\n");
                free(fileName);
                return 3;
            }
            fileNumber++;
            openFile = 1;
            if (openFile == 1)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, JPEG);
            }
            //If you find new JPEG close current one and open new file
            else if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                openFile = 0;
                fclose(JPEG);
                fopen(fileName, "w");
                if (JPEG == NULL)
                {
                    printf("Could not open file.\n");
                    free(fileName);
                    return 4;
                }
            }
        }
        else if (openFile == 1)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, JPEG);
        }
    }
    free(fileName);
    fclose(JPEG);

    //Close all remaining open files
}