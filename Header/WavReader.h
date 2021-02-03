#ifndef WAV_HEADER_H
#define WAV_HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace wavReader{

  /* List of header info                    */
  /* The following comments are taken from  */
  /* https://docs.fileformat.com/audio/wav/ */
  struct wavFileInfo {

    /* BLOCK : File Declaration */
    char      ChunkID[4];      /* 4 bytes : “RIFF”	Marks the file as a riff file. Characters are each 1 byte long. */
    uint32_t  ChunkSize;       /* 4 bytes : File size (integer)	Size of the overall file - 8 bytes, in bytes (32-bit integer). Typically, you’d fill this in after creation. */
    char      Format[4];       /* 4 bytes : “WAVE”	File Type Header. For our purposes, it always equals “WAVE”. */

    /* BLOCK : Audio Format */
    char      Subchunk1ID[4];  /* 4 bytes :  “fmt "	Format chunk marker. Includes trailing null */
    uint32_t  Subchunk1Size;   /* 4 bytes :  Length of format data as listed above              */
    uint16_t  AudioFormat;     /* 2 bytes :  Type of format (1 is PCM) - 2 byte integer */
    uint16_t  NbrChannels;     /* 2 bytes :  Number of Channels - 2 byte integer*/
    uint32_t  SampleRate;      /* 4 bytes :  Sample Rate - 32 byte integer. Common values are 44100 (CD), 48000 (DAT). Sample Rate = Number of Samples per second, or Hertz. */
    uint32_t  ByteRate;        /* 4 bytes :  (Sample Rate * BitsPerSample * Channels) / 8.*/
    uint16_t  BlockAlign;      /* 2 bytes :  (BitsPerSample * Channels) / 8.1 - 8 bit mono2 - 8 bit stereo/16 bit mono4 - 16 bit stereo*/
    uint16_t  BitsPerSample;   /* 2 bytes :  Bits per sample */

    /* BLOCK : Data */
    char      Subchunk2ID[4];  /* 4 bytes :  “data” chunk header. Marks the beginning of the data section. */
    uint32_t  DataSize;         /* 4 bytes :  File size (data)	Size of the data section. */
  };

  /* Location of the header information in bytes
  Ex : FileTypeBlocID starts at 0  and ends at 4
  Ex : NbrCanaux      starts at 22 and ends at 24 */
  const uint64_t headerValueIndex[] = { 0, 4, 8, 12, 16, 20, 22, 24, 28, 32, 34, 36, 40, 44 };

  /* Class Wav File */
  class WavFile {

    string      fileName;     /* Absolute path to the file */
    ifstream    fileHandle;   /* Handle to the file        */
    wavFileInfo fileInfo;     /* Struct which contains the information contained in the header */

    void verifyExtension();
    void openFile();
    void parseHeader();
    void initWavFile();
    void closeFile();

    public:
      WavFile();
      WavFile(string file);
      inline wavFileInfo getWavFileInfo() { return fileInfo; }
  };
}

#endif