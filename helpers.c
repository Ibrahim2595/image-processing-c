#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a for loop to navigate per rows
    for (int i = 0; i < height; i++)
    {
        // Create a for loop within the first for loop to navigate to the columns, ie: pixels
        for (int j = 0; j < width; j++)
        {
            // Extract the RGB values into defined ints
            int x = image[i][j].rgbtBlue;
            int y = image[i][j].rgbtGreen;
            int z = image[i][j].rgbtRed;

            // Find the average of the RGB values + rounding to nearest int
            int avg = round((x + y + z) / 3.0);

            // Retrun the same average to all 3 RGB values
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Calculate the new values using the sepia formula
            int newBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            // Ensure that all values are withing 0 and 255 inclusive
            if (newBlue > 255)
            {
                newBlue = 255;
            }

            int newGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            if (newGreen > 255)
            {
                newGreen = 255;
            }

            int newRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            if (newRed > 255)
            {
                newRed = 255;
            }

            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtRed = newRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Create a temporary storage value called tempa and it would equal temp.
            RGBTRIPLE temp = image[i][j];
            // Location of pixel 1 = location of pixel two
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

 
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    // Copy the 2D array of the original image into a new image
    //RGBTRIPLE image[height][width] = RGBTRIPLE copy[height][width];

    // Declare a copy of the array
    RGBTRIPLE copy[height][width];

    // Copying each pixel into copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Find the pixels around
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Declare a counter to count the number of selected pixels
            int count = 0;
            // Declare the total values of RGB from the selected pixels
            int xA = 0;
            int yA = 0;
            int zA = 0;

            // Select the pixels that are within -+1 of i horizontally
            for (int d = -1; d <= 1; d++)
            {
                // Select the pixels that are within -+1 of i vertically
                for (int e = -1; e <= 1; e++)
                {
                    // index location of the selected pixels
                    int localX = i + d;
                    int localY = j + e;

                    // Check if the pixel is valid and not outside the heigth and width boundaries
                    if (localX >= 0 && localX < height && localY >= 0 && localY < width)
                    {
                        count++;
                        // Calculate the new total amounts of RGB of the selected pixels
                        xA += copy[localX][localY].rgbtBlue;
                        yA += copy[localX][localY].rgbtGreen;
                        zA += copy[localX][localY].rgbtRed;
                    }
                }
                
            }
            // Average the pixels and apply them to the original image
            image[i][j].rgbtBlue = round((float) xA / count);
            image[i][j].rgbtGreen = round((float) yA / count);
            image[i][j].rgbtRed = round((float) zA / count);
        }
    }
}