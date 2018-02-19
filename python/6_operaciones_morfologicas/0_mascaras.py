# -*- coding: utf-8 -*-
"""
Created on Mon Feb 12 12:27:58 2018

@author: Romualdo Villalobos
"""

import numpy as np
import cv2

# calibration factor
c = 3
n = 75 # using n fotograms

kernel = np.ones((5, 5), np.uint8)
kernel[0:2, 0:2] = 0
kernel[0:2, 3:5] = 0
kernel[3:5, 0:2] = 0
kernel[3:5, 3:5] = 0
#kernel[4, 0] = 0
#kernel[4, 4] = 0
print(kernel)

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
fctr = 1 / n
while(True):
    isDisponible, fotograma = captura.read()
    
    if (isDisponible == True):
        
        hsv_frame = cv2.cvtColor(fotograma, cv2.COLOR_BGR2HSV)        
        h, s, v = cv2.split(hsv_frame)
        
        if (isCalibrating):
            #h_f64 = h.astype(np.float64)
            tmp_h_avg, tmp_h_stddev = cv2.meanStdDev(h)                                                  
            h_avg = h_avg + tmp_h_avg[0][0] * fctr
            h_stddev = h_stddev + tmp_h_stddev[0][0] * fctr
            print(h_stddev)
            
            tmp_s_avg, tmp_s_stddev = cv2.meanStdDev(s)
            s_avg = s_avg + tmp_s_avg[0][0] * fctr
            s_stddev = s_stddev + tmp_s_stddev[0][0] * fctr
            
            if (i < n):                
                i += 1
            else:
                h_dist = c * h_stddev
                h_min = h_avg - h_dist
                h_max = h_avg + h_dist
                
                s_dist = c * s_stddev
                s_min = s_avg - s_dist
                s_max = s_avg + s_dist                
                
                isCalibrating = False
                i = 0                
        
        mask_nobin = cv2.inRange(hsv_frame, (h_min, s_min, 20), (h_max, s_max, 255))
        
        #ret, mask_inv = cv2.threshold(mask_nobin, 126, 1, cv2.THRESH_BINARY_INV)
        
        #fondo = cv2.bitwise_and(imgfondo, imgfondo, mask=mask)
        #focus = cv2.bitwise_and(fotograma, fotograma, mask=1-mask)
        
        #shader = cv2.add(fondo, focus)
        dilatacion = cv2.dilate(mask_nobin, kernel, iterations=4)
        erocion = cv2.erode(dilatacion, kernel, iterations=2)
        
        #mask_nobin = dilatacion
        #mask_nobin = erocion
        #ret, mask = cv2.threshold(mask_nobin, 126, 1, cv2.THRESH_BINARY)
        #focus = cv2.bitwise_and(fotograma, fotograma, mask=1-mask)
        
        shader = dilatacion-erocion
        
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
