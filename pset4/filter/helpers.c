#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            BYTE avg = ((int)image[i][j].rgbtBlue + (int)image[i][j].rgbtGreen + (int)image[i][j].rgbtRed) / 3;
            
            if (((int)image[i][j].rgbtBlue + (int)image[i][j].rgbtGreen + (int)image[i][j].rgbtRed) % 3 > 1)
            {
                image[i][j].rgbtBlue = avg + 1;
                image[i][j].rgbtGreen = avg + 1;
                image[i][j].rgbtRed = avg + 1;
            }
            else
            {
                image[i][j].rgbtBlue = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtRed = avg;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE aux;
            aux.rgbtBlue = image[i][j].rgbtBlue;
            aux.rgbtGreen = image[i][j].rgbtGreen;
            aux.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = aux.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = aux.rgbtGreen;
            image[i][width - j - 1].rgbtRed = aux.rgbtRed;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE auximg[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auximg[i][j].rgbtBlue = image[i][j].rgbtBlue;
            auximg[i][j].rgbtGreen = image[i][j].rgbtGreen;
            auximg[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //middle
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i - 1; x < i + 2; x++)
                {
                    for (int y = j - 1; y < j + 2; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 9;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 9;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 9;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 9;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 9;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 9;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 9;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 9;

                image[i][j].rgbtRed += divrest.rgbtRed / 9;

                if (divrest.rgbtBlue % 9 > 4)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 9 > 4)
                {
                    image[i][j].rgbtGreen++;
                }

                if (divrest.rgbtRed % 9 > 4)
                {
                    image[i][j].rgbtRed++;
                }
            }

            //top edge
            if (i == 0 && j != 0 && j != width - 1)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i; x < i + 2; x++)
                {
                    for (int y = j - 1; y < j + 2; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 6;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 6;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 6;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 6;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 6;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 6;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 6;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 6;

                image[i][j].rgbtRed += divrest.rgbtRed / 6;

                if (divrest.rgbtBlue % 6 >= 3)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 6 >= 3)
                {
                    image[i][j].rgbtGreen++;
                }
                
                if (divrest.rgbtRed % 6 >= 3)
                {
                    image[i][j].rgbtRed++;
                }
            }
            //bottom edge
            if (i == height - 1 && j != 0 && j != width - 1)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i - 1; x < i + 1; x++)
                {
                    for (int y = j - 1; y < j + 2; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 6;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 6;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 6;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 6;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 6;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 6;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 6;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 6;

                image[i][j].rgbtRed += divrest.rgbtRed / 6;

                if (divrest.rgbtBlue % 6 >= 3)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 6 >= 3)
                {
                    image[i][j].rgbtGreen++;
                }
                
                if (divrest.rgbtRed % 6 >= 3)
                {
                    image[i][j].rgbtRed++;
                }
            }
            //left edge
            if (i != 0 && i != height - 1 && j == 0)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i - 1; x < i + 2; x++)
                {
                    for (int y = j; y < j + 2; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 6;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 6;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 6;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 6;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 6;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 6;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 6;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 6;

                image[i][j].rgbtRed += divrest.rgbtRed / 6;

                if (divrest.rgbtBlue % 6 >= 3)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 6 >= 3)
                {
                    image[i][j].rgbtGreen++;
                }
                
                if (divrest.rgbtRed % 6 >= 3)
                {
                    image[i][j].rgbtRed++;
                }
            }
            //right edge
            if (i != 0 && i != height - 1 && j == width - 1)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i - 1; x < i + 2; x++)
                {
                    for (int y = j - 1; y < j + 1; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 6;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 6;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 6;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 6;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 6;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 6;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 6;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 6;

                image[i][j].rgbtRed += divrest.rgbtRed / 6;

                if (divrest.rgbtBlue % 6 >= 3)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 6 >= 3)
                {
                    image[i][j].rgbtGreen++;
                }
                
                if (divrest.rgbtRed % 6 >= 3)
                {
                    image[i][j].rgbtRed++;
                }
            }
            // Top-left corner
            if (i == 0 && j == 0)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i; x < i + 2; x++)
                {
                    for (int y = j; y < j + 2; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 4;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 4;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 4;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 4;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 4;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 4;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 4;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 4;

                image[i][j].rgbtRed += divrest.rgbtRed / 4;

                if (divrest.rgbtBlue % 4 >= 2)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 4 >= 2)
                {
                    image[i][j].rgbtGreen++;
                }
                
                if (divrest.rgbtRed % 4 >= 2)
                {
                    image[i][j].rgbtRed++;
                }
            }
            // Top-right corner
            if (i == 0 && j == width - 1)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i; x < i + 2; x++)
                {
                    for (int y = j - 1; y < j + 1; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 4;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 4;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 4;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 4;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 4;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 4;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 4;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 4;

                image[i][j].rgbtRed += divrest.rgbtRed / 4;

                if (divrest.rgbtBlue % 4 >= 2)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 4 >= 2)
                {
                    image[i][j].rgbtGreen++;
                }
                
                if (divrest.rgbtRed % 4 >= 2)
                {
                    image[i][j].rgbtRed++;
                }
            }
            //bottom-left corner
            if (i == height - 1 && j == 0)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i - 1; x < i + 1; x++)
                {
                    for (int y = j; y < j + 2; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 4;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 4;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 4;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 4;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 4;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 4;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 4;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 4;

                image[i][j].rgbtRed += divrest.rgbtRed / 4;

                if (divrest.rgbtBlue % 4 >= 2)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 4 >= 2)
                {
                    image[i][j].rgbtGreen++;
                }
                
                if (divrest.rgbtRed % 4 >= 2)
                {
                    image[i][j].rgbtRed++;
                }
            }
            //bottom-right corner
            if (i == height - 1 && j == width - 1)
            {
                RGBTRIPLE divrest;
                divrest.rgbtBlue = 0;
                divrest.rgbtGreen = 0;
                divrest.rgbtRed = 0;

                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 0;

                for (int x = i - 1; x < i + 1; x++)
                {
                    for (int y = j - 1; y < j + 1; y++)
                    {
                        image[i][j].rgbtBlue += auximg[x][y].rgbtBlue / 4;
                        divrest.rgbtBlue += auximg[x][y].rgbtBlue % 4;

                        image[i][j].rgbtGreen += auximg[x][y].rgbtGreen / 4;
                        divrest.rgbtGreen += auximg[x][y].rgbtGreen % 4;

                        image[i][j].rgbtRed += auximg[x][y].rgbtRed / 4;
                        divrest.rgbtRed += auximg[x][y].rgbtRed % 4;
                    }
                }
                image[i][j].rgbtBlue += divrest.rgbtBlue / 4;

                image[i][j].rgbtGreen += divrest.rgbtGreen / 4;

                image[i][j].rgbtRed += divrest.rgbtRed / 4;

                if (divrest.rgbtBlue % 4 >= 2)
                {
                    image[i][j].rgbtBlue++;
                }

                if (divrest.rgbtGreen % 4 >= 2)
                {
                    image[i][j].rgbtGreen++;
                }
                
                if (divrest.rgbtRed % 4 >= 2)
                {
                    image[i][j].rgbtRed++;
                }
            }
            
            
        }
    }
    
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE auximg[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auximg[i][j].rgbtBlue = image[i][j].rgbtBlue;
            auximg[i][j].rgbtGreen = image[i][j].rgbtGreen;
            auximg[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //middle
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i - 1][j - 1].rgbtBlue * (-1);
                GxBlue += auximg[i][j - 1].rgbtBlue * (-2);
                GxBlue += auximg[i + 1][j - 1].rgbtBlue * (-1);
                GxBlue += auximg[i - 1][j + 1].rgbtBlue * (1);
                GxBlue += auximg[i][j + 1].rgbtBlue * (2);
                GxBlue += auximg[i + 1][j + 1].rgbtBlue * (1);

                GxGreen += auximg[i - 1][j - 1].rgbtGreen * (-1);
                GxGreen += auximg[i][j - 1].rgbtGreen * (-2);
                GxGreen += auximg[i + 1][j - 1].rgbtGreen * (-1);
                GxGreen += auximg[i - 1][j + 1].rgbtGreen * (1);
                GxGreen += auximg[i][j + 1].rgbtGreen * (2);
                GxGreen += auximg[i + 1][j + 1].rgbtGreen * (1);

                GxRed += auximg[i - 1][j - 1].rgbtRed * (-1);
                GxRed += auximg[i][j - 1].rgbtRed * (-2);
                GxRed += auximg[i + 1][j - 1].rgbtRed * (-1);
                GxRed += auximg[i - 1][j + 1].rgbtRed * (1);
                GxRed += auximg[i][j + 1].rgbtRed * (2);
                GxRed += auximg[i + 1][j + 1].rgbtRed * (1);

                GyBlue += auximg[i - 1][j - 1].rgbtBlue * (-1);
                GyBlue += auximg[i - 1][j].rgbtBlue * (-2);
                GyBlue += auximg[i - 1][j + 1].rgbtBlue * (-1);
                GyBlue += auximg[i + 1][j - 1].rgbtBlue * (1);
                GyBlue += auximg[i + 1][j].rgbtBlue * (2);
                GyBlue += auximg[i + 1][j + 1].rgbtBlue * (1);

                GyGreen += auximg[i - 1][j - 1].rgbtGreen * (-1);
                GyGreen += auximg[i - 1][j].rgbtGreen * (-2);
                GyGreen += auximg[i - 1][j + 1].rgbtGreen * (-1);
                GyGreen += auximg[i + 1][j - 1].rgbtGreen * (1);
                GyGreen += auximg[i + 1][j].rgbtGreen * (2);
                GyGreen += auximg[i + 1][j + 1].rgbtGreen * (1);

                GyRed += auximg[i - 1][j - 1].rgbtRed * (-1);
                GyRed += auximg[i - 1][j].rgbtRed * (-2);
                GyRed += auximg[i - 1][j + 1].rgbtRed * (-1);
                GyRed += auximg[i + 1][j - 1].rgbtRed * (1);
                GyRed += auximg[i + 1][j].rgbtRed * (2);
                GyRed += auximg[i + 1][j + 1].rgbtRed * (1);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }

            }

            //top edge
            if (i == 0 && j != 0 && j != width - 1)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i][j - 1].rgbtBlue * (-2);
                GxBlue += auximg[i + 1][j - 1].rgbtBlue * (-1);
                GxBlue += auximg[i][j + 1].rgbtBlue * (2);
                GxBlue += auximg[i + 1][j + 1].rgbtBlue * (1);

                GxGreen += auximg[i][j - 1].rgbtGreen * (-2);
                GxGreen += auximg[i + 1][j - 1].rgbtGreen * (-1);
                GxGreen += auximg[i][j + 1].rgbtGreen * (2);
                GxGreen += auximg[i + 1][j + 1].rgbtGreen * (1);

                GxRed += auximg[i][j - 1].rgbtRed * (-2);
                GxRed += auximg[i + 1][j - 1].rgbtRed * (-1);
                GxRed += auximg[i][j + 1].rgbtRed * (2);
                GxRed += auximg[i + 1][j + 1].rgbtRed * (1);


                GyBlue += auximg[i + 1][j - 1].rgbtBlue * (1);
                GyBlue += auximg[i + 1][j].rgbtBlue * (2);
                GyBlue += auximg[i + 1][j + 1].rgbtBlue * (1);

                GyGreen += auximg[i + 1][j - 1].rgbtGreen * (1);
                GyGreen += auximg[i + 1][j].rgbtGreen * (2);
                GyGreen += auximg[i + 1][j + 1].rgbtGreen * (1);

                GyRed += auximg[i + 1][j - 1].rgbtRed * (1);
                GyRed += auximg[i + 1][j].rgbtRed * (2);
                GyRed += auximg[i + 1][j + 1].rgbtRed * (1);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }
            }
            //bottom edge
            if (i == height - 1 && j != 0 && j != width - 1)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i - 1][j - 1].rgbtBlue * (-1);
                GxBlue += auximg[i][j - 1].rgbtBlue * (-2);
                GxBlue += auximg[i - 1][j + 1].rgbtBlue * (1);
                GxBlue += auximg[i][j + 1].rgbtBlue * (2);

                GxGreen += auximg[i - 1][j - 1].rgbtGreen * (-1);
                GxGreen += auximg[i][j - 1].rgbtGreen * (-2);
                GxGreen += auximg[i - 1][j + 1].rgbtGreen * (1);
                GxGreen += auximg[i][j + 1].rgbtGreen * (2);

                GxRed += auximg[i - 1][j - 1].rgbtRed * (-1);
                GxRed += auximg[i][j - 1].rgbtRed * (-2);
                GxRed += auximg[i - 1][j + 1].rgbtRed * (1);
                GxRed += auximg[i][j + 1].rgbtRed * (2);

                GyBlue += auximg[i - 1][j - 1].rgbtBlue * (-1);
                GyBlue += auximg[i - 1][j].rgbtBlue * (-2);
                GyBlue += auximg[i - 1][j + 1].rgbtBlue * (-1);

                GyGreen += auximg[i - 1][j - 1].rgbtGreen * (-1);
                GyGreen += auximg[i - 1][j].rgbtGreen * (-2);
                GyGreen += auximg[i - 1][j + 1].rgbtGreen * (-1);

                GyRed += auximg[i - 1][j - 1].rgbtRed * (-1);
                GyRed += auximg[i - 1][j].rgbtRed * (-2);
                GyRed += auximg[i - 1][j + 1].rgbtRed * (-1);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }
            }
            //left edge
            if (i != 0 && i != height - 1 && j == 0)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i - 1][j + 1].rgbtBlue * (1);
                GxBlue += auximg[i][j + 1].rgbtBlue * (2);
                GxBlue += auximg[i + 1][j + 1].rgbtBlue * (1);

                GxGreen += auximg[i - 1][j + 1].rgbtGreen * (1);
                GxGreen += auximg[i][j + 1].rgbtGreen * (2);
                GxGreen += auximg[i + 1][j + 1].rgbtGreen * (1);

                GxRed += auximg[i - 1][j + 1].rgbtRed * (1);
                GxRed += auximg[i][j + 1].rgbtRed * (2);
                GxRed += auximg[i + 1][j + 1].rgbtRed * (1);

                GyBlue += auximg[i - 1][j].rgbtBlue * (-2);
                GyBlue += auximg[i - 1][j + 1].rgbtBlue * (-1);
                GyBlue += auximg[i + 1][j].rgbtBlue * (2);
                GyBlue += auximg[i + 1][j + 1].rgbtBlue * (1);

                GyGreen += auximg[i - 1][j].rgbtGreen * (-2);
                GyGreen += auximg[i - 1][j + 1].rgbtGreen * (-1);
                GyGreen += auximg[i + 1][j].rgbtGreen * (2);
                GyGreen += auximg[i + 1][j + 1].rgbtGreen * (1);

                GyRed += auximg[i - 1][j].rgbtRed * (-2);
                GyRed += auximg[i - 1][j + 1].rgbtRed * (-1);
                GyRed += auximg[i + 1][j].rgbtRed * (2);
                GyRed += auximg[i + 1][j + 1].rgbtRed * (1);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }
            }
            //right edge
            if (i != 0 && i != height - 1 && j == width - 1)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i - 1][j - 1].rgbtBlue * (-1);
                GxBlue += auximg[i][j - 1].rgbtBlue * (-2);
                GxBlue += auximg[i + 1][j - 1].rgbtBlue * (-1);

                GxGreen += auximg[i - 1][j - 1].rgbtGreen * (-1);
                GxGreen += auximg[i][j - 1].rgbtGreen * (-2);
                GxGreen += auximg[i + 1][j - 1].rgbtGreen * (-1);

                GxRed += auximg[i - 1][j - 1].rgbtRed * (-1);
                GxRed += auximg[i][j - 1].rgbtRed * (-2);
                GxRed += auximg[i + 1][j - 1].rgbtRed * (-1);

                GyBlue += auximg[i - 1][j - 1].rgbtBlue * (-1);
                GyBlue += auximg[i - 1][j].rgbtBlue * (-2);
                GyBlue += auximg[i + 1][j - 1].rgbtBlue * (1);
                GyBlue += auximg[i + 1][j].rgbtBlue * (2);

                GyGreen += auximg[i - 1][j - 1].rgbtGreen * (-1);
                GyGreen += auximg[i - 1][j].rgbtGreen * (-2);
                GyGreen += auximg[i + 1][j - 1].rgbtGreen * (1);
                GyGreen += auximg[i + 1][j].rgbtGreen * (2);

                GyRed += auximg[i - 1][j - 1].rgbtRed * (-1);
                GyRed += auximg[i - 1][j].rgbtRed * (-2);
                GyRed += auximg[i + 1][j - 1].rgbtRed * (1);
                GyRed += auximg[i + 1][j].rgbtRed * (2);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }
            }
            // Top-left corner
            if (i == 0 && j == 0)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i][j + 1].rgbtBlue * (2);
                GxBlue += auximg[i + 1][j + 1].rgbtBlue * (1);

                GxGreen += auximg[i][j + 1].rgbtGreen * (2);
                GxGreen += auximg[i + 1][j + 1].rgbtGreen * (1);

                GxRed += auximg[i][j + 1].rgbtRed * (2);
                GxRed += auximg[i + 1][j + 1].rgbtRed * (1);

                GyBlue += auximg[i + 1][j].rgbtBlue * (2);
                GyBlue += auximg[i + 1][j + 1].rgbtBlue * (1);

                GyGreen += auximg[i + 1][j].rgbtGreen * (2);
                GyGreen += auximg[i + 1][j + 1].rgbtGreen * (1);

                GyRed += auximg[i + 1][j].rgbtRed * (2);
                GyRed += auximg[i + 1][j + 1].rgbtRed * (1);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }
            }
            // Top-right corner
            if (i == 0 && j == width - 1)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i][j - 1].rgbtBlue * (-2);
                GxBlue += auximg[i + 1][j - 1].rgbtBlue * (-1);

                GxGreen += auximg[i][j - 1].rgbtGreen * (-2);
                GxGreen += auximg[i + 1][j - 1].rgbtGreen * (-1);

                GxRed += auximg[i][j - 1].rgbtRed * (-2);
                GxRed += auximg[i + 1][j - 1].rgbtRed * (-1);

                GyBlue += auximg[i + 1][j - 1].rgbtBlue * (1);
                GyBlue += auximg[i + 1][j].rgbtBlue * (2);

                GyGreen += auximg[i + 1][j - 1].rgbtGreen * (1);
                GyGreen += auximg[i + 1][j].rgbtGreen * (2);

                GyRed += auximg[i + 1][j - 1].rgbtRed * (1);
                GyRed += auximg[i + 1][j].rgbtRed * (2);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }
            }
            //bottom-left corner
            if (i == height - 1 && j == 0)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i - 1][j + 1].rgbtBlue * (1);
                GxBlue += auximg[i][j + 1].rgbtBlue * (2);

                GxGreen += auximg[i - 1][j + 1].rgbtGreen * (1);
                GxGreen += auximg[i][j + 1].rgbtGreen * (2);

                GxRed += auximg[i - 1][j + 1].rgbtRed * (1);
                GxRed += auximg[i][j + 1].rgbtRed * (2);

                GyBlue += auximg[i - 1][j].rgbtBlue * (-2);
                GyBlue += auximg[i - 1][j + 1].rgbtBlue * (-1);

                GyGreen += auximg[i - 1][j].rgbtGreen * (-2);
                GyGreen += auximg[i - 1][j + 1].rgbtGreen * (-1);

                GyRed += auximg[i - 1][j].rgbtRed * (-2);
                GyRed += auximg[i - 1][j + 1].rgbtRed * (-1);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }
            }
            //bottom-right corner
            if (i == height - 1 && j == width - 1)
            {
                int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
                
                
                GxBlue += auximg[i - 1][j - 1].rgbtBlue * (-1);
                GxBlue += auximg[i][j - 1].rgbtBlue * (-2);

                GxGreen += auximg[i - 1][j - 1].rgbtGreen * (-1);
                GxGreen += auximg[i][j - 1].rgbtGreen * (-2);

                GxRed += auximg[i - 1][j - 1].rgbtRed * (-1);
                GxRed += auximg[i][j - 1].rgbtRed * (-2);

                GyBlue += auximg[i - 1][j - 1].rgbtBlue * (-1);
                GyBlue += auximg[i - 1][j].rgbtBlue * (-2);

                GyGreen += auximg[i - 1][j - 1].rgbtGreen * (-1);
                GyGreen += auximg[i - 1][j].rgbtGreen * (-2);

                GyRed += auximg[i - 1][j - 1].rgbtRed * (-1);
                GyRed += auximg[i - 1][j].rgbtRed * (-2);


                if (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }

                if (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                }

                if (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                }
            }
        }
    }
    
    return;
}
