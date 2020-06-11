# Huffman Coding

This is an Implementation for the huffman coding algorithm for lossless compression.
This implementation is done on PGM greyscale photo files with some examples in the **data** folder.

## Table of contents
* [Running](#Running)
* [Status](#Status)

## Running
> To compile Project run the following command
```terminal
g++ main.cpp huffman.cpp IOStream.cpp -o huffman.o
```

> To Run the program for compression you should pass one argument (photo path) and you should have a folder in the pwd named ``encoded``
```terminal
./huffman.o ./directory/filename.pgm
```

> To Run the program for decompression you should pass two arguments (frequency table and compressed file) and you shold have a folder in the pwd named ``decoded``
```terminal
./huffman.o ./encoded/filename.huf ./encoded/filename.frq
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
./huffman.o ../data/filename.pgm
```
> To Run the program for decompression you should pass two arguments (frequency table and compressed file) and you shold have a folder in the pwd named ``decoded``
```terminal
./huffman.o ./encoded/filename.huf ./encoded/filename.frq
```


## Status
* The Console application is done.
