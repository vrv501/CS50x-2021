#include "helpers.h"
#include <math.h>
#include <stdio.h>

int validCell(int, int);
RGBTRIPLE nearbyAvg(int, int, int height, int width, RGBTRIPLE image[height][width]);
RGBTRIPLE convolute(int, int, int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
// Replace RGB with their avg sum
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            BYTE avg_pixel = round((image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed) / 3.0);
            image[row][col].rgbtRed = avg_pixel;
            image[row][col].rgbtBlue = avg_pixel;
            image[row][col].rgbtGreen = avg_pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int halfWidth = (width / 2);
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < halfWidth; col++)
        {
            // Swap every byte with its conjugate from right
            RGBTRIPLE tempByte = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = tempByte;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];

    // Compute avg of nearby cells for every pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            imageCopy[row][col] = nearbyAvg(row, col, height, width, image);
        }
    }

    // After final computation, copy back to original matrix
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = imageCopy[row][col];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];

    // Compute sqrt(Gx^2 + Gy^2) of nearby cells for every pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            imageCopy[row][col] = convolute(row, col, height, width, image);
        }

    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = imageCopy[row][col];
        }
    }
    return;
}

RGBTRIPLE nearbyAvg(int row, int col, int height, int width, RGBTRIPLE image[height][width])
{
    // Get valid starting & ending row, col numbers of nearbyCells
    int rowLimit = height - 1, colLimit = width - 1;
    int startRow = validCell((row - 1), rowLimit), startCol = validCell((col - 1), colLimit), endRow = validCell((row + 1), rowLimit), endCol = validCell((col + 1), colLimit);

    // Count the number of cells
    float nearbyCells = (1 + (endRow - startRow)) * (1 + (endCol - startCol));

    RGBTRIPLE tempByte;
    int nearbyRed = 0, nearbyBlue = 0, nearbyGreen = 0;

    // nearbyCells RGB calculation
    for (int subRow = startRow; subRow <= endRow; subRow++)
    {
        for (int subCol = startCol; subCol <= endCol; subCol++)
        {
            nearbyRed += image[subRow][subCol].rgbtRed;
            nearbyBlue += image[subRow][subCol].rgbtBlue;
            nearbyGreen += image[subRow][subCol].rgbtGreen;
        }
    }

    // int / float = float
    tempByte.rgbtRed = round(nearbyRed / nearbyCells);
    tempByte.rgbtBlue = round(nearbyBlue / nearbyCells);
    tempByte.rgbtGreen = round(nearbyGreen / nearbyCells);

    return tempByte;
}

RGBTRIPLE convolute(int row, int col, int height, int width, RGBTRIPLE image[height][width])
{
    // Get valid starting & ending row, col numbers of nearbyCells
    int rowLimit = height - 1, colLimit = width - 1;
    int startRow = validCell((row - 1), rowLimit), startCol = validCell((col - 1), colLimit), endRow = validCell((row + 1), rowLimit), endCol = validCell((col + 1), colLimit);

    RGBTRIPLE tempByte;
    int Gxy[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // Three cols for RGB
    int Gx[3] = {0, 0, 0}, Gy[3] = {0, 0, 0};

    // nearbyCells Gx, Gy calculation
    for (int subRow = startRow; subRow <= endRow; subRow++)
    {
        int absRow = subRow - row + 1;
        for (int subCol = startCol; subCol <= endCol; subCol++)
        {
            int absCol = subCol - col + 1;
            Gx[0] += (image[subRow][subCol].rgbtRed * Gxy[absRow][absCol]);
            Gy[0] += (image[subRow][subCol].rgbtRed * Gxy[absCol][absRow]);
            Gx[1] += (image[subRow][subCol].rgbtBlue * Gxy[absRow][absCol]);
            Gy[1] += (image[subRow][subCol].rgbtBlue * Gxy[absCol][absRow]);
            Gx[2] += (image[subRow][subCol].rgbtGreen * Gxy[absRow][absCol]);
            Gy[2] += (image[subRow][subCol].rgbtGreen * Gxy[absCol][absRow]);
        }
    }

    int Gxred = round(sqrt(pow(Gx[0], 2) + pow(Gy[0], 2)));
    tempByte.rgbtRed = Gxred < 255 ? Gxred : 255;
    int Gxblue = round(sqrt(pow(Gx[1], 2) + pow(Gy[1], 2)));
    tempByte.rgbtBlue = Gxblue < 255 ? Gxblue : 255;
    int Gxgreen = round(sqrt(pow(Gx[2], 2) + pow(Gy[2], 2)));
    tempByte.rgbtGreen = Gxgreen < 255 ? Gxgreen : 255;

    return tempByte;
}

// Check if a given row/col is valid or not
int validCell(int num, int limit)
{
    if (num < 0)
    {
        return 0;
    }

    else if (num > limit)
    {
        return limit;
    }
    else
    {
        return num;
    }
}
