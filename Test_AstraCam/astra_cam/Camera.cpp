#include "Camera.h"

Declare_Element_ID(VISION_SENSOR_GUID_CAMERA)
Declare_Feature_None

Declare_Input_Pin_Start
Declare_Pin_End

Declare_Output_Pin_Start
Declare_Output_Pin(1, PIN_CAMERA_OUT_1)
Declare_Output_Pin(2, PIN_CAMERA_OUT_2)
Declare_Pin_End

Declare_Feedback_Start
Declare_FeedBack_End

Declare_Element_Implement(CCameraRS)

CCameraRS::CCameraRS()
{
    m_piThreadPointer = CEBaseFactory::GetThreadInstance();
    m_bGUISwitch = false;
    m_bImLoader = false;
}

CCameraRS::~CCameraRS()
{
    //dtor

}

void CCameraRS::ProcInit()
{
    m_iCam.InitCam(0, m_pdIntrinsic);
    m_bThreadRunning = true;
    m_piThreadPointer->CreateThread(CCameraRS::ThreadProc, (eint)this);
    CCamIntrinsic::WriteIntrinsic(m_pdIntrinsic);

    //read the Intrinsic parameter by the pointer;

    FILE* fp;
    fp = fopen("/home/ewaybot/Desktop/trunk/RoboticSys/EwayOS/Bin/Debug/NewSensor/SupportLib/param.txt","r");
    edouble *p;
    // fread(p,sizeof(),1,fp);
    fread(p,1,20,fp);
    //m_pdIntrinsic=p;
    m_iCam.InitCam(0,p);
    CCamIntrinsic::WriteIntrinsic(p);
//    rs::  intrinsics sIntrinsics = m_piCam->get_stream_intrinsics(rs::stream::color);
//    pdIntrinsic[0] = sIntrinsics.fx;
//    pdIntrinsic[1] = sIntrinsics.ppx;
//    pdIntrinsic[2] = sIntrinsics.fy;
//    pdIntrinsic[3] = sIntrinsics.ppy;
//    for(eint i = 0; i < 5; i++)
//    {
//        pdIntrinsic[4+i] = sIntrinsics.coeffs[i];
//    }


    void* pXmlPointer = CProfileAccess::OpenLocalXmlDoc("./Elem/Camera/Camera.xml", false);
    CProfileAccess::ReadParameter(pXmlPointer, "GUI", m_bGUISwitch);
    CProfileAccess::ReadParameter(pXmlPointer, "ImageLoader", m_bImLoader);
    CProfileAccess::ReadParameter(pXmlPointer, "LoaderPath", m_strLoaderPath);
    CProfileAccess::ReadParameter(pXmlPointer, "LoaderNum", m_nLoaderNum);
    CProfileAccess::CloseXmlDoc(pXmlPointer);

}

void CCameraRS::ProcUninit()
{
    m_bThreadRunning = false;
    m_piThreadPointer->WaitForThreadQuit();

}

void CCameraRS::ProcFeatureEnabled(ebool bEnableFlag)
{
}

void CCameraRS::ProcPinDisabled(euint unPinID,euint unPinType)
{
}

void CCameraRS::ProcPinEnabled(euint unPinID,euint unPinType)
{
}

void CCameraRS::ProcInputData(std::vector<CPinDataWithID>& iDataList)
{
}

void CCameraRS::ProcFeedbackData(CFeedbackData& iFeedbackData)
{
}

void* CCameraRS::ThreadProc(void* pArgv)
{
   ((CCameraRS*)pArgv)->CamCapture();
    return NULL;
}

void CCameraRS::CamCapture()
{    
    eint nLoaderCounter = 1;
    while(m_bThreadRunning)
    {
        cv::Mat iColor, iDepth;
        if(!m_bImLoader)
            m_iCam.ReadFrame(iColor,iDepth);
        else
        {

            stringstream iTemp;
            iTemp << nLoaderCounter;
            estring strFile = m_strLoaderPath + iTemp.str() + ".jpg";
            estring strFile2 = m_strLoaderPath + iTemp.str() + ".tiff";
            iColor = cv::imread(strFile.c_str());
            iDepth = cv::imread(strFile2.c_str());
            iDepth.convertTo(iDepth, CV_32F);

            if(nLoaderCounter < m_nLoaderNum - 1)
            {
                nLoaderCounter++;
            }
            else
            {
                m_nLoaderNum = 1;
            }
        }
        if(m_bGUISwitch)
        {
            cv::imshow("color", iColor);
            cv::imshow("depth", iDepth);
            cv::waitKey(10);
        }

        ESleep(30);
        edouble dCamTime = EGetCurTime();
        CPinData iPinData;
        iPinData.m_dOrigTimeStamp = dCamTime;
        iPinData.m_dProcTimeStamp = dCamTime;
        iPinData.m_strDataFormat = SENSOR_FORMAT_DESCRIPTION_OPENCV_MAT;
        iPinData.m_strDataDescription = SENSOR_DATA_DESCRIPTION_CAM_RGB_MAT;
        iPinData.FillInInstance(&iColor, &cv::Mat::copyTo, CopyFlag_SelfToIn);
        OutputData(1, iPinData);
        CPinData iPinData2;
        iPinData2.m_dOrigTimeStamp = dCamTime;
        iPinData2.m_dProcTimeStamp = dCamTime;
        iPinData2.m_strDataFormat = SENSOR_FORMAT_DESCRIPTION_OPENCV_MAT;
        iPinData2.m_strDataDescription = SENSOR_DATA_DESCRIPTION_CAM_RGB_MAT;
        iPinData2.FillInInstance(&iDepth, &cv::Mat::copyTo, CopyFlag_SelfToIn);
        OutputData(2, iPinData2);



//       iPinData.SetData(&iDepthImage,0,&CPinDataDeliver<cv::Mat,void>::Destory,CPinDataDeliver<cv::Mat,void>::GetDupFn(&cv::Mat::copyTo,1));



        //FillInInstance(cv::Mat, iColorImage8bit, cv::Mat::copyTo,, 1);

//        OutputInstance(1, Mat, iColorImage8bit, 0, dCamTime, dCamTime,
//                       SENSOR_DATA_DESCRIPTION_CAM_RGB_MAT, SENSOR_FORMAT_DESCRIPTION_OPENCV_MAT, iPinData);
//        OutputInstance(2, Mat, iDepthImage, 0, dCamTime, dCamTime,
//                       SENSOR_DATA_DESCRIPTION_CAM_DEPTHMAP_MAT, SENSOR_FORMAT_DESCRIPTION_OPENCV_MAT, iPinData);
    }

}
