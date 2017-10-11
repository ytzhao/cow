# ObtDetElem: bridge between EwayOS and ObtDet algorithm   

1. feature code : 55   
2. parameter xml:
>- /EwayOS/Configuration/xml/ObtDetElem.xml   
3. set parameters:
>- resolution
>- valide range (300mm ~ 3000mm)
>- camera intrinsic matrix (9 doubles)
4. create new thread   
5. write into share memory data format: **n | yaw | pitch | x1 | y1 | x2 | y2 | ...**   

## **0. flowchart**
(1). PinData: get camera image data   
(2). decouple RGBD image -> RGB image & depth image   
(3). get and dispatch head position and rotation matrix
>- 12 elements in total;
>- first 9 elements are rotation matrix (**TODO: check share memory head position and rotation matrix alignment**);
>- last 3 elements are translation values.   

(4). **(!!!connect to ObtDet algorithm)** m_piDetector->Detect(de)pthmap, map, RTmatrix)  
(5). convert result to meet Zeng Xia's need  
>- *n | yaw | pitch | x1 | y1 | x2 | y2 | ...*   

(6). write into share memory


## **1. variables** 
CObtDet *m_piDetetor  

## **2. functions** 
>- (1). Detect()
>- (2). ConvertResult(cv::Mat map, vector<double> result, double yaw, double pitch)

---

# ObtDet algorithm
1. set parameter list(get values from xml file): 
>- resolution 
>- intrinsic matrix
>- valid range

## **0. flowchart**
### **Detect(depth map, map, RTmatix):**
(0). FilterDepth(depth map)   
(1). **ReFilter(depth map, filtered)**  
(2). **DMTrans()**   
(3). PostPro(x map, y map, z map, map): separate map to x/y/z submap   

#### FilterDepth(depth map)
(0). depth map convert to **CV_16U**   
(1). cv::compare to lower & upper bound  
(2). cv mul   

#### ReFilter(depth map, filtered get map): **CUDA related**   
(1). **LayeredFiltering**  
(2). cv::getStructuringElement  
(3). erode  
(4). dilate  

#### DMTrans: **CUDA related** 
according with camera intrinsic & RTmatrix convert depth map to robot x/y/z  

