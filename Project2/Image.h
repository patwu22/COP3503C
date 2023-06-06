#pragma once
#include <string>
#include <fstream>
#include "Header.h"
using namespace std;

class Image
{
    struct Pixel
    {
        unsigned char B;
        unsigned char G;
        unsigned char R;

        template <typename T>
        T clamp(T i)
        {
            if (i < 0)
                return 0;
            if (i > 255)
                return 255;
            return i;
        }

        void loadPixel(ifstream &fin)
        {
            fin.read((char *)&B, 1);
            fin.read((char *)&G, 1);
            fin.read((char *)&R, 1);
        }

        void writePixel(ofstream &fout)
        {
            fout.write((char *)&B, 1);
            fout.write((char *)&G, 1);
            fout.write((char *)&R, 1);
        }

        void multiplyPixel(float _b, float _g, float _r)
        {
            B = (unsigned char)clamp((float)B * _b / 255 + 0.5f);
            G = (unsigned char)clamp((float)G * _g / 255 + 0.5f);
            R = (unsigned char)clamp((float)R * _r / 255 + 0.5f);
        }

        void screenPixel(unsigned char _b, unsigned char _g, unsigned char _r)
        {
            B = (unsigned char)((float)B + (float)_b - (float)B * (float)_b / 255 + 0.5f);
            G = (unsigned char)((float)G + (float)_g - (float)G * (float)_g / 255 + 0.5f);
            R = (unsigned char)((float)R + (float)_r - (float)R * (float)_r / 255 + 0.5f);
        }

        void addPixel(unsigned char _b, unsigned char _g, unsigned char _r)
        {
            B = (unsigned char)clamp((int)B + (int)_b);
            G = (unsigned char)clamp((int)G + (int)_g);
            R = (unsigned char)clamp((int)R + (int)_r);
        }

        void subtractPixel(unsigned char _b, unsigned char _g, unsigned char _r)
        {
            B = (unsigned char)clamp((int)B - (int)_b);
            G = (unsigned char)clamp((int)G - (int)_g);
            R = (unsigned char)clamp((int)R - (int)_r);
        }

        void editPixel(unsigned char _b, unsigned char _g, unsigned char _r)
        {
            B = _b;
            G = _g;
            R = _r;
        }
    };

    Header ImgHead;
    Pixel *Pixels = nullptr;
    unsigned int numPixels;

public:
    Image();
    ~Image();

    bool open(string fname);
    void output(string fname);
    void Multiply(Image &bImage);
    void Multiply(unsigned int _b, unsigned int _g, unsigned int _r);
    void Screen(Image &bImage);
    void Addition(Image &bImage);
    void Addition(unsigned int _b, unsigned int _g, unsigned int _r);
    void Subtract(Image &bImage);
    void Subtract(unsigned int _b, unsigned int _g, unsigned int _r);
    void Overlay(Image &bImage);
    void Separate(unsigned int clr);
    void Combine(Image &bImage, unsigned int clr);
    void Rotate180();
};
