# 系统要求
Intel官方要求realsense v2.0需要在Ubuntu16.04的系统环境中运行，目前我们在Ubuntu14.04 4.4.0-101-generic中安装成功，正常运行。
| Required Info |  |
| --- | --- |
| Camera Model | D415 & D435 |
| Operation System & Version | Ubuntu 14.04 + |
| Kernel Version | 4.4.0-101-generic |
| SDK Version | rs2 |

# D415 & D435 参数对比
| RealSense | D415 | D435 |
| --------- | --------- | --------- |
| Serial NO. | 739112060064 | 728612070754 |
| Firmware Version | 05.08.15.00 | 05.08.14.00 |
| --------- | Color intrinsices | --------- |
| fx | 613.298 | 618.638 |
| ppx | 321.863 | 319.006 |
| fy | 611.59 | 618.691 |
| ppy | 234.936 | 251.402 |
| **TODO: coeff(?)** | 0 0 0 0 0 | 0 0 0 0 0 |
| --------- | Field of View | --------- |
| Color | **x: 55.1078, y: 42.8501** | **x: 54.7019, y: 42.3917** |
| Depth | **x: 53.7063, y: 41.5863** | **x: 79.3763, y: 63.7966** |
| --------- | Depth detection in practice(not quit precise) | --------- |
| z-axis | **0.25m** | **0.15m** |

# 目前存在的一些问题：
- 1. 当彩色和深度图像分辨率为640x480，帧数30帧每秒运行时，CPU四个核的内存占有率普遍在80%以上；
- 2. 两款RealSense在使用时都存在视频流配置错误问题，可能是由于USB供电不稳引起，重新热插拔几次即可；
- 3. 目前到手的两款RealSense，其中有一条数据线无法正常使用，已贴上红色胶布，请使用时注意；
- 4. 之前摄像头接入EwayOS时，彩色和深度图像均有接近1s的延时，是因为在CameraManager Element中有两次ESleep(30)。

# 安装教程
## 0. Useful links
[librealsense github](https://github.com/IntelRealSense/librealsense/blob/development/doc/installation.md)  
[Intel official sample code](https://github.com/IntelRealSense/librealsense/wiki/API-How-To#get-first-realsense-device)  
[Intel developer zone](https://software.intel.com/en-us/articles/using-librealsense-and-opencv-to-stream-rgb-and-depth-data)  

## 1. Enable 'Secure Boot' 

BIOS -> Security -> Secure Boot -> Enable

## 2. Make Ubuntu Up-to-date

```shell
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade
sudo update-grub
```

**Grub2 Boot Menu -> 'Advanced Options for Ubuntu'** and select the kernel version installed in the previous step.

```shell
sudo reboot
```

Complete the boot, login and verify that the required kernel version (4.4.0-79 or 4.8.0-54 as of June 17th 2017) is in place with
```shell
uname -r
```

**kernel version**: 4.4.0-101-generic

## 3. Install the packages required for *librealsense* build:

- *libusb-1.0*, *pkg-config* and *libgtk-3*

  ```shell
  sudo apt-get install libusb-1.0-0-dev pkg-config libgtk-3-dev
  ```

- On Ubuntu 14.04 or when running of Ubuntu 16.04 live-disk, please use `./scripts/install_glfw3.sh`

- On Ubuntu 14.04, update your build toolchain to *gcc-5*

```shell
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-5 g++-5
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 --slave /usr/bin/g++ g++ /usr/bin/g++-5
sudo update-alternatives --set gcc "/usr/bin/gcc-5"
```

Check gcc version with 
```shell 
gcc -v
```
I used **gcc version**: 5.4.1 20160904 which does **NOT** match what it requires

- Update CMake version: 

Ubuntu14.04 default CMake version is 2.8.X, but realsense requires for 3.1.0 or higher

```shell
sudo apt-get install build-essential
wget http://www.cmake.org/files/v3.4/cmake-3.4.1.tar.gz
tar xf cmake-3.4.1.tar.gz
cd cmake-3.4.1
./configure
make
sudo make install
sudo ln -s /usr/local/bin/cmake /usr/bin/cmake
```

## 4. Compile librealsense
- Navigate to *librealsense* root directory and run: 

  ```shell
  mkdir build && cd build
  ```

- Run CMake:

  - `cmake ../` - The default build is set to produce the core shared object and unit-tests binaries
  - `cmake ../ -DBUILD_EXAMPLES=true` - Builds *librealsense* along with the demos and tutorials
  - `cmake ../ -DBUILD_EXAMPLES=true -DBUILD_GRAPHICAL_EXAMPLES=false` - For systems without OpenGL or X11 build only textual examples

- ```shell
  make
  sudo make install
  ```

## 5. Test
Reconnect the Intel RealSense D435 camera and run: 

```shell
cd /usr/local/bin/
./realsense-viewer
```

## Issue:
1. terminate called after throwing an instance of 'rs2::backend_error'
  what():  libusb_open(...) returned LIBUSB_ERROR_ACCESS Last Error: Permission denied
- Try re-installing udev rules located in librealsense source directory:   
```shell
sudo cp config/99-realsense-libusb.rules /etc/udev/rules.d/   
sudo udevadm control --reload-rules && udevadm trigger  
```

If the issue persists, the cause might be due to the fact that your user is not part of the plugdev group.
```shell
sudo adduser "moro" plugdev 
```
