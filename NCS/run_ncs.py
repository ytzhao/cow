from mvnc import mvncapi as ncs 
import numpy as np
import cv2
import sys


if 2!=len(sys.argv):
    print("Error - input argument wrong!")
    quit()

# image_path = '/home/moro/Desktop/test_mvnc/test_imgs/coke.jpg'
image_path = sys.argv[1]

print('This is the name of the script: ', sys.argv[0])
print('The image path: ', sys.argv[1])

# Parameters
dim = (224,224)

# Get labels
# labels_file = '/home/moro/Desktop/test_mvnc/VGG/translation.txt'
# labels = np.loadtxt(open(labels_file, encoding='utf8'), str, delimiter='\n')

# Configure the NCS
# 1 - errors only; 2 - verbose
ncs.SetGlobalOption(ncs.GlobalOption.LOG_LEVEL, 2)

# Get a device
deviceNames = ncs.EnumerateDevices()
if 0==len(deviceNames):
    print("Error - No NCS devices detected.")
    quit()

# Open first NCS device found
device = ncs.Device(deviceNames[0])
device.OpenDevice()

# Load blob 
network_blob = './VGG/deploy.graph'
with open(network_blob, mode='rb') as f:
    blob = f.read()

# Allocate graph / otherwise use device as needed
graph = device.AllocateGraph(blob)

# Load the image
network_mean = np.load('/home/moro/Desktop/test_mvnc/test_ncs/VGG/ilsvrc_2012_mean.npy').mean(1).mean(1) # loading the mean file
print('mean-subtracted values:{}'.format(zip('BGR', network_mean)))

# img = cv2.imread('/home/moro/Desktop/test_mvnc/test_imgs/coke.jpg')
img = cv2.imread(image_path)
width, height = img.shape[:2]
# print('image width: {}, height: {}'.format(width, height))
img = cv2.resize(img, dim)
img = img.astype(np.float32)
img[:,:,0] = (img[:,:,0] - network_mean[0])
img[:,:,1] = (img[:,:,1] - network_mean[1])
img[:,:,2] = (img[:,:,2] - network_mean[2])

# Send the image to the NCS
graph.LoadTensor(img.astype(np.float16), 'user object')

# Get the result from the NCS
output, userobj = graph.GetResult()

# Deallocate graph if allocated 
graph.DeallocateGraph()

# Close device
device.CloseDevice()

# Print the results of the inference from the NCS
# order = output.argsort()[::-1][:6]
order = output.argsort()[::-1][:1]
print('\n------------ predictions ------------')
print(order)
# for i in range(0,5):
#     print('prediction ' + str(i) + ' (probability ' + str(output[order[i]] + ') is ' + labels[order[i]] + ' label index is: ' + str(order[i]) )
