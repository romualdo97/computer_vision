# -*- coding: utf-8 -*-
"""
Created on Mon Jan 29 12:45:59 2018

@author: Romualdo J. Villalobos P.
"""

import numpy as np
import cv2

entrada = cv2.imread("cat2.jpg")

alto, ancho, channels = entrada.shape
salida = np.zeros((alto, ancho), np.uint8)

while(True):
    for i in range(0, alto):
        for j in range(0, ancho):
            # READ IMAGE DATA
            r = entrada.item(i,j,2)
            g = entrada.item(i,j,1)
            b = entrada.item(i,j,0)
            
            br = True if r > 50 else False            
            bg = True if g > 65 else False
            bb = True if b > 40 else False
            
            c = 255 if br and bg and bb else 0
            
            salida.itemset((i,j), c)
            
    cv2.imshow("Resultado", entrada)
    cv2.imshow("original", salida)
    ch = 0xFF & cv2.waitKey()
    if (ch == ord('q')):
        cv2.imwrite("resultado.jpg", salida)
        break;
cv2.destroyAllWindows();


    

