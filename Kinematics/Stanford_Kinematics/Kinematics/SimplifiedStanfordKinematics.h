#ifndef SIMPLIFIED_STANFORD_KINEMATICS
#define	SIMPLIFIED_STANFORD_KINEMATICS

#include <iostream>
#include <random>
#include <string>

using namespace std;

const int NUM_RUNS		= 50;
//const int NUM_TRIALS	= 20000;
const double PI			= 3.141593658979323846;
const double MAX_D		= 0.866025403784438647;  // square root of 0.75
//bool isDynamic			= false;

// 3x3
const string PATH_FWD_3_3_STATIC_DC = "..\\Logs\\3x3_FWD_KNM\\Static\\Continuous_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_3_3_DYNAMIC_DC = "..\\Logs\\3x3_FWD_KNM\\Dynamic\\Continuous_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_3_3_STATIC_DC = "..\\Logs\\3x3_INV_KNM\\Static\\Continuous_Continuous\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_3_3_DYNAMIC_DC = "..\\Logs\\3x3_INV_KNM\\Dynamic\\Continuous_Continuous\\Kinematics_Data\\InverseKinematics\\";
// 4x3
const string PATH_FWD_12_3_STATIC_DC = "..\\Logs\\12x3_FWD_KNM\\Static\\Discrete_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_12_3_DYNAMIC_DC = "..\\Logs\\12x3_FWD_KNM\\Dynamic\\Discrete_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_12_3_STATIC_DC = "..\\Logs\\12x3_INV_KNM\\Static\\Discrete_Continuous\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_12_3_DYNAMIC_DC = "..\\Logs\\12x3_INV_KNM\\Dynamic\\Discrete_Continuous\\Kinematics_Data\\InverseKinematics\\";
// 3x4
const string PATH_FWD_3_12_STATIC_CD = "..\\Logs\\3x12_FWD_KNM\\Static\\Continuous_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_3_12_DYNAMIC_CD = "..\\Logs\\3x12_FWD_KNM\\Dynamic\\Continuous_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_3_12_STATIC_CD = "..\\Logs\\3x12_INV_KNM\\Static\\Continuous_Discrete\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_3_12_DYNAMIC_CD = "..\\Logs\\3x12_INV_KNM\\Dynamic\\Continuous_Discrete\\Kinematics_Data\\InverseKinematics\\";
// 4x4
const string PATH_FWD_12_12_STATIC_DD = "..\\Logs\\12x12_FWD_KNM\\Static\\Discrete_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_12_12_DYNAMIC_DD = "..\\Logs\\12x12_FWD_KNM\\Dynamic\\Discrete_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_12_12_STATIC_DD = "..\\Logs\\12x12_INV_KNM\\Static\\Discrete_Discrete\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_12_12_DYNAMIC_DD = "..\\Logs\\12x12_INV_KNM\\Dynamic\\Discrete_Discrete\\Kinematics_Data\\InverseKinematics\\";
// 21x21
const string PATH_FWD_21_21_STATIC_DD = "..\\Logs\\21x21_FWD_KNM\\Static\\Discrete_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_21_21_DYNAMIC_DD = "..\\Logs\\21x21_FWD_KNM\\Dynamic\\Discrete_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_21_21_STATIC_DD = "..\\Logs\\21x21_INV_KNM\\Static\\Discrete_Discrete\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_21_21_DYNAMIC_DD = "..\\Logs\\21x21_INV_KNM\\Dynamic\\Discrete_Discrete\\Kinematics_Data\\InverseKinematics\\";
// 30x30
const string PATH_FWD_30_30_STATIC_DD = "..\\Logs\\30x30_FWD_KNM\\Static\\Discrete_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_30_30_DYNAMIC_DD = "..\\Logs\\30x30_FWD_KNM\\Dynamic\\Discrete_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_30_30_STATIC_DD = "..\\Logs\\30x30_INV_KNM\\Static\\Discrete_Discrete\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_30_30_DYNAMIC_DD = "..\\Logs\\30x30_INV_KNM\\Dynamic\\Discrete_Discrete\\Kinematics_Data\\InverseKinematics\\";
// 3x21
const string PATH_FWD_3_21_STATIC_CD = "..\\Logs\\3x21_FWD_KNM\\Static\\Continuous_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_3_21_DYNAMIC_CD = "..\\Logs\\3x21_FWD_KNM\\Dynamic\\Continuous_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_3_21_STATIC_CD = "..\\Logs\\3x21_INV_KNM\\Static\\Continuous_Discrete\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_3_21_DYNAMIC_CD = "..\\Logs\\3x21_INV_KNM\\Dynamic\\Continuous_Discrete\\Kinematics_Data\\InverseKinematics\\";
// 3x30
const string PATH_FWD_3_30_STATIC_CD = "..\\Logs\\3x30_FWD_KNM\\Static\\Continuous_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_3_30_DYNAMIC_CD = "..\\Logs\\3x30_FWD_KNM\\Dynamic\\Continuous_Discrete\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_3_30_STATIC_CD = "..\\Logs\\3x30_INV_KNM\\Static\\Continuous_Discrete\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_3_30_DYNAMIC_CD = "..\\Logs\\3x30_INV_KNM\\Dynamic\\Continuous_Discrete\\Kinematics_Data\\InverseKinematics\\";
// 21x3
const string PATH_FWD_21_3_STATIC_DC = "..\\Logs\\21x3_FWD_KNM\\Static\\Discrete_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_21_3_DYNAMIC_DC = "..\\Logs\\21x3_FWD_KNM\\Dynamic\\Discrete_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_21_3_STATIC_DC = "..\\Logs\\21x3_INV_KNM\\Static\\Discrete_Continuous\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_21_3_DYNAMIC_DC = "..\\Logs\\21x3_INV_KNM\\Dynamic\\Discrete_Continuous\\Kinematics_Data\\InverseKinematics\\";
// 30x3
const string PATH_FWD_30_3_STATIC_DC = "..\\Logs\\30x3_FWD_KNM\\Static\\Discrete_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_30_3_DYNAMIC_DC = "..\\Logs\\30x3_FWD_KNM\\Dynamic\\Discrete_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_30_3_STATIC_DC = "..\\Logs\\30x3_INV_KNM\\Static\\Discrete_Continuous\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_30_3_DYNAMIC_DC = "..\\Logs\\30x3_INV_KNM\\Dynamic\\Discrete_Continuous\\Kinematics_Data\\InverseKinematics\\";
// 6x6
const string PATH_FWD_6_6_STATIC_CC = "..\\Logs\\6x6_FWD_KNM\\Static\\Continuous_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_FWD_6_6_DYNAMIC_CC = "..\\Logs\\6x6_FWD_KNM\\Dynamic\\Continuous_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_6_6_STATIC_CC = "..\\Logs\\6x6_INV_KNM\\Static\\Continuous_Continuous\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_6_6_DYNAMIC_CC = "..\\Logs\\6x6_INV_KNM\\Dynamic\\Continuous_Continuous\\Kinematics_Data\\InverseKinematics\\";

// Misc
const string PATH_FWD_3_6_STATIC_CC = "..\\Logs\\3x6_FWD_KNM\\Static\\Continuous_Continuous\\Kinematics_Data\\ForwardKinematics\\";
const string PATH_INV_6_3_STATIC_CC = "..\\Logs\\6x3_INV_KNM\\Static\\Continuous_Continuous\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_6_3_DYNAMIC_CC = "..\\Logs\\6x3_INV_KNM\\Dynamic\\Continuous_Continuous\\Kinematics_Data\\InverseKinematics\\";
const string PATH_INV_24_6_DYNAMIC_DC = "..\\Logs\\24x6_INV_KNM\\Dynamic\\Discrete_Continuous\\Kinematics_Data\\InverseKinematics\\";

const string PATH_INV_3_3_DYNAMIC_CC = "..\\Logs\\3x3_INV_KNM\\Dynamic\\Continuous_Continuous\\Kinematics_Data\\InverseKinematics\\";

#endif // SIMPLIFIED_STANFORD_KINEMATICS
