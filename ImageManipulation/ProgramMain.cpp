/** *********************************************************************
 * @file
 *
 * @brief   Program main and supporting functions for image manupulation
 ***********************************************************************/


 /** ********************************************************************
 *
 * @mainpage Take Home Programming Exam 1 - Image manipulation
 *
 * @section course_section Course Information
 *
 * @author Niven Fernandes
 *
 * @date March 5, 2022
 *
 * @par Instructor:
 *         Prof. Roger Schrader
 *
 * @par Course:
 *         CSC 215 - Section 1 - 9:00 am
 *
 * @par Location:
 *         CB - 329
 *
 * @section program_section Program Information
 * @details This program manupulates netPBM images.To run this program we
 * use command line arguments. The program will read the file mentioned
 * in the command line arguments. The input file can be a ascii or binary
 * file with the magic number of P6 or P3.
 * The data files with the extension .ppm are coloured the ones with
 * .pgm are grayscale. It will read in the option if
 * mentioned and try to implemend it .
 * The manupulations the program can do are
 * Flip over the X axis
 * Flip over the Y axis
 * Rotate clockwise
 * Rotate counter clockwise
 * Convert image to grayscale
 * Convert image to Antique
 * If no options are mentioned, the program will go to write.
 * Writing options include
 * writing in integer form / ascii with the magic number P3 or P2
 * writing in binary form in with the magic number P5 or p6
 * The program uses dynamically allocated memory and reads the data in this
 * 2D array. This program has a structure which stores all the data.
 * The program will check for the errors and output the required error
 * message
 * The program will delete all the dynamically allocated memory before exiting
 * the program
 * the options can be
 *
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim

   "C:\> theExam.exe [option] --outputtype basename image.ppm"
   "C:\> theExam.exe --outputtype basename image.ppm"

     output Type
     --ascii - integer text will be written to the file
     --binary - integer numbers will be written in binary form

     Option code
     --flipX      flip the image on the X axis
     --flipY      flip the image on the Y axis
     --rotateCw   Rotate the image clockwise
     --rotateCCW  Rotate the image counter clockwise
     --grarscale  Convert image to grayscale
     --sepia      convert image to sepia

   @endverbatim
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  sepia failed once a bit before pushing. I did modify it to pass.
 * But I did not get to test it a lot again
 *
 * @todo none
 *
 * @par Modifications and Development Timeline:

   Gitlab commit log, <a href = "https://gitlab.cse.sdsmt.edu/101095650/csc215s22programs/activity ">
   Click Here.</a>
 *
 ***********************************************************************/
#include"netPBM.h"




 /** *********************************************************************
  * @author Niven Fernandes
  *
  * @par Description:
  * This is the main function of thpExam1 - image manupulation.
  * Command line arguments are passed to thsi function.
  * It will check if the correct number of command line
  * arguments are pssed to this function. If yes, it will
  * call the appropriate function to open the file name mention
  * in the command line arguments to open in binary. Later, according
  * to the output option it will call a function to open the output
  * file by using the name mentioned in the command line arguments.
  * it will later call the handle options function which will call
  * the appropriate function to manupulate the image. Finally it will
  * call handleOutput function to handle the output. It will clear the
  * arrays and exit the function with a code 0
  *
  * @param[in] argc - the number of command line arguments
  * @param[in] argv - the c strle array having the data from the command
  *                   line arguments
  *
  * @returns 0 before ending the program
  *
  *
  * @par Example:
    @verbatim

    //command line argument
       "C:\> theExam.exe --sepia --binary sepia image.ppm"

    //it will read the binary file and output the image in sepia in a binary
    // file named sepia.ppm

    @endverbatim

  ***********************************************************************/
int main(int argc, char** argv)
{
    ifstream fin;
    ofstream fout;
    bool isInput, isOutput, read;
    image img;
    int maxPixel;
    string output;

    //check if the number of command line arguments are correct
    if (argc != 5 && argc != 4)
    {
        //output an error message
        printUsage();
        return 0;
    }
    //open the input file
    isInput = isBinFileOpen(string(argv[argc - 1]), fin);

    //if grayscale, add .pgm extension to the output file name
    if (string(argv[argc - 4]) == "--grayscale")
    {
        output = string(argv[argc - 2]) + ".pgm";
    }

    //else add .ppm
    else
    {
        output = string(argv[argc - 2]) + ".ppm";
    }


    //check the outpute type in the command line arguments
    if (string(argv[argc - 3]) == "--binary" || string(argv[argc - 3]) == "--ascii")
    {
        isOutput = isBinOutputOpen(output, fout);
    }

    else
    {
        //print usage error
        printUsage();
        exit(0);
    }


    if (isInput && isOutput)
    {
        //read file
        read = readFile(fin, img, maxPixel);

        //handle options
        if (argc == 5)
        {
            handleOptions(string(argv[argc - 4]), img);
        }

        //handle output
        handleOutput(string(argv[argc - 4]), string(argv[argc - 3]), img, fout, maxPixel);
    }
    //clear the temp arrays
    clearArray(img.redGray, img.rows);
    clearArray(img.green, img.rows);
    clearArray(img.blue, img.rows);


    //close the files
    fin.close();
    fout.close();


    //return 0
    return 0;
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * According to the string passed, this function will call the appropriate
 * image manupulation function. The strucure is passed by reference.
 *
 * @param[in] option - the image manupulation option
 * @param[in,out] img - the structure that has the data that will be modified
 *
 *
 * @par Example:
   @verbatim

   image img;

    handleOptions("--sepia" , img);
    //this function will call the sepia function and the sepia functions
   // will modify the data of the image to sepia

   @endverbatim

 ***********************************************************************/
void handleOptions(string option, image& img)
{
    //if option is --rotataCW , call rotateImageCW function
    if (option == "--rotateCW")
    {
        rotateImageCW(img);
    }

    //else if option is --rotataCCW , call rotateImageCCW function
    else if (option == "--rotateCCW")
    {
        rotateImageCCW(img);
    }

    //else if option is --flipX, call flipX function
    else if (option == "--flipX")
    {
        flipX(img);
    }

    //else if option is --flipY, call flipY function
    else if (option == "--flipY")
    {
        flipY(img);
    }

    //else if option is --grayscale call grayscale function
    else if (option == "--grayscale")
    {
        grayScale(img);
    }

    //else if option is --sepia, call sepia function
    else if (option == "--sepia")
    {
        sepia(img);
    }

    else
    {
        printUsage();
        exit(0);
    }
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * According to the option string and the output type string passed to this
 * function, this function will call the approprite function to write the
 * data to the array. we pass the structure, output stream and the maxPixel
 * to this function.
 *
 * @param[in] option - the image manupulation option
 * @param[in] type - the image output type
 * @param[in] img - the structure having the data
 * @param[out] fout - the output stream
 * @param[in] maxPixel -  the maximum pixel in the file
 *
 *
 * @par Example:
   @verbatim
   ofstream fout;
   image img;
   int maxPixel=255;

   handleOutput("--sepia", "--binary",img, fout, int maxPixel)
   //this function will call writeFileP6(fout, img, maxpixel)
   //to write the data to the file

   @endverbatim

 ***********************************************************************/
void handleOutput(string option, string type, image img, ofstream& fout, int maxPixel)
{
    //check if option is --grayscale
    if (option == "--grayscale")
    {
        //if grayscale, call P5 or P2 functions according to the option string
        if (type == "--binary")
        {
            writeGrayP5(fout, img, maxPixel);
        }

        else if (type == "--ascii")
        {
            writeGrayP2(fout, img, maxPixel);
        }
    }


    //if type is --ascii, call writeP3
    else if (type == "--ascii")
    {
        writeFileP3(fout, img, maxPixel);
    }


    //if type is --ascii, call writeP6
    else if (type == "--binary")
    {
        writeFileP6(fout, img, maxPixel);
    }
}


/** *********************************************************************
* @author Niven Fernandes
*
* @par Description:
* Prints usage statement
*
*
*
* @par Example:
  @verbatim

  int main()
  {
    bool isInvalid;

    if(isInvalid)
    {
       printUsage();
       //it will print the usage statement
       return 0;
    }

  }

  @endverbatim

***********************************************************************/
void printUsage()
{

    //print the usage error statement
    cout << "Usage:thpExam1.exe [option] --outputtype basename image.ppm" << endl;
    cout << endl;

    cout << "Output Type" << endl;
    cout << endl;
    cout << "       --ascii            integer text numbers will be written for the data" << endl;
    cout << "       --binary            integer numbers will be written in binary form" << endl;

    cout << endl;

    cout << "Option Code            " << endl;

    cout << "       --flipX            Flip the image on the X axis" << endl;
    cout << "       --flipY            Flip the image on the Y axis" << endl;
    cout << "       --roatateCW        Rotate the image clockwise" << endl;
    cout << "       --roatateCCW       Rotate the image counter clockwise" << endl;
    cout << "       --grayscale        Convert image to grayscale" << endl;
    cout << "       --sepia            Antique a color image" << endl;

}