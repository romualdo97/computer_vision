# -*- coding: utf-8 -*-
"""
Created on Thu Jan 25 07:05:44 2018

@author: Romualdo J. Villalobos P.
"""

import numpy as np
import cv2

# GLOBALS
img_original = cv2.imread("cho.jpg")
height, width, chanels = img_original.shape
img_out = np.zeros((height, width, 3), np.uint8)

# =====================================================================
# COMPUTE KERNEL DEFINITIONS

# 0) conclusion: don't transform the original image.
def none_kernel(in_color):    
    out_color = [in_color[0], in_color[1], in_color[2]] #rgb order
    return out_color;

# 1) conclusion: convert the image from color 
#                to black and white using the average
#                technique.
def bw_kernel(in_color):
    avrg = (in_color[0] + in_color[1] + in_color[2]) / 3
    out_color = [avrg, avrg, avrg]
    return out_color

# =====================================================================
# EXERCISE IMPLEMENTATIONS
    
# 0) no transform 
def none_program(i, j):
    # READ IMAGE DATA
    texel = texture(img_original)
    
    # EXECUTE A COMPUTE KERNEL               
    color = none_kernel(texel)
    
    # SAVE IMAGE TRANSFORMATIONS
    texImage2D(img_out, color, False)

# =====================================================================
# MISC DEFINITIONS
    
# read texture texels like in glsl
def texture(texture2D):
    b0 = texture2D.item(i, j, 0)
    g0 = texture2D.item(i, j, 1)
    r0 = texture2D.item(i, j, 2)
    texel = [r0, g0, b0];
    return texel;

# put image data to a texture object (image) similar to opengl
def texImage2D(img_obj, img_data, is_mono):    
    if is_mono: # use one channel?
        img_obj.itemset((i, j, 0), img_data[2])
    else: # use 3 channels
        img_obj.itemset((i, j, 0), img_data[2]) # b
        img_obj.itemset((i, j, 1), img_data[1]) # g
        img_obj.itemset((i, j, 2), img_data[0]) # r
        
def writeTex2D(name, image, is_mono):
    
    if is_mono: # use one channel?
        _img_out = np.zeros((height, width), np.uint8)
        _img_out = image
        cv2.imwrite(name, _img_out)
    else:
        _img_out = np.zeros((height, width, 3), np.uint8)
        _img_out = image
        cv2.imwrite(name, _img_out)

# =====================================================================
# PROGRAM MAIN
        
while (True):
    for i in range(0, height):
        for j in range(0, width):
            none_program(i, j);
            # READ IMAGE DATA
            #texel = texture(img_original)
            
            # EXECUTE A COMPUTE KERNEL
            # 0) no transform            
            #color = none_kernel(texel)
            
            # 1) convert from color to bw
            #color = bw_kernel(texel);
            
            # SAVE IMAGE TRANSFORMATIONS
            #texImage2D(img_out, color, False)
            
            
            
    cv2.imshow("Original", img_original)
    cv2.imshow("Resultado", img_out)

    ch = 0xFF & cv2.waitKey()
    if (ch == ord('q')):
        writeTex2D("out.jpg", img_out, True);
        break
    
cv2.destroyAllWindows();
    
   