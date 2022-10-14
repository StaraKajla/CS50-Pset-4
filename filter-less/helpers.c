#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int newRed;
    int newGreen;
    int newBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            if (newRed > 255)
            {
                newRed = 255;
            }
            else if (newRed < 0)
            {
                newRed = 0;
            }

            newGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            if (newGreen > 255)
            {
                newGreen = 255;
            }
            else if (newGreen < 0)
            {
                newGreen = 0;
            }

            newBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            if (newBlue > 255)
            {
                newBlue = 255;
            }
            else if (newBlue < 0)
            {
                newBlue = 0;
            }

            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtBlue = newBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            //Top left
            if (i == 0 && j == 0)
            {
                temp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                            image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0);
                temp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                              image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0);
                temp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                             image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0);
            }
            //Top right
            else if (i == 0 && j == (width - 1))
            {
                temp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                            image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0);
                temp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                              image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0);
                temp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                             image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0);
            }
            //Bottom left
            else if (i == height - 1 && j == 0)
            {
                temp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                            image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0);
                temp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                              image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0);
                temp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                             image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0);
            }
            //Bottom right
            else if (i == height - 1 && j == (width - 1))
            {
                temp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                            image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0);
                temp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                              image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0);
                temp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                             image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0);
            }

            //Top row
            else if ((i == 0 && j > 0) && (i == 0 && j < width - 1))
            {
                temp[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                  image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                temp[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                  image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                temp[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                  image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //Left side col
            else if ((i > 0 && j == 0) && (i < height && j == 0))
            {
                temp[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed +
                                  image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                temp[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen +
                                  image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                temp[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                                  image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //Right side col
            else if ((i > 0 && j == (width - 1)) && (i < height && j == (width - 1)))
            {
                temp[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed +
                                  image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);
                temp[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                  image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
                temp[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                  image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
            }
            //Bottom row
            else if ((i == height - 1 && j > 0) && (i == height - 1 && j < width - 1))
            {
                temp[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                  image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 6.0);
                temp[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                  image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 6.0);
                temp[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                  image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 6.0);
            }
            //Middle
            else if (i > 0 && i < height - 1 && j > 0 && j < (width - 1))
            {
                temp[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                  image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                  image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);
                temp[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                    image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                    image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
                temp[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                    image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                    image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }
    //copy to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
