// Bin2Array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdint.h>
#include <fstream>
#include <ostream>
#include <istream>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: inputfile outputfile");
        return -1;
    }
    char* memblock = nullptr;
    uint32_t fileSize = 0u;

    std::ifstream file(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open())
    {
        std::streampos size = file.tellg();
        memblock = new char[size];
        fileSize = static_cast<uint32_t>(size);
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();
    }
    else
    {
        printf("Unable to open file");
    }

    if (memblock != nullptr)
    {
        std::string arrayData;
        arrayData += "uint8_t binaryArray[] = \n";
        arrayData += "{";
        for (uint32_t i = 0; i < fileSize; ++i)
        {
            if ((i % 16u) == 0u)
                arrayData += "\n\t";
            char buf[16];
            sprintf_s(buf, 16, "0x%02X, ", (uint8_t)memblock[i]);
            arrayData += buf;
        }

        arrayData.resize(arrayData.size() - 2); // Remove last comma
        arrayData += "\n};";

        std::ofstream ofile(argv[2]);
        if (ofile.is_open())
        {
            ofile.write(arrayData.c_str(), arrayData.size());
        }

    }

    delete[] memblock;

    return 0;
}