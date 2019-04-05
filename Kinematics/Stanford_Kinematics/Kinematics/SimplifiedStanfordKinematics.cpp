/*
Calculates end positions in x, y, z three-space and orienations in roll, pitch, yaw angles relative to the origin
for a simple two-link robot arm with a waist joint (that rotates 360 degrees in the horizontal plane), a shoulder
joint (that rotates 360 degrees vertically, with 0 degrees straight out to one side), and an elbow joint (that
rotates vertically, with 0 degrees bent up at a right angle to the first link), and a three DOF wrist of zero
length. The elbow rotation can be from -90 to 90 degrees (considered the "elbow forward" configuration) or 90 to
270 degress (considered the "elbow backward" configuration). Both links are 1/2 unit length and the first link is
situated at the origin. This means that for either configuration the robot is able to reach any position within a
unit sphere with a unique set of joint angles for each end position except straight up (0, 0, 1), straight down
(0, 0, -1), and the origin (0, 0, 0) for which there are an infinite number of possibilities each. (For straight
up, the shoulder and elbow joint angles must be 0 but the waist angle may be any value. Similarly, for straight
down, the shoulder angle must be 180 degrees and the elbow angle must be 0 degrees but the the waist angle may be
any value. Finally, for the origin, the elbow joint must be 180 degrees (or -180 degrees for the "elbow backward"
configuration) but the waist and shoulder angles may be any value.) Moreover, the wrist allows for end of the arm
to be placed at any arbitrary orientation.

To reorient the axis of rotation between the end of the arm and the wrist joint, we add a 90 degree theta transform.

The arm is assumed to have zero volume, so the full range of motion is possible on all joints without the
risk of self collisions.

For static experiments, generate all values with one range of joint angles. For dynamic experiments, generate the
first half of the data with one range of joint angles and the second half of the data with a second set.
*/

#include "SimplifiedStanfordKinematics.h"
#include "Util.h"

using namespace std;

static void RunExperiments(int numTrials, string dirNames, string fName, bool isDynamic, bool isForwardKnm, bool isCC, bool isCutOff, bool isSubInput, bool isSubOutput)
{
	std::cout << std::fixed; std::cout.precision(2);

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	double T[7][4][4];  // an array of seven 4x4 transformation matrices (including the origin)

	// Generate some number of runs of sum number of trials each.
	for (int run = 0; run < NUM_RUNS; ++run) 
	{
		string fileName = "DataSet_" + to_string(run) + "_" + fName;
		OpenFile(dirNames + fileName);
		cout << dirNames + fileName << endl;
		for (int trial = 0; trial < numTrials; ++trial)
		{
			// get the five joint angles and one sliding distance at random from their ranges (in radians for angles, unspecified distance units for sliding joint)
			double t1 = distribution(generator) * PI / 2.0;							// 0 to pi/2
			double t2 = distribution(generator) * PI / 2.0 - PI / 4.0;				// -pi/4 to pi/4
			double d3 = distribution(generator) * MAX_D / 2.0;						// 0 to ~0.443
			double t4 = distribution(generator) * PI / 4.0 - PI / 4.0;				// -pi/4 to 0; set to 0 for 3x6 or 6x3 cases
			double t5 = distribution(generator) * PI / 4.0;							// 0 to pi/4; set to 0 for 3x6 or 6x3 cases
			double t6 = distribution(generator) * PI / 4.0;							// 0 to pi/4; set to 0 for 3x6 or 6x3 cases

			if (isDynamic && trial >= numTrials / 2.0) {						// after midpoint
				t1 += PI;															// pi to 3pi/2
				t2 += PI;															// 3pi/4 to 5pi/4 
				d3 += MAX_D / 2.0;													// ~0.443 to ~0.886
				t4 += PI / 4.0;														// 0 to pi/4; set to 0 for 3x6 or 6x3 cases
				t5 -= PI / 4.0;														// -pi/4 to 0; set to 0 for 3x6 or 6x3 cases
				t6 -= PI / 4.0;														// -pi/4 to 0; set to 0 for 3x6 or 6x3 cases
			}

			if (isCutOff)
			{
				t4 = t5 = t6 = 0.0;
			}

			// calculate the matrices in turn

			// base is the origin (identity matrix)
			T[0][0][0] = 1.0;
			T[0][0][1] = 0.0;
			T[0][0][2] = 0.0;
			T[0][0][3] = 0.0;

			T[0][1][0] = 0.0;
			T[0][1][1] = 1.0;
			T[0][1][2] = 0.0;
			T[0][1][3] = 0.0;

			T[0][2][0] = 0.0;
			T[0][2][1] = 0.0;
			T[0][2][2] = 1.0;
			T[0][2][3] = 0.0;

			T[0][3][0] = 0.0;
			T[0][3][1] = 0.0;
			T[0][3][2] = 0.0;
			T[0][3][3] = 1.0;

			// after waist, rotate 90 degrees about x for shoulder, affix second joint at same position
			T[1][0][0] = cos(t1);
			T[1][0][1] = 0.0;
			T[1][0][2] = sin(t1);
			T[1][0][3] = 0.0;

			T[1][1][0] = sin(t1);
			T[1][1][1] = 0.0;
			T[1][1][2] = -cos(t1);
			T[1][1][3] = 0.0;

			T[1][2][0] = 0.0;
			T[1][2][1] = 1.0;
			T[1][2][2] = 0.0;
			T[1][2][3] = 0.0;

			T[1][3][0] = 0.0;
			T[1][3][1] = 0.0;
			T[1][3][2] = 0.0;
			T[1][3][3] = 1.0;

			// after shoulder, extend 0.5 units along radius of motion, rotate -90 degrees, affix sliding elbow
			T[2][0][0] = cos(t2);
			T[2][0][1] = 0.0;
			T[2][0][2] = -sin(t2);
			T[2][0][3] = 0.0;

			T[2][1][0] = sin(t2);
			T[2][1][1] = 0.0;
			T[2][1][2] = cos(t2);
			T[2][1][3] = 0.0;

			T[2][2][0] = 0.0;
			T[2][2][1] = -1.0;
			T[2][2][2] = 0.0;
			T[2][2][3] = 0.5;

			T[2][3][0] = 0.0;
			T[2][3][1] = 0.0;
			T[2][3][2] = 0.0;
			T[2][3][3] = 1.0;

			// sliding elbow is affixed at end of upper arm, so this is the identity matrix; slide length accounted for in next matrix
			T[3][0][0] = 1.0;
			T[3][0][1] = 0.0;
			T[3][0][2] = 0.0;
			T[3][0][3] = 0.0;

			T[3][1][0] = 0.0;
			T[3][1][1] = 1.0;
			T[3][1][2] = 0.0;
			T[3][1][3] = 0.0;

			T[3][2][0] = 0.0;
			T[3][2][1] = 0.0;
			T[3][2][2] = 1.0;
			T[3][2][3] = 0.0;

			T[3][3][0] = 0.0;
			T[3][3][1] = 0.0;
			T[3][3][2] = 0.0;
			T[3][3][3] = 1.0;

			// translate length of prismatic elbow units along forearm to attach first wrist joint, rotate 90 degrees around x to attach second wrist joint
			T[4][0][0] = cos(t4);
			T[4][0][1] = 0.0;
			T[4][0][2] = sin(t4);
			T[4][0][3] = 0.0;

			T[4][1][0] = sin(t4);
			T[4][1][1] = 0.0;
			T[4][1][2] = -cos(t4);
			T[4][1][3] = 0.0;

			T[4][2][0] = 0.0;
			T[4][2][1] = 1.0;
			T[4][2][2] = 0.0;
			T[4][2][3] = d3;

			T[4][3][0] = 0.0;
			T[4][3][1] = 0.0;
			T[4][3][2] = 0.0;
			T[4][3][3] = 1.0;

			// rotate -90 degrees around x to attach third wrist joint (parallel to first wrist joint if second wrist joint is at zero)
			T[5][0][0] = cos(t5);
			T[5][0][1] = 0.0;
			T[5][0][2] = -sin(t5);
			T[5][0][3] = 0.0;

			T[5][1][0] = sin(t5);
			T[5][1][1] = 0.0;
			T[5][1][2] = cos(t5);
			T[5][1][3] = 0.0;

			T[5][2][0] = 0.0;
			T[5][2][1] = -1.0;
			T[5][2][2] = 0.0;
			T[5][2][3] = 0.0;

			T[5][3][0] = 0.0;
			T[5][3][1] = 0.0;
			T[5][3][2] = 0.0;
			T[5][3][3] = 1.0;

			// attach tool plate
			T[6][0][0] = cos(t6);
			T[6][0][1] = -sin(t6);
			T[6][0][2] = 0.0;
			T[6][0][3] = 0.0;

			T[6][1][0] = sin(t6);
			T[6][1][1] = cos(t6);
			T[6][1][2] = 0.0;
			T[6][1][3] = 0.0;

			T[6][2][0] = 0.0;
			T[6][2][1] = 0.0;
			T[6][2][2] = 1.0;
			T[6][2][3] = 0.0;

			T[6][3][0] = 0.0;
			T[6][3][1] = 0.0;
			T[6][3][2] = 0.0;
			T[6][3][3] = 1.0;

			double A[4][4];		// the matrix of results, also initialized to origin (identity)
			A[0][0] = 1.0;
			A[0][1] = 0.0;
			A[0][2] = 0.0;
			A[0][3] = 0.0;

			A[1][0] = 0.0;
			A[1][1] = 1.0;
			A[1][2] = 0.0;
			A[1][3] = 0.0;

			A[2][0] = 0.0;
			A[2][1] = 0.0;
			A[2][2] = 1.0;
			A[2][3] = 0.0;

			A[3][0] = 0.0;
			A[3][1] = 0.0;
			A[3][2] = 0.0;
			A[3][3] = 1.0;

			double B[4][4];		// temp matrix used for calculations
			for (int t = 0; t < 7; t++) {  // for each transformation matrix; because the sliding joint doesn't show up until the fifth transformation matrix, don't cap this at 4 for 6x3 or 3x6 case, zero out the wrist joints instead
				for (int row = 0; row < 4; row++) {
					for (int col = 0; col < 4; col++) {
						B[row][col] = 0.0;
						for (int i = 0; i < 4; i++) {
							B[row][col] += A[row][i] * T[t][i][col];
						}
					}
				}
				for (int row = 0; row < 4; row++) {
					for (int col = 0; col < 4; col++) {
						A[row][col] = B[row][col];
					}
				}
			}

			// pull the relevant elements from the rotation and translation matrix
			double x = A[0][3];
			double y = A[1][3];
			double z = A[2][3];

			// calculate roll, pitch, and yaw of the end of the arm
			double roll = atan2(A[0][1], A[0][0]);  // around original z axis
			double pitch = atan2(-A[0][2], A[0][0] * cos(roll) + A[0][1] * sin(roll));  // around original x axis
			double yaw = atan2(A[1][2], A[2][2]);  // around original y axis

			double scaledYaw = yaw / PI / 2.0 + 0.75;
			if (scaledYaw > 1.0) {
				scaledYaw -= 1.0;
			}
			// Computations are complete


			//// output data scaled to the range [0,+1]
			//std::cout << "Trial " << trial << ":" << '\t'
			//	<< t1 / PI / 2.0 + 0.125 << '\t'
			//	<< t2 / PI / 2.0 + 0.25 << '\t'
			//	<< d3 / MAX_D << '\t'
			//	<< t4 / PI + 0.5 << '\t'
			//	<< t5 / PI + 0.5 << '\t'
			//	<< t6 / PI + 0.5 << '\t'
			//	<< (x + 1.0) / 2.0 << '\t'
			//	<< (y + 1.0) / 2.0 << '\t'
			//	<< (z + 1.0) / 2.0 + 0.1 << '\t'
			//	<< roll / PI / 2.0 + 0.5 << '\t'
			//	<< pitch / PI + 0.5 << '\t'
			//	<< scaledYaw << std::endl;

			vector<double> data;
			if (isForwardKnm)
			{
				// Forward Kinematics

				// Angles
				data.push_back(t1 / PI / 2.0 + 0.125);
				data.push_back(t2 / PI / 2.0 + 0.25);
				data.push_back(d3 / MAX_D);
				if (!isSubInput)
				{
					data.push_back(t4 / PI + 0.5);
					data.push_back(t5 / PI + 0.5);
					data.push_back(t6 / PI + 0.5);
				}
				// Position/Orientation
				data.push_back((x + 1.0) / 2.0);
				data.push_back((y + 1.0) / 2.0);
				data.push_back((z + 1.0) / 2.0 + 0.1); 
				if (!isSubOutput)
				{
					data.push_back(roll / PI / 2.0 + 0.5);
					data.push_back(pitch / PI + 0.5);
					data.push_back(scaledYaw);
				}
			}
			else
			{
				// Inverse Kinematics

				// Position/Orientation
				data.push_back((x + 1.0) / 2.0);
				data.push_back((y + 1.0) / 2.0);
				data.push_back((z + 1.0) / 2.0 + 0.1);
				if (!isSubInput)
				{
					data.push_back(roll / PI / 2.0 + 0.5);
					data.push_back(pitch / PI + 0.5);
					data.push_back(scaledYaw);
				}
				// Angles
				data.push_back(t1 / PI / 2.0 + 0.125);
				data.push_back(t2 / PI / 2.0 + 0.25);
				data.push_back(d3 / MAX_D);
				if (!isSubOutput)
				{
					data.push_back(t4 / PI + 0.5);
					data.push_back(t5 / PI + 0.5);
					data.push_back(t6 / PI + 0.5);
				}
			}
			if (!isCC)
			{
				// Translate data according to the discrete bits
				data = ConvertToBits(dirNames, data);
			}
			WriteVector(data, to_string(trial));
		}
		CloseFile();
		cout << "Run " << run << " Complete." << std::endl;
	}
}

static void SetParamAndRun()
{

	// RunExperiments(numTrials, string dirNames, string fName, bool isDynamic, bool isForwardKnm, bool isCC, bool isCutOff, bool isSubInput, bool isSubOutput)

	RunExperiments(20000, PATH_INV_3_3_DYNAMIC_CC, "InverseKinematics.txt", true, false, true, true, true, true);

	//RunExperiments(20000, PATH_INV_6_6_DYNAMIC_CC, "InverseKinematics.txt", true, false, true, false, false, false);
	//RunExperiments(20000, PATH_INV_6_3_DYNAMIC_CC, "InverseKinematics.txt", true, false, true, true, false, true);
	//RunExperiments(20000, PATH_INV_24_6_DYNAMIC_DC, "InverseKinematics.txt", true, false, false, false, false, false);

	//RunExperiments(8000, PATH_FWD_6_6_STATIC_CC, "ForwardKinematics.txt", false, true, true, false, false, false);
	//RunExperiments(8000, PATH_FWD_3_6_STATIC_CC, "ForwardKinematics.txt", false, true, true, true, true, false);
	//RunExperiments(8000, PATH_INV_6_6_STATIC_CC, "InverseKinematics.txt", false, false, true, false, false, false);
	//RunExperiments(8000, PATH_INV_6_3_STATIC_CC, "InverseKinematics.txt", false, false, true, true, false, true);
	//RunExperiments(20000, PATH_INV_6_6_DYNAMIC_CC, "InverseKinematics.txt", true, false, true, false, false, false);
	//RunExperiments(20000, PATH_INV_6_3_DYNAMIC_CC, "InverseKinematics.txt", true, false, true, true, false, true);

	//RunExperiments(20000, PATH_INV_24_6_DYNAMIC_DC, "InverseKinematics.txt", true, false, false, false, false, false);


	////RunExperiments(PATH_FWD_3_3_STATIC_DC, "ForwardKinematics.txt", false, true, true);
	//RunExperiments(PATH_FWD_3_3_DYNAMIC_DC, "ForwardKinematics.txt", true, true, true);
	////RunExperiments(PATH_INV_3_3_STATIC_DC, "InverseKinematics.txt", false, false, true);
	//RunExperiments(PATH_INV_3_3_DYNAMIC_DC, "InverseKinematics.txt", true, false, true);

	////RunExperiments(PATH_FWD_12_3_STATIC_DC, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_12_3_DYNAMIC_DC, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_12_3_STATIC_DC, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_12_3_DYNAMIC_DC, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_21_3_STATIC_DC, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_21_3_DYNAMIC_DC, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_21_3_STATIC_DC, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_21_3_DYNAMIC_DC, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_30_3_STATIC_DC, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_30_3_DYNAMIC_DC, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_30_3_STATIC_DC, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_30_3_DYNAMIC_DC, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_3_12_STATIC_CD, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_3_12_DYNAMIC_CD, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_3_12_STATIC_CD, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_3_12_DYNAMIC_CD, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_12_12_STATIC_DD, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_12_12_DYNAMIC_DD, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_12_12_STATIC_DD, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_12_12_DYNAMIC_DD, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_21_21_STATIC_DD, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_21_21_DYNAMIC_DD, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_21_21_STATIC_DD, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_21_21_DYNAMIC_DD, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_30_30_STATIC_DD, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_30_30_DYNAMIC_DD, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_30_30_STATIC_DD, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_30_30_DYNAMIC_DD, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_3_21_STATIC_CD, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_3_21_DYNAMIC_CD, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_3_21_STATIC_CD, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_3_21_DYNAMIC_CD, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_3_30_STATIC_CD, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_3_30_DYNAMIC_CD, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_3_30_STATIC_CD, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_3_30_DYNAMIC_CD, "InverseKinematics.txt", true, false, false);

	////RunExperiments(PATH_FWD_6_6_STATIC_CC, "ForwardKinematics.txt", false, true, false);
	//RunExperiments(PATH_FWD_6_6_DYNAMIC_CC, "ForwardKinematics.txt", true, true, false);
	////RunExperiments(PATH_INV_6_6_STATIC_CC, "InverseKinematics.txt", false, false, false);
	//RunExperiments(PATH_INV_6_6_DYNAMIC_CC, "InverseKinematics.txt", true, false, false);

}

int main()
{
	SetParamAndRun();

	return 0;
}