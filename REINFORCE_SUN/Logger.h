
/*****************************************************************************
 ******************* Class that provides all the FILE IO *********************
 *****************************************************************************

							 FILE IO

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once

#ifndef _LOGGER_H
#define _LOGGER_H

#include "Globals.h"

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Logger
{
public:
	Logger();
	Logger(string dirPath, string filePath, std::ios_base::openmode mode);
	~Logger();

	static void PrepareKinematicsLoggerObject(Logger** ppLogger, string lastDirName, int ds, string fName);
	static void PrepareDebugLoggerObject(Logger** ppLogger, bool skipLastDir, string lastDirName, int ds, string fName);
	static void DestructLoggerObject(Logger* pLogger);
	static bool VerifyOrOpenFile(fstream & stream, string path, std::ios_base::openmode mode);

	void EnsureDirAndFile(string dirPath, string filePath);
	bool VerifyOrCreateDirectory(string path);

	bool WriteString(string str);

	bool WriteVector(vector<double> vecVal, string title);
	bool ReadVector(vector<double> & vecVal);

	bool WriteVectors(vector<vector<double>> vecVal, string title);
	bool WriteVectors(vector<vector<double>> vecVal, unsigned int HorizCount);

	static bool GetLastDirFileName(RunType eChoice, string & dirName, string & fName);
	static string GetRootDirName(RunType eChoice);
	static bool ConstructBasicDirFilePaths(RunType runChoice, EnvType envType, IOType ioType);
	static bool ConstructFullDirFilePaths(string& finalDirPath, string& finalFileName, bool skipLastDir, string lastDirName, string fileVersion, string fName);
	static bool ConstructFullKinematicsDirFilePaths(string& finalDirPath, string& finalFileName, string lastDirName, string fileVersion, string fName);
	static bool ConstructFullDebugDirFilePaths(string& finalDirPath, string& finalFileName, bool skipLastDir, string lastDirName, string fileVersion, string fName);

	static string	s_BaseDirPath;
	static string	s_BaseFileName;

	fstream	m_OutStream;
	fstream	m_InStream;

protected:
	bool CloseFile();

private:

};

#endif