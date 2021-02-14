#ifndef __SBE201__2020__TEAM01__IOSTREAM__H__
#define __SBE201__2020__TEAM01__IOSTREAM__H__

// #include <fstream>
// #include <iostream>
// #include <vector>
// #include <map>

#include <bits/stdc++.h>

class IOStream
{
public:
   /**
 	* setTargetName is the first method called when starting encoding or
	* decoding process
    *
    * @param filename is the name of the file to be encoded/decoded
 	*/
   void setTargetName(std::string filename);

   /**
 	* pgmRead Reads the PGM file and saves its parameters in different variables
	* 
    * @param target this is the full path of the PGM file to be opened
    * @param filetype this is the file type of the PGM and it is either P2 or P5
    * @param row is the nubmer of rows in the Image
    * @param cols is the number of columbs in the Image
    * @param greyScaleMax is the maximum potential value of the pixels
    * @param size is the total number of pixels
    * @param input is the vector that contains all of the pixels values in order
 	*/
   void pgmRead(std::string target, std::string &filetype, int &rows, int &cols,
                int &greyScaleMax, int &size, std::vector<uint8_t> &input);

   /**
 	* pgmWrite writes the PGM file after being decoded from .huf and .frq
	* 
    * @param decoded is the vector that holds the decoded pixels in order
    * Other parameters are the same as that of pgmRead method
 	*/
   void pgmWrite(std::string filetype, int rows, int cols,
                 int greyScaleMax, std::vector<uint8_t> &decoded);

   /**
 	* huffRead Reads the content of the encoded .huf file
    *
    * @param target if the full path of the .huf file to be decoded
	* @param strDecoded is a string that holds the encoded data in binary format
    * to traverse down the huffman tree with it to retieve the original data
 	*/
   void hufRead(std::string target, std::string &strDecoded);

   /**
 	* huffWrite writes the encoded .huf file into the encoded directory
	* 
    * @param data is a vector of the pixels encoded data to be printed to file
 	*/
   void hufWrite(std::vector<int8_t> &data);

   /**
 	* freqRead Reads the Frequency table pairs into a map
    *
	* @param encodedLength is an integer that holds the number of bits encoded
    * @param ferq is a map that holds the pairs of greyLevels and their frequencies
    * Other parameters are discribed with the pgmRead method
 	*/
   void freqRead(std::string target, std::string &filetype, int &rows, int &cols,
                 int &greyScaleMax, int &size, int &encodedLength, std::map<int, int> &freq);

   /**
 	* freqWrite Writes writes the frequency table in the .frq file 
    * it also saves the pgm parameters for the decoding process 
	* 
    * @param encodedLength is the total number of bits in the encoded huf files
    * @param freq is the frequency table pairs
    * Other parameters are the same as that of pgmRead
 	*/
   void freqWrite(std::string &filetype, int &rows, int &cols,
                  int &greyScaleMax, int encodedLength, std::map<int, int> freq);

private:
   std::string targetName; // This is the absolute file name
};

#endif