#include "helpers.h"
#include <math.h>
#include <stdio.h>
void swap(BYTE *, BYTE *);
int isValid(int, int);
void nearby_avg(int, int, int, int, int, int row, int col, RGBTRIPLE image[row][col]);
void convolute(int, int, int row, int col, RGBTRIPLE image[row][col]);
int avg_green, avg_blue, avg_red, pixel_red, pixel_blue, pixel_green;
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE avg_pixel = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float)3);       //avg pixel value
            image[i][j].rgbtBlue = avg_pixel;
            image[i][j].rgbtGreen = avg_pixel;
            image[i][j].rgbtRed = avg_pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = (width / 2);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width - 1 - j].rgbtRed);       //swap the values for mirror image
            swap(&image[i][j].rgbtGreen, &image[i][width - 1 - j].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - 1 - j].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    
    for (int row = 0; row < height; row++)
    {
        int i_start = isValid((row - 1), height);
        int i_end = isValid((row + 1), height);
        for (int col = 0; col < width; col++)
        {
            int j_start = isValid((col - 1), width);              //get all valid nearby cell coordinates start and end
            int j_end = isValid((col + 1), width);
            float nearby_cells = (1 + (j_end - j_start)) * (1 + (i_end - i_start));   //compute number of cells
            nearby_avg(i_start, j_start, j_start, i_end, j_end, height, width, image);
            image_copy[row][col].rgbtRed = round(avg_red / nearby_cells);            //round off and assign them
            image_copy[row][col].rgbtBlue = round(avg_blue / nearby_cells);
            image_copy[row][col].rgbtGreen = round(avg_green / nearby_cells);
            avg_red = 0, avg_blue = 0, avg_green = 0;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_copy[i][j].rgbtRed;          //After final computation, copy back to original matrix
            image[i][j].rgbtBlue = image_copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_copy[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            convolute((i - 1), (j - 1), height, width, image);    //Compute gx and gy for all the 3 colors
            image_copy[i][j].rgbtRed = avg_red;
            image_copy[i][j].rgbtBlue = avg_blue;              //Assign those in a image copy
            image_copy[i][j].rgbtGreen = avg_green;
            avg_red = 0, avg_blue = 0, avg_green = 0;
        }
            
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_copy[i][j].rgbtRed;           //Update the new values back in original image
            image[i][j].rgbtBlue = image_copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_copy[i][j].rgbtGreen;
        }
    }
    return;
}

void swap(BYTE *a, BYTE *b)                            //Swap helper
{
    BYTE temp = *a;
    *a = *b;
    *b = temp;
}

int isValid(int i, int limit)                         //To give a valid start and ending neighbour cells
{
    if (i >= 0 && i < limit)
    {
        return i;
    }
    else if (i < 0)
    {
        return 0;
    }
    else
    {
        return (limit - 1);
    }
}

void nearby_avg(int i, int j, int j_s, int i_e, int j_e, int row, int col, RGBTRIPLE image[row][col])
//Summation of pixels of all neighbour cells
{
    if (i <= i_e)
    {
        
        avg_red += image[i][j].rgbtRed;
        avg_blue += image[i][j].rgbtBlue;
        avg_green += image[i][j].rgbtGreen;
        if (j == j_e)
        {
            nearby_avg((i + 1), j_s, j_s, i_e, j_e, row, col, image);        //Increment row
        }
        else
        {
            nearby_avg(i, (j + 1), j_s, i_e, j_e, row, col, image);     //Increment column
        }
    }
    return;
}

void get_rgb(int i_ind, int j_ind, int row, int col, RGBTRIPLE image[row][col])        //At any index get the rgb values
{
    if ((i_ind >= 0 && i_ind < row) && (j_ind >= 0 && j_ind < col))
    {
        pixel_red = image[i_ind][j_ind].rgbtRed, pixel_green = image[i_ind][j_ind].rgbtGreen, pixel_blue = image[i_ind][j_ind].rgbtBlue;
    }
    else
    {
        pixel_red = 0, pixel_green = 0, pixel_blue = 0;
    }
}

void convolute(int i_ind, int j_ind, int row, int col, RGBTRIPLE image[row][col])         //Compuatation of gx & gy values
{
    int conv[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int g_matrix[3][2] = {{0, 0}, {0, 0}, {0, 0}};
    for (int i = 0; i < 3; i++)
    {
        int k = j_ind;
        for (int j = 0; j < 3; j++)
        {
            get_rgb(i_ind, k, row, col, image);
            g_matrix[0][0] += (conv[j][i] * pixel_red);                                   
            g_matrix[0][1] += (conv[i][j] * pixel_red);
            g_matrix[1][0] += (conv[j][i] * pixel_blue);
            g_matrix[1][1] += (conv[i][j] * pixel_blue);
            g_matrix[2][0] += (conv[j][i] * pixel_green);
            g_matrix[2][1] += (conv[i][j] * pixel_green);
            k++;
        }
        i_ind++;
    }
    avg_red = round(sqrt(pow(g_matrix[0][0], 2) + pow(g_matrix[0][1], 2)));
    avg_red = avg_red < 255 ? avg_red : 255;
    avg_blue = round(sqrt(pow(g_matrix[1][0], 2) + pow(g_matrix[1][1], 2)));
    avg_blue = avg_blue < 255 ? avg_blue : 255;
    avg_green = round(sqrt(pow(g_matrix[2][0], 2) + pow(g_matrix[2][1], 2)));
    avg_green = avg_green < 255 ? avg_green : 255;
}
