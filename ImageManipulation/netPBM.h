/** *********************************************************************
 * @file
 *
 * @brief   Prototypes and structure
 ***********************************************************************/

#include<fstream>
#include <string>
#include<iostream>
#include<iomanip>

using namespace std;

#ifndef _NETPBM_H_
#define  _NETPBM_H_

/************************************************************************
 *             Typedef
 ***********************************************************************/
 /*!
  * @brief pixel as an allias of unsigned char
  */
typedef unsigned char pixel;



/************************************************************************
 *             Structure
 ***********************************************************************/
 /**
 * @brief Holds data of the netPBM image
 */
struct image
{
    /**
    * @brief holds the magic number of the netPBM file
    */
    string magicNumber;
    /**
    * @brief holds the magic number of the netPBM file
    */
    string comment;
    /**
    * @brief holds the number of rows
    */
    int rows;
    /**
    * @brief holds the number of columns
    */
    int cols;
    /**
    * @brief pointer to a 2D dynamica array redGray
    */
    pixel** redGray;
    /**
    * @brief pointer to a 2D dynamica array green
    */
    pixel** green;
    /**
    * @brief pointer to a 2D dynamica array blue
    */
    pixel** blue;
};


/************************************************************************
 *               Prototypes
 ***********************************************************************/
void printUsage();

bool isBinFileOpen(string bfile, ifstream& fin);
bool isBinOutputOpen(string file, ofstream& fout);

bool readFile(ifstream& fin, image& img, int& maxPixel);
bool readFileP3(ifstream& fin, image& img);
bool readFileP6(ifstream& fin, image& img);

pixel** createArrays(int rows, int cols);
void clearArray(pixel**& pointer, int rows);
void copyArray(pixel**& array, pixel** array1, image img);

void handleOptions(string option, image& img);
void rotateImageCW(image& img);
void rotateImageCCW(image& img);
void flipX(image& img);
void flipY(image& img);
void grayScale(image& img);
void sepia(image& img);

void handleOutput(string option, string type, image img, ofstream& fout, int maxPixel);

bool writeFileP3(ofstream& fout, image img, int maxPixel);
bool writeFileP6(ofstream& fout, image img, int maxPixel);
bool writeGrayP2(ofstream& fout, image img, int maxPixel);
bool writeGrayP5(ofstream& fout, image img, int maxPixel);
#endif
