# -*- coding: utf-8 -*-
"""
Created on Mon Jan 29 12:45:59 2018

@author: Romualdo J. Villalobos P.
"""

import numpy as np
import cv2

frame = cv2.imread("database/A0.jpg")
frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

alto, ancho = frame_gray.shape
salida = np.zeros((alto, ancho), np.uint8)

while(True):
    
    frame_ui8 = frame_gray.astype(np.uint8)
    
    # CALCULATE AREA, CONTOURS AND CENTROID
    moments = cv2.moments(frame_ui8, False);
    
    if moments["m00"] <= 1:
            continue;
    
    area = moments["m00"]
    frame2, contours, hierarchy = cv2.findContours(frame_ui8, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(frame, contours, -1, (0, 255, 0), 3)
    centroide = (moments["m10"]/moments["m00"], moments["m01"]/moments["m00"])
    
    cv2.imshow("Resultado", frame)
    
    ch = 0xFF & cv2.waitKey()
    if (ch == ord('q')):
        break;

cv2.destroyAllWindows();


    

