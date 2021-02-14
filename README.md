# Huffman Coding

<p align="center">
  <img src="https://img.shields.io/github/license/RamadanIbrahem98/huffmanCoding?style=plastic&logo=appveyor&color=blue" alt="license" />
  <img src="https://img.shields.io/github/last-commit/RamadanIbrahem98/huffmanCoding?style=plastic&logo=appveyor" alt="last-commit" />
</p>

This is an Implementation for the huffman coding algorithm for lossless compression.
This implementation is done on PGM greyscale photo files with some examples in the **data** folder.

## Table of contents
* [Running](#Running)
* [Status](#Status)
* [About](#About)

## Running
> To compile Project run the following command
```terminal
g++ main.cpp huffman.cpp IOStream.cpp -o huffman
```

> To Run the program for compression you should pass one argument (photo path) and you should have a folder in the pwd named ``encoded``
```terminal
./huffman ./directory/filename.pgm
```

> To Run the program for decompression you should pass two arguments (frequency table and compressed file) and you shold have a folder in the pwd named ``decoded``
```terminal
./huffman ./encoded/filename.huf ./encoded/filename.frq
```

### Using CMake
> To compile project run the following commands
```terminal
mkdir build
cd build
mkdir encoded decoded
cmake ..
make
```
> To Run the program for compression you should pass one argument (photo path) and you should have a folder in the pwd named ``encoded``
```terminal
./huffman ../data/filename.pgm
```
> To Run the program for decompression you should pass two arguments (frequency table and compressed file) and you shold have a folder in the pwd named ``decoded``
```terminal
./huffman ./encoded/filename.huf ./encoded/filename.frq
```


## Status
* The Console application is done.

## About
> This is part of the SBE201 course in the [Systems and Biomedical Engineering Department - Cairo University](http://bmes.cufe.edu.eg/)\
 Dr.Ahmed Kandil\
 TA. Asem Alaa
