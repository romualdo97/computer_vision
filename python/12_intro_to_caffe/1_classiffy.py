# In the previous net, weight and bias params 
# have been initialiazed randomly.

import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import caffe

caffe.set_device(0)
caffe.set_mode_gpu()

print("Caffe initialized")

"""
sIt is possible to load trained parameters
and in this case, the result of the net
will produce a classification.

Many trained models can be downloaded from
the community in the Caffe Model Zoo,
such as car classification, flower classification,
digit classification…
"""