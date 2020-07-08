/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPlane.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef IOUTIL_H
#define IOUTIL_H

#include <fstream>
using namespace std;

class IOUtil {
public:
    int readShortInteger(int pos, ifstream &in);
    void writeShortInteger(short num, int pos, ofstream &out);
    int readLongInteger(ifstream &in, int pos);
    void writeLongInteger(int num,int pos, ofstream &out);
    float readFloat(ifstream &in);
    void writeFloat( float num, ofstream &out);
    char readChar(ifstream &in);
    void writeChar(char c, ofstream &out);
    void swap(char* a, char* b);
    bool isBigEndian;
    static IOUtil* Instance()
    {
        if(instance == NULL)
            instance = new IOUtil();
        return instance;
    }
    int getFileSize(ifstream& in);

private:
    IOUtil();
    static IOUtil* instance;
    bool checkIfBigEndian() {
        unsigned short a = 0x1234;
        if (*((unsigned char *) &a) == 0x12)
            return true;
        return false;
    }

};


#endif //SEGYVISUALIZER2D_IOUTIL_H
