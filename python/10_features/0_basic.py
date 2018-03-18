# -*- coding: utf-8 -*-
"""
Created on Mon Jan 29 12:45:59 2018

@author: Romualdo J. Villalobos P.
"""

import numpy as np
import cv2

filename = 'database/B1.jpg'
img_color = cv2.imread(filename)
img = cv2.imread(filename, 0) # load any image
ret,thresh = cv2.threshold(img, 127, 255, 0) # segmentation
im2,contours,hierarchy = cv2.findContours(thresh, 1, 2) # find contours