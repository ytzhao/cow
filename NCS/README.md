- 1. 注意：默认已经安装好movidius ncs相关驱动！  
- 2. 先在ftp上/detection/Models/VisionModels/ObjectRec/下载VGG模型   
- 3. 运行
```shell
./build_run.sh
```
- 4. `images`： 待做预测的图片  
- 5. `run_pure_caffe.py`：caffe python版本  
- 6. `run_ncs.py`：运行在ncs上的python代码  
- 7. `cpp`：运行在ncs上的cpp代码   
