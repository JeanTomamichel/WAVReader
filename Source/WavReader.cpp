#include "../Header/WavReader.h"
using namespace WavReader;

/* Default Constructor */
WavFile::WavFile() 
{
  cout << "Default WavFile constructor called ! " << endl; 
  cout << "Please enter Wav File Absolute Path  " << endl;
  cin  >> fileName;

  initWavFile();
}

/* Const string constructor */
WavFile::WavFile(const string file) : fileName(file) 
{ 
  cout << "Const string constructor called " << endl; 
  initWavFile(); 
}

/* Copy Constructor */
WavFile::WavFile(const WavFile& file) : fileName(file.fileName)
{
  cout << "Copy Constructor Called " << endl; 
  cout << fileName << endl;

  initWavFile(); 
}

/* Move Constructor */
WavFile::WavFile(const WavFile&& file) : fileName(file.fileName) 
{
  cout << "Move Constructor Called" << endl; 
  cout << fileName << endl; 
}

/* Verify .WAV or .wav extension */
/* in the current file name      */
void WavFile::verifyExtension() {
  bool         WavExtensionFound =  false; 
  string       EXTENSION         = ".WAV";
  string       extension         = ".wav"; 

  if (fileName.length() >= extension.length()) {
    WavExtensionFound = (0 == fileName.compare(fileName.length() - extension.length(), extension.length(), extension)
                      || 0 == fileName.compare(fileName.length() - EXTENSION.length(), EXTENSION.length(), EXTENSION));
  }

  if (WavExtensionFound) {
    cout << " Wav extension found ! " << endl;
  }
  else {
    cout << "Not the right extension, the software only supports .WAV, sorry ! " << endl;
    throw exception("Not a wav file");
  } 
}

/* Open File and sanity check */
void WavFile::openFile() {

  fileHandle.open(fileName, ios::binary | ios::in);
  if (fileHandle.is_open()) {
    cout << "The file " << fileName << " has been successfully opened !" << endl;
  }
  else {
    cout << "Can't open file : " << fileName << endl;
    throw exception("Open FileName");
  }
}

/* Parse header to collect the Wav Header info */
void WavFile::parseHeader() {
  cout << "Starting parsing ! " << endl; 

  const int   headerSize = 44;                      /* Header size in bytes */

  /* Get file size */
  fileHandle.seekg(0, ios::end);
  streampos size = fileHandle.tellg();

  /* Sanity check header size */
  if (size < headerSize) {
    cout << "The wav file size is under 44 bytes. " << endl;
    throw exception("Wav file too short");
  }

  /* Get header bytes in an array */
  fileHandle.seekg(0, ios::beg);
  char* headerMemory = new char[headerSize];    /* Memory */
  fileHandle.read(headerMemory, 4); 

  /* Collect Info into wav file info struct */
  memcpy(&(fileInfo.ChunkID[0]     ), &headerMemory[headerValueIndex[0] ], headerValueIndex[1]  - headerValueIndex[0] );
  memcpy(&(fileInfo.ChunkSize      ), &headerMemory[headerValueIndex[1] ], headerValueIndex[2]  - headerValueIndex[1] );
  memcpy(&(fileInfo.Format[0]      ), &headerMemory[headerValueIndex[2] ], headerValueIndex[3]  - headerValueIndex[2] );
  memcpy(&(fileInfo.Subchunk1ID    ), &headerMemory[headerValueIndex[3] ], headerValueIndex[4]  - headerValueIndex[3] );
  memcpy(&(fileInfo.Subchunk1Size  ), &headerMemory[headerValueIndex[4] ], headerValueIndex[5]  - headerValueIndex[4] );
  memcpy(&(fileInfo.AudioFormat    ), &headerMemory[headerValueIndex[5] ], headerValueIndex[6]  - headerValueIndex[5] );
  memcpy(&(fileInfo.NbrChannels    ), &headerMemory[headerValueIndex[6] ], headerValueIndex[7]  - headerValueIndex[6] );
  memcpy(&(fileInfo.SampleRate     ), &headerMemory[headerValueIndex[7] ], headerValueIndex[8]  - headerValueIndex[7] );
  memcpy(&(fileInfo.ByteRate       ), &headerMemory[headerValueIndex[8] ], headerValueIndex[9]  - headerValueIndex[8] );
  memcpy(&(fileInfo.BlockAlign     ), &headerMemory[headerValueIndex[9] ], headerValueIndex[10] - headerValueIndex[9] );
  memcpy(&(fileInfo.BitsPerSample  ), &headerMemory[headerValueIndex[10]], headerValueIndex[11] - headerValueIndex[10]);
  memcpy(&(fileInfo.Subchunk2ID[0] ), &headerMemory[headerValueIndex[11]], headerValueIndex[12] - headerValueIndex[11]);
  memcpy(&(fileInfo.DataSize       ), &headerMemory[headerValueIndex[12]], headerValueIndex[13] - headerValueIndex[12]);

  /* delete header memory */
  delete[] headerMemory; 
}

WavFile::~WavFile() {
  cout << "Destructor Called" << endl;

  /* close file */
  if (!fileHandle.is_open())
  {
    fileHandle.close();
    if (!fileHandle.is_open()) {
      cout << fileName << " has been successfully closed ! " << endl;
    }
  }
}

void WavFile::initWavFile() {

  /*Verify Extension */
  verifyExtension(); 
  
  /* Open File */
  openFile(); 

  /* Parse file Header */
  parseHeader(); 
}
