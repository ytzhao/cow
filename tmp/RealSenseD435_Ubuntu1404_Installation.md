[librealsense github](https://github.com/IntelRealSense/librealsense/blob/development/doc/installation.md)  
[Intel official sample code](https://github.com/IntelRealSense/librealsense/wiki/API-How-To#get-first-realsense-device)

### 1. Enable 'Secure Boot' 

BIOS -> Security -> Secure Boot -> Enable

### 2. Make Ubuntu Up-to-date

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

Complete the boot, login and verify that the required kernel version (4.4.0-79 or 4.8.0-54 as of June 17th 2017) is in place with `uname -r`

**kernel version**: 4.4.0-101-generic

### 3. Install the packages required for *librealsense* build:

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

Check gcc version with `gcc -v`:  **gcc version**: 5.4.1 20160904 **NOT** match what it requires

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

### 4. Compile librealsense

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

### 5. Test

Reconnect the Intel RealSense D435 camera and run: 

```shell
cd /usr/local/bin/
./realsense-viewer
```

### 6. :tada: :tada: :tada:

