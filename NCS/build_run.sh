#!/bin/bash
mvNCCompile deploy.prototxt -w model.caffemodel -s 12 -in conv1 -on prob -is 224 224 -o ./VGG/deploy.graph
