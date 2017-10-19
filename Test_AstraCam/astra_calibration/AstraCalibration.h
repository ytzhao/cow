#ifndef CASTRACALIBRATION_H_INCLUDED
#define CASTRACALIBRATION_H_INCLUDED

#include <math.h>
#include <vector>
#include <fstream>
using namespace std;

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"

#include "../../../../../../EwayPublic/OS/publicdef.h"

// some definition
#define CHESS_BOARD_WIDTH  9
#define CHESS_BOARD_HEIGHT 6
#define SQUARE_SIDE        25
#define TERMCRITETIA_MAXCOUNT 30
#define TERMCRITETIA_EPSILON 0.001
#define WINDOW_SIZE 11
#define ZERO_ZONE -1
#define SAMPLE_INTERVAL 100
#define SAMPLE_FRAMES 25

class CAstraCalibration
{
    public:
        CAstraCalibration();
        ~CAstraCalibration();

        void  Initialize(eint nImageWidth, eint nImageHeight);
        // ebool RunCalibration(cv::Mat matColor);
        ebool RunCalibration(estring strFileName);
        ebool IsCalibrated() { return m_bCalibrated; }

        ebool   ReadParamFile(estring strFile, cv::Mat &CamMatrix, cv::Mat &DistCoeffs);
        edouble Evaluate(cv::Mat CamMatrix, cv::Mat DistCoeffs);

    private:
        void  SaveFile(cv::Mat, cv::Mat);
        void  InitMatrix(vector<cv::Point3f>*);

        ebool   m_bCalibrated=false;
        eint    m_nCalibratedImageNum=0;

        eint    m_nImageWidth=640;
        eint    m_nImageHeight=480;

        vector<cv::Point3f>         *m_pvObjectPoints;
        vector<vector<cv::Point3f> > m_vObjectPointsList;
        vector<vector<cv::Point2f> > m_vImagePointsList;
        vector<eint>                 m_vPointsCounts;

        vector<cv::Mat> m_vMatrixR; 
        vector<cv::Mat> m_vMatrixT;
};

#endif // CCALIBRATION_H_INCLUDED
