# -*- coding: utf-8 -*-
"""
Created on Thu Mar 29 15:38:49 2018

@author: gb10
https://www.pyimagesearch.com/2017/04/03/facial-landmarks-dlib-opencv-python/
"""
import numpy as np
import cv2
import dlib

from pythonosc import udp_client
from pythonosc import osc_message_builder

IP_OUT = '127.0.0.1'
PORT_OUT = 9000

def rect_to_bb(rect):
	# take a bounding predicted by dlib and convert it
	# to the format (x, y, w, h) as we would normally do
	# with OpenCV
	x = rect.left()
	y = rect.top()
	w = rect.right() - x
	h = rect.bottom() - y
 
	# return a tuple of (x, y, w, h)
	return (x, y, w, h)

def shape_to_np(shape, dtype="int"):
	# initialize the list of (x, y)-coordinates
	coords = np.zeros((68, 2), dtype=dtype)
 
	# loop over the 68 facial landmarks and convert them
	# to a 2-tuple of (x, y)-coordinates
	for i in range(0, 68):
		coords[i] = (shape.part(i).x, shape.part(i).y)
 
	# return the list of (x, y)-coordinates
	return coords


captura = cv2.VideoCapture(0)

# initialize dlib's face detector (HOG-based)
detector = dlib.get_frontal_face_detector()

client = udp_client.SimpleUDPClient(IP_OUT, PORT_OUT)


while(True):
    isDisponible, fotograma = captura.read()
    height, width, ch = fotograma.shape;
    #print(height, width)
    
    if (isDisponible == True):
        #cv2.imshow('Camera', fotograma)
        gray = cv2.cvtColor(fotograma, cv2.COLOR_BGR2GRAY)
        
        # Detect faces in the actual frame
        '''
        The second parameter is the number of image pyramid layers to apply
        when upscaling the image prior to applying the detector
        (this it the equivalent of computing cv2.pyrUp N number of times on the image).
        '''
        rects = detector(gray, 1)
        
        # iterates over the detected faces
        for (i, rect) in enumerate(rects):
            # Converts a dlib's rectangle to an opencv-like rectangle
            x, y, w, h = rect_to_bb(rect)
            point = (int((x+(x+w))/2), int((y+(y+h))/2))
            
            cv2.circle(fotograma, point, 4, (255, 0, 0), 5)
            cv2.rectangle(fotograma, (x, y), (x+w, y+w), (0, 255, 0), 2)
            # print(point)
            
            client.send_message('/face/pos/x', point[0])
            client.send_message('/face/pos/y', point[1])
        
        cv2.imshow('Camera', fotograma) 
    
    else:
        print('Camera not available')

    ch = 0xFF & cv2.waitKey(1)
    if (ch == ord('q') or ch == ord('Q')):
        break

captura.release()
cv2.destroyAllWindows();     