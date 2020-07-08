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
#ifndef SEGYREADER_H
#define SEGYREADER_H

#include <fstream>
#include <string>
#include <vector>

class SegYTraceReader;
class SegYTrace;
class SegYBinaryHeaderBytesPositions;

class SegYReader
{
public:
    SegYReader();
        ~SegYReader();

    bool LoadFromFile(std::string path);
    void SetVerticalCRS(int v);
private:
  bool ReadHeader(std::ifstream& in);
  std::vector<SegYTrace*> Traces;
  int FormatCode;
  SegYBinaryHeaderBytesPositions* BinaryHeaderBytesPos;
  SegYTraceReader *TraceReader;
  int SampleCountPerTrace;
  int VerticalCRS;
};

#endif // SEGYREADER_H
