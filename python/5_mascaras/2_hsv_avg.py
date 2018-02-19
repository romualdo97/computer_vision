# -*- coding: utf-8 -*-
"""
Created on Thu Feb  8 07:03:58 2018

@author: Romualdo Villalobos
"""

import numpy as np
import cv2


captura = cv2.VideoCapture("video.mp4")

# Creates the window where slider will be placed
cv2.namedWindow("Salida")


while(True):
    isDisponible, fotograma = captura.read()
    fotograma_hsv = cv2.cvtColor(fotograma, cv2.COLOR_BGR2HSV)
    
    if (isDisponible == True):
        #cv2.imshow('Camera', fotograma)
        
        #h, s, v = cv2.split(fotograma_hsv)
        
        #shader = cv2.inRange(fotograma, (bmin, gmin, rmin), (bmax, gmax, rmax))
        #shader = fotograma_hsv
        shader = cv2.inRange(fotograma_hsv, (50, 60, 60), (65, 255, 255))
        #shader = cv2.inRange(fotograma_hsv, (0, 100, 50), (150, 100, 50))
        
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
