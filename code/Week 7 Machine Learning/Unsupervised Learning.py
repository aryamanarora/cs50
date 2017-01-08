
# coding: utf-8

# # Unsupervised Learning

# In[1]:

import numpy as np                # scientific computing
import matplotlib.pyplot as plt   # easily plot
get_ipython().magic('matplotlib notebook')


# Here is a training dataset:

# In[2]:

X_train = np.array([[1,1], [2,2.5], [3,1.2], [5.5,6.3], [6,9], [7,6]]) # Define numpy array of two-dim points
Y_train = ['red', 'red', 'red', 'blue', 'blue', 'blue'] # Define a Python built-in list (i.e., array) of strings


# This creates a Numpy array of 6 points. Each point is in 2D space. The second list is a builtin array, labels for the x values.

# In[3]:

print(X_train[5,0])
print(X_train[5,1])


# In[4]:

print(X_train[:, 0])
print(X_train[:, 1])


# Python has some cool slicing syntax. Here, we've grabbed the individual $x$ and $y$ values.

# In[5]:

plt.figure()
plt.scatter(X_train[:, 0], X_train[:, 1], s = 170, color = Y_train[:])
plt.show()


# This is our labelled training set. Now we can add a test point.

# In[8]:

X_test = np.array([3,4])


# In[9]:

plt.figure()
plt.scatter(X_train[:, 0], X_train[:, 1], s = 170, color = Y_train[:])
plt.scatter(X_test[0], X_test[1], s= 170, color = "green")
plt.show()


# So, that's our test point. Now we must run the nearest neighbour classifier.

# In[10]:

def dist(x, y):
    return np.sqrt(np.sum((x - y)**2))


# So now we have a distance function. If we have two points, such as:
# 
# $$x = (1, 1)$$
# $$y = (3, 4)$$
# 
# then (vectorization)
# 
# $$x - y = (-2, -3)$$
# $$(x - y)^2 = (4, 9)$$
# 
# The Python magic adds these elements to get $13$, and the square root of that is $3.60$, our distance.

# In[11]:

num = len(X_train) # number of points
distance = np.zeros(num) # array of num zeroes
for i in range(num):
    distance[i] = dist(X_train[i], X_test)
print(distance)


# Now we have the distance between the test point and every other point. To finish the classification, we just choose the closest point.

# In[12]:

min_index = np.argmin(distance) # index of nearest point
print(Y_train[min_index]) # label of that point


# So it's red! That was like 4-5 lines of code. With better idiomatic syntax, we can reduce this further.
