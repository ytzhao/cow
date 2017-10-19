#include <iostream>
using namespace std;

#include <OpenNI.h>
#include "opencv2/opencv.hpp"

#include "../../../../EwayPublic/OS/publicdef.h"
#include "./astra_reader/AstraReader.h"
#include "./astra_calibration/AstraCalibration.h"

int main(int argc, char *argv[])
{
   edouble  darryIntrinsicMat[9];
   eint     nImgWidth, nImgHeight;

//   CAstraReader iCam;
//   iCam.Initialize(0, darryIntrinsicMat);
//   iCam.GetResolution(nImgWidth, nImgHeight);

//    cv::Mat matColor, matDepth;
//     while (1) {
//         iCam.ReadFrame(matColor, matDepth);
//         cv::imshow("color", matColor);
//         cv::waitKey(1);
//         cv::imshow("depth", matDepth);
//         cv::waitKey(1);
//     }

    // complete path + "/"
//    iCam.GetImage("/home/moro/Desktop/", "cb");


    // do Astra camera calibration
    CAstraCalibration iCalibrator;
    iCalibrator.Initialize(640, 480);
    
    // while( false==iCalibrator.IsCalibrated() ) {
    //      iCam.ReadFrame(matColor, matDepth);
    //      iCalibrator.RunCalibration(matColor);
    // }
    iCalibrator.RunCalibration("/home/moro/Desktop/cb.txt");

     estring strFile = "/home/moro/Desktop/AstraCam_Intrinsic_Param.txt";
     cv::Mat CamMatrix, DistCoeffs;
     iCalibrator.ReadParamFile(strFile, CamMatrix, DistCoeffs);

    edouble err = iCalibrator.Evaluate(CamMatrix, DistCoeffs);
    cout << "err: " << err << endl;


    cout << "Test_AstraCame done" << endl;
    return 0;
}
