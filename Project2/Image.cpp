#include "Image.h"

Image::Image() {}

Image::~Image()
{
    delete[] Pixels;
    Pixels = nullptr;
}

bool Image::open(string fname)
{
    ifstream fin;
    fin.open(fname, ifstream::binary);
    if (fin.is_open())
    {
        ImgHead.loadHeader(fin);
        numPixels = ImgHead.width * ImgHead.height;
        Pixels = new Pixel[numPixels];
        for (unsigned int i = 0; i < numPixels; i++)
        {
            Pixels[i].loadPixel(fin);
        }
        fin.close();
        return true;
    }
    return false;
}

void Image::output(string fname)
{
    ofstream fout;
    fout.open(fname, ofstream::binary);
    if (fout.is_open())
    {
        ImgHead.writeHeader(fout);
        for (unsigned int i = 0; i < numPixels; i++)
        {
            Pixels[i].writePixel(fout);
        }
    }
    fout.close();
}

void Image::Multiply(Image &bImage)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        Pixels[i].multiplyPixel((float)bImage.Pixels[i].B, (float)bImage.Pixels[i].G, (float)bImage.Pixels[i].R);
    }
}

void Image::Multiply(unsigned int _b, unsigned int _g, unsigned int _r)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        Pixels[i].multiplyPixel((float)(_b * 255), (float)(_g * 255), (float)(_r * 255));
    }
}

void Image::Screen(Image &bImage)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        Pixels[i].screenPixel(bImage.Pixels[i].B, bImage.Pixels[i].G, bImage.Pixels[i].R);
    }
}

void Image::Addition(Image &bImage)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        Pixels[i].addPixel(bImage.Pixels[i].B, bImage.Pixels[i].G, bImage.Pixels[i].R);
    }
}

void Image::Addition(unsigned int _b, unsigned int _g, unsigned int _r)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        Pixels[i].addPixel((unsigned char)_b, (unsigned char)_g, (unsigned char)_r);
    }
}

void Image::Subtract(Image &bImage)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        Pixels[i].subtractPixel(bImage.Pixels[i].B, bImage.Pixels[i].G, bImage.Pixels[i].R);
    }
}

void Image::Subtract(unsigned int _b, unsigned int _g, unsigned int _r)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        Pixels[i].subtractPixel((unsigned char)_b, (unsigned char)_g, (unsigned char)_r);
    }
}

void Image::Overlay(Image &bImage)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        if ((float)bImage.Pixels[i].B / 255 <= 0.5f)
        {
            Pixels[i].B = (unsigned char)(2 * (float)Pixels[i].B / 255 * (float)bImage.Pixels[i].B + 0.5f);
        }
        else
        {
            Pixels[i].B = (unsigned char)((1 - 2 * (1 - (float)Pixels[i].B / 255) * (1 - (float)bImage.Pixels[i].B / 255)) * 255 + 0.5f);
        }
        if ((float)bImage.Pixels[i].G / 255 <= 0.5f)
        {
            Pixels[i].G = (unsigned char)(2 * (float)Pixels[i].G / 255 * (float)bImage.Pixels[i].G + 0.5f);
        }
        else
        {
            Pixels[i].G = (unsigned char)((1 - 2 * (1 - (float)Pixels[i].G / 255) * (1 - (float)bImage.Pixels[i].G / 255)) * 255 + 0.5f);
        }
        if ((float)bImage.Pixels[i].R / 255 <= 0.5f)
        {
            Pixels[i].R = (unsigned char)(2 * (float)Pixels[i].R / 255 * (float)bImage.Pixels[i].R + 0.5f);
        }
        else
        {
            Pixels[i].R = (unsigned char)((1 - 2 * (1 - (float)Pixels[i].R / 255) * (1 - (float)bImage.Pixels[i].R / 255)) * 255 + 0.5f);
        }
    }
}

void Image::Separate(unsigned int clr)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        if (clr == 1)
            Pixels[i].editPixel(Pixels[i].B, Pixels[i].B, Pixels[i].B);
        else if (clr == 2)
            Pixels[i].editPixel(Pixels[i].G, Pixels[i].G, Pixels[i].G);
        else if (clr == 3)
            Pixels[i].editPixel(Pixels[i].R, Pixels[i].R, Pixels[i].R);
    }
}

void Image::Combine(Image &bImage, unsigned int clr)
{
    for (unsigned int i = 0; i < numPixels; i++)
    {
        if (clr == 1)
            Pixels[i].editPixel(bImage.Pixels[i].B, Pixels[i].G, Pixels[i].R);
        else if (clr == 2)
            Pixels[i].editPixel(Pixels[i].B, bImage.Pixels[i].G, Pixels[i].R);
        else if (clr == 3)
            Pixels[i].editPixel(Pixels[i].B, Pixels[i].G, bImage.Pixels[i].R);
    }
}

void Image::Rotate180()
{
    Pixel *newPixels = new Pixel[numPixels];
    for (unsigned int i = 0; i < numPixels; i++)
    {
        newPixels[i] = Pixels[numPixels - i - 1];
    }
    delete[] Pixels;
    Pixels = newPixels;
}
