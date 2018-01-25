# -*- coding: utf-8 -*-
"""
Created on Thu Jan 25 07:05:44 2018

@author: Romualdo J. Villalobos P.
"""
# =====================================================================
# CONFIG PANEL
# Here you can select one of the four proposed exercises for revision,
# change the EXERCISE_NUMBER for select an exersice.

EXERCISE_NUMBER = 3

# when EXERCISE_NUMBER == 0
#   conclusion: don't transform the original image.

# when EXERCISE_NUMBER == 1
#   conclusion: convert the image from color 
#               to black and white using the average
#               technique.

# when EXERCISE_NUMBER == 2
#   conclusion: control brightness and contrast

# when EXERCISE_NUMBER == 3
#   conclusion: control brightness and contrast for each channel
#               separately



# =====================================================================
# =====================================================================
# =====================================================================
# =====================================================================
# GLOBALS

import numpy as np
import cv2

# input vars
if EXERCISE_NUMBER == 0 or EXERCISE_NUMBER == 1 or EXERCISE_NUMBER == 3:
    img_original = cv2.imread("1_cho_in_color.jpg")
    height, width, chanels = img_original.shape
elif EXERCISE_NUMBER == 2:
    img_original = cv2.imread("2_low_contrast.jpg", 0)
    height, width = img_original.shape


# output vars
if EXERCISE_NUMBER == 0 or EXERCISE_NUMBER == 3:
    img_out = np.zeros((height, width, 3), np.uint8)
elif EXERCISE_NUMBER == 1 or EXERCISE_NUMBER == 2:
    img_out_mono = np.zeros((height, width), np.uint8)
    



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

# 3) conslusion: control brightness and contrast
def high_contrast_kernel(in_color):
    a = 1.08
    b = -50
    A = in_color;
    out_color = [(A[0] + b) * a, (A[1] + b) * a, (A[2] + b) * a]
    return out_color

# 3) conslusion: control brightness and contrast for each channel
def high_contrast_color_kernel(in_color):
    ra = 1.12
    rb = -10
    
    ga = 1.09
    gb = -15
    
    ba = 1.06
    bb = -20
    
    A = in_color;
    out_color = [(A[0] + rb) * ra, (A[1] + gb) * ga, (A[2] + bb) * ba]
    return out_color

# =====================================================================
# EXERCISE IMPLEMENTATIONS
    
# 0) no transform 
def none_program():
    # READ IMAGE DATA
    texel = texture(img_original, False)    
    # EXECUTE A COMPUTE KERNEL               
    color = none_kernel(texel)    
    # SAVE IMAGE TRANSFORMATIONS
    texImage2D(img_out, color, False)

# 1) convert from color to bw
def bw_program():
    # READ IMAGE DATA
    texel = texture(img_original, True)            
    # EXECUTE A COMPUTE KERNEL   
    color = bw_kernel(texel);            
    # SAVE IMAGE TRANSFORMATIONS
    texImage2D(img_out_mono, color, True)
    
# 2) control brightness and contrast
def high_contrast_program():
    # READ IMAGE DATA
    texel = texture(img_original, True)            
    # EXECUTE A COMPUTE KERNEL   
    color = high_contrast_kernel(texel);            
    # SAVE IMAGE TRANSFORMATIONS
    texImage2D(img_out_mono, color, True)
    
# 2) control brightness and contrast
def high_contrast_color_program():
    # READ IMAGE DATA
    texel = texture(img_original, False)            
    # EXECUTE A COMPUTE KERNEL   
    color = high_contrast_color_kernel(texel);            
    # SAVE IMAGE TRANSFORMATIONS
    texImage2D(img_out, color, False)
    
# =====================================================================
# MISC DEFINITIONS
    
# read texture texels similar to glsl
def texture(texture2D, is_mono):
    if is_mono:
        b0 = texture2D.item(i, j)
        g0 = b0
        r0 = b0
        texel = [r0, g0, b0]
    else:
        b0 = texture2D.item(i, j, 0)
        g0 = texture2D.item(i, j, 1)
        r0 = texture2D.item(i, j, 2)
        texel = [r0, g0, b0]
    return texel

# put image data to a texture object (image) similar to opengl
def texImage2D(img_obj, img_data, is_mono):    
    if is_mono: # use one channel?
        img_obj.itemset((i, j), img_data[0])
    else: # use 3 channels
        img_obj.itemset((i, j, 0), img_data[2]) # b
        img_obj.itemset((i, j, 1), img_data[1]) # g
        img_obj.itemset((i, j, 2), img_data[0]) # r
        
def writeTex2D(name, image, is_mono):    
    if is_mono: # use one channel?
        _img_out = np.ones((height, width), np.uint8)
        _img_out = image
    else:
        _img_out = np.zeros((height, width, 3), np.uint8)
        _img_out = image
    cv2.imwrite(name, _img_out)

# =====================================================================
# PROGRAM MAIN
        
while (True):
    for i in range(0, height):
        for j in range(0, width):
            if EXERCISE_NUMBER == 0:
                none_program();
            elif EXERCISE_NUMBER == 1:
                bw_program();
            elif EXERCISE_NUMBER == 2:
                high_contrast_program();
            elif EXERCISE_NUMBER == 3:
                high_contrast_color_program();
    
    cv2.imshow("Original", img_original)
    if EXERCISE_NUMBER == 0 or EXERCISE_NUMBER == 3:
        cv2.imshow("Resultado", img_out)
    elif EXERCISE_NUMBER == 1 or EXERCISE_NUMBER == 2:
        cv2.imshow("Resultado", img_out_mono)
        

    ch = 0xFF & cv2.waitKey()
    if (ch == ord('q')):
        #cv2.imwrite("out.jpg", img_out_mono)
        if EXERCISE_NUMBER == 0 or EXERCISE_NUMBER == 3:
            writeTex2D("out.jpg", img_out, False);
        elif EXERCISE_NUMBER == 1 or EXERCISE_NUMBER == 2:
            writeTex2D("out.jpg", img_out_mono, True);
        break
    
cv2.destroyAllWindows();
    
   