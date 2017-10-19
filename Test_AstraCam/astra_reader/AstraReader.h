#ifndef C_ASTRA_CAM_READER_H
#define C_ASTRA_CAM_READER_H

#include <iostream>
using namespace std;

#include "OpenNI.h"
#include "opencv2/opencv.hpp"

#include "../../../../../../EwayPublic/OS/publicdef.h"
#include "../../../SensorPublic/VisionGlobal.h"

#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms

class CAstraReader
{
    public:
        CAstraReader(){};
        ~CAstraReader();
        ebool Initialize(eint nCamNo, edouble *pdIntrinsic);
        ebool ReadFrame(cv::Mat& matColor, cv::Mat& matDepth);

        void  SetResolution(eint  nWidth, eint  nHeight);
        void  GetResolution(eint &nWidth, eint &nHeight);

        void  GetImage(estring strLocation, estring strFileTitle);

    private:
        openni::Device      m_iDevice;
        openni::VideoStream m_iDepth, m_iColor;

        ebool m_bIsOpened=false;

        eint m_nWidth=640;
        eint m_nHeight=480;

        clock_t m_prevTimestamp=0;
};

#endif
