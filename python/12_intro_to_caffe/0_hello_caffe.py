# -*- coding: utf-8 -*-
"""
Created on Tue Apr 24 21:39:29 2018

@author: user
"""

# In this net, weight and bias params have been initialiazed randomly.

import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import caffe

caffe.set_device(0)
caffe.set_mode_gpu()


# conv.prototxt describes the neuron network.
# load the net:

net = caffe.Net("conv.prototxt", caffe.TEST)

# Blobs are memory abstraction objects
# (with execution depending on the mode), and data
# is contained in the field data as an array :

print(net.blobs['conv'].data.shape)

# We need to reshape the data blob (1, 1, 100, 100) to
# the new size (1, 1, 360, 480) to fit the image

im = np.array(Image.open("cat_gray.jpg"))
im_input = im[np.newaxis, np.newaxis, :, :]
net.blobs['data'].reshape(*im_input.shape)
net.blobs['data'].data[...] = im_input

# Let’s compute the blobs given this input
net.forward()

# Now net.blobs['conv'] is filled with data,
# and the 3 pictures inside each of the 3 neurons
# (net.blobs['conv'].data[0,i]) can be plotted easily.

# To save the net parameters net.params:
net.save('mymodel.caffemodel')

