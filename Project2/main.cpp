#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
using namespace std;

bool tgaCheck(string fname);

bool argcCheck(int &i, int &argc, bool &out);

bool nameCheck(string name, Image &inImage, bool &out);

bool numCheck(char *num, unsigned int &inint, bool &neg, bool &out);

int main(int argc, char **argv)
{
    if (argc == 1 || string(argv[1]) == string("--help"))
    {
        cout << "Project 2: Image Processing, Spring 2023" << endl
             << endl;
        cout << "Usage:" << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
    }
    else
    {
        if (tgaCheck(string(argv[1])) && tgaCheck(string(argv[2])))
        {
            Image outImage;
            if (outImage.open(string(argv[2])))
            {
                string cmd;
                Image inImage;
                unsigned int inint;
                bool neg = false;
                bool out = true;
                for (int i = 3; i < argc; i++)
                {
                    cmd = argv[i];
                    if (cmd == "multiply")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (nameCheck(string(argv[i]), inImage, out))
                            {
                                outImage.Multiply(inImage);
                                inImage.~Image();
                            }
                        }
                    }
                    else if (cmd == "subtract")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (nameCheck(string(argv[i]), inImage, out))
                            {
                                outImage.Subtract(inImage);
                                inImage.~Image();
                            }
                        }
                    }
                    else if (cmd == "overlay")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (nameCheck(string(argv[i]), inImage, out))
                            {
                                outImage.Overlay(inImage);
                                inImage.~Image();
                            }
                        }
                    }
                    else if (cmd == "screen")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (nameCheck(string(argv[i]), inImage, out))
                            {
                                outImage.Screen(inImage);
                                inImage.~Image();
                            }
                        }
                    }
                    else if (cmd == "combine")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (nameCheck(string(argv[i]), inImage, out))
                            {
                                outImage.Combine(inImage, 2);
                                inImage.~Image();
                            }
                        }
                        if (argcCheck(i, argc, out))
                        {
                            if (nameCheck(string(argv[i]), inImage, out))
                            {
                                outImage.Combine(inImage, 1);
                                inImage.~Image();
                            }
                        }
                    }
                    else if (cmd == "flip")
                    {
                        outImage.Rotate180();
                    }
                    else if (cmd == "onlyblue")
                    {
                        outImage.Separate(1);
                    }
                    else if (cmd == "onlygreen")
                    {
                        outImage.Separate(2);
                    }
                    else if (cmd == "onlyred")
                    {
                        outImage.Separate(3);
                    }
                    else if (cmd == "addblue")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (numCheck(argv[i], inint, neg, out))
                            {
                                if (!neg)
                                    outImage.Addition(inint, 0, 0);
                                else
                                    outImage.Subtract(inint, 0, 0);
                            }
                        }
                    }
                    else if (cmd == "addgreen")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (numCheck(argv[i], inint, neg, out))
                            {
                                if (!neg)
                                    outImage.Addition(0, inint, 0);
                                else
                                    outImage.Subtract(0, inint, 0);
                            }
                        }
                    }
                    else if (cmd == "addred")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (numCheck(argv[i], inint, neg, out))
                            {
                                if (!neg)
                                    outImage.Addition(0, 0, inint);
                                else
                                    outImage.Subtract(0, 0, inint);
                            }
                        }
                    }
                    else if (cmd == "scaleblue")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (numCheck(argv[i], inint, neg, out))
                                outImage.Multiply(inint, 1, 1);
                        }
                    }
                    else if (cmd == "scalegreen")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (numCheck(argv[i], inint, neg, out))
                                outImage.Multiply(1, inint, 1);
                        }
                    }
                    else if (cmd == "scalered")
                    {
                        if (argcCheck(i, argc, out))
                        {
                            if (numCheck(argv[i], inint, neg, out))
                                outImage.Multiply(1, 1, inint);
                        }
                    }
                    else
                    {
                        cout << "Invalid method name." << endl;
                        out = false;
                    }
                }
                if (out)
                {
                    outImage.output(string(argv[1]));
                    outImage.~Image();
                }
            }
            else
            {
                cout << "File does not exist." << endl;
            }
        }
        else
        {
            cout << "Invalid file name." << endl;
        }
    }
    return 0;
}

bool tgaCheck(string fname)
{
    if (fname.length() > 4)
    {
        if (fname.substr(fname.length() - 4, 4) == ".tga")
            return true;
    }
    return false;
}

bool argcCheck(int &i, int &argc, bool &out)
{
    if (i + 1 < argc)
    {
        i++;
        return true;
    }
    cout << "Missing argument." << endl;
    out = false;
    return false;
}

bool nameCheck(string name, Image &inImage, bool &out)
{
    if (tgaCheck(name))
    {
        if (inImage.open(name))
            return true;
        cout << "Invalid argument, file does not exist." << endl;
        out = false;
        return false;
    }
    cout << "Invalid argument, invalid file name." << endl;
    out = false;
    return false;
}

bool numCheck(char *arg, unsigned int &inint, bool &neg, bool &out)
{
    char *isNum;
    neg = false;
    long num = strtol(arg, &isNum, 10);
    if (*isNum)
    {
        cout << "Invalid argument, expected number." << endl;
        out = false;
        return false;
    }
    if (num < 0)
    {
        num = -num;
        neg = true;
    }
    inint = (unsigned int)num;
    return true;
}
