#include "helpers.h"
#include <math.h>
#include <stdio.h>

int validCell(int, int);
RGBTRIPLE nearbyAvg(int, int, int height, int width, RGBTRIPLE image[height][width]);

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

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sepiaRed = round((0.393 * image[row][col].rgbtRed) + (0.769 * image[row][col].rgbtGreen) + (0.189 * image[row][col].rgbtBlue));
            int sepiaGreen = round((0.349 * image[row][col].rgbtRed) + (0.686 * image[row][col].rgbtGreen) + (0.168 * image[row][col].rgbtBlue));
            int sepiaBlue = round((0.272 * image[row][col].rgbtRed) + (0.534 * image[row][col].rgbtGreen) + (0.131 * image[row][col].rgbtBlue));
            imageCopy[row][col].rgbtRed = sepiaRed < 255 ? sepiaRed : 255;
            imageCopy[row][col].rgbtBlue = sepiaBlue < 255 ? sepiaBlue : 255;
            imageCopy[row][col].rgbtGreen = sepiaGreen < 255 ? sepiaGreen : 255;
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
