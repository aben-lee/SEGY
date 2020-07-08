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
#ifndef SEGYWRITER_H
#define SEGYWRITER_H

#include <fstream>
#include <string>
#include <vector>
#include "SegYCommon.h"

class SegYTraceWriter;
class SegYTrace;
class SegYBinaryHeaderBytesPositions;

class SegYWriter
{
public:
    SegYWriter();
        ~SegYWriter();


    bool AllocateFile( std::string path);
    void pushSegYTrace(SegYTrace *sTrace);

    SegYBinaryHeader *binaryHeader();
    void setBinaryHeader(SegYBinaryHeader *b);
    void SetVerticalCRS(int v);

private:
  void WriterHeader(std::ofstream& out);
  std::vector<SegYTrace*> Traces;    // the map of  tracr and  SegYTrace map
  SegYBinaryHeaderBytesPositions *BinaryHeaderBytesPos;
  SegYBinaryHeader *binH;
  SegYTraceWriter *TraceWriter;
  int SampleCountPerTrace;
  int VerticalCRS;
};



#endif // SEGYWRITER_H
