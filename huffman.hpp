#ifndef __SBE201__2020__TEAM01__HUFFMAN__H__
#define __SBE201__2020__TEAM01__HUFFMAN__H__

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// #include <map>
// #include <string>
// #include <stdint.h>

#include <bits/stdc++.h>

#include "IOStream.hpp"

/**
* Node is a structure that contains the important information of
* every node in the huffman tree
* 
* greyScaleValue is the level of grey color which is in range [0,255]
* freq is the frequency of occurance of the grey level in the PGM file
* left is the left child if found (default = NULL)
* right is the right child if found (default = NULL)
*/
struct Node
{
    int greyScaleValue;
    int freq;
    Node* left = nullptr;
    Node* right = nullptr;
};

class HuffmanCoding
{
public:
	
	/**
 	* HuffmanCoding is a constructor that sets the file name of the 
	* IOStream object IO to that of the file entered in command line
 	*/
	HuffmanCoding(std::string fileName);

	/**
 	* encode is used to start the encoding process and is called from main
	*  
	* @param toEncode this is a string that represents the full path of the PGM file
 	*/
    void encode(std::string toEncode);

	/**
 	* decode is used to start the decoding process and is called from main
	* 
	* @param hufDestination is the full path of the .huf file (contains encoded data)
	* @param freqDestination is the full path of the .frq file (contains frequency table)
 	*/
    void decode(std::string hufDestination, std::string freqDestination);

private:
	std::string filetype;								// This is the type of the PGM file (P2 or P%)
	int rows, cols, size;								// This is the parametes of the photo
	int greyscaleMax;									// This is the max grey level (usually 255)
	IOStream IO;										// This is an object of the class IOStream

	Node* builtTree;									// This is the root node of the huffman tree

	std::vector<uint8_t> input;							// This is a vector that holds each PGM pixel value
	std::vector<int8_t> decimalPacked;					// This is a vector that holds each PGM pixel after being Encoded
	std::vector<uint8_t> decoded;						// This is a vector that holds each PGM pixel after being Decoded
	std::map<int, int> freqTable;					// This is a map that holds the frequency pair of each grey level
	std::map<uint8_t, std::string> leafCodeWord;		// This is a map that holds the codeWord of each grey Level after Encoding
	std::string strEncoded;								// This is a string that holds the Encoded pixels in order after Encoding in binary format
	std::string strToDecode;							// This is a string that holds the Encoded pixels in binary format to be Decoded
	int encodedLength;									// This is an integer that represents the total number of bits in the binary strEncoded

	/**
 	* Construct the frequency table of each greyLevel value
	* using a map called freqTable
 	*/
	void constructFreqTable();
	
	/**
 	* Construct tree is used to construct the huffman tree
	* out of the frequency table using a minHeap priority queue
 	*/
	void constructTree();

	/**
 	* Construct codeWords is used after the construction of the tree
	* to set each leaf node of the tree to its modified codeWord 
	* using the convention of adding 0 on traversing left and 1 on
	* traversing right
 	*/
	void constructCodeWords(Node *parent, char *word, int index);

	/**
 	* Create Encoded works on the original data of the PGM file and
	* change every pixel value with its modified codeWord value
 	*/
	void createEncoded();

	/**
 	* to decimal is used to pack every 8 succissive bits zeros and ones
	* into one byte
 	*/
	void toDecimal();

	/**
 	* Traverse Down is used to reverse the encoding process and get the
	* original value of every bit of the code
 	*/
	void traverseDown();
};

#endif