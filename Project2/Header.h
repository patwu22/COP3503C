#pragma once
#include <fstream>
using namespace std;

struct Header
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    void loadHeader(ifstream &fin)
    {
        fin.read(&idLength, 1);
        fin.read(&colorMapType, 1);
        fin.read(&dataTypeCode, 1);
        fin.read((char *)&colorMapOrigin, 2);
        fin.read((char *)&colorMapLength, 2);
        fin.read(&colorMapDepth, 1);
        fin.read((char *)&xOrigin, 2);
        fin.read((char *)&yOrigin, 2);
        fin.read((char *)&width, 2);
        fin.read((char *)&height, 2);
        fin.read(&bitsPerPixel, 1);
        fin.read(&imageDescriptor, 1);
    }

    void writeHeader(ofstream &fout)
    {
        fout.write(&idLength, 1);
        fout.write(&colorMapType, 1);
        fout.write(&dataTypeCode, 1);
        fout.write((char *)&colorMapOrigin, 2);
        fout.write((char *)&colorMapLength, 2);
        fout.write(&colorMapDepth, 1);
        fout.write((char *)&xOrigin, 2);
        fout.write((char *)&yOrigin, 2);
        fout.write((char *)&width, 2);
        fout.write((char *)&height, 2);
        fout.write(&bitsPerPixel, 1);
        fout.write(&imageDescriptor, 1);
    }
};
