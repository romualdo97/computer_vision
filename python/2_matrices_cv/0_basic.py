# -*- coding: utf-8 -*-
"""
Created on Mon Jan 29 12:45:59 2018

@author: Romualdo J. Villalobos P.
"""

import numpy as np
import cv2

entrada = cv2.imread("cat.jpg", 0)

alto, ancho = entrada.shape
salida = np.zeros((alto, ancho), np.uint8)

while(True):
    for i in range(0, alto):
        for j in range(0, ancho):
            # READ IMAGE DATA
            c = entrada.item(i,j)            
            salida.itemset((i,j), c)
            
    cv2.imshow("Resultado", entrada)
    cv2.imshow("original", salida)
    ch = 0xFF & cv2.waitKey()
    if (ch == ord('q')):
        cv2.imwrite("resultado.jpg", salida)
        break;
cv2.destroyAllWindows();


    

