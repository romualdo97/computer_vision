# -*- coding: utf-8 -*-
"""
Created on Sat Mar 17 21:40:08 2018

@author: rojo
"""
import numpy as np
import cv2

# B0: box
# A0, A2: stars
# A1, A5, A6, B1: circles

filename = 'database/B1.jpg'
img_color = cv2.imread(filename)
img = cv2.imread(filename, 0) # load any image
ret,thresh = cv2.threshold(img, 127, 255, 0) # segmentation
im2,contours,hierarchy = cv2.findContours(thresh, 1, 2) # find contours

cnt = contours[0]
M = cv2.moments(cnt)

cx = int(M['m10']/M['m00'])
cy = int(M['m01']/M['m00'])

area = cv2.contourArea(cnt)

perimeter = cv2.arcLength(cnt, True)

approx = cv2.approxPolyDP(cnt, 0.04 * perimeter, True)

#cv2.drawContours(img_color, cnt, -1, (0, 255, 0), 2)
cv2.drawContours(img_color, approx, -1, (0, 255, 0), 10)

cv2.imwrite("result.jpg", img_color)

#print("moments: " + str(M))
print("len(cnt): " + str(len(cnt)))
print("len(cnt_approx): " + str(len(approx)))
print("area: " + str(area))
print("perimeter: " + str(perimeter))
print("===================================")
if len(approx) == 4:
    print("The image is a box")
elif len(approx) == 8:
    print("The image is a circle")
elif len(approx) == 10:
    print("The image is an star")    