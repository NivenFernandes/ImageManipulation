/** *********************************************************************
 * @file
 *
 * @brief   Allocate and clear memory functions for dynamic array
 ***********************************************************************/
#include "netPBM.h"






 /** *********************************************************************
  * @author Niven Fernandes
  *
  * @par Description:
  * This function receives the number of rows and columns and it will
  * create a dynamic 2D array of the given rows and columns.
  * At every step it will check whether it was able to allocate memory.
  * If it was not able to alloate memory,
  * it will call the clearArray function to clear the memory and exit the
  *program with exit code 0.
  *
  * @param[in] rows - the number of rows required in the 2D array
  * @param[in] cols - the number of columns needed
  *
  * @returns a pointer to a 2D array that is a pointer to a pointer
  *
  * @par Example:
    @verbatim

    pixel** tempRedGray;
    int tempRows=100;
    int tempCols=50;

    tempRedGray=createArrays(tempRows, tempCols);
    //tempRedGray will have an address to a dynamically allocated 2D array
    with 100 rows and 50 columns

    @endverbatim

  ***********************************************************************/
pixel** createArrays(int rows, int cols)
{
    int i;
    //declare the pixel ointer
    pixel** pointer = nullptr;

    //create a dynamic arrray of the number of rows
    pointer = new (nothrow) pixel * [rows];
    //check if it was able to allocate memory
    if (pointer == nullptr)
    {
        //unable to allocate memory - error message and exit
        delete[] pointer;
        cout << "Unable to allocate memory" << endl;
        exit(0);
    }


    //go through each row and allocate memory for each row
    for (i = 0; i < int(rows); i++)
    {
        pointer[i] = new (nothrow) pixel[cols];
        if (pointer[i] == nullptr)
        {
            //unable to allocate memory - error message, clear array exit
            cout << "Unable to allocate memory" << endl;
            clearArray(pointer, i - 1);
            exit(0);
        }
    }

    //return pointer to a 2D array
    return pointer;
}



/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function receives the pointer to a dynamically allocated
 * 2D array and the number of rows in the array. This function deletes
 * the 2D array
 *
 * @param[in out] pointer - the pointer to a 2D array
 * @param[in] rows - the number of rows in the 2D array
 *
 * @par Example:
   @verbatim

   int tempRows=100;
   int tempCols=50;
   pixel** tempRedGray = createArrays(tempRows, tempCols);
   //tempRedGray will have an address to a dynamically allocated 2D array
   with 100 rows and 50 columns

   clearArray(tempCols, tempRows); //delete the dynamically allocated 2D array

   @endverbatim

 ***********************************************************************/
void clearArray(pixel**& pointer, int rows)
{
    int i;
    //delete every row 
    for (i = 0; i < rows; i++)
    {
        delete[] pointer[i];
    }

    //delete the array of pointers
    delete[] pointer;
}