import numpy as np
import os
import sys
import argparse
import glob
import time

import caffe

def main(argv):
    if 2!=len(sys.argv):
        print("Error - input argument wrong!")
        quit()

    image_path = sys.argv[1]

    print('This is the name of the script: ', sys.argv[0])
    print('The image path: ', sys.argv[1])  

    caffe.set_mode_cpu()

    model_def    = '/home/moro/Desktop/test_mvnc/test_ncs/VGG/deploy.prototxt'
    model_weight = '/home/moro/Desktop/test_mvnc/test_ncs/VGG/model.caffemodel'

    net = caffe.Net(model_def, model_weight, caffe.TEST)

    mu = np.load('/home/moro/Desktop/test_mvnc/test_ncs/VGG/ilsvrc_2012_mean.npy')
    mu = mu.mean(1).mean(1)
    print('mean-subtracted values:{}'.format(zip('BGR', mu)))

    transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})
    transformer.set_transpose('data', (2,0,1))

    transformer.set_mean('data', mu)
    transformer.set_raw_scale('data', 255)

    transformer.set_channel_swap('data', (2,1,0))

    # image = caffe.io.load_image('/home/moro/Desktop/test_mvnc/test_imgs/coke.jpg')
    image = caffe.io.load_image(image_path)

    net.blobs['data'].data[...] = transformer.preprocess('data', image)

    output = net.forward()

    output_prob = output['prob'][0]

    print('predicted class is:{}'.format(output_prob.argmax()))
    
    
if __name__ == '__main__':
    main(sys.argv)