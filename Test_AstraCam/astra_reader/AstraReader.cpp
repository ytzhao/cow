#include "AstraReader.h"

CAstraReader::~CAstraReader()
{
    if ( m_bIsOpened )
    {
        cv::destroyAllWindows();

        m_iColor.stop();
        m_iDepth.stop();

        m_iColor.destroy();
        m_iDepth.destroy();

        m_iDevice.close();
        openni::OpenNI::shutdown();
    }
}

ebool CAstraReader::Initialize(eint nCamNo, edouble *pdIntrinsic)
{
    // 1. initialize openni developing environment
    openni::Status opni = openni::OpenNI::initialize();

    if ( openni::STATUS_OK != opni ) {
        cout << "!!!!!! Astra camera initialize failed: " << openni::OpenNI::getExtendedError() << endl;
        EASSERT(0);
        return false;
    }

    // 2. get camera device 
    // TODO: several sensor devices
    if ( openni::STATUS_OK != m_iDevice.open( openni::ANY_DEVICE ) )
    {
        cout << "!!!!!! Astra camera couldn't open device:" << openni::OpenNI::getExtendedError() << endl;
        EASSERT(0);
        return false;
    }

    // 3. get video stream
    if ( NULL != m_iDevice.getSensorInfo(openni::SENSOR_DEPTH) )
    {
        if ( openni::STATUS_OK == m_iDepth.create(m_iDevice, openni::SENSOR_DEPTH) ) {
            openni::VideoMode modeDepth;
            modeDepth.setResolution( m_nWidth, m_nHeight );
            modeDepth.setFps( 30 );
            modeDepth.setPixelFormat( openni::PIXEL_FORMAT_DEPTH_1_MM );
            m_iDepth.setVideoMode(modeDepth);

            if ( openni::STATUS_OK == m_iDepth.start() ) {
                cout << "====== Start depth stream ======" << endl;
            } else {
                cout << "!!!!!! Couldn't start depth stream: " << openni::OpenNI::getExtendedError() << endl;
                EASSERT(0);
                return false;
            }
        } else {
            cout << "!!!!!! Couldn't create depth stream: " << openni::OpenNI::getExtendedError() << endl;
            EASSERT(0);
            return false;
        }
    }

    if ( NULL != m_iDevice.getSensorInfo(openni::SENSOR_COLOR) )
    {
        if ( openni::STATUS_OK == m_iColor.create(m_iDevice, openni::SENSOR_COLOR) ) {
            openni::VideoMode modeColor;
            modeColor.setResolution( m_nWidth, m_nHeight );
            modeColor.setFps( 30 );
            modeColor.setPixelFormat( openni::PIXEL_FORMAT_RGB888 );
            m_iColor.setVideoMode( modeColor );
            if (  openni::STATUS_OK == m_iColor.start() ) {
                cout << "====== Start color stream ======" << endl;
            } else {
                cout << "!!!!!! Couldn't start color stream: " << openni::OpenNI::getExtendedError() << endl;
                EASSERT(0);
                return false;
            }
        } else {
            cout << "!!!!!! Couldn't create color stream: " << openni::OpenNI::getExtendedError() << endl;
            EASSERT(0);
            return false;
        }
    }

    // 4. set depth and color image synchronization
    if ( openni::STATUS_OK != m_iDevice.setDepthColorSyncEnabled(TRUE) ) {
        cout << "!!!!!! Couldn't set depth and color frame synchronization" << openni::OpenNI::getExtendedError() << endl;               
    }

    // 5. set depth and color image registration mode
    if( m_iDevice.isImageRegistrationModeSupported(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR) ) {
        m_iDevice.setImageRegistrationMode( openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR );
    }

    m_bIsOpened = true;
    cout << "====== Initialize Astra camera done ======" << endl;
    return true;
}

ebool CAstraReader::ReadFrame(cv::Mat& matColor, cv::Mat& matDepth)
{
    openni::VideoFrameRef iDepthFrame;
    openni::VideoFrameRef iColorFrame;

    ebool bIsColorFrameReaded = false;
    ebool bIsDepthFrameReaded = false;

    while( (false==bIsColorFrameReaded) || (false==bIsDepthFrameReaded) )
    {
        if( openni::STATUS_OK==m_iColor.readFrame(&iColorFrame) )
        {
            // convert data into OpenCV type
            cv::Mat matTmpColor( iColorFrame.getHeight(), iColorFrame.getWidth(), CV_8UC3, (void*)iColorFrame.getData() );
            cv::cvtColor( matTmpColor, matTmpColor, CV_BGR2RGB );
            matColor = matTmpColor.clone();
            bIsColorFrameReaded = true;
        }

        if( openni::STATUS_OK==m_iDepth.readFrame(&iDepthFrame) )
        {
            cv::Mat matTmpDepth( iDepthFrame.getHeight(), iDepthFrame.getWidth(), CV_16UC1, (void*)iDepthFrame.getData() );
            matDepth = matTmpDepth.clone();
            bIsDepthFrameReaded = true;
        }
    }
    return true;
}

void CAstraReader::SetResolution(eint nWidth, eint nHeight)
{
    this->m_nHeight = nHeight;
    this->m_nWidth  = nWidth;
}

void CAstraReader::GetResolution(eint &nWidth, eint &nHeight)
{
    nWidth  = this->m_nWidth;
    nHeight = this->m_nHeight;
    cout << "====== Astra camera resolution: ";
    cout << nWidth  << " width, ";
    cout << nHeight << " height ======" << endl;
}

void CAstraReader::GetImage(estring strLocation, estring strFileTitle)
{
    eint nCount = 0;
    if (m_bIsOpened){
        while (1) {
            cv::Mat matColor, matDepth;
            this->ReadFrame(matColor, matDepth);
            cv::imshow("color", matColor);
            int nKey = cv::waitKey(1);

            if ( ('q'==nKey) || ('Q'==nKey) ) {
                break;
            }

            if( ('s'==nKey) || ('S'==nKey) ) {
                nCount++;
                imwrite( (strLocation + strFileTitle + to_string(nCount) + ".jpg"), matColor);
                bitwise_not(matColor, matColor);
                cout << "Frame captured: " << nCount << endl;
            }
        }
    } else {
        cout << "!!!!!! Astra camera is not initialized" << endl;
    }
}

