1)
The dir names exaplained:

S(SUN)RL:	Stochastic (Synapse, Unit, Network) Reinforcement Learning
REINFORCE_SUN:	Family of REINFORCE based algorithms

Dynamic_CC => where C: Continuous states and C: Continuous actions
Dynamic_DC => where D: Discrete states and C: Continuous actions

Num_InputsxNum_Outputs_Inverse_Kinematics_JointType

e.g., 3x3_INV_KNM_R represents a 3 input, 3 output, inverse kinematics revolute-joint robotic arm dataset.

At the end of the dir name, revolute joint is presented as _R  => PUMA arm
while 
prismatic joint is presented as _P => Stanford arm

2)
DataSet_0_Rewards.txt contains the rewards collected during each run indicated by _0_ in this example split by trials from 0 to 19999 within each file.

3)
DataSet_*_InverseKinematics.txt contains the dataset with following values in a sequence from left to right in each row for a distinct trial:
the position in Cartesian three-space ($x, y, z$) and orientation given as roll, pitch, and yaw of the end effector base plate followed by the waist, shoulder, elbow, and three joints of a spherical wrist.

The above order of the position, orientation, and joint angles is consistent across all datasets however which ones are included depend upon the dataset type specified by the number of inputs/outputs.

For example, 3x3 includes the following:
position in Cartesian three-space ($x, y, z$) followed by waist, shoulder, elbow joints

For discrete inputs, each number is discretized so several bits replace the decimal number.




