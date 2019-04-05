
/*****************************************************************************
 ******************* Class that provides all the FILE IO *********************
 *****************************************************************************

						Implementation of FILE IO

**************************Author: Syed Naveed H Shah**************************/

#include "pch.h"
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;

string Logger::s_BaseDirPath;
string Logger::s_BaseFileName;

Logger::Logger()
{
}

Logger::Logger(string dirPath, string filePath, std::ios_base::openmode mode)
{
	VerifyOrCreateDirectory(dirPath);
	Logger::VerifyOrOpenFile(m_OutStream, filePath, mode);
}

Logger::~Logger()
{
	if (m_InStream.is_open())
	{
		m_InStream.flush();
		m_InStream.close();
	}

	if (m_OutStream.is_open())
	{
		m_OutStream.flush();
		m_OutStream.close();
	}
}

void Logger::PrepareKinematicsLoggerObject(Logger** ppLogger, string lastDirName, int ds, string fName)
{
	Logger* pLogger = nullptr;

	assert(ppLogger != nullptr);

	pLogger = new Logger();
	string	finalDirPath;
	string	finalFileName;

	Logger::ConstructFullKinematicsDirFilePaths(finalDirPath, finalFileName, lastDirName, to_string(ds), fName);
	Logger::VerifyOrOpenFile(pLogger->m_InStream, finalDirPath + finalFileName, std::ios::in);

	*ppLogger = pLogger;
}

void Logger::PrepareDebugLoggerObject(Logger** ppLogger, bool skipLastDir, string lastDirName, int ds, string fName)
{
	Logger* pLogger = nullptr;

	assert(ppLogger != nullptr);

	pLogger = new Logger();
	string	finalDirPath;
	string	finalFileName;

	Logger::ConstructFullDebugDirFilePaths(finalDirPath, finalFileName, skipLastDir, lastDirName, to_string(ds), fName);
	pLogger->EnsureDirAndFile(finalDirPath, finalDirPath + finalFileName);

	*ppLogger = pLogger;
}

void Logger::DestructLoggerObject(Logger * pLogger)
{
	if (pLogger != nullptr)
	{
		delete pLogger;
	}
}

void Logger::EnsureDirAndFile(string dirPath, string filePath)
{
	VerifyOrCreateDirectory(dirPath);
	Logger::VerifyOrOpenFile(m_OutStream, filePath, std::ios::out);
}

bool Logger::VerifyOrCreateDirectory(string path)
{
	bool	result	= true;
	string	command	= "mkdir " + path;

	assert(!path.empty());
	
	if (system(command.c_str()) != 0)
	{
		cout << "Error creating directory!" << endl;
	}

	return result;
}

bool Logger::VerifyOrOpenFile(fstream & stream, string path, std::ios_base::openmode mode)
{
	bool result	= true;

	assert(!path.empty());
	
	//stream.open(path, mode);
	//if (!stream.is_open())
	//{
	//	cout << "Error opening file!" << endl;
	//}
	//prepare f to throw if failbit gets set

	std::ios_base::iostate exceptionMask = stream.exceptions() | std::ios::failbit;
	stream.exceptions(exceptionMask);

	try
	{
		stream.open(path, mode);
	}
	catch (std::ios_base::failure & e) 
	{
		std::cerr << e.what() << '\n';
	}

	return result;
}

bool Logger::WriteString(string str)
{
	bool result = true;

	assert(!str.empty());

	m_OutStream << str << "\n";

	return result;
}

bool Logger::WriteVector(vector<double> vecVal, string title)
{
	bool	result = true;

	if (vecVal.size() == 0)
	{
		cout << "Error: Vector of Size 0 can't be logged!" << endl;
	}

	m_OutStream << title << "\t";

	for (int i = 0; i < vecVal.size(); i++)
	{
		m_OutStream << vecVal[i];
		if (i < vecVal.size() - 1)
			m_OutStream << "\t ";
	}
	m_OutStream << endl;

	return result;
}

bool Logger::ReadVector(vector<double> & vecVal)
{
	bool	result	= true;

	vecVal.clear();

	if (m_InStream.is_open())
	{
		std::string line;
		std::string partial;

		std::vector<std::string> tokens;

		getline(m_InStream, line);
		std::istringstream iss(line);
		std::string token;
		while (getline(iss, token, '\t'))   // Read each value one by one
		{
			vecVal.push_back(stod(token));
		}
	}

	return result;
}

// This method assumes all vectors inside the 2D Vector to be of same size
bool Logger::WriteVectors(vector<vector<double>> vecVal, unsigned int HorizCount)
{
	bool	result = true;

	if (vecVal.size() == 0)
	{
		cout << "Error: Vector of Size 0 can't be logged!" << endl;
	}

	unsigned int innerVecSize = vecVal[0].size();

		for (unsigned int j = 0; j < innerVecSize; j++)
		{
			m_OutStream << j << "\t";
			for (unsigned int i = 0; i < HorizCount; i++)
			{
				m_OutStream << vecVal[i][j];
				if (i < HorizCount - 1)
					m_OutStream << "\t";
			}
			m_OutStream << "\n";
		}
		m_OutStream.flush();

	return result;
}

bool Logger::WriteVectors(vector<vector<double>> vecVal, string title)
{
	bool	result = true;

	if (vecVal.size() == 0)
	{
		cout << "Error: Vector of Size 0 can't be logged!" << endl;
	}
	
	m_OutStream << title << "\t";

	for (int i = 0; i < vecVal.size(); i++)
	{
		for (int j = 0; j < vecVal[i].size(); j++)
		{
			m_OutStream << vecVal[i][j];
			if (i < vecVal.size() - 1 || j < vecVal[i].size() - 1)
				m_OutStream << "\t ";
		}
	}
	m_OutStream << endl;

	return result;
}

bool Logger::CloseFile()
{
	bool result	= true;

	return result;
}

bool Logger::GetLastDirFileName(RunType eChoice, string & dirName, string & fName)
{
	bool result = true;

	switch (eChoice)
	{
	case RunType::e3_3_NonLinear_FwdKinematics:
	case RunType::e12_3_NonLinear_FwdKinematics:
	case RunType::e3_12_NonLinear_FwdKinematics:
	case RunType::e12_12_NonLinear_FwdKinematics:
	case RunType::e21_21_NonLinear_FwdKinematics:
	case RunType::e30_30_NonLinear_FwdKinematics:
	case RunType::e3_21_NonLinear_FwdKinematics:
	case RunType::e3_30_NonLinear_FwdKinematics:
	case RunType::e21_3_NonLinear_FwdKinematics:
	case RunType::e30_3_NonLinear_FwdKinematics:
	case RunType::e6_6_NonLinear_FwdKinematics:
	case RunType::e3_6_NonLinear_FwdKinematics:
		dirName	= DIR_FWD_KINM_DATA;
		fName	= FILE_NAME_FWD_KINM;
	break;
	case RunType::e3_3_NonLinear_InvKinematics:
	case RunType::e12_3_NonLinear_InvKinematics:
	case RunType::e3_12_NonLinear_InvKinematics:
	case RunType::e12_12_NonLinear_InvKinematics:
	case RunType::e21_21_NonLinear_InvKinematics:
	case RunType::e30_30_NonLinear_InvKinematics:
	case RunType::e3_21_NonLinear_InvKinematics:
	case RunType::e3_30_NonLinear_InvKinematics:
	case RunType::e21_3_NonLinear_InvKinematics:
	case RunType::e30_3_NonLinear_InvKinematics:
	case RunType::e6_6_NonLinear_InvKinematics:
	case RunType::e6_3_NonLinear_InvKinematics:
	case RunType::e24_6_NonLinear_InvKinematics:
		dirName = DIR_INV_KINM_DATA;
		fName	= FILE_NAME_INV_KINM;
	break;
	
	default:
		std::cout << "Choice not supported!! \n";
		break;
	}

	return result;
}

string Logger::GetRootDirName(RunType eChoice)
{
	string result;

	switch (eChoice)
	{
		case RunType::e3_3:
			result = DIR_3_3;
		break;
		case RunType::e3_3_NonLinear_FwdKinematics:
			result = DIR_FWD_3_3;
		break;
		case RunType::e3_3_NonLinear_InvKinematics:
			result = DIR_INV_3_3;
		break;
		case RunType::e12_3_NonLinear_FwdKinematics:
			result = DIR_FWD_12_3;
		break;
		case RunType::e12_3_NonLinear_InvKinematics:
			result = DIR_INV_12_3;
		break;
		case RunType::e3_12_NonLinear_FwdKinematics:
			result = DIR_FWD_3_12;
		break;
		case RunType::e3_12_NonLinear_InvKinematics:
			result = DIR_INV_3_12;
		break;
		case RunType::e12_12_NonLinear_FwdKinematics:
			result = DIR_FWD_12_12;
		break;
		case RunType::e12_12_NonLinear_InvKinematics:
			result = DIR_INV_12_12;
		break;
		case RunType::e21_21_NonLinear_FwdKinematics:
			result = DIR_FWD_21_21;
		break;
		case RunType::e21_21_NonLinear_InvKinematics:
			result = DIR_INV_21_21;
		break;
		case RunType::e30_30_NonLinear_FwdKinematics:
			result = DIR_FWD_30_30;
		break;
		case RunType::e30_30_NonLinear_InvKinematics:
			result = DIR_INV_30_30;
		break;
		case RunType::e3_21_NonLinear_FwdKinematics:
			result = DIR_FWD_3_21;
		break;
		case RunType::e3_21_NonLinear_InvKinematics:
			result = DIR_INV_3_21;
		break;
		case RunType::e3_30_NonLinear_FwdKinematics:
			result = DIR_FWD_3_30;
		break;
		case RunType::e3_30_NonLinear_InvKinematics:
			result = DIR_INV_3_30;
		break;
		case RunType::e21_3_NonLinear_FwdKinematics:
			result = DIR_FWD_21_3;
		break;
		case RunType::e21_3_NonLinear_InvKinematics:
			result = DIR_INV_21_3;
		break;
		case RunType::e30_3_NonLinear_FwdKinematics:
			result = DIR_FWD_30_3;
		break;
		case RunType::e30_3_NonLinear_InvKinematics:
			result = DIR_INV_30_3;
		break;
		case RunType::e6_6_NonLinear_FwdKinematics:
			result = DIR_FWD_6_6;
		break;
		case RunType::e6_6_NonLinear_InvKinematics:
			result = DIR_INV_6_6;
		break;
		case RunType::e3_6_NonLinear_FwdKinematics:
			result = DIR_FWD_3_6;
		break;
		case RunType::e6_3_NonLinear_InvKinematics:
			result = DIR_INV_6_3;
		break;
		case RunType::e24_6_NonLinear_InvKinematics:
			result = DIR_INV_24_6;
		break;

		default:
			std::cout << "Choice not supported!! \n";
		break;
	}

	return result;
}

bool Logger::ConstructBasicDirFilePaths(RunType runChoice, EnvType envType, IOType ioType)
{
	bool result = true;

	s_BaseDirPath = DIR_LOGS;
	s_BaseDirPath += PATH_CONCAT;

	// Construct Basic Directory Path
	s_BaseDirPath += GetRootDirName(runChoice);
	s_BaseDirPath += PATH_CONCAT;

	switch (envType)
	{
	case EnvType::eStatic:
		s_BaseDirPath += DIR_STATIC;
		break;

	case EnvType::eDynamic:
		s_BaseDirPath += DIR_DYNAMIC;
		break;

	default:
		cout << "Environment Type not supported!" << endl;
	}
	s_BaseDirPath += PATH_CONCAT;

	switch (ioType)
	{
	case IOType::eDiscreteContinuous:
		s_BaseDirPath += DIR_DISC_CONT;
		break;

	case IOType::eContinuousContinuous:
		s_BaseDirPath += DIR_CONT_CONT;
		break;

	case IOType::eContinuousDiscrete:
		s_BaseDirPath += DIR_CONT_DISC;
		break;

	case IOType::eDiscreteDiscrete:
		s_BaseDirPath += DIR_DISC_DISC;
		break;

	default:
		cout << "IO Type not supported!" << endl;
	}
	s_BaseDirPath += PATH_CONCAT;

	// Construct Basic File Path
	s_BaseFileName = FILE_NAME_DATASET;
	s_BaseFileName += "_";

	return result;
}

bool Logger::ConstructFullDirFilePaths(string & finalDirPath, string & finalFileName, bool skipLastDir, string lastDirName, string fileVersion, string fName)
{
	bool result = true;

	string	dirPath;
	string	fileName;

	dirPath =	Logger::s_BaseDirPath;
	if (!skipLastDir)
	{
		dirPath += lastDirName;
		dirPath += PATH_CONCAT;
	}

	fileName =	Logger::s_BaseFileName;
	fileName += fileVersion;
	fileName += "_";
	fileName += fName;

	finalDirPath	= dirPath;
	finalFileName	= fileName;

	return result;
}

bool Logger::ConstructFullKinematicsDirFilePaths(string& finalDirPath, string& finalFileName, string lastDirName, string fileVersion, string fName)
{
	bool result = true;

	string	dirPath;
	string	fileName;

	dirPath = Logger::s_BaseDirPath;

	dirPath += DIR_KINM_DATA;
	dirPath += PATH_CONCAT;
	dirPath += lastDirName;
	dirPath += PATH_CONCAT;

	fileName = Logger::s_BaseFileName;
	fileName += fileVersion;
	fileName += "_";
	fileName += fName;

	finalDirPath	= dirPath;
	finalFileName	= fileName;

	return result;
}

bool Logger::ConstructFullDebugDirFilePaths(string& finalDirPath, string& finalFileName, bool skipLastDir, string lastDirName, string fileVersion, string fName)
{
	bool result = true;

	string	dirPath;
	string	fileName;

	dirPath = Logger::s_BaseDirPath;
	if (!skipLastDir)
	{
		dirPath += lastDirName;
		dirPath += PATH_CONCAT;
	}
	dirPath += DIR_DEBUG;
	dirPath += PATH_CONCAT;

	fileName = Logger::s_BaseFileName;
	fileName += fileVersion;
	fileName += "_";
	fileName += fName;

	finalDirPath	= dirPath;
	finalFileName	= fileName;

	return result;
}
