# -*- coding: utf-8 -*-
"""
Created on Mon Feb 12 12:27:58 2018

@author: Romualdo Villalobos
"""

import numpy as np
import cv2

# calibration factor
c = 3
n = 5 # using n fotograms

captura = cv2.VideoCapture("video2.mp4")

# Creates the window where slider will be placed
cv2.namedWindow("Salida")

h_avg = 0
h_stddev = 0
s_avg = 0
s_stddev = 0

h_min = 0
h_max = 0
s_min = 0
s_max = 0

isCalibrating = True
i = 1
while(True):
    isDisponible, fotograma = captura.read()    
    #h_min = 0
    #h_max = 0
    
    if (isDisponible == True):
        
        fotograma_hsv = cv2.cvtColor(fotograma, cv2.COLOR_BGR2HSV)
        h, s, v = cv2.split(fotograma_hsv)
        
        if (isCalibrating):            
            tmp_h_avg, tmp_h_stddev = cv2.meanStdDev(h)
            tmp_s_avg, tmp_s_stddev = cv2.meanStdDev(s)            
            
            print(cv2.meanStdDev(h))
            tmp_h_avg = tmp_h_avg
            tmp_h_stddev = tmp_h_stddev
            
            h_avg = h_avg + (1/n) * tmp_h_avg
            h_stddev = h_stddev + (1/n) * tmp_h_stddev           
            
            #print(tmp_s_avg)
            tmp_s_avg = tmp_s_avg[0][0]
            tmp_s_stddev = tmp_s_stddev[0][0]        
            
            if (i < n):                
                i += 1
            else:
                h_dist = c * h_stddev
                h_min = h_avg - h_dist
                h_max = h_avg + h_dist
                print(h_avg)
                print(h_max)
                
                s_dist = c * s_stddev
                s_min, s_max = (s_avg - s_dist, s_avg + s_dist)
                           
                
                isCalibrating = False
                i = 0
        
                
        
        #shader = cv2.inRange(fotograma, (bmin, gmin, rmin), (bmax, gmax, rmax))
        #shader = fotograma_hsv
        #shader = cv2.inRange(fotograma_hsv, (h_min, s_min, 20), (h_max, s_max, 255))
        shader = cv2.inRange(fotograma_hsv, (h_min, s_min, 20), (h_max, s_max, 255))
        
        #res = shader.astype(np.uint8)
        cv2.imshow('Original', fotograma)
        cv2.imshow('Mask', shader)        
        
    else:
        print('Camera not available')
    
    # Waits for 25ms
    wait = 0xFF & cv2.waitKey(10)
    if (wait == ord('q') or wait == ord('Q')):
        print('Here we go')
        break

captura.release()
cv2.destroyAllWindows()
