# -*- coding: utf-8 -*-
"""
Created on Mon Jan 29 12:45:59 2018

@author: Romualdo J. Villalobos P.
"""

import numpy as np
import cv2

#entrada = cv2.imread("cat.jpg")
entradas = []
for i in range(1, 7): # from 1 to 6
    imagename = "cat" + str(i) + ".jpg"
    entradas.append(cv2.imread(imagename))

alto, ancho, canales = entradas[0].shape
salida = np.zeros((alto, ancho, canales), np.float)

while(True):
    numImgs = len(entradas)
    
    for i in range(numImgs):
        # show original images
        print("Printing image " + str(i))
        cv2.imshow("original" + str(i), entradas[i])
        # calulate mean
        salida += (1.0/numImgs) * entradas[i]
    
    c = salida.astype(np.uint8)
    cv2.imshow("output", c)
    
    ch = 0xFF & cv2.waitKey()
    if (ch == ord('q')):
        #cv2.imwrite("resultado.jpg", salida)
        break;
cv2.destroyAllWindows();


    

