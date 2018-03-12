# -*- coding: utf-8 -*-
"""
Created on Thu Feb  8 07:03:58 2018

@author: Romualdo Villalobos
"""

import numpy as np
import cv2


captura = cv2.VideoCapture(0)

isFirstFrame = True

gausian3x3_kernel = np.array([[0.06, 0.16, 0.06],
                              [0.13, 0.25, 0.13],
                              [0.06, 0.13, 0.06]], np.float32)

gausian5x5_kernel = np.array([
        [0, 0.02, 0.02, 0.02, 0],
        [0.02, 0.06, 0.09, 0.06, 0.02],
        [0.02, 0.09, 0.14, 0.09, 0.02],
        [0.02, 0.06, 0.09, 0.06, 0.02],
        [0, 0.02, 0.02, 0.02, 0]], np.float32);

# Creates the window where slider will be placed
cv2.namedWindow("Salida")


while(True):
    isDisponible, fotograma = captura.read()
    
    if (isDisponible == True):
        fotograma_gris = cv2.cvtColor(fotograma, cv2.COLOR_BGR2GRAY)
        cv2.imshow('Camera', fotograma_gris)
        
        #shader = cv2.inRange(fotograma, (bmin, gmin, rmin), (bmax, gmax, rmax))
        f1 = cv2.filter2D(fotograma_gris, -1, gausian3x3_kernel)
        f2 = cv2.filter2D(fotograma_gris, -1, gausian5x5_kernel)
        
        
        #res = shader.astype(np.uint8)
        #cv2.imshow('linea', shader)
        cv2.imshow('resta de suavizados', f2-f1)
        cv2.imshow('Salida', fotograma_gris)
        
    else:
        print('Camera not available')
    
    # Waits for 25ms
    wait = 0xFF & cv2.waitKey(10)
    if (wait == ord('q') or wait == ord('Q')):
        print('Here we go')
        break

captura.release()
cv2.destroyAllWindows()