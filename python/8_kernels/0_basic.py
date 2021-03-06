# -*- coding: utf-8 -*-
"""
Created on Thu Feb  8 07:03:58 2018

@author: Romualdo Villalobos
"""

import numpy as np
import cv2


captura = cv2.VideoCapture(0)

isFirstFrame = True

# Creates the window where slider will be placed
cv2.namedWindow("Salida")


while(True):
    isDisponible, fotograma = captura.read()
    
    if (isDisponible == True):
        cv2.imshow('Camera', fotograma)
        
        #shader = cv2.inRange(fotograma, (bmin, gmin, rmin), (bmax, gmax, rmax))
        shader = fotograma
        
        res = shader.astype(np.uint8)
        cv2.imshow('Salida', res)
        
    else:
        print('Camera not available')
    
    # Waits for 25ms
    wait = 0xFF & cv2.waitKey(10)
    if (wait == ord('q') or wait == ord('Q')):
        print('Here we go')
        break

captura.release()
cv2.destroyAllWindows()