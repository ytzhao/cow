## 1. 安装Orbbec Astra相机相关驱动与软件
### 1). 检查 udev 版本
Orbbec相机驱动需要`libudev.so.1`, 如果您不能找到相关文件，制作软链接。
```shell
$ldconfig -p | grep libudev.so.1
$cd /lib/x86_64-linux-gnu # Or /lib/i386-linux-gnu
$sudo ln -s libudev.so.x.x.x libudev.so.1
```  

### 2). 环境配置
拷贝 Orbbec camera rules 到系统路径。  
```shell
$sudo cp ./orbbec-usb.rules /etc/udev/rules.d/558-orbbec-usb.rules 
```  

### 3). Replug in the device for usb-register  

### 4). 添加系统变量
首先需要再次**检查**`OpenNIDevEnvironment`里的路径是否指向您使用的`OpenNI`文件夹。
```shell  
$source ./OpenNIDevEnvironment
```


## 2. 相机标定
针对每一台新相机设备，需要进行相机的内参矩阵标定。

### 1). 文件说明
```
AstraCam_Calib
|   AstraCam_Calib.pro
|   main.cpp
|   TrajFileIO.cpp
|   TrajFileIO.h
|___astra_calibration
|       AstraCalibration.cpp       
|       AstraCalibration.h
|___astra_cam
|       Camera.cpp  
|       Camera.h
|___astra_reader
|       AstraReader.cpp
|       AstraReader.h
|___chessboard
|       cb.txt
|       cb1.jpg
|       cb2.jpg
|       ...
```

### 2). 使用说明
- AstraCam_Calib是一个可执行的app，目前测试工程所需要的校准图片暂时放在 `AstraCam_Calib/chessboard/`文件夹下，如有其他需要，可自行修改;
- 对于每一个新设备，需要使用新设备**重新采集图像**进行校准;
- TODO：需要修改新生成的内参矩阵文件路径；
- `AstraIntrin.txt`文件中9个数值分别表示为：`fx, cx, fy, cy, k1, k2, p1, p2, k3`;
- 编译该工程时，注意**不要勾选** `Shadow build` 选项。
