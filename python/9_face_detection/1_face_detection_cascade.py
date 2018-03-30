# -*- coding: utf-8 -*-
"""
@author: Romualdo Villalobos
"""

import numpy as np
import cv2


captura = cv2.VideoCapture("video.mp4")

face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")


isFirstFrame = True

# Creates the window where slider will be placed
cv2.namedWindow("Salida")


while(True):
    isDisponible, fotograma = captura.read()
    
    if (isDisponible == True):        
        #input
        fotograma_gray = cv2.cvtColor(fotograma, cv2.COLOR_BGR2GRAY)
        
        # detect faces (segmentation)
        faces = face_cascade.detectMultiScale(fotograma_gray, 1.3, 5)
        for (x, y, w, h) in faces:
            # draw rectangles
            cv2.rectangle(fotograma, (x, y), (x + w, y + h), (255, 0, 0), 2)
            cv2.rectangle(fotograma_gray, (x, y), (x + w, y + h), (255, 0, 0), 2)
            # draw circles
            x_ = int(x + w/2)
            y_ = int(y + h/2)
            cv2.circle(fotograma, (x_, y_), 5, (255, 255, 0), 10)
            cv2.circle(fotograma_gray, (x_, y_), 5, (255, 255, 0), 10)
            
        #shader = cv2.inRange(fotograma, (bmin, gmin, rmin), (bmax, gmax, rmax))
        shader = fotograma_gray        
        res = shader.astype(np.uint8)
        
        # output
        cv2.imshow('Camera', fotograma)
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