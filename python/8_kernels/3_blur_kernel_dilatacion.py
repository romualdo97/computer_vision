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

border3x3_kernel = np.array([[-1, -1, -1],
                             [-1, 8, -1],
                             [-1, -1, -1]], np.float32)

dilatacion_kernel = np.ones((5, 5), np.uint8)
dilatacion_kernel[0:2, 0:2] = 0
dilatacion_kernel[0:2, 3:5] = 0
dilatacion_kernel[3:5, 0:2] = 0
dilatacion_kernel[3:5, 3:5] = 0

# Creates the window where slider will be placed
cv2.namedWindow("Salida")


while(True):
    isDisponible, fotograma = captura.read()
    
    if (isDisponible == True):
        fotograma_gris = cv2.cvtColor(fotograma, cv2.COLOR_BGR2GRAY)
        cv2.imshow('Camera', fotograma_gris)
        
        #shader = cv2.inRange(fotograma, (bmin, gmin, rmin), (bmax, gmax, rmax))
        shader = cv2.filter2D(fotograma_gris, -1, gausian3x3_kernel)
        lineas = cv2.filter2D(shader, -1, border3x3_kernel)
        dilatado = cv2.dilate(lineas, dilatacion_kernel, iterations=4)
        
        
        #res = shader.astype(np.uint8)
        #cv2.imshow('linea', shader)
        cv2.imshow('dilatacion', dilatado)
        cv2.imshow('Salida', fotograma_gris - lineas)
        
    else:
        print('Camera not available')
    
    # Waits for 25ms
    wait = 0xFF & cv2.waitKey(10)
    if (wait == ord('q') or wait == ord('Q')):
        print('Here we go')
        break

captura.release()
cv2.destroyAllWindows()