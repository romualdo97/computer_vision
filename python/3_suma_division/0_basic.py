# -*- coding: utf-8 -*-
"""
Created on Mon Jan 29 12:45:59 2018

@author: Romualdo J. Villalobos P.
"""

import numpy as np
import cv2

#entrada = cv2.imread("cat.jpg")
entradas = []
for i in range(1, 7):
    imagename = "cat" + str(i) + ".jpg"
    entradas.append(cv2.imread(imagename))

alto, ancho, channels = entradas[0].shape
salida = np.zeros((alto, ancho), np.uint8)

while(True):
            
    #cv2.imshow("Resultado", entrada)    
    
    for j in range(len(entradas)):
        print("Printing image " + str(j))
        cv2.imshow("original" + str(j), entradas[j])
    
    
    ch = 0xFF & cv2.waitKey()
    if (ch == ord('q')):
        #cv2.imwrite("resultado.jpg", salida)
        break;
cv2.destroyAllWindows();


    

