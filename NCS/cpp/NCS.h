#ifndef NCS_H
#define NCS_H

#include <stdio.h>
#include <stdlib.h>
using namespace std;

extern "C" {
    #include "./util/fp16.h"
}

#include <mvnc.h>

#include "opencv2/opencv.hpp"

#define GRAPH_FILE "../VGG/deploy.graph"
#define NAME_SIZE   100


class NCS
{
public:
    NCS();
    ~NCS();

    bool    InitDevice();
    int     Predict(const char* path, float &prob);
    int     Predict(cv::Mat matColor, float &prob);

private:
    const int networkDim = 224;
    float networkMean[3] = {0.40787054*255.0, 0.45752458*255.0, 0.48109378*255.0};

    int             Process(unsigned short* imageBufFp16, unsigned int lenBufFp16, float &prob);
    void*           LoadFile(const char* path, unsigned int* length);
    unsigned short* LoadImage(const char* path, int reqsize, float* mean);

    mvncStatus  m_ncsStatus;
    bool    m_bncsInit = false;

    void*   m_deviceHandler;

    void*   m_graphFileBuf;
    void*   m_graphHandler;
};

#endif // NCS_H
