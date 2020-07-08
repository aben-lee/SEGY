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
#include "SegYWriter.h"
#include "SegYBytesPositions.h"
#include "SegYIOUtils.h"
#include "SegYTraceWriter.h"
#include "SegYCommon.h"

#include <iostream>
#include <map>
#include <set>

SegYWriter::SegYWriter()
{
    this->BinaryHeaderBytesPos = new SegYBinaryHeaderBytesPositions();
    this->TraceWriter = new SegYTraceWriter();
    this->VerticalCRS = 0;
}

SegYWriter::~SegYWriter()
{
    delete this->BinaryHeaderBytesPos;
    delete this->TraceWriter;
    for (auto trace : this->Traces)
        delete trace;
}

bool SegYWriter::AllocateFile(std::string path)
{
    std::ofstream out(path, std::ios_base::binary);
    if (!out)
    {
      std::cerr << "File not found:" << path << std::endl;
      return false;
    }

    WriterHeader(out);

    int traceStartPos = 3600; // this->Traces start after 3200 + 400 file header

    for (auto trace : this->Traces)
    {
        this->TraceWriter->WriteTrace(traceStartPos,out, binH->formatCode,trace);
    }

    out.close();
    return true;
}

void SegYWriter::pushSegYTrace(SegYTrace *sTrace)
{
    this->Traces.push_back(sTrace);
}

SegYBinaryHeader *SegYWriter::binaryHeader()
{
    return this->binH;
}

void SegYWriter::setBinaryHeader(SegYBinaryHeader *b)
{
    this->binH = b;
}

void SegYWriter::SetVerticalCRS(int v)
{
  this->VerticalCRS = v > 0 ? 1 : 0;
}

void SegYWriter::WriterHeader(std::ofstream &out)
{
    for (int i = 0; i < 3200; i ++)
    {
       SegYIOUtils::Instance()->writeChar(this->binaryHeader()->comment[i], out);
       out.seekp(i, out.beg);
    }

   SegYIOUtils::Instance()->writeLongInteger(this->binaryHeader()->jobID, this->BinaryHeaderBytesPos->JobID,out);
   SegYIOUtils::Instance()->writeLongInteger(this->binaryHeader()->lineNumbe, this->BinaryHeaderBytesPos->LineNumber,out);
   SegYIOUtils::Instance()->writeLongInteger(this->binaryHeader()->reelNumber, this->BinaryHeaderBytesPos->ReelNumber,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->numberTracesPerEnsemble, this->BinaryHeaderBytesPos->NumberTracesPerEnsemble,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->numberAuxTracesPerEnsemble, this->BinaryHeaderBytesPos->NumberAuxTracesPerEnsemble,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->sampleInterval, this->BinaryHeaderBytesPos->SampleInterval,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->sampleIntervalOriginal, this->BinaryHeaderBytesPos->SampleIntervalOriginal,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->numSamplesPerTrace, this->BinaryHeaderBytesPos->NumSamplesPerTrace,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->numSamplesPerTraceOriginal, this->BinaryHeaderBytesPos->NumSamplesPerTraceOriginal,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->formatCode, this->BinaryHeaderBytesPos->FormatCode,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->ensembleType, this->BinaryHeaderBytesPos->EnsembleType,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->measurementSystem, this->BinaryHeaderBytesPos->MeasurementSystem,out);
   SegYIOUtils::Instance()->writeShortInteger(this->binaryHeader()->byteOrderingDetection, this->BinaryHeaderBytesPos->ByteOrderingDetection,out);
}
