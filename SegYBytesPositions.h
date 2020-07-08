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
#ifndef SEGYBYTESPOSITIONS_H
#define SEGYBYTESPOSITIONS_H

class SegYBinaryHeaderBytesPositions
{
public:
  int JobID;
  int LineNumber;
  int ReelNumber;
  int NumberTracesPerEnsemble;
  int NumberAuxTracesPerEnsemble;
  int SampleInterval;
  int SampleIntervalOriginal;
  int NumSamplesPerTrace;
  int NumSamplesPerTraceOriginal;
  int FormatCode;
  int EnsembleType;
  int MeasurementSystem;
  int ByteOrderingDetection;
  int MajorVersion;
  int MinorVersion;
  int FixedLengthFlag;

public:
  SegYBinaryHeaderBytesPositions() { initDefaultValues(); }

private:
  void initDefaultValues()
  {
    // Default data field positions
    JobID = 3200;
    LineNumber = 3204;
    ReelNumber = 3208;
    NumberTracesPerEnsemble = 3212;
    NumberAuxTracesPerEnsemble = 3214;
    SampleInterval = 3216;
    SampleIntervalOriginal = 3218;
    NumSamplesPerTrace = 3220;
    NumSamplesPerTraceOriginal = 3222;
    FormatCode = 3224;
    EnsembleType = 3228;
    MeasurementSystem = 3254;
    ByteOrderingDetection = 3296;
    MajorVersion = 3500;
    MinorVersion = 3501;
    FixedLengthFlag = 3502;
  }
};

class SegYTraceHeaderBytesPositions
{
public:
  int TraceNumber;
  int InlineNumber;
  int CrosslineNumber;
  int TraceNumberWithinEnsemble;
  int CoordinateMultiplier;
  int CoordinateUnits;
  int NumberSamples;
  int SampleInterval;
  int SourceXcoordinate;
  int SourceYcoordinate;
  int GeophoneXcoordinate;
  int GeophoneYcoordinate;

public:
  SegYTraceHeaderBytesPositions()
  {
    initDefaultValues();
  }

private:
  void initDefaultValues()
  {
      TraceNumber = 0;
      InlineNumber = 8;
      CrosslineNumber = 20;
      TraceNumberWithinEnsemble = 24;
      CoordinateMultiplier = 70;
      SourceXcoordinate = 72;
      SourceYcoordinate = 76;
      GeophoneXcoordinate = 80;
      GeophoneYcoordinate = 84;
      CoordinateUnits = 88;
      NumberSamples = 114;
      SampleInterval = 116;

  }
};

#endif // SEGYCOMMON_H
