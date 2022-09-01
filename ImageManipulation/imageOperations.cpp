/** *********************************************************************
 * @file
 *
 * @brief  Image operations and supporting functions
 ***********************************************************************/
#include "netPBM.h"

/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
* This function will rotate the image in clockwise direcion.
* If the dimensions of the of the original array is 10 X 5 the new array wil
* have a dimensino of 5 X 10.
* Each row will be coppied to a column in the new array. The top rows will
* will be in the last column. The second to the second last column and so on.
* It will rotate the 2D dynamically allocated array in the clockwise direction
* It creates temporary arrays for the three 2D arrays and and assigns the
* temporary array in such a way that the temporary arrays
* are rotated clockwise.
 * The function will call the clearArray function to clear the original
 * array. Later it will call the create array to create three arrays
 * with the new dimensions and finally call the copyArray function to copy
 * the temporary array in the old array having the new dimensions.
 * it will clear the temporary array before exiting the function
 *
 * @param[in, out] img - the structure when the data of the image is stored
 *
 *
 * @par Example:
   @verbatim

   image img;
   //consider img.blue , img.redGray, img.green to be  3 X 2 arrays
   // 1,2,3
   // 4,5,6
   rotateImageCW(img);
   //img.blue , img.redGray, img.green will now be  2 X 3 arrays
   //the contentents of img.blue will now be
   // 4,1
   // 5,2
   // 6,3

   @endverbatim

 ***********************************************************************/
    void rotateImageCW(image & img)
{
    int i, j;
    //declare the temporary 2D array pointers
    pixel** tempRedGray;
    pixel** tempGreen;
    pixel** tempBlue;

    //set teemp rows and columns to the new dimentions
    int tempRows = img.cols;
    int tempCols = img.rows;

    //create the three new temporary arrays with the new dimentions
    tempRedGray = createArrays(tempRows, tempCols);
    tempGreen = createArrays(tempRows, tempCols);
    tempBlue = createArrays(tempRows, tempCols);


    //go through each row of the 2D array
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            //assign the values from the original array to the temporary such that
            // the three 2D arrays are rotated clockise
            tempRedGray[j][img.rows - i - 1] = img.redGray[i][j];
            tempGreen[j][img.rows - i - 1] = img.green[i][j];
            tempBlue[j][img.rows - i - 1] = img.blue[i][j];
        }
    }

    //delete all three original arrays
    clearArray(img.redGray, img.rows);
    clearArray(img.green, img.rows);
    clearArray(img.blue, img.rows);

    //swap the values of img.rows and img.cols
    swap(img.cols, img.rows);

    //create the new arrays with the new dimensions and store it in the 
    //img.redGray etc.
    img.redGray = createArrays(img.rows, img.cols);
    img.green = createArrays(img.rows, img.cols);
    img.blue = createArrays(img.rows, img.cols);

    //copy the contents of the temp arrays to the new arrays
    copyArray(img.redGray, tempRedGray, img);
    copyArray(img.green, tempGreen, img);
    copyArray(img.blue, tempBlue, img);

    //delete the temp arrays
    clearArray(tempRedGray, tempRows);
    clearArray(tempGreen, tempRows);
    clearArray(tempBlue, tempRows);

}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This functinon will copy the contents of one dynamicallly allocated
 * 2D array to another dynamically allocate 2D array. The structure is
 * passed to it for it to know th enumber of number of rows and cols
 *
 * @param[out] array -the 2D dynamic array to which the data is to be copied to
 * @param[in] array1 - the array which has the data
 * @param[in] img - the structure with the data of the number of rows and cols
 *
 *
 * @par Example:
   @verbatim

   image img;
   //consider img.redGray is empty
   pixel ** temp;
   //we assign some data to temp

   copyArray(img.redGray, temp, img);
   //img.redGray will have a copy of the data that is in temp

   @endverbatim

 ***********************************************************************/
void copyArray(pixel**& array, pixel** array1, image img)
{
    int i, j;
    //go through each row of the 2D array
    for (i = 0; i < img.rows; i++)
    {
        //go throught each column of the array
        for (j = 0; j < img.cols; j++)
        {
            //assign the contents of one index to another
            array[i][j] = array1[i][j];
        }
    }
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * *This function will rotate the image in clockwise direcion.
 * If the dimensions of the of the original array is 10 X 5 the new array wil
 * have a dimensino of 5 X 10.
 * Each row will be coppied to a column in the new array. The top rows will
 * will be in the first column. The second to the second column.
 *  It creates temporary arrays for the three 2D arrays and and assigns the
 *  temporary array in such a way that the temporary arrays
 * are rotated counter clockwise. If the dimensions of the
 * original array is 10 X 5 the new array wil have a dimensino of 5 X 10.
 * The function will call the clearArray function to clear the original
 * array. Later it will call the create array to create three arrays
 * with the new dimensions and finally call the copyArray function to copy
 * the temporary array in the old array having the new dimensions.
 * it will clear the temporary array before exiting the function
 *
 * @param[in, out] img - the structure where the data of the image is stored
 *
 *
 * @par Example:
   @verbatim

    image img;
    //consider img.blue , img.redGray, img.green to be  3 X 2 arrays
    //consider the contents of img.blue to be
    // 1,2,3
    // 4,5,6
    rotateImageCCW(img);
    //img.blue , img.redGray, img.green will now be  2 X 3 arrays
    //the contentents of img.blue will now be
    // 3,6
    // 2,5
    // 1,4

   @endverbatim

 ***********************************************************************/
void rotateImageCCW(image& img)
{
    int i, j;

    //declare the temporary 2D array pointers
    pixel** tempRedGray;
    pixel** tempGreen;
    pixel** tempBlue;

    //set teemp rows and columns to the new dimentions
    int tempRows = img.cols;
    int tempCols = img.rows;

    //create the three new temporary arrays with the new dimentions
    tempRedGray = createArrays(tempRows, tempCols);
    tempGreen = createArrays(tempRows, tempCols);
    tempBlue = createArrays(tempRows, tempCols);

    //go through each row of the 2D array
    for (i = 0; i < img.rows; i++)
    {
        //go through each colum of the 2D array
        for (j = 0; j < img.cols; j++)
        {
            //assign the values from the original array to the temporary such that
            // the three 2D arrays are rotated counter clockise
            tempRedGray[img.cols - 1 - j][i] = img.redGray[i][j];
            tempGreen[img.cols - 1 - j][i] = img.green[i][j];
            tempBlue[img.cols - 1 - j][i] = img.blue[i][j];
        }

    }

    //delete all three original arrays
    clearArray(img.redGray, img.rows);
    clearArray(img.green, img.rows);
    clearArray(img.blue, img.rows);

    //swap the values of img.rows and img.cols
    swap(img.cols, img.rows);

    //create the new arrays with the new dimensions and store it in the 
    //img.redGray etc.
    img.redGray = createArrays(img.rows, img.cols);
    img.green = createArrays(img.rows, img.cols);
    img.blue = createArrays(img.rows, img.cols);

    //copy the contents of the temp arrays to the new arrays
    copyArray(img.redGray, tempRedGray, img);
    copyArray(img.green, tempGreen, img);
    copyArray(img.blue, tempBlue, img);

    //delets the temp arrays
    clearArray(tempRedGray, tempRows);
    clearArray(tempGreen, tempRows);
    clearArray(tempBlue, tempRows);

}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function flips the image along the x axis. it uses temporary
 * dyanmically allocated temporary arrays to store the modified data.
 * The original array is cleared out and new arrays are stored in the
 * original pointers, then the modified array is copied back to the
 * new array. The temporary array is cleared before exiting the function
 *
 * @param[in, out] img - the structure where the data of the image is stored
 *
 *
 * @par Example:
   @verbatim

   image img;
   //consider img.blue , img.redGray, img.green to be  3 X 2 arrays
   //consider the contents of img.blue to be a array
   //             1,2,3
   //             4,5,6

   flipX(img);

   //the contentents of img.blue will now be
   //             4,5,6
   //             1,2,3
   @endverbatim

 ***********************************************************************/
void flipX(image& img)
{
    int i, j;
    //declare the temporary 2D array pointers
    pixel** tempRedGray;
    pixel** tempGreen;
    pixel** tempBlue;
    //create the three new temporary arrays with the new dimentions
    tempRedGray = createArrays(img.rows, img.cols);
    tempGreen = createArrays(img.rows, img.cols);
    tempBlue = createArrays(img.rows, img.cols);

    //go through each row of the 2D array
    for (i = 0; i < img.rows; i++)
    {
        //go through each colum of the 2D array
        for (j = 0; j < img.cols; j++)
        {
            //write an algorithm to flip the three 2D array over the x axis
            tempRedGray[img.rows - 1 - i][j] = img.redGray[i][j];
            tempGreen[img.rows - 1 - i][j] = img.green[i][j];
            tempBlue[img.rows - 1 - i][j] = img.blue[i][j];
        }
    }

    //delete all the original arrays
    clearArray(img.redGray, img.rows);
    clearArray(img.green, img.rows);
    clearArray(img.blue, img.rows);

    //create new 2D arrays and store them in the original pointer
    img.redGray = createArrays(img.rows, img.cols);
    img.green = createArrays(img.rows, img.cols);
    img.blue = createArrays(img.rows, img.cols);

    //copy the contents of the temp arrays to the new arrays
    copyArray(img.redGray, tempRedGray, img);
    copyArray(img.green, tempGreen, img);
    copyArray(img.blue, tempBlue, img);

    //delete all the temp arrays
    clearArray(tempRedGray, img.rows);
    clearArray(tempGreen, img.rows);
    clearArray(tempBlue, img.rows);
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function flips the image along the y axis. it uses temporary
 * dyanmically allocated temporary arrays to store the modified data.
 * The original array is cleared out and new arrays are stored in the
 * original pointers, then the modified array is copied back to the
 * new array.  The temporary array is cleared before exiting the function
 *
 * @param[in, out] img - the structure where the data of the image is stored
 *
 *
 * @par Example:
   @verbatim

   image img;
   //consider img.blue , img.redGray, img.green to be  3 X 2 arrays
   //consider the contents of img.blue to be a array
   //            1,2,3
   //            4,5,6


   flipX(img);

   //the contentents of img.blue will now be
   //             3,2,1
   //             6,5,4
   @endverbatim

 ***********************************************************************/
void flipY(image& img)
{
    int i, j;
    //declare the temporary 2D array pointers
    pixel** tempRedGray;
    pixel** tempGreen;
    pixel** tempBlue;
    //create the three new temporary arrays with the new dimentions
    tempRedGray = createArrays(img.rows, img.cols);
    tempGreen = createArrays(img.rows, img.cols);
    tempBlue = createArrays(img.rows, img.cols);

    //go through each row of the 2D array
    for (i = 0; i < img.rows; i++)
    {
        //go through each column of the 2D array
        for (j = 0; j < img.cols; j++)
        {
            //write an algorithm to flip the 2D array over the y axis
            tempRedGray[i][img.cols - 1 - j] = img.redGray[i][j];
            tempGreen[i][img.cols - 1 - j] = img.green[i][j];
            tempBlue[i][img.cols - 1 - j] = img.blue[i][j];
        }
    }
    //delete all the original arrays
    clearArray(img.redGray, img.rows);
    clearArray(img.green, img.rows);
    clearArray(img.blue, img.rows);

    //create new 2D arrays and store them in the original pointer
    img.redGray = createArrays(img.rows, img.cols);
    img.green = createArrays(img.rows, img.cols);
    img.blue = createArrays(img.rows, img.cols);

    //copy the contents of the temp arrays to the new arrays
    copyArray(img.redGray, tempRedGray, img);
    copyArray(img.green, tempGreen, img);
    copyArray(img.blue, tempBlue, img);

    //delete all the temp arrays
    clearArray(tempRedGray, img.rows);
    clearArray(tempGreen, img.rows);
    clearArray(tempBlue, img.rows);
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function will convert the image into gray scale. It will multiply
 * the contents of each array by certain number and then store the result
 * as a pixel in the redGray array.
 *
 * @param[in, out] img - the structure where the data of the image is stored
 *
 *
 * @par Example:
   @verbatim

   image img;

   //consider we allocate some image data to img

   grayscale(img);

   //the output image will result in a gray image.

   @endverbatim

 ***********************************************************************/
void grayScale(image& img)
{
    int i, j;
    int redGray;
    int green;
    int blue;
    int value;

    //go through each row
    for (i = 0; i < img.rows; i++)
    {
        //go through each column
        for (j = 0; j < img.cols; j++)
        {
            //store the int data from the array in a temporary variable
            redGray = int(img.redGray[i][j]);
            green = int(img.green[i][j]);
            blue = int(img.blue[i][j]);

            //multiply the contents by specific number to convert it to gray
            value = int(0.3 * redGray + 0.6 * green + 0.1 * blue);
            // store the content as pixel in the same index of the array
            img.redGray[i][j] = pixel(value);
        }
    }
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function will convert the image into sepia. It will multiply
 * the contents of each array by certain number and then store the result
 * as a pixel in the redGray array. if the result is more than 255 it will
 * store 255
 *
 * @param[in, out] img - the structure where the data of the image is stored
 *
 *
 * @par Example:
   @verbatim

   image img;

   //consider we allocate some image data to img

   sepia(img);

   //the output array will result in a sepia image

   @endverbatim

 ***********************************************************************/
void sepia(image& img)
{
    //declare the variables
    int i, j;
    int tempRedGray, tempGreen, tempBlue;
    int redGray;
    int green;
    int blue;

    //go through each row
    for (i = 0; i < img.rows; i++)
    {
        //go through each column
        for (j = 0; j < img.cols; j++)
        {
            //store the int data from the index to a temporary variables
            redGray = int(img.redGray[i][j]);
            green = int(img.green[i][j]);
            blue = int(img.blue[i][j]);

            //multiply the data by the numbers, store the sum of tempRedGray
            tempRedGray = int(0.393 * redGray + 0.769 * green + 0.189 * blue);
            //if the value is more than 255 then store 255
            if (tempRedGray > 255)
            {
                tempRedGray = 255;
            }
            //multiply the data by the numbers, store the sum of tempGreen
            tempGreen = int(0.349 * redGray + 0.686 * green + 0.168 * blue);
            //if the value is more than 255 then store 255
            if (tempGreen > 255)
            {
                tempGreen = 255;
            }

            //multiply the data by the numbers, store the sum of tempBlue
            tempBlue = int(0.272 * redGray + 0.534 * green + 0.131 * blue);
            //if the value is more than 255 then store 255
            if (tempBlue > 255)
            {
                tempBlue = 255;
            }

            //store the data in the same index of the array as pixels
            img.redGray[i][j] = pixel(tempRedGray);
            img.green[i][j] = pixel(tempGreen);
            img.blue[i][j] = pixel(tempBlue);

        }
    }
}
