/****************************************************************************
**
** Copyright (C) Eageo Information & Exploration Technology Co.,Ltd.,
**
** Use of this file is limited according to the terms specified by
** Eageo Exploration & Information Technology Co.,Ltd.  Details of
** those terms are listed in licence.txt included as part of the distribution
** package ** of this file. This file may not be distributed without including
** the licence.txt file.
**
** Contact aben.lee@foxmail.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "SegYIOUtils.h"

#include <cmath>
#include <cstring>
#include <sys/types.h>

//----------------------------------------------------------------------------
SegYIOUtils::SegYIOUtils()
{
  isBigEndian = checkIfBigEndian();
}

//----------------------------------------------------------------------------
SegYIOUtils* SegYIOUtils::Instance()
{
  static SegYIOUtils SegYIOUtils;
  return &SegYIOUtils;
}

//----------------------------------------------------------------------------
int SegYIOUtils::readShortInteger(int pos, std::ifstream& in)
{
  in.seekg(pos, in.beg);
  char buffer[2];
  in.read(buffer, sizeof(buffer));

  if (!isBigEndian)
  {
    swap(buffer, buffer + 1);
  }

  short num;
  memcpy(&num, buffer, 2);
  return num;
}

void SegYIOUtils::writeShortInteger(short num, int pos, std::ofstream &out)
{
    out.seekp(pos, out.beg);
    char buffer[2];
    memcpy(buffer, &num, 2);

    if (!isBigEndian)
    {
      swap(buffer, buffer + 1);
    }

    out.write(buffer, sizeof(buffer));
}

//----------------------------------------------------------------------------
int SegYIOUtils::readLongInteger(int pos, std::ifstream& in)
{
  in.seekg(pos, in.beg);
  char buffer[4];
  in.read(buffer, sizeof(buffer));

  if (!isBigEndian)
  {
    swap(buffer, buffer + 3);
    swap(buffer + 1, buffer + 2);
  }

  int num;
  memcpy(&num, buffer, 4);
  return num;
}

void SegYIOUtils::writeLongInteger(int num, int pos, std::ofstream &out)
{
    out.seekp(pos,out.beg);
    char buffer[4];
    memcpy(buffer, &num, 4);

    if (!isBigEndian)
    {
      swap(buffer, buffer + 3);
      swap(buffer + 1, buffer + 2);
    }

    out.write(buffer, sizeof(buffer));
}

//----------------------------------------------------------------------------
int SegYIOUtils::readLongInteger(std::ifstream& in)
{
  char buffer[4];
  in.read(buffer, sizeof(buffer));

  if (!isBigEndian)
  {
    swap(buffer, buffer + 3);
    swap(buffer + 1, buffer + 2);
  }

  int num;
  memcpy(&num, buffer, 4);
  return num;
}

void SegYIOUtils::writeLongInteger(int num, std::ofstream &out)
{
  char buffer[4];
  memcpy(buffer,&num, 4);

  if (!isBigEndian)
  {
    swap(buffer, buffer + 3);
    swap(buffer + 1, buffer + 2);
  }

  out.write(buffer,sizeof(buffer));
}

//----------------------------------------------------------------------------
float SegYIOUtils::readFloat(std::ifstream& in)
{
  char buffer[4];
  in.read(buffer, sizeof(buffer));

  if (!isBigEndian)
  {
    swap(buffer, buffer + 3);
    swap(buffer + 1, buffer + 2);
  }

  float num;
  memcpy(&num, buffer, 4);
  return num;
}

void SegYIOUtils::writeFloat(float num, std::ofstream &out)
{
  char buffer[4];
  memcpy(buffer, &num,  4);

  if (!isBigEndian)
  {
    swap(buffer, buffer + 3);
    swap(buffer + 1, buffer + 2);
  }

  out.write(buffer,sizeof(buffer));
}

//----------------------------------------------------------------------------
float SegYIOUtils::readIBMFloat(std::ifstream& in)
{
  char buffer[4];
  in.read(buffer, sizeof(buffer));

  if (!isBigEndian)
  {
    swap(buffer, buffer + 3);
    swap(buffer + 1, buffer + 2);
  }

  // The IBM Hex single precision floating point representation:
  //
  //  1      7                           24                    (width in bits)
  // +-+----------------+-----------------------------------------+
  // |S|   Exponent     |                Fraction                 |
  // +-+----------------+-----------------------------------------+
  // 31 30           24 23                                        0 (bit index)
  //
  //     Value = (-1^S) (0.F) (16^(E - 64))
  //
  // Key points:
  // - S = sign: 0 = Positive, 1 = Negative
  // - Exponent = power of 16 with a bias of 64
  // - Fraction = Normalized F portion of 24 bit fraction 0.F
  // - Value = 0 if F = 0
  // More details at
  // https://en.m.wikipedia.org/wiki/IBM_Floating_Point_Architecture

  long* longbuffer = reinterpret_cast<long*>(buffer);
  int sign = longbuffer[0] >> 31 & 0x01;
  int exponent = longbuffer[0] >> 24 & 0x7F;
  float fraction = (longbuffer[0] & 0x00ffffff) / float(pow(2.0, 24));
  if (fraction == 0.0f)
  {
    // Value is 0
    return 0.0f;
  }
  float num = (1 - 2 * sign) * fraction * pow(16.0, double(exponent - 64.0));
  return num;
}

void SegYIOUtils::writeIBMFloat(float num, std::ofstream &out)
{
  char buffer[4];
  unsigned char* btemp=(unsigned char* )&num;
  buffer[0] = *btemp;
  buffer[1] = *btemp+1;
  buffer[2] = *btemp+2;
  buffer[3] = *btemp+3;

  if (!isBigEndian)
  {
    swap(buffer, buffer + 3);
    swap(buffer + 1, buffer + 2);
  }

  out.write(buffer, sizeof(buffer));
}

//----------------------------------------------------------------------------
char SegYIOUtils::readChar(std::ifstream& in)
{
  char buffer;
  in.read(&buffer, sizeof(buffer));
  return buffer;
}

void SegYIOUtils::writeChar(char c,std::ofstream &out)
{
  out.write(&c, sizeof(c));
}

//----------------------------------------------------------------------------
unsigned char SegYIOUtils::readUChar(std::ifstream& in)
{
  char buffer;
  in.read(&buffer, sizeof(buffer));
  return buffer;
}

//----------------------------------------------------------------------------
void SegYIOUtils::swap(char* a, char* b)
{
  char temp = *a;
  *a = *b;
  *b = temp;
}

//----------------------------------------------------------------------------
int SegYIOUtils::getFileSize(std::ifstream& in)
{
  in.seekg(0, in.end);
  return in.tellg();
}

