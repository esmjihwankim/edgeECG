import math

import matplotlib.pyplot as plt
import os


import keras
from keras import *
from keras.datasets import mnist
from keras.layers import *
from keras.activations import *
from keras.models import load_model, save_model
import tensorflow as tf
import numpy as np

import matplotlib.pyplot as plt

from nnom import *

model_name = 'regression_simple_trained_model.h5'

nsamples = 1000
val_ratio = 0.2
test_ratio = 0.2
x_values = np.random.uniform(low=0, high=(2 * math.pi), size=nsamples)
y_values = np.sin(x_values)

# Split dataset training, validation and test as 60%, 20%, and 20% respectively
val_split = int(val_ratio * nsamples)
test_split = int(val_split + (test_ratio * nsamples))
x_val, x_test, x_train = np.split(x_values, [val_split, test_split])
y_val, y_test, y_train = np.split(y_values, [val_split, test_split])

