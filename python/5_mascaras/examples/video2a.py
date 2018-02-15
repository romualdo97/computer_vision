# -*- coding: utf-8 -*-
"""
Created on Mon Jan 29 13:42:29 2018

@author: Jose VIllalobos
"""
import numpy as np
import cv2


captura = cv2.VideoCapture(0)
#img = cv2.imread('tucan.jpg', cv2.IMREAD_COLOR)
#print(img.shape)

isFirstFrame = True

# Creates the window where slider will be placed
cv2.namedWindow("Salida")

while(True):
    isDisponible, fotograma = captura.read()
    
    if (isDisponible == True):
        cv2.imshow('Camera', fotograma)
        
        # Checks the first video frame
        if (isFirstFrame):
            lastFotograma = np.zeros(fotograma.shape, np.uint8)
            isFirstFrame = False
        
        
        shader = cv2.absdiff(lastFotograma, fotograma)
        
        
        
        res = shader.astype(np.uint8)
        cv2.imshow('Last', lastFotograma)
        cv2.imshow('Actual', fotograma)
        cv2.imshow('Shader', shader)
        lastFotograma = fotograma;
        
    else:
        print('Camera not available')
    
    # Waits for 25ms
    wait = 0xFF & cv2.waitKey(10)
    if (wait == ord('q') or wait == ord('Q')):
        print('Here we go')
        break

captura.release()
cv2.destroyAllWindows()

