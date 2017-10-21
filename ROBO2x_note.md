---
title: notes of ROBO2x on edx 
created: 2017-10-20 11:16:02
modified: /
categories: notes
tags: [notes, cv, ml]
description: this is just a study note of ROBO2x from PennX on edx
author: yuting zhao
---

# [ROBO2x: Vision Intelligence and Machine Learning](https://courses.edx.org/courses/course-v1:PennX+ROBO2x+2T2017/course/)
**Vision intelligence**: it allows a robot to "sense" and "recognize" the surrounding envrionment and also enables a robot to "learn" from the memory of past experiences by extracting patterns in visual signals.
**Machine learning**: This part will talks about how Machine Learning extracts statistically meaningful patterns in data that support classification, regression and clustering. 

Then by studying Computer Vision and Machine Learning together you will be able to build recognition algorithms that can learn from data and adapt to new environments. 



---

## Week 1: Camera Geometry and Color Sensing

**concept**: Focal Lens, the Field of View, Linear Algebra and it's application to represented picture in using it's homogenous coordinate

### 0. Introduction to 3D Shape perception

- 3D perception

  (1) **Depth**: the distance of the surface from the observer (problem: depth ambiguity)

  (2) **Surface orientation**: the slant and tilt of the surface with respect to observers' sight

- **Perspective projection** and **shading** also give us cues for 3D shape.

- **Stereo Vision** is just works like human eyes.

### 1. What is a camera?

- **A photon collecting machine**

  Pinhole camera  (the opening known as the **aperture**): to make the images less blurry

  Sensor Array: CMOS sensor / CCD sensor

  Bayer Grid : blocks all the lights **except** from red / green / blue light separetely

  In a computer, convert analog signal to digital signal

  **_Any 2D matrix can be seen as an image_**!!!

- **A dimension reduction machine**

  3D world to 2D image, from this process, what have we lost?

  ​	(1). Angles

  ​	(2). Distances  (lengths)

  3D to 2D mapping : just like **painting** process (J. Barozzi's Perspectograph)

### 2.  How to image 3D objects to 2D plane?

#### 	(1). How the 3D objects is measure in 3D space in terms its X, Y, Z?

#### 	(2). How a pierced image where it is and the exact location in 2D space?

#### 	(3). How to select focal length?

#### 	(4). How far we need to be with a focal length of 50 milimeters?

#### 	(5). Focal Length

**Shorter focal length, larger fiel of view!**

#### 	(6). Dolly Zoom
It keeps the size of an object of interests constant in the image, while making the foreground and background objects appear larger or smaller by adjusting focal length and moving the camera. Dolly zoom effect exploits the compensation between depth and focal length, which produces depth sensation. This effect used by Alfred Hitchcock in film "Vertigo".

### 3. Lab - Dolly Zoom



## Week 2 & 3: Fourier Transforms, Image Convolution, Edge Detection, Image Pyramids

**[ ... ] 1. Fourier Transform -> [ ... ] 2. Image Convolution and Edge Detection -> [ ... ] 3. Image Pyramids -> [ ... ] 4. Project \# 1 - Laplacian Pyramid for Image Encoding**



## Week 4: Feature Detection: Filters, SIFT, HOG

**[ ... ] 1. Gabor -> [ ... ] 2. SIFT -> [ ... ] 3. Harris Corners and Other Features**

