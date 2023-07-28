#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];
    char *outfile = calloc(7, sizeof(char));
    
    
    int i = 0;
    sprintf(outfile, "%03i.jpg", i);

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // Read infile's block
    BYTE *block = calloc(512, sizeof(BYTE));
    
    int blocksize = fread(block, sizeof(BYTE),  512, inptr);
    
    while (blocksize == 512)
    {
        if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && ((block[3] & 0xf0) == 0xe0))
        {
            fclose(outptr);
            sprintf(outfile, "%03i.jpg", i);
            i++;
            outptr = fopen(outfile, "w");
            fwrite(block, sizeof(BYTE), blocksize, outptr);
            blocksize = fread(block, sizeof(BYTE),  512, inptr);
        }
        else
        {
            if (i > 0)
            {
                fwrite(block, sizeof(BYTE),  blocksize, outptr);
                blocksize = fread(block, sizeof(BYTE),  512, inptr);
            }
            else
            {
                blocksize = fread(block, sizeof(BYTE),  512, inptr);
            }
        }
        
    }

    fwrite(block, sizeof(BYTE),  blocksize, outptr);

    
    fclose(outptr);
    fclose(inptr);

    free(block);

    return 0;
}