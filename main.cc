/*
 *Filename:              main.cc
 *Date:                  4/30/2020
 *Author:                Brian Rahmoune
 *Email:                 bmr180000@utdallas.com
 *Version:               1.0
 *Copyright:             2020, All Rights Reserved
 *
 * Description:
 *
 * This program creates the matrix
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "cdk.h"
//#include "main.h"
#include <stdint.h>
#include <cstdint>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary Matrix"

using namespace std;

class BinaryFileHeader{

public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
  };


int main(){
  WINDOW            *window;
  CDKSCREEN         *cdkscreen;
  CDKMATRIX         *myMatrix;

  // ifstream binaryFile;

  stringstream stringsm;
  string var;

  BinaryFileHeader* binaryHeader = new BinaryFileHeader;
  binaryHeader->magicNumber = 0;
  binaryHeader->versionNumber = 0;
  binaryHeader->numRecords = 0;
  
  BinaryFileRecord* binaryRecord = new BinaryFileRecord;
  binaryRecord->strLength = 0;

  const char                *rowTitles[MATRIX_HEIGHT + 1] = {"R0", "a", "b", "c", "d", "e"};
  const char                *columnTitles[MATRIX_WIDTH + 1] = {"C0", "a", "b", "c"};
  int               boxWidths[MATRIX_WIDTH + 1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int               boxTypes[MATRIX_WIDTH + 1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  window = initscr();
  cdkscreen = initCDKScreen(window);

  initCDKColor();

  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if(myMatrix == NULL){
    printf("ERROR creating matrix\n");
    _exit(1);
  }

  drawCDKMatrix(myMatrix, true);

  ifstream binaryFile ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);
  
  if(binaryFile.is_open()){
    binaryFile.read((char*) binaryHeader, sizeof(BinaryFileHeader));
    stringsm << "Magic: 0x" << std::hex << binaryHeader->magicNumber;
    var = stringsm.str();

    setCDKMatrixCell(myMatrix, 1, 1, var.c_str());
    stringsm.clear();
    stringsm.str("");

    stringsm << "Versions: " << std::dec << binaryHeader->versionNumber;
    var = stringsm.str();
    stringsm.str("");

    setCDKMatrixCell(myMatrix, 1, 2, var.c_str());
    stringsm.clear();
    
    stringsm << "NumRecords: " << binaryHeader->numRecords << endl;
    var = stringsm.str();
    stringsm.str("");
    
    setCDKMatrixCell(myMatrix, 1, 3, var.c_str());

    

    for(int i = 0; i < 4; i++){
      binaryFile.read((char*)binaryRecord, sizeof(BinaryFileRecord));
      int length = binaryRecord->strLength;
      stringsm << "strLen: " << length;
      var = stringsm.str();
      char* stringLen = (char*) var.c_str();
      stringsm.str("");
      
      stringstream convert = stringLen;
      
      setCDKMatrixCell(myMatrix, i + 2, stringLen);
      setCDKMatrixCell(myMatrix, i + 2, binary->stringBuffer);
    }
  }

  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);

  sleep(10);

  endCDK();

  return 0;
}
