#include "IOStream.hpp"

void IOStream::setTargetName(std::string filename)
{
    targetName = filename;
}

void IOStream::pgmRead(std::string target, std::string &filetype, int &rows, int &cols,
                       int &greyScaleMax, int &size, std::vector<uint8_t> &input)
{
    std::ifstream read(target, std::ios::in | std::ios::binary);
    if (read.fail())
    {
        std::cerr << "Couldn't Open \"" << target << "\", Make sure that file exists";
        return;
    }

    read >> filetype >> rows >> cols >> greyScaleMax;
    size = rows * cols;

    std::cout << "filetype: " << filetype << "\n";
    std::cout << "rows: " << rows << "\n";
    std::cout << "cols: " << cols << "\n";
    std::cout << "greylevels: " << greyScaleMax << "\n";
    std::cout << "size: " << size << "\n";

    for (int i = 0; i < size; i++)
    {
        uint8_t pixel = read.get();

        int t_data = static_cast<int>(pixel);

        input.push_back(t_data);
    }

    read.close();
}

void IOStream::pgmWrite(std::string filetype, int rows, int cols,
                        int greyScaleMax, std::vector<uint8_t> &decoded)
{
    std::cout << "filetype: " << filetype << "\n";
    std::cout << "rows: " << rows << "\n";
    std::cout << "cols: " << cols << "\n";
    std::cout << "greylevels: " << greyScaleMax << "\n";
    std::cout << "size: " << rows * cols << "\n";

    std::string target = "./decoded/" + targetName + ".pgm";
    std::ofstream write(target, std::ios::out | std::ios::binary);
    if (write.fail())
    {
        std::cerr << "Couldn't Write to directory \"" << target << "\" Make sure it exists";
        return;
    }
    write << filetype << "\n"
          << rows << " " << cols << "\n"
          << greyScaleMax << "\n";

    int line = 1;
    if (filetype.compare("P5") == 0)
    {
        for (auto value : decoded)
        {
            write << value;
        }
    }
    else
    {
        for (auto value : decoded)
        {
            write << (int)value << " ";
            if (line % 50 == 0)
                write << "\n";
            line++;
        }
    }
}

void IOStream::hufRead(std::string target, std::string &strDecoded)
{
    std::ifstream read(target, std::ios::in | std::ios::binary);
    if (read.fail())
    {
        std::cerr << "Couldn't Open the encoded file. Make sure that \"" << target << "\" exists";
        return;
    }
    strDecoded = "";
    int8_t packed;

    while (!read.eof())
    {
        packed = read.get();
        int t_data = static_cast<int>(packed);
        strDecoded += std::bitset<8>(t_data).to_string();
    }
    read.close();
}

void IOStream::hufWrite(std::vector<int8_t> &data)
{
    std::string target = "./encoded/" + targetName + ".huf";
    std::ofstream write(target, std::ios::out | std::ios::binary);
    if (write.fail())
    {
        std::cerr << "Couldn't Write to directory \"" << target << "\" Make sure it exists";
        return;
    }

    for (auto value : data)
    {
        write << value;
    }
    write.close();
}

void IOStream::freqRead(std::string target, std::string &filetype, int &rows, int &cols,
                        int &greyScaleMax, int &size, int &encodedLength, std::map<int, int> &freq)
{
    std::ifstream read(target, std::ios::in | std::ios::binary);

    if (read.fail())
    {
        std::cerr << "Couldn't Open the Frequency Table. Make sure that \"" << target << "\" exists";
        return;
    }
    read >> filetype >> rows >> cols >> greyScaleMax >> encodedLength;
    size = rows * cols;

    int greyValue;
    int frequency;
    while (true)
    {
        read >> greyValue >> frequency;
        if (read.eof())
            break;
    }
    read.close();
}

void IOStream::freqWrite(std::string &filetype, int &rows, int &cols,
                         int &greyScaleMax, int encodedLength, std::map<int, int> freq)
{
    std::string target = "./encoded/" + targetName + ".frq";
    std::ofstream write(target, std::ios::out | std::ios::binary);
    if (write.fail())
    {
        std::cerr << "Couldn't Write to directory " << target << "\n"
                  << "Make Sure the Directory exists";
        return;
    }
    write << filetype << " " << rows << " " << cols << " " << greyScaleMax << " " << encodedLength << "\n";

    for (auto value : freq)
    {
        write << (int)(value.first) << " " << (int)(value.second) << "\n";
    }
    write.close();
}
