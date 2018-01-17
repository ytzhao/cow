#include "NCS.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "./util/stb_image.h"
#include "./util/stb_image_resize.h"

NCS::NCS()
{
    // cor
    cout << "NCS::NCS()" << endl;
}


NCS::~NCS()
{
    if (m_bncsInit) {
        // Deallocate graph if allocated
        m_ncsStatus = mvncDeallocateGraph(m_graphHandler);
        m_graphHandler = NULL;


        // Close device
        free(m_graphFileBuf);
        mvncCloseDevice(m_deviceHandler);
        m_deviceHandler = NULL;
    }
}


bool NCS::InitDevice()
{
    // Configure the NCS
    // 0 - nothing; 1 - error only; 2 - verbose
    int logLevel = 0;
    m_ncsStatus = mvncSetGlobalOption(MVNC_LOG_LEVEL, &logLevel, sizeof(int));

    // Get a device
    char devName[NAME_SIZE];
    m_ncsStatus = mvncGetDeviceName(0, devName, NAME_SIZE);
    if (MVNC_OK != m_ncsStatus) {
        cout << "Error - No NCS devices detected." << endl;
        return false;
    }

    // Open NCS device
    m_ncsStatus = mvncOpenDevice(devName, &m_deviceHandler);
    if (MVNC_OK != m_ncsStatus) {
        cout << "Error - Could not open NCS device." << endl;
        return false;
    }

    // deviceHandler is ready to use now
    // Pass it to other NC API calls as needed and close it when finished
    cout << "Successfully opened NCS device!" << endl;

    // Load blob
    unsigned int graphFileLen;
    m_graphFileBuf = LoadFile(GRAPH_FILE, &graphFileLen);

    // Allocate graph / otherwise use device as needed
    m_ncsStatus = mvncAllocateGraph(m_deviceHandler, &m_graphHandler
    , m_graphFileBuf, graphFileLen);
    if (MVNC_OK != m_ncsStatus) {
        cout << "Error - Could not allocate graph for file: " << GRAPH_FILE << endl;
        cout << "Error from mvncAllocateGraph is: " << m_ncsStatus << endl;
        return false;
    }
    else
    {
        // Succesfully allocate graph
        cout << "Successfully allocated graph for: " << GRAPH_FILE << endl;
        m_bncsInit = true;
    }

    return true;
}

int NCS::Predict(const char* path, float &prob)
{
    if (!m_bncsInit) {
        cout << "Error - NCS is not initialized." << endl;
        return -1;
    }

    // Load the image
    // Send the image to the NCS
    cout << "Predict image path: " << path << endl;
    unsigned short* imageBufFp16 = LoadImage(path, networkDim, networkMean);
    unsigned int    lenBufFp16   = 3*networkDim*networkDim*sizeof(*imageBufFp16);

    return this->Process(imageBufFp16, lenBufFp16, prob);
}

int NCS::Predict(cv::Mat matColor, float &prob)
{
    /// TODO!
    return -1;
}

int NCS::Process(unsigned short* imageBufFp16, unsigned int lenBufFp16, float &prob)
{
    m_ncsStatus = mvncLoadTensor(m_graphHandler, imageBufFp16, lenBufFp16, NULL);
    if (MVNC_OK != m_ncsStatus)
    {
        cout << "Error - Could not load tensor." << endl;
        cout << "Error from mvncLoadTensor is: " << m_ncsStatus << endl;
        return -1;
    }
    else
    {
        // The inference has been started, now call mvncGetResult() for the inference result
        void* resultData16;
        void* userParam;
        unsigned int lenResultData;

        // Get the result from the NCS
        m_ncsStatus = mvncGetResult(m_graphHandler, &resultData16, &lenResultData, &userParam);
        if (MVNC_OK == m_ncsStatus) {
            // Successfully got the result. The inference result is in the buffer pointed to by resultData
            cout << "resultData is: " << lenResultData << " bytes which is: " << lenResultData/(int)sizeof(unsigned short) << " 16-bit floats." << endl;

            // Convert unsigned short precision floats to full floats
            int numResults = lenResultData / sizeof(unsigned short);
            float* resultData32;
            resultData32 = (float*)malloc(numResults*sizeof(*resultData32));
            fp16tofloat(resultData32, (unsigned char*)resultData16, numResults);

            float maxResult = 0.0;
            int   maxIndex  = -1;
            for (int index = 0; index < numResults; index++) {
                if (resultData32[index] > maxResult) {
                    maxResult = resultData32[index];
                    maxIndex  = index;
                }
            }
            cout << "Index of top result is: " << maxIndex << endl;
            cout << "Probability of top result is: " << resultData32[maxIndex] << endl;

            prob = resultData32[maxIndex];
            return maxIndex;
        }
    } // -end else

    return -1;
}

// Load a graph file. Caller must free the buffer returned.
void* NCS::LoadFile(const char* path, unsigned int* length)
{
    FILE *fp;
    char *buf;

    fp = fopen(path, "rb");
    if (NULL == fp) {
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    *length = ftell(fp);
    rewind(fp);

    if (!(buf = (char*)malloc(*length))) {
        fclose(fp);
        return 0;
    }
    if (fread(buf, 1, *length, fp) != *length) {
        fclose(fp);
        free(buf);
        return 0;
    }
    fclose(fp);
    return buf;
}

unsigned short* NCS::LoadImage(const char* path, int reqsize, float* mean)
{
    int             width, height, cp;
    unsigned char  *img, *imgresized;
    float          *imgfp32;
    unsigned short *imgfp16;

    img = stbi_load(path, &width, &height, &cp, 3);
    if (!img) {
        cout << "The image: " << path << " could not be loaded." << endl;
        return 0;
    }

    imgresized = (unsigned char*)malloc(3*reqsize*reqsize);
    if (!imgresized) {
        free(img);
        perror("LoadImage, malloc 1");
        return 0;
    }

    stbir_resize_uint8(img, width, height, 0, imgresized, reqsize, reqsize, 0, 3);
    free(img);

    imgfp32 = (float*)malloc(sizeof(*imgfp32)*reqsize*reqsize*3);
    if (!imgfp32) {
        free(imgresized);
        perror("LoadImage, malloc 2");
        return 0;
    }

    for (int i = 0; i < reqsize*reqsize*3; i++) {
        imgfp32[i] = imgresized[i];
    }
    free(imgresized);

    imgfp16 = (unsigned short*)malloc(sizeof(*imgfp16)*reqsize*reqsize*3);
    if (!imgfp16) {
        free(imgfp32);
        perror("LoadImage, malloc 3");
        return 0;
    }

    for (int i = 0; i < reqsize*reqsize; i++) {
        float blue, green, red;
        blue  = imgfp32[3*i+2];
        green = imgfp32[3*i+1];
        red   = imgfp32[3*i+0];

        imgfp32[3*i+0] = blue  - mean[0];
        imgfp32[3*i+1] = green - mean[1];
        imgfp32[3*i+2] = red   - mean[2];
    }

    floattofp16((unsigned char *)imgfp16, imgfp32, 3*reqsize*reqsize);
    free(imgfp32);
    return imgfp16;
}
