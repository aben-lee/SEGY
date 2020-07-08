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
#ifndef SEGYCOMMON_H
#define SEGYCOMMON_H

#include <vector>

//#define UNUSED(A) (void*)(A);

struct SegYBinaryHeader
{ /* bhed - binary header */
    char comment[3200];
    int jobID;                          /* job identification number */
    int lineNumbe;                      /* line number (only one line per reel) */
    int reelNumber;                     /* reel number */
    short numberTracesPerEnsemble;      /* number of data traces per record */
    short numberAuxTracesPerEnsemble;   /* number of auxiliary traces per record */
    unsigned short sampleInterval;              /* sample interval in micro secs for this reel */
    unsigned short sampleIntervalOriginal;      /* same for original field recording */
    unsigned short numSamplesPerTrace;          /* number of samples per trace for this reel */
    unsigned short numSamplesPerTraceOriginal;  /* same for original field recording */
    short formatCode;               /* data sample format code:
                                    1 = floating point (4 bytes)
                                    2 = fixed point (4 bytes)
                                    3 = fixed point (2 bytes)
                                    4 = fixed point w/gain code (4 bytes) */
    short fold;                     /* CDP fold expected per CDP ensemble */
    short ensembleType;         /* trace sorting code:
                                1 = as recorded (no sorting)
                                2 = CDP ensemble
                                3 = single fold continuous profile
                                4 = horizontally stacked */
    short verticalSumCode;  /* vertical sum code:
                                1 = no sum
                                2 = two sum ...
                                N = N sum (N = 32,767) */
    short sweepFrequencyStart;          /* sweep frequency at start */
    short sweepFrequencyEnd;         /* sweep frequency at end */
    short sweepLenght;          /* sweep length (ms) */
    short sweepTypeCode;        /* sweep type code:
                                1 = linear
                                2 = parabolic
                                3 = exponential
                                4 = other */
    short sweepChannel;         /* trace number of sweep channel */
    short sweepTaperStart;       /* sweep trace taper length at start if
                                    tapered (the taper starts at zero time
                                    and is effective for this length) */
    short sweepTaperEnd;    /* sweep trace taper length at end (the ending
                                taper starts at sweep length minus the taper
                                length at end) */
    short sweepTaperCode; /* sweep trace taper type code:
                            1 = linear
                             2 = cos-squared
                            3 = other */
    short correlatedTracesCode; /* correlated data traces code:
                                    1 = no
                                    2 = yes */
    short gainRecoveredCode; /* binary gain recovered code:
                                1 = yes
                                2 = no */
    short amplitudeRecoveryCode; /* amplitude recovery method code:
                                1 = none
                                2 = spherical divergence
                                3 = AGC
                                4 = other */
    short measurementSystem;    /* measurement system code:
                                1 = meters
                                2 = feet */
    short impulsePolarityCode; /* impulse signal polarity code:
                                1 = increase in pressure or upward
                                geophone case movement gives
                                negative number on tape
                                2 = increase in pressure or upward
                                geophone case movement gives
                                positive number on tape */
    short vibratoryPolarityCode; /* vibratory polarity code:
                                code seismic signal lags pilot by
                                1 337.5 to 22.5 degrees
                                2 22.5 to 67.5 degrees
                                3 67.5 to 112.5 degrees
                                4 112.5 to 157.5 degrees
                                5 157.5 to 202.5 degrees
                                6 202.5 to 247.5 degrees
                                7 247.5 to 292.5 degrees
                                8 293.5 to 337.5 degrees */
    short byteOrderingDetection;
    char majorVersion;
    char minorVersion;
    char hunass[94]; /* unassigned */

    SegYBinaryHeader()
    {

    }
};

struct SegYTraceHeader
{
    SegYTraceHeader();
    int fileNumber; /* Trace sequence number within line
                    --numbers continue to increase if the
                    same line continues across multiple
                    SEG Y files.*/
    int traceNumber; /* Trace sequence number within SEG Y file
                    ---each file starts with trace sequence one*/
    int InlineNumber; /* Original field record number */
    int numberWithinField; /* Trace number within original field record */
    int sourcePoint; /* energy source point number
                        ---Used when more than one record occurs
                        at the same effective surface location.*/
    int crosslineNumber; /* Ensemble number (i.e. CDP, CMP, CRP,...) */
    int traceNumberWithinEnsemble; /* trace number within the ensemble
                         ---each ensemble starts with trace number one.*/
    short trid; /* trace identification code:
                -1 = Other
                0 = Unknown
                1 = Seismic data
                2 = Dead
                3 = Dummy
                4 = Time break
                5 = Uphole
                6 = Sweep
                7 = Timing
                8 = Water break
                9 = Near-field gun signature
                10 = Far-field gun signature
                11 = Seismic pressure sensor
                12 = Multicomponent seismic sensor
                - Vertical component
                13 = Multicomponent seismic sensor
                - Cross-line component
                14 = Multicomponent seismic sensor
                - in-line component
                15 = Rotated multicomponent seismic sensor
                - Vertical component
                16 = Rotated multicomponent seismic sensor
                - Transverse component
                17 = Rotated multicomponent seismic sensor
                 - Radial component
                18 = Vibrator reaction mass
                19 = Vibrator baseplate
                20 = Vibrator estimated ground force
                21 = Vibrator reference
                22 = Time-velocity pairs
                23 ... N = optional use
                (maximum N = 32,767)
                Following are CWP id flags:
                109 = autocorrelation
                110 = Fourier transformed - no packing
                xr[0],xi[0], ..., xr[N-1],xi[N-1]
                111 = Fourier transformed - unpacked Nyquist
                xr[0],xi[0],...,xr[N/2],xi[N/2]
                112 = Fourier transformed - packed Nyquist
                even N:
                xr[0],xr[N/2],xr[1],xi[1], ...,
                xr[N/2 -1],xi[N/2 -1]
                (note the exceptional second entry)
                odd N:
                xr[0],xr[(N-1)/2],xr[1],xi[1], ...,
                xr[(N-1)/2 -1],xi[(N-1)/2 -1],xi[(N-1)/2]
                (note the exceptional second & last entries)
                113 = Complex signal in the time domain
                xr[0],xi[0], ..., xr[N-1],xi[N-1]
                114 = Fourier transformed - amplitude/phase
                a[0],p[0], ..., a[N-1],p[N-1]
                115 = Complex time signal - amplitude/phase
                a[0],p[0], ..., a[N-1],p[N-1]
                116 = Real part of complex trace from 0 to Nyquist
                117 = Imag part of complex trace from 0 to Nyquist
                118 = Amplitude of complex trace from 0 to Nyquist
                119 = Phase of complex trace from 0 to Nyquist
                121 = Wavenumber time domain (k-t)
                122 = Wavenumber frequency (k-omega)
                123 = Envelope of the complex time trace
                124 = Phase of the complex time trace
                125 = Frequency of the complex time trace
                130 = Depth-Range (z-x) traces
                143 = Seismic Data, Vertical Component
                144 = Seismic Data, Horizontal Component 1
                145 = Seismic Data, Horizontal Component 2
                146 = Seismic Data, Radial Component
                147 = Seismic Data, Transverse Component
                201 = Seismic data packed to bytes (by supack1)
                202 = Seismic data packed to 2 bytes (by supack2)
                */
    short nvs; /* Number of vertically summed traces yielding
                this trace. (1 is one trace,
                2 is two summed traces, etc.)*/
    short nhs; /* Number of horizontally summed traces yielding
                this trace. (1 is one trace
                2 is two summed traces, etc.)*/
    short duse; /* Data use:
                1 = Production
                2 = Test*/
    int offset; /* Distance from the center of the source point
                to the center of the receiver group
                (negative if opposite to direction in which
                the line was shot).*/
    int gelev; /* Receiver group elevation from sea level
                (all elevations above the Vertical datum are
                positive and below are negative).*/
    int selev; /* Surface elevation at source. */
    int sdepth; /* Source depth below surface (a positive number). */
    int gdel; /* Datum elevation at receiver group. */
    int sdel; /* Datum elevation at source. */
    int swdep; /* Water depth at source. */
    int gwdep; /* Water depth at receiver group. */
    short scalel; /* Scalar to be applied to the previous 7 entries
                        to give the real value.
                        Scalar = 1, +10, +100, +1000, +10000.
                        If positive, scalar is used as a multiplier,
                        if negative, scalar is used as a divisor.*/
    short coordinateMultiplier; /* Scalar to be applied to the next 4 entries
                            to give the real value.
                            Scalar = 1, +10, +100, +1000, +10000.
                            If positive, scalar is used as a multiplier,
                            if negative, scalar is used as a divisor.*/
    int sourceXcoordinate; /* Source coordinate - X */
    int sourceYcoordinate; /* Source coordinate - Y */
    int geophoneXcoordinate; /* Group coordinate - X */
    int geophoneYcoordinate; /* Group coordinate - Y */
    short coordinateUnits; /* Coordinate units: (for previous 4 entries and
                            for the 7 entries before scalel)
                            1 = Length (meters or feet)
                             2 = Seconds of arc
                            3 = Decimal degrees
                            4 = Degrees, minutes, seconds (DMS)
                            In case 2, the X values are longitude and
                            the Y values are latitude, a positive value designates
                            the number of seconds east of Greenwich
                            or north of the equator
                            In case 4, to encode +-DDDMMSS
                            counit = +-DDD*10^4 + MM*10^2 + SS,
                            with scalco = 1. To encode +-DDDMMSS.ss
                            counit = +-DDD*10^6 + MM*10^4 + SS*10^2
                        with scalco = -100.*/
    short wevel; /* Weathering velocity. */
    short swevel; /* Subweathering velocity. */
    short sut; /* Uphole time at source in milliseconds. */
    short gut; /* Uphole time at receiver group in milliseconds. */
    short sstat; /* Source static correction in milliseconds. */
    short gstat; /* Group static correction in milliseconds.*/
    short tstat; /* Total static applied in milliseconds.
                (Zero if no static has been applied.) */
    short laga; /* Lag time A, time in ms between end of 240-
                byte trace identification header and time
                break, positive if time break occurs after
                end of header, time break is defined as
                the initiation pulse which maybe recorded
                on an auxiliary trace or as otherwise
                specified by the recording system */
    short lagb; /* lag time B, time in ms between the time break
                and the initiation time of the energy source,
                may be positive or negative */
    short delrt; /* delay recording time, time in ms between
                initiation time of energy source and time
                when recording of data samples begins
                (for deep water work if recording does not
                start at zero time) */
    short muts;                     /* mute time--start */
    short mute;                     /* mute time--end */
    unsigned short numberSamples;   /* number of samples in this trace */
    unsigned short sampleInterval;              /* sample interval; in micro-seconds */
    short gain;                     /* gain type of field instruments code:
                                    1 = fixed
                                    2 = binary
                                     3 = floating point
                                    4 ---- N = optional use */
    short igc; /* instrument gain constant */
    short igi; /* instrument early or initial gain */
    short corr; /* correlated:
                1 = no
                2 = yes */
    short sfs; /* sweep frequency at start */
    short sfe; /* sweep frequency at end */
    short slen; /* sweep length in ms */
    short styp; /* sweep type code:
                1 = linear
                2 = cos-squared
                3 = other */
    short stas; /* sweep trace length at start in ms */
    short stae; /* sweep trace length at end in ms */
    short tatyp; /* taper type: 1=linear, 2=cos^2, 3=other */
    short afilf; /* alias filter frequency if used */
    short afils; /* alias filter slope */
    short nofilf; /* notch filter frequency if used */
    short nofils; /* notch filter slope */
    short lcf; /* low cut frequency if used */
    short hcf; /* high cut frequncy if used */
    short lcs; /* low cut slope */
    short hcs; /* high cut slope */
    short year; /* year data recorded */
    short day; /* day of year */
    short hour; /* hour of day (24 hour clock) */
    short minute; /* minute of hour */
    short sec; /* second of minute */
    short timbas; /* time basis code:
                    1 = local
                    2 = GMT
                    3 = other */
    short trwf; /* trace weighting factor, defined as 1/2^N
                volts for the least sigificant bit */
    short grnors; /* geophone group number of roll switch
                    position one */
    short grnofr; /* geophone group number of trace one within
                    original field record */
    short grnlof; /* geophone group number of last trace within
                    original field record */
    short gaps; /* gap size (total number of groups dropped) */
    short otrav; /* overtravel taper code:
                     1 = down (or behind)
                    2 = up (or ahead) */
                    /* cwp local assignments */
    float d1; /* sample spacing for non-seismic data */
    float f1; /* first sample location for non-seismic data */
    float d2; /* sample spacing between traces */
    float f2; /* first trace location */
    float ungpow; /* negative of power used for dynamic range compression */
    float unscale; /* reciprocal of scaling factor to normalize range */
    int ntr; /* number of traces */
    short mark; /* mark selected traces */
    short shortpad; /* alignment padding */
    short unass[14]; /* unassigned--NOTE: last entry causes
                    a break in the word alignment, if we REALLY
                    want to maintain 240 bytes, the following
                    entry should be an odd number of short/UINT2
                    OR do the insertion above the "mark" keyword
                    entry */
};

/*
 * Single Seg-Y trace
 */
class SegYTrace
{
public:
    float xCoordinate;
    float yCoordinate;
    short CoordinateMultiplier;
    std::vector<float> data;
    int inlineNumber;
    int crosslineNumber;
    short SampleInterval;
};

#endif // SEGYCOMMON_H
