# Week 1: Welcome 

1. [DARPA Grand Challenge and Stanley][1]
2. There're 2 distinct approaches to autonomous development:

>- A **robotics** approach: fuses output from a suite of sensors to directly measure the vehicle surroundings and then navigate accordingly  
>- A **deep learning** approach: teach computer learn how to drive by mimicking human driving behavior        

3. Projects to build in this fantastic program

> - Term 1: Computer vision and deep learning  
>
>   > Project 1: Finding lane lines
>   >
>   > Project 2: Behavioral cloning
>   >
>   > Project 3: Advanced lane finding and vehicle detection

> - Term 2: Sensor fusion, localization and control  
>
>   > Project 4: Sensor fusion
>   >
>   > Project 5: Localization
>   >
>   > Project 6: Controllers

> - Term 3: Path planning & controlling a real self-driving car  
>
>   > Project 7: Path planning
>   >
>   > Project 8: Put your code in a real self-driving car!  



---

# Week 2: Finding Lane Lines on the Road

**1. what is the problem? -> 2. color selection -> 3. region masking -> 4. canny edge detection -> 5. hough transform -> 6. project 1**

## 1. What is the problem?

how to perceive the world.

camera is just like our eyes

identify and track the position of the lane lines in a series of images(video)

## 2. Color Selection

a color image is combined of 3 channels : R(ed), G(reen), B(lue).

each of these color channels contains pixels whose values range from 0(black) to 255(white).

**Always make a COPY of array or images, otherwise it is just a reference**

## 3. Region Masking

region interest us

in this case, we could assume that the camera that took the image is mounted in a fixed position on the front of the car, therefore, the lane lines will always appear in the same general region of the image

## 4. Canny edge detection

## 5. Hough transform

## 6. Project 1



---

[1]https://classroom.udacity.com/nanodegrees/nd013/parts/fbf77062-5703-404e-b60c-95b78b2f3f9e/modules/83ec35ee-1e02-48a5-bdb7-d244bd47c2dc/lessons/facdff19-61a5-47e4-8179-a6a5dc28987f/concepts/70763f5c-a090-454f-aef9-8e05c16d2db5