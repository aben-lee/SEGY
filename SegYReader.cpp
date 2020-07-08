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
#include "SegYReader.h"

#include "SegYBytesPositions.h"
#include "SegYIOUtils.h"
#include "SegYTraceReader.h"

#include <iostream>
#include <map>
#include <set>

SegYReader::SegYReader()
{
    this->BinaryHeaderBytesPos = new SegYBinaryHeaderBytesPositions();
    this->TraceReader = new SegYTraceReader();
    this->VerticalCRS = 0;
}

SegYReader::~SegYReader()
{
    delete this->BinaryHeaderBytesPos;
    delete this->TraceReader;
    for (auto trace : this->Traces)
        delete trace;
}

bool SegYReader::LoadFromFile(std::string path)
{
    std::ifstream in(path, std::ios_base::binary);
    if (!in)
    {
      std::cerr << "File not found:" << path << std::endl;
      return false;
    }

    ReadHeader(in);

    int traceStartPos = 3600; // this->Traces start after 3200 + 400 file header
    while (true)
    {
      SegYTrace* pTrace = new SegYTrace();
      if (!this->TraceReader->ReadTrace(
            traceStartPos, in, this->FormatCode, pTrace))
      {
        delete pTrace;
        break;
      }
      this->Traces.push_back(pTrace);
    }

    in.close();
    return true;
}

void SegYReader::SetVerticalCRS(int v)
{
  this->VerticalCRS = v > 0 ? 1 : 0;
}

bool SegYReader::ReadHeader(std::ifstream &in)
{
    short sampleInterval = SegYIOUtils::Instance()->readShortInteger(
      this->BinaryHeaderBytesPos->SampleInterval, in);
    this->FormatCode = SegYIOUtils::Instance()->readShortInteger(
      this->BinaryHeaderBytesPos->FormatCode, in);
    in.seekg(this->BinaryHeaderBytesPos->MajorVersion, in.beg);
    unsigned char majorVersion = SegYIOUtils::Instance()->readUChar(in);
    unsigned char minorVersion = SegYIOUtils::Instance()->readUChar(in);
    this->SampleCountPerTrace = SegYIOUtils::Instance()->readShortInteger(
      this->BinaryHeaderBytesPos->NumSamplesPerTrace, in);
    short tracesPerEnsemble = SegYIOUtils::Instance()->readShortInteger(
      this->BinaryHeaderBytesPos->NumberTracesPerEnsemble, in);
    short ensembleType = SegYIOUtils::Instance()->readShortInteger(
      this->BinaryHeaderBytesPos->EnsembleType, in);
    short measurementSystem = SegYIOUtils::Instance()->readShortInteger(
      this->BinaryHeaderBytesPos->MeasurementSystem, in);
    int byteOrderingDetection = SegYIOUtils::Instance()->readLongInteger(
      this->BinaryHeaderBytesPos->ByteOrderingDetection, in);

    std::cout << "Segy version = " << int(majorVersion) << "."
              << int(minorVersion) << std::endl;
    std::cout << "FormatCode = " << this->FormatCode << std::endl;
    std::cout << "ByteOrderingDetection = " << byteOrderingDetection << std::endl;
    std::cout << "this->SampleCountPerTrace=" << this->SampleCountPerTrace
              << std::endl;
    std::cout << "ensembleType=" << ensembleType << std::endl;
    std::cout << "measurementSystem=" << measurementSystem << std::endl;
    std::cout << "sampleInterval=" << sampleInterval << std::endl;
    std::cout << "tracesPerEnsemble=" << tracesPerEnsemble << std::endl
              << std::endl;
    return true;
}
