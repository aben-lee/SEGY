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

#include "IOUtil.h"

#include <cstring>
#include <iostream>

IOUtil* IOUtil::instance = NULL;

IOUtil::IOUtil()
{
    isBigEndian = checkIfBigEndian();
}

int IOUtil::readShortInteger(int pos, ifstream &in) {
    in.seekg(pos, ios_base::beg);
    char buffer[2];
    in.read(buffer, sizeof(buffer));

    if (!isBigEndian) {
        swap(buffer, buffer + 1);
    }

    short num;
    memcpy(&num, buffer, 2);
    return num;
}

void IOUtil::writeShortInteger(short num, int pos, ofstream &out)
{
    out.seekp(pos, ios_base::beg);
    char buffer[2];
    memcpy(buffer, &num, 2);

    if (!isBigEndian) {
        swap(buffer, buffer + 1);
    }

    out.write(buffer, sizeof(buffer));
}

int IOUtil::readLongInteger(ifstream &in, int pos) {
    in.seekg(pos, ios_base::beg);
    char buffer[4];
    in.read(buffer, sizeof(buffer));

    if (!isBigEndian) {
        swap(buffer, buffer + 3);
        swap(buffer + 1, buffer + 2);
    }

    int num;
    memcpy(&num, buffer, 4);
    return num;
}

void IOUtil::writeLongInteger(int num, int pos, ofstream &out)
{
    out.seekp(pos, ios_base::beg);
    char buffer[4];
    memcpy(buffer, &num, 4);

    if (!isBigEndian) {
        swap(buffer, buffer + 3);
        swap(buffer + 1, buffer + 2);
    }

    out.write(buffer, sizeof(buffer));
}

float IOUtil::readFloat(ifstream &in) {
    char buffer[4];
    in.read(buffer, sizeof(buffer));

    if (!isBigEndian) {
        swap(buffer, buffer + 3);
        swap(buffer + 1, buffer + 2);
    }

    float num;
    memcpy(&num, buffer, 4);
    return num;
}

void IOUtil::writeFloat(float num, ofstream &out)
{
    char buffer[4];
    memcpy(buffer, &num,  4);

    if (!isBigEndian) {
        swap(buffer, buffer + 3);
        swap(buffer + 1, buffer + 2);
    }

    out.write(buffer, sizeof(buffer));
}

char IOUtil::readChar(ifstream &in) {
    char buffer;
    in.read(&buffer, sizeof(buffer));
    return buffer;
}

void IOUtil::writeChar(char c, ofstream &out)
{
    out.write(&c,sizeof(c));
}

void IOUtil::swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int IOUtil::getFileSize(ifstream &in) {
    in.seekg(0, ios_base::end);
    return in.tellg();
}

