
# coding: utf-8

# # Digit Classification

# In[4]:

from sklearn import datasets
import numpy as np
import matplotlib.pyplot as plt
get_ipython().magic('matplotlib notebook')
digits = datasets.load_digits()


# `sklearn` is a common machine learning module in Python. The dataset we have imported is the digits dataset, with 1800 images of digits and labels. Let's look at the first element.

# In[2]:

print(digits.images[0])


# In[5]:

plt.figure()
plt.imshow(digits.images[0], cmap = plt.cm.gray_r, interpolation = 'nearest')
plt.show()


# In[6]:

print(digits.target[0])


# First we are going to look at a subset of the data, our training set.

# In[7]:

X_train = digits.data[0:10]
Y_train = digits.target[0:10]


# In[8]:

X_test = digits.data[345]
plt.figure()
plt.imshow(digits.images[345], cmap = plt.cm.gray_r, interpolation = 'nearest')
plt.show()


# Now we'll do the nearest neighbour classifier.

# In[9]:

def dist(x, y):
    return np.sqrt(np.sum((x - y)**2))

num = len(X_train)
distance = np.zeros(num)
for i in range(num):
    distance[i] = dist(X_train[i], X_test)
min_index = np.argmin(distance)
print(Y_train[min_index])


# In[17]:

num = len(X_train)
no_errors = 0
distance = np.zeros(num)
for j in range(500, 1500):
    X_test = digits.data[j]
    for i in range(num):
        distance[i] = dist(X_train[i], X_test)
    min_index = np.argmin(distance)
    if Y_train[min_index] != digits.target[j]:
        no_errors += 1
print(no_errors)
print(str(int((no_errors/9.99)//1)) + "% incorrect")


# Not that good, huh... But it's better than random! More training data will help.

# In[18]:

X_train = digits.data[0:1000]
Y_train = digits.target[0:1000]

num = len(X_train)
no_errors = 0
distance = np.zeros(num)
for j in range(1000, 1500):
    X_test = digits.data[j]
    for i in range(num):
        distance[i] = dist(X_train[i], X_test)
    min_index = np.argmin(distance)
    if Y_train[min_index] != digits.target[j]:
        no_errors += 1
print(no_errors)
print(str(int((no_errors/4.99)//1)) + "% incorrect")


# Oh my god, that's amazing. 98% correctness.

# In[ ]:



