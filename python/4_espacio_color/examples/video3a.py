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
n = 10
index = 0
nFotogramas = []

shader = 0
out = 0
_a = 1/n
isFirstN = True

while(True):
    isDisponible, fotograma = captura.read()
    
    if (isDisponible == True):
        cv2.imshow('Camera', fotograma)
        
        # Checks the first video frame
        if (isFirstFrame):
            shader = np.zeros(fotograma.shape, np.uint8)
            out = np.zeros(fotograma.shape, np.uint8)
            isFirstFrame = False
        
        
        # shader = cv2.absdiff(lastFotograma, fotograma)
        
        if (index < n and isFirstN):
            res = _a*fotograma
            shader += res.astype(np.uint8)
        elif (index >= n):                
            index = 0
            nFotogramas = []
            out = shader
            # shader = np.zeros(fotograma.shape, np.uint8)
            isFirstN = False
            
            
        diff = cv2.absdiff(out, fotograma)
        #res = shader.astype(np.uint8)
        cv2.imshow('Prmedio', out)
        cv2.imshow('Diff', diff)
        index = index + 1
        
    else:
        print('Camera not available')
    
    # Waits for 25ms
    wait = 0xFF & cv2.waitKey(10)
    if (wait == ord('q') or wait == ord('Q')):
        print('Here we go')
        break

captura.release()
cv2.destroyAllWindows()

