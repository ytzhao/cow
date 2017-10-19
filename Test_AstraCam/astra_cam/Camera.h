#ifndef CAMERA_H
#define CAMERA_H

#include "../../SensorPublic/BaseElement.h"
#include "../../SensorPublic/VisionGlobal.h"
#include "../../../OSPublic/ProfileAccess/ProfileAccess.hpp"
  //#include "../../VisionAlgo/RealSenseReader/RealSenseReader.h"
#include "../../VisionAlgo/AstraReader/AstraReader.h"
#include "../../VisionAlgo/AstraReader/CCalibration/CCalibration.h"

#include "../../VisionAlgo/CamIntrinsic/CCamIntrinsic.h"

#include "opencv/cv.hpp"
//#include "librealsense/rs.hpp"
#include <iostream>
//#include "OpenNI.h"
#include <stdio.h>



Declare_Element_Inferface

class CCameraRS : public CBaseElement
{
    public:
        CCameraRS();
        ~CCameraRS();

       // void test() {ProcInit();};

    protected:
        virtual void ProcInit();
        virtual void ProcUninit();
        virtual void ProcFeatureEnabled(ebool bEnableFlag);
        virtual void ProcPinDisabled(euint unPinID,euint unPinType);
        virtual void ProcPinEnabled(euint unPinID,euint unPinType);
        virtual void ProcInputData(std::vector<CPinDataWithID>& iDataList);
        virtual void ProcFeedbackData(CFeedbackData& iFeedbackData);
        ebool m_bThreadRunning;

    private:
        static void* ThreadProc(void* pArgv);
        void CamCapture();

        CEBaseThread *m_piThreadPointer;
        eint m_bGUISwitch;
         // CRealSenseReader m_iCam;
        CAstraReader m_iCam;
        ebool m_bImLoader;
        estring m_strLoaderPath;
        eint m_nLoaderNum;
        edouble m_pdIntrinsic[9];

     //  openni::Device m_iDevice;
};

#endif // CAMERA_H
