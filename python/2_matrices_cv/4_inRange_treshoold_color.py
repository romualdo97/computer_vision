# -*- coding: utf-8 -*-
"""
Created on Mon Jan 29 12:45:59 2018

@author: Romualdo J. Villalobos P.
"""

import numpy as np
import cv2

entrada = cv2.imread("cat2.jpg")

alto, ancho, channels = entrada.shape
salida = np.zeros((alto, ancho, 3), np.uint8)

while(True):

    salida = cv2.inRange(entrada, (50, 65, 40), (255, 255, 255))
            
    cv2.imshow("Resultado", entrada)
    cv2.imshow("original", salida)
    ch = 0xFF & cv2.waitKey()
    if (ch == ord('q')):
        cv2.imwrite("resultado.jpg", salida)
        break;
cv2.destroyAllWindows();


    

