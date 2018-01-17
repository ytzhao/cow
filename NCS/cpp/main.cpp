#include <iostream>

#include "NCS.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

int main(int argc, char *argv[])
{
    NCS ncs;
    ncs.InitDevice();

if (0)
{
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        std::cout << "Video camera can not open." << std::endl;
        return -1;
    }

    cv::Mat matColor(480, 640, CV_8UC3);
    while (1) {
        capture >> matColor;

        float prob;
        std::cout << "--------------------------------------------------" << std::endl;
        int index = ncs.Predict(matColor, prob);
        std::cout << "Inference index: " << index << ", prob: " << prob << std::endl;

        cv::imshow("color", matColor);
        cv::waitKey(10);
    }
}
else
{
    char* dict[] = {
        "../images/bread.jpg",
        "../images/cok.jpg",
        "../images/coke.jpg",
        "../images/dog.jpg",
        "../images/monkey.jpg"
    };

    float prob;
    for (int i = 0; i < 5; i++) {
        std::cout << "--------------------------------------------------" << std::endl;
        int index = ncs.Predict(dict[i], prob);
        std::cout << "Inference index: " << index << ", prob: " << prob << std::endl;
    }
}

    std::cout << "............ goodbye olala" << std::endl;
    return 0;
}
