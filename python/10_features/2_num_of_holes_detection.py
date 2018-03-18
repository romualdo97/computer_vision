# -*- coding: utf-8 -*-
"""
Created on Sat Mar 17 21:40:08 2018

@author: rojo
"""
import numpy as np
import cv2

# C0, C1

filename = 'database/C0.png'
img_color = cv2.imread(filename)
img = cv2.imread(filename, 0) # load any image
ret,thresh = cv2.threshold(img, 127, 255, 0) # segmentation
im2,contours,hierarchy = cv2.findContours(thresh, cv2.RETR_CCOMP, 2) # find contours

print("Num of holes: " + str(len(contours) - 1))

cv2.imwrite("result.jpg", img_color)