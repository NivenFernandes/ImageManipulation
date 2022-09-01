/** *********************************************************************
 * @file
 *
 * @brief   simple sorts and supporting functions.
 ***********************************************************************/
#include "netPBM.h"


 /** *********************************************************************
  * @author Niven Fernandes
  *
  * @par Description:
  * This function will open the file with the given name in binary for
  * input in ate so that we can move around in the file to input data
  *
  * @param[in] bfile - the name of the binary file to be opened
  * @param[out] fin - the input file stream
  *
  * @returns true - file open sucessful
  *
  * @par Example:
    @verbatim

    ifstream fin;
    string name="MybFile";
    bool open= isBinFileOpen(MybFile, fin);
    //open will be true if it was able to open the file, false otherwie

    @endverbatim

  ***********************************************************************/
bool isBinFileOpen(string bfile, ifstream& fin)
{
    //open the files
    fin.open(bfile, ios::in | ios::ate | ios::binary);

    //check if the files were opened if not give a message and exit the program
    if (!fin.is_open())
    {
        cout << "Unable to open binary file: " << bfile;
        exit(0);
    }
    return true;
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function will open the file with the given name in binary for
 * output.
 *
 * @param[in] file - the name of the binary file to be opened
 * @param[out] fout - the output file stream
 *
 * @returns true - file open sucessful
 * @par Example:
   @verbatim

   ofstream fout;
   string name="MybFile";
   bool open= isBinOutputOpen(MybFile, fout);
   //open will be true if it was able to open the file, false otherwie

   @endverbatim

 ***********************************************************************/
bool isBinOutputOpen(string file, ofstream& fout)
{
    //open the files
    fout.open(file, ios::out | ios::binary);

    //check if the files were opened if not give a message and exit the program
    if (!fout.is_open())
    {
        cout << "Unable to open output file: " << file;
        exit(0);
    }
    return true;
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function will read all the data in the structure. It reads the
 * file till the maxPixel, calls the appropriate functino to read
 * the rest data
 *
 * @param[out] fin - the input stream
 * @param[out] img -  the structure which will store the data
 * @param[out] maxPixel - the varaible which will store the msxPixel
 *
 * @returns true - if it is able to read all the data
 * @par Example:
   @verbatim

   ifstream fin;
   image img;
   int maxPixel;

   bool read =readFile(fin, img, maxPixel)
   //image will contain all the data from the file
   // maxPixel will contain the max pixel

   @endverbatim

 ***********************************************************************/
bool readFile(ifstream& fin, image& img, int& maxPixel)
{
    bool isComment = true;
    string line;
    unsigned char comment;
    bool read;

    //seek to th begaining
    fin.seekg(0, ios::beg);
    //read the magic number
    fin >> img.magicNumber;

    //if the magic number is not P3 or P6 exit the program
    if (img.magicNumber != "P3" && img.magicNumber != "P6")
    {
        cout << "Invalid  magic number" << endl;
        exit(0);
    }

    //ignore any extra character
    fin.ignore();

    //read the comments
    while (isComment)
    {
        isComment = false;
        //peek to see if the next line is a comment
        comment = fin.peek();
        if (comment = '#')
        {
            getline(fin, line);
            //use += and '\n' to get multiple line comments
            img.comment = img.comment + line + '\n';
        }
    }

    //read image columns
    fin >> img.cols;
    //input image rows
    fin >> img.rows;

    //read maxPixel
    fin >> maxPixel;
    fin.ignore();

    //call createArray function to create dynamic arrays
    img.redGray = createArrays(img.rows, img.cols);
    img.green = createArrays(img.rows, img.cols);
    img.blue = createArrays(img.rows, img.cols);

    //if magic number is P3 call readFileP# function
    if (img.magicNumber == "P3")
    {
        read = readFileP3(fin, img);
    }

    //else call readFileP6 funcxtion
    else
    {
        read = readFileP6(fin, img);
    }

    //return the boolean
    return read;
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * reads the integer data from a ascii file which is stored as pixels
 * into the dynamic arrays in  the strucure
 *
 * @param[in, out] fin - the input stream
 * @param[in, out] img - the strucure to which the data is stored to
 *
 * @returns true - sucessful in reading the file
 * @par Example:
   @verbatim

   ifstream fin;
   image img;
   int maxPixel;
   bool read;

   read=readFileP3(fin, img, maxPixel);
   //if read is true the data from the ascii file is stored in dynamic
   //arrays of img

   @endverbatim

 ***********************************************************************/
bool readFileP3(ifstream& fin, image& img)
{
    //declare variables
    int i, j;
    int input, input1, input2;

    //go through each row 
    for (i = 0; i < img.rows; i++)
    {
        //go through each column
        for (j = 0; j < img.cols; j++)
        {
            //input the data as int into the temp variables
            fin >> input >> input1 >> input2;
            //store them as pixels in the array
            img.redGray[i][j] = pixel(input);
            img.green[i][j] = pixel(input1);
            img.blue[i][j] = pixel(input2);
        }
    }

    //sucessful in reading
    return true;
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * reads the pixel data from a binary file into the dynamic arrays in the
 * strucure
 *
 * @returns true - sucessful in reading the file
 *
 * @param[in, out] fin - the input stream
 * @param[in, out] img - the strucure to which the data is stored to
 *
 * @par Example:
   @verbatim

   ifstream fin;
   image img;
   int maxPixel;
   bool read;

   read=readFileP6(fin, img, maxPixel);
   //if read is true, the data from the binary file is stored
   //in dynamic arrays in img
   @endverbatim

 ***********************************************************************/
bool readFileP6(ifstream& fin, image& img)
{
    int i, j;

    //go through each row 
    for (i = 0; i < img.rows; i++)
    {
        //go through each column
        for (j = 0; j < img.cols; j++)
        {
            //use fin.read to input the data in the 2D dynamic array
            fin.read((char*)&img.redGray[i][j], sizeof(unsigned char));
            fin.read((char*)&img.green[i][j], sizeof(unsigned char));
            fin.read((char*)&img.blue[i][j], sizeof(unsigned char));
        }
    }
    //sucessful in reading
    return true;
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function writes the data from the 2D dynamic array and the maxPixel
 * to the file in ascii. the magic number will be P3
 *
 * @returns true - sucessful in writing the file
 *
 * @param[in] fout - the output stream
 * @param[in] img - the strucure which has the data
 * @param[in] maxPixel - the maxPixel in the data file
 *
 * @par Example:
   @verbatim

   ofstream fout;
   image img;
   //consider we allocate some data to dynamic arrays in img
   int maxPixel=255;
   bool write;

   write=writeFileP3(fout, img, maxPixel);
   //if write is true the data from the structure and maxPixel is
   //written to the file in ascii
   @endverbatim

 ***********************************************************************/
bool writeFileP3(ofstream& fout, image img, int maxPixel)
{
    int i, j;
    //write data from the magic number till maxPixel
    fout << "P3" << '\n';
    fout << img.comment;
    fout << img.cols << " " << img.rows << endl;
    fout << maxPixel << '\n';

    //Go through each row of the array
    for (i = 0; i < img.rows; i++)
    {
        //Go through each column 
        for (j = 0; j < img.cols; j++)
        {
            //write data as int to the file
            fout << int(img.redGray[i][j]) << endl;
            fout << int(img.green[i][j]) << endl;
            fout << int(img.blue[i][j]) << endl;
        }
    }

    //sucessful in writing
    return true;
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function writes the data from the 2D dynamic array and the maxPixel
 * to the file in binary. The magic number will be P6
 *
 * @returns true - sucessful in writing the file
 *
 * @param[in] fout - the output stream
 * @param[in] img - the strucure which has the data
 * @param[in] maxPixel - the maxPixel in the data file
 *
 * @par Example:
   @verbatim

   ofstream fout;
   image img;
   //consider we allocate some data to dynamic arrays in img
   int maxPixel=255;
   bool write;

   write=writeFileP6(fout, img, maxPixel);
   //if write is true the data from the structure and maxPixel is
   //written to the file in binary
   @endverbatim

 ***********************************************************************/
bool writeFileP6(ofstream& fout, image img, int maxPixel)
{
    int i, j;

    //write data from the magic number till maxPixel
    fout << "P6" << '\n';
    fout << img.comment;
    fout << img.cols << " " << img.rows << endl;
    fout << maxPixel << '\n';

    //Go through each row of the array
    for (i = 0; i < img.rows; i++)
    {
        //Go through each column of the array
        for (j = 0; j < img.cols; j++)
        {
            //write the data as pixels to the binary file
            fout.write((char*)&img.redGray[i][j], sizeof(unsigned char));
            fout.write((char*)&img.green[i][j], sizeof(unsigned char));
            fout.write((char*)&img.blue[i][j], sizeof(unsigned char));
        }
    }

    //sucessful in writing
    return true;
}


/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function writes the data from img.redGray and the maxPixel
 * to the file in ascii. The magic number will be P2.
 *
 * @returns true - sucessful in writing the file
 *
 * @param[in] fout - the output stream
 * @param[in] img - the strucure which has the img.redGray data
 * @param[in] maxPixel - the maxPixel in the data file
 *
 * @par Example:
   @verbatim

   ofstream fout;
   image img;
   //consider we allocate some data to dynamic array img.redGray
   int maxPixel=255;
   bool write;

   write = writeGrayP2(fout, img, maxPixel);
   //if write is true the data from the structure and maxPixel is
   //written to the file in ascii
   @endverbatim

 ***********************************************************************/
bool writeGrayP2(ofstream& fout, image img, int maxPixel)
{
    int i, j;

    //write data from the magic number till maxPixel
    fout << "P2" << '\n';
    fout << img.comment;
    fout << img.cols << " " << img.rows << endl;
    fout << maxPixel << '\n';

    //Go through each row of the array
    for (i = 0; i < img.rows; i++)
    {
        //Go through each row of the array
        for (j = 0; j < img.cols; j++)
        {
            //write the data from img.redGray as int to the file
            fout << int(img.redGray[i][j]) << endl;
        }
    }
    //sucessful in writing
    return true;
}

/** *********************************************************************
 * @author Niven Fernandes
 *
 * @par Description:
 * This function writes the data from img.redGray and the maxPixel
 * to the file in binary. The magic number will be P5.
 *
 * @returns true - sucessful in writing the file
 *
 * @param[in] fout - the output stream
 * @param[in] img - the strucure which has the img.redGray data
 * @param[in] maxPixel - the maxPixel in the data file
 *
 * @par Example:
   @verbatim

   ofstream fout;
   image img;
   //consider we allocate some data to dynamic array img.redGray
   int maxPixel=255;
   bool write;

   write = writeGrayP5=(fout, img, maxPixel);
   //if write is true the data from the structure and maxPixel is
   //written to the file in binary
   @endverbatim

 ***********************************************************************/
bool writeGrayP5(ofstream& fout, image img, int maxPixel)
{
    int i, j;

    //write data from the magic number till maxPixel
    fout << "P5" << '\n';
    fout << img.comment;
    fout << img.cols << " " << img.rows << endl;
    fout << maxPixel << '\n';

    //Go through each row of the array
    for (i = 0; i < img.rows; i++)
    {
        //Go through each row of the array
        for (j = 0; j < img.cols; j++)
        {
            //write the data from the array to the files as pixels
            fout.write((char*)&img.redGray[i][j], sizeof(unsigned char));
        }
    }

    //sucessful in writing
    return true;
}
