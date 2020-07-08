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
#ifndef SEGYTRACEWRITER_H
#define SEGYTRACEWRITER_H
#include <fstream>
#include <vector>

#include "SegYBytesPositions.h"
#include "SegYCommon.h"
/*
 * Single Seg-Y trace writer
 */

class SegYTraceWriter
{
private:
  SegYTraceHeaderBytesPositions traceHeaderBytesPos;


public:
    SegYTraceWriter();

    bool WriteTrace(int& startPos,
      std::ofstream &out,
      int formatCode,
      SegYTrace* trace);
  int GetTraceSize(int numSamples, int formatCode);
};

#endif // SEGYTRACEWRITER_H
