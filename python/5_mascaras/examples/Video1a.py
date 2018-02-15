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


def onMixValueChange():
    pass;

# Creates the slider
cv2.createTrackbar("Rmax", "Salida", 0, 255, onMixValueChange)
cv2.createTrackbar("Gmax", "Salida", 0, 255, onMixValueChange)
cv2.createTrackbar("Bmax", "Salida", 0, 255, onMixValueChange)

cv2.createTrackbar("Rmin", "Salida", 0, 255, onMixValueChange)
cv2.createTrackbar("Gmin", "Salida", 0, 255, onMixValueChange)
cv2.createTrackbar("Bmin", "Salida", 0, 255, onMixValueChange)

while(True):
    isDisponible, fotograma = captura.read()
    
    if (isDisponible == True):
        cv2.imshow('Camera', fotograma)
        
        # Checks the first video frame
        #if (isFirstFrame):
            # Resizes the input img to the size of the camera resolution
            # This resize operation is needed for the matrix operaions that we are going to perform later
            # cv2.INTER_AREA is recommended for shrinking images (for resize them)
            #img = cv2.resize(img, (fotograma.shape[1], fotograma.shape[0]), interpolation=cv2.INTER_AREA)
            #ifFirstFrame = False
        
        rmax = cv2.getTrackbarPos("Rmax", "Salida")
        gmax = cv2.getTrackbarPos("Gmax", "Salida")
        bmax = cv2.getTrackbarPos("Bmax", "Salida")
        
        rmin = cv2.getTrackbarPos("Rmin", "Salida")
        gmin = cv2.getTrackbarPos("Gmin", "Salida")
        bmin = cv2.getTrackbarPos("Bmin", "Salida") 
        shader = cv2.inRange(fotograma, (bmin, gmin, rmin), (bmax, gmax, rmax))
        
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

