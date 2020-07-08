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
#include "SegYTraceReader.h"
#include "SegYIOUtils.h"

#include <iostream>

//-----------------------------------------------------------------------------
SegYTraceReader::SegYTraceReader()
{

}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void SegYTraceReader::PrintTraceHeader(std::ifstream& in, int startPos)
{
  int traceSequenceNumberInLine = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.TraceNumber, in);
  std::cout << "Trace sequence number in line : " << traceSequenceNumberInLine
            << std::endl;

  int traceSequenceNumberInFile =
    SegYIOUtils::Instance()->readLongInteger(in);
  std::cout << "Trace sequence number in file : " << traceSequenceNumberInFile
            << std::endl;

  // Get number_of_samples from trace header position 115-116
  int numSamples = SegYIOUtils::Instance()->readShortInteger(
    startPos + traceHeaderBytesPos.NumberSamples, in);
  std::cout << "number of samples: " << numSamples << std::endl;

  short sampleInterval = SegYIOUtils::Instance()->readShortInteger(
    startPos + traceHeaderBytesPos.SampleInterval, in);
  std::cout << "sample interval: " << sampleInterval << std::endl;

  // Get inline number from trace header position 189-192
  int inlineNum = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.InlineNumber, in);
  std::cout << "Field record number (inline number) : " << inlineNum
            << std::endl;

  int crosslineNum = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.CrosslineNumber, in);
  std::cout << "cross-line number (ensemble number) : " << crosslineNum
            << std::endl;

  int traceNumberWithinEnsemble = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.TraceNumberWithinEnsemble, in);
  std::cout << "trace number within ensemble : " << traceNumberWithinEnsemble
            << std::endl;

  short coordinateMultiplier = SegYIOUtils::Instance()->readShortInteger(
    startPos + traceHeaderBytesPos.CoordinateMultiplier, in);
  std::cout << "coordinate multiplier : " << coordinateMultiplier << std::endl;

  int xCoordinate = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.SourceXcoordinate, in);
  std::cout << "X coordinate for ensemble position of the trace : "
            << xCoordinate << std::endl;

  int yCoordinate = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.SourceYcoordinate, in);
  std::cout << "Y coordinate for ensemble position of the trace : "
            << yCoordinate << std::endl;

  short coordinateUnits = SegYIOUtils::Instance()->readShortInteger(
    startPos + traceHeaderBytesPos.CoordinateUnits, in);
  std::cout << "coordinateUnits: " << coordinateUnits << std::endl;
}

//-----------------------------------------------------------------------------
bool SegYTraceReader::ReadTrace(int& startPos,
  std::ifstream& in,
  int formatCode,
  SegYTrace* trace)
{
  int fileSize = SegYIOUtils::Instance()->getFileSize(in);

  if (startPos + 240 >= fileSize)
  {
    return false;
  }

  // PrintTraceHeader(in, startPos);
  trace->crosslineNumber = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.CrosslineNumber, in);
  trace->inlineNumber = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.InlineNumber, in);
  int numSamples = SegYIOUtils::Instance()->readShortInteger(
    startPos + traceHeaderBytesPos.NumberSamples, in);
  trace->xCoordinate = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.SourceXcoordinate, in);
  trace->yCoordinate = SegYIOUtils::Instance()->readLongInteger(
    startPos + traceHeaderBytesPos.SourceYcoordinate, in);
  trace->CoordinateMultiplier= SegYIOUtils::Instance()->readShortInteger(
    startPos + traceHeaderBytesPos.CoordinateMultiplier, in);
  trace->SampleInterval = SegYIOUtils::Instance()->readShortInteger(
    startPos + traceHeaderBytesPos.SampleInterval, in);

  in.seekg(startPos + 240, in.beg);
  for (int i = 0; i < numSamples; i++)
  {
    float value;
    switch (formatCode)
    {
      case 1:
        value = SegYIOUtils::Instance()->readIBMFloat(in);
        break;
      case 5:
        value = SegYIOUtils::Instance()->readFloat(in);
        break;
      default:
        std::cerr << "Data sample format code " << formatCode
                  << " not supported." << std::endl;
        value = 0;
    }
    trace->data.push_back(value);
  }

  startPos += 240 + GetTraceSize(numSamples, formatCode);
  return true;
}

//-----------------------------------------------------------------------------
int SegYTraceReader::GetTraceSize(int numSamples, int formatCode)
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
