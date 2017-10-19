#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

#include "AstraCalibration.h"

CAstraCalibration::CAstraCalibration()
{
    // Init object point matrix
    m_pvObjectPoints = new vector<cv::Point3f>;
    InitMatrix(m_pvObjectPoints);
}

CAstraCalibration::~CAstraCalibration()
{
    delete m_pvObjectPoints;
}

void CAstraCalibration::Initialize(eint nImageWidth, eint nImageHeight)
{
    m_nImageWidth  = nImageWidth;
    m_nImageHeight = nImageHeight;
}


// ebool CAstraCalibration::RunCalibration(cv::Mat matColor)
ebool CAstraCalibration::RunCalibration(estring strFileName)
{
    ifstream fin;
    fin.open(strFileName.c_str());
    if ( !fin ) {
        cout << "!!!!!! Run calibration can not open file" << endl;
        return false;
    }

    cv::Size patternSize(CHESS_BOARD_WIDTH, CHESS_BOARD_HEIGHT);
    vector<cv::Point2f> vCornersInImg;

    while ( fin.good() )
    {
        estring strJpg;
        getline(fin, strJpg);
        if (""==strJpg) {
            break;
        }

        m_nCalibratedImageNum++;
        estring strFile = "/home/moro/Desktop/chessboard/" + strJpg;
        cout << strFile << endl;

        // get frame height and width
        cv::Mat matColor = cv::imread(strFile);
        m_nImageWidth  = matColor.cols;
        m_nImageHeight = matColor.rows;

        // 1. covert image to gray
        cv::Mat matGray;
        cv::cvtColor(matColor, matGray, CV_BGR2GRAY);

        // 2. find chessboard interior corners
        ebool bPatternFound = cv::findChessboardCorners(matGray, patternSize, vCornersInImg, \
                                                        CV_CALIB_CB_ADAPTIVE_THRESH + CV_CALIB_CB_NORMALIZE_IMAGE + CV_CALIB_CB_FAST_CHECK);

        if (bPatternFound) {
            // 3. improve the found corners' coordinate accuracy for chessboard
            cv::cornerSubPix(matGray, vCornersInImg, cv::Size(WINDOW_SIZE, WINDOW_SIZE), cv::Size(ZERO_ZONE, ZERO_ZONE), 
                             cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, TERMCRITETIA_MAXCOUNT, TERMCRITETIA_EPSILON));

            m_vObjectPointsList.push_back(*m_pvObjectPoints);
            m_vImagePointsList.push_back(vCornersInImg);
            m_vPointsCounts.push_back(CHESS_BOARD_WIDTH * CHESS_BOARD_HEIGHT);

            // 4. draw chessboard corners
            cv::drawChessboardCorners(matColor, patternSize, cv::Mat(vCornersInImg), bPatternFound);
            cv::imshow("Image calibrate", matColor);
            cv::waitKey(200);
        } else {
            cout << "pattern found fail" << endl;
            EASSERT(0);
        }
    }


    // // 4. draw chessboard corners
    // cv::drawChessboardCorners(matColor, patternSize, cv::Mat(vCornersInImg), bPatternFound);
    // cv::imshow("Image calibrate", matColor);
    // cv::waitKey(1);
   
    // 5. get enough samples for calibration
    if ( (!m_bCalibrated) && (0 != m_vImagePointsList.size()) ) {
        cv::Mat cameraMatrix;
        cv::Mat distCoeffs;
        
        cv::calibrateCamera(m_vObjectPointsList, m_vImagePointsList, cv::Size(m_nImageWidth, m_nImageHeight),
                            cameraMatrix, distCoeffs, m_vMatrixR, m_vMatrixT);

        SaveFile(cameraMatrix, distCoeffs);

        m_bCalibrated = true;
        cout << "Camera calibration done." << endl;
    }

    return m_bCalibrated;
}

void CAstraCalibration::InitMatrix(vector<cv::Point3f> *pvObjectPoints)
{
    eint nCounter = 0;
    cv::Point3d PointTemp;
    for (eint i = 0; i != CHESS_BOARD_HEIGHT; i++) {
        for (eint j = 0; j != CHESS_BOARD_WIDTH; j++) {
            PointTemp.x = edouble( i * SQUARE_SIDE );
            PointTemp.y = edouble( j * SQUARE_SIDE );
            PointTemp.z = edouble(0);
            pvObjectPoints->push_back(PointTemp);
        }
    }
}

void CAstraCalibration::SaveFile(cv::Mat CamMatrix, cv::Mat DistCoeffs)
{
    estring strFile = "/home/moro/Desktop/AstraCam_Intrinsic_Param.txt";
    
    FILE *CamFile = fopen(strFile.c_str(), "w+");
    fprintf(CamFile,"%.12f\n", CamMatrix.at<edouble>(0, 0));    // fx
    fprintf(CamFile,"%.12f\n", CamMatrix.at<edouble>(0, 2));    // cx
    fprintf(CamFile,"%.12f\n", CamMatrix.at<edouble>(1, 1));    // fy
    fprintf(CamFile,"%.12f\n", CamMatrix.at<edouble>(1, 2));    // cy

    // k1, k2, p1, p2, k3
    for(eint i = 0; i < DistCoeffs.rows * DistCoeffs.cols; i++)
    {
        fprintf(CamFile,"%.12f\n", DistCoeffs.at<edouble>(i));
    }

    fclose(CamFile);
}

ebool CAstraCalibration::ReadParamFile(estring strFile, cv::Mat &CamMatrix, cv::Mat &DistCoeffs) 
{
    CamMatrix  = cv::Mat::zeros(3,3,CV_64FC1);
    CamMatrix.at<edouble>(2,2) = 1.0;
    DistCoeffs = cv::Mat::zeros(5,1,CV_64FC1);

    ifstream fin;
    fin.open(strFile.c_str());

    if (!fin) {
        cout << "!!!!!! Can't open calibration matrix file: " << strFile << endl; 
        return false;
    }

    cout << "read calibration file: " << strFile << endl;
    eint nCount = 0;
    estring strTmp;
    while (fin.good()) {
        getline(fin, strTmp);
        nCount++;
        switch (nCount) {
            case 1: { CamMatrix.at<edouble>(0,0)  = atof(strTmp.c_str()); break; }
            case 2: { CamMatrix.at<edouble>(0,2)  = atof(strTmp.c_str()); break; }
            case 3: { CamMatrix.at<edouble>(1,1)  = atof(strTmp.c_str()); break; }
            case 4: { CamMatrix.at<edouble>(1,2)  = atof(strTmp.c_str()); break; }

            case 5: { DistCoeffs.at<edouble>(0,0) = atof(strTmp.c_str()); break; }
            case 6: { DistCoeffs.at<edouble>(1,0) = atof(strTmp.c_str()); break; }
            case 7: { DistCoeffs.at<edouble>(2,0) = atof(strTmp.c_str()); break; }
            case 8: { DistCoeffs.at<edouble>(3,0) = atof(strTmp.c_str()); break; }
            case 9: { DistCoeffs.at<edouble>(4,0) = atof(strTmp.c_str()); break; }
        }
    }

    fin.close();
    return true;
}


edouble CAstraCalibration::Evaluate(cv::Mat CamMatrix, cv::Mat DistCoeffs) 
{
    edouble dTotalErr = 0.0;
    edouble dErr = 0.0;

    cout << "Evaluate......" << endl;
    cout << "m_nCalibratedImageNum  : " << m_nCalibratedImageNum << endl;
    cout << "m_vImagePointsList size: " << m_vImagePointsList.size() << endl;
    EASSERT(m_nCalibratedImageNum == m_vImagePointsList.size());

    cout << "m_vMatrixR size: " << m_vMatrixR.size() << endl;
    cout << "m_vMatrixT size: " << m_vMatrixT.size() << endl;
    EASSERT(m_vMatrixR.size());

    for (eint i = 0; i != m_vImagePointsList.size(); i++)
    {
        // object points and image points of each image
        // size should be CHESS_BOARD_WIDTH*CHESS_BOARD_HEIGHT = 54
        vector<cv::Point3f> tempObjectPoints = m_vObjectPointsList[i];
        vector<cv::Point2f> tempImagePoints  = m_vImagePointsList[i];
        vector<cv::Point2f> calibedImagePoints;

        cv::projectPoints(tempObjectPoints, m_vMatrixR[i], m_vMatrixT[i], CamMatrix, DistCoeffs, calibedImagePoints);

        cv::Mat tempImagePointsMat    = cv::Mat(1, tempImagePoints.size(), CV_64FC2);
        cv::Mat calibedImagePointsMat = cv::Mat(1, calibedImagePoints.size(), CV_64FC2);

        eint nLength = tempImagePointsMat.size().width * tempImagePointsMat.size().height;
        
        cout << "++++++++++ " << i << " ++++++++++" << endl;
        for (eint j = 0 ; j != nLength; j++) {
            tempImagePointsMat.at<cv::Vec2f>(0,j)     = cv::Vec2f(tempImagePoints[j].x, tempImagePoints[j].y);
            calibedImagePointsMat.at<cv::Vec2f>(0,j)  = cv::Vec2f(calibedImagePoints[j].x, calibedImagePoints[j].y);
            
            cout << "j: " << j << "\t";
            printf("%.8f, %.8f \t", tempImagePointsMat.at<cv::Vec2f>(0,j)(0), tempImagePointsMat.at<cv::Vec2f>(0,j)(1));
            printf("%.8f, %.8f \n", calibedImagePointsMat.at<cv::Vec2f>(0,j)(0), calibedImagePointsMat.at<cv::Vec2f>(0,j)(1));
        }
        cout << "--------------------" << endl;

        dErr = cv::norm(tempImagePointsMat, calibedImagePointsMat, cv::NORM_L2);

        // dTotalErr += dErr /= m_vPointsCounts[i];
        dTotalErr += dErr;
        cout << i << " error: " << dErr << " pixel, " \
              "average error: " << dErr/m_vPointsCounts[i] << " pixel" << endl;
    }

    cout << "total error: " << dTotalErr/m_nCalibratedImageNum << " pixel" << endl;
    cout << "====== Calibartion evaluation done ======" << endl;
    return dTotalErr;
}

