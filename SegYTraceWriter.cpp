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
#include "SegYTraceWriter.h"
#include "SegYIOUtils.h"

#include <iostream>

SegYTraceWriter::SegYTraceWriter()
{

}

bool SegYTraceWriter::WriteTrace(int &startPos, std::ofstream &out, int formatCode, SegYTrace *trace)
{

//    this->WriteTraceHeader(trace, out, startPos);

    out.seekp(startPos, out.beg);


    SegYIOUtils::Instance()->writeLongInteger(trace->crosslineNumber, startPos + traceHeaderBytesPos.CrosslineNumber, out);
    SegYIOUtils::Instance()->writeLongInteger(trace->inlineNumber, startPos + traceHeaderBytesPos.InlineNumber, out);
    SegYIOUtils::Instance()->writeShortInteger(trace->data.size(), startPos + traceHeaderBytesPos.NumberSamples, out);
    SegYIOUtils::Instance()->writeLongInteger(trace->xCoordinate, startPos + traceHeaderBytesPos.SourceXcoordinate, out);
    SegYIOUtils::Instance()->writeLongInteger(trace->yCoordinate, startPos + traceHeaderBytesPos.SourceYcoordinate, out);
    SegYIOUtils::Instance()->writeShortInteger(trace->CoordinateMultiplier, startPos + traceHeaderBytesPos.CoordinateMultiplier, out);
    SegYIOUtils::Instance()->writeShortInteger(trace->SampleInterval, startPos + traceHeaderBytesPos.SampleInterval, out);

    out.seekp(startPos + 240, out.beg);

    for (unsigned int i = 0; i < trace->data.size(); i++)
    {
        switch (formatCode)
        {
            case 1:
                SegYIOUtils::Instance()->writeIBMFloat(trace->data.at(i), out);
                break;
            case 5:
                SegYIOUtils::Instance()->writeFloat(trace->data.at(i), out);
              break;
            default:
                std::cerr << "Data sample format code " << formatCode
                        << " not supported." << std::endl;
        }
    }

    startPos += 240 + GetTraceSize(trace->data.size(), formatCode);
    return true;
}

int SegYTraceWriter::GetTraceSize(int numSamples, int formatCode)
{
    if (formatCode == 1 || formatCode == 2 || formatCode == 4 || formatCode == 5)
    {
      return 4 * numSamples;
    }
    if (formatCode == 3)
    {
      return 2 * numSamples;
    }
    if (formatCode == 8)
    {
      return numSamples;
    }
    std::cerr << "Unsupported data format code : " << formatCode << std::endl;
    return -1;
}
