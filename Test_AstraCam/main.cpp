#include <iostream>
using namespace std;

#include <OpenNI.h>
#include "opencv2/opencv.hpp"

#include "../../../../../EwayPublic/OS/publicdef.h"
#include "./astra_reader/AstraReader.h"
#include "./astra_calibration/AstraCalibration.h"

int main(int argc, char *argv[])
{
   edouble  darryIntrinsicMat[9];
   eint     nImgWidth, nImgHeight;

   /*
    * Use Obec Astra camera to get image and stored in the path the user pointed
    */

   /*
    CAstraReader iCam;
    iCam.Initialize(0, darryIntrinsicMat);
    iCam.GetResolution(nImgWidth, nImgHeight);

    cv::Mat matColor, matDepth;
    // complete path + "/"
    iCam.GetImage("/home/moro/Desktop/", "test");
   */


    estring strChessBoardFile = "./chessboard/cb.txt";
    estring strCalibFile      = "../../VisionElement/AstraCam/AstraIntrin.txt";
    /*
     * Do Obec Astra camera calibration
     */
    CAstraCalibration iCalibrator;
    iCalibrator.Initialize(640, 480);
    iCalibrator.RunCalibration(strChessBoardFile, strCalibFile);

    /*
     * Read camera calibration parameter file
     */
    cv::Mat CamMatrix, DistCoeffs;
    iCalibrator.ReadParamFile(strCalibFile, CamMatrix, DistCoeffs);

    cout << "====== AstraCam_Calib done. ======" << endl;
    return 0;
}
