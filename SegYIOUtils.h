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
#ifndef SEGYIOUTILS_H
#define SEGYIOUTILS_H

#include <fstream>

class SegYIOUtils
{
public:
  int readShortInteger(int pos, std::ifstream& in);
  void writeShortInteger(short num, int pos, std::ofstream& out);
  int readLongInteger(int pos, std::ifstream& in);
  void writeLongInteger(int num, int pos, std::ofstream& out);
  int readLongInteger(std::ifstream& in);
  void writeLongInteger(int num, std::ofstream& out);
  float readFloat(std::ifstream& in);
  void writeFloat(float num, std::ofstream& out);
  float readIBMFloat(std::ifstream& in);
  void writeIBMFloat(float num, std::ofstream& out);
  char readChar(std::ifstream& in);
  void writeChar(char c, std::ofstream& out);
  unsigned char readUChar(std::ifstream& in);
  void swap(char* a, char* b);
  bool isBigEndian;
  static SegYIOUtils* Instance();
  int getFileSize(std::ifstream& in);

private:
    SegYIOUtils();
    bool checkIfBigEndian()
    {
      unsigned short a = 0x1234;
      if (*((unsigned char*)&a) == 0x12)
        return true;
      return false;
    }
};

#endif // SEGYIOUTILS_H
