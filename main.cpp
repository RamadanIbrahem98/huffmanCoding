#include "huffman.hpp"
/**
* getExtension takes the full path of the input file and returns 
* the extension of the file (it has to be only 3 characters) 
* 
* @param path is the full path of the input file
* @return string that returns the extension (i.e. .aaa)
*/
inline std::string getExtension(const std::string& path)
{
    std::string::size_type index = path.rfind(".");

    if (index != std::string::npos && index+3 < path.length())
    {
        return path.substr(index, 4);
    }
    else
    {
        return "";
    }
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        std::cerr << "You have to Pass the file to be encoded or decoded.\n";
    }
    else
    {
        std::string path = argv[1];

        std::string::size_type index = std::string(argv[1]).rfind("/");
        std::string fileName = "";
        fileName.append(path.begin()+ index + 1,path.end() - 4);

        HuffmanCoding H(fileName);

        if (argc == 2)
        {
            if (getExtension(path) == ".pgm")
            {
                H.encode(path);
            }
            else
            {
                std::cerr << "Please Input .pgm file to be encoded\nor a .huf and .frq files to be decoded";
            }
        }
        else if(argc == 3)
        {
            if (getExtension(argv[1]) == ".huf")
            {
                if(getExtension(argv[2]) == ".frq")
                {
                    H.decode(argv[1], argv[2]);
                }
                else
                {
                    std::cerr << "Please Input the .frq file";
                }
            }
            else if (getExtension(argv[1]) == ".frq")
            {
                if(getExtension(argv[2]) == ".huf")
                {
                    H.decode(argv[2], argv[1]);
                }
                else
                {
                    std::cerr << "Please Input the .huf file";
                }
            }
        }
    }
    return 0;
}