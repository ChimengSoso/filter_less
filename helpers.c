#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get value of red green blue from original image
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            // find the average
            int avg = (int)round((r + g + b) / 3.0);

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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get value of red green blue from original image
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            int sepiaRed = (int)round(.393 * r + .769 * g + .189 * b);
            sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;

            int sepiaGreen = (int)round(.349 * r + .686 * g + .168 * b);
            sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;

            int sepiaBlue = (int)round(.272 * r + .534 * g + .131 * b);
            sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
            // swap opposite of index j
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary value of new image
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // variable for sum value of color from original image
            int red = 0, green = 0, blue = 0;
            int cnt = 0;
            for (int r = i - 1; r <= i + 1; r++)
            {
                for (int c = j - 1; c <= j + 1; c++)
                {
                    if (0 <= r && r < height && 0 <= c && c < width)
                    {
                        red += image[r][c].rgbtRed;
                        green += image[r][c].rgbtGreen;
                        blue += image[r][c].rgbtBlue;
                        cnt++;
                    }
                }
            }
            tmp[i][j].rgbtRed = (int)round(1.0 * red / cnt);
            tmp[i][j].rgbtGreen = (int)round(1.0 * green / cnt);
            tmp[i][j].rgbtBlue = (int)round(1.0 * blue / cnt);
        }
    }

    // transfer blue image to original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
