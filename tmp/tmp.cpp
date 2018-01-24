#include <iostream>
using namespace std;

#include "Eigen/Dense"

struct MarkerInfo
{
    double dX;
    double dY;
    double dZ;

    double dRx;
    double dRy;
    double dRz;
};


int CalcPosByKnownMarker(MarkerInfo seenMarker, Eigen::Vector3d vecKnownMarker, Eigen::Vector3d &vecBotPos)
{
    /* A_Robot_World: Robot coordinate in World coordinate presentation */
    Eigen::Matrix4d A_Robot_World, A_Marker_World, A_Marker_Robot, A_Robot_Marker;

    Eigen::Vector3d vecRotationalVector;
    Eigen::Matrix3d R_Marker_Robot;
    Eigen::Vector3d p_Marker_Robot;

    p_Marker_Robot      << seenMarker.dX,  seenMarker.dY,  seenMarker.dZ;   // marker x,y,z in Robot coordinate system
    vecRotationalVector << seenMarker.dRx, seenMarker.dRy, seenMarker.dRz;
    ConvertRodrigues2RotationM(vecRotationalVector, R_Marker_Robot);    // convert to 3x3 matrix in Robot, marker_Marker_in_Robot

    cout << "vecRotationalVector: \n" << vecRotationalVector << endl;
    A_Marker_Robot << R_Marker_Robot(0,0), R_Marker_Robot(0,1), R_Marker_Robot(0,2), seenMarker.dX,
                      R_Marker_Robot(1,0), R_Marker_Robot(1,1), R_Marker_Robot(1,2), seenMarker.dY,
                      R_Marker_Robot(2,0), R_Marker_Robot(2,1), R_Marker_Robot(2,2), seenMarker.dZ,
                      0,                   0,                   0,                   1;

    cout << "A_Marker_Robot: \n" << A_Marker_Robot << endl;

    Eigen::Matrix3d tmpR;
    Eigen::Vector3d tmpT;
    tmpR =  R_Marker_Robot.transpose();
    tmpT = -R_Marker_Robot.transpose()*p_Marker_Robot;

    A_Robot_Marker << tmpR(0,0), tmpR(0,1), tmpR(0,2), tmpT(0),
                      tmpR(1,0), tmpR(1,1), tmpR(1,2), tmpT(1),
                      tmpR(2,0), tmpR(2,1), tmpR(2,2), tmpT(2),
                      0,         0,         0,         1;

    cout << "A_Robot_Marker: \n" << A_Robot_Marker << std::endl;

//       x<---
//          /|
//         / |
//        z  y
//        A_Marker_World << sin(vecKnownMarker[2]), 0,  cos(vecKnownMarker[2]), vecKnownMarker[0],
//                         -cos(vecKnownMarker[2]), 0,  sin(vecKnownMarker[2]), vecKnownMarker[1],
//                          0,                     -1,  0,                      seenMarker.dZ,
//                          0,                      0,  0,                      1;

//           y
//           |
//           |
//           --->x
//          /
//         /
//        z
    A_Marker_World << -sin(vecKnownMarker[2]), 0,  cos(vecKnownMarker[2]), vecKnownMarker[0],
                       cos(vecKnownMarker[2]), 0,  sin(vecKnownMarker[2]), vecKnownMarker[1],
                       0,                      1,  0,                      seenMarker.dZ,
                       0,                      0,  0,                      1;

    cout << "A_Marker_World: \n" << A_Marker_World << endl;

    A_Robot_World = A_Marker_World * A_Robot_Marker;
    cout << "A_Robot_World: \n" << A_Robot_World << endl;

    vecBotPos[0] = A_Robot_World(0, 3);
    vecBotPos[1] = A_Robot_World(1, 3);
    vecBotPos[2] = atan2(A_Robot_World(1,0), A_Robot_World(0,0));
    cout << "vecBotPos: \n" << vecBotPos << endl;

    return 0;
}
