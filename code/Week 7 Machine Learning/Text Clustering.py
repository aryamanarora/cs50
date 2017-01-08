
# coding: utf-8

# # Unsupervised Training
# 
# In *unsupervised training*, you just group. There are no structures, just abstract categories. Our algorithm is k-means.
# 
# Grouping images is not hard; just pixels in higher-dimensional space. What about text?
# 
# - words (minus stop words), the bags of word interpretation
#     - divide by number of words in the string

# In[1]:

import numpy as np
import matplotlib.pyplot as plt
get_ipython().magic('matplotlib notebook')


# In[3]:

X = np.array([[1,1], [2,2.5], [3,1.2], [5.5,6.3], [6,9], [7,6], [8,8]])


# In[4]:

plt.figure()
plt.scatter(X[:,0], X[:,1], s = 170, color = "black")
plt.show()


# In[5]:

# Import k-means algorithm
from sklearn.cluster import KMeans


# In[6]:

k = 2
kmeans = KMeans(n_clusters = k)
kmeans.fit(X)
centroids = kmeans.cluster_centers_
labels = kmeans.labels_


# In[7]:

colors = ['r.', 'g.']
plt.figure()
for i in range(len(X)):
    plt.plot(X[i,0], X[i,1], colors[labels[i]], markersize = 30)
plt.scatter(centroids[:,0], centroids[:,1], marker = 'x', s = 300, linewidths = 5)
plt.show()


# What about $k = 3$?

# In[8]:

k = 3
kmeans = KMeans(n_clusters = k)
kmeans.fit(X)
centroids = kmeans.cluster_centers_
labels = kmeans.labels_

colors = ['r.', 'g.', 'b.']
plt.figure()
for i in range(len(X)):
    plt.plot(X[i,0], X[i,1], colors[labels[i]], markersize = 30)
plt.scatter(centroids[:,0], centroids[:,1], marker = 'x', s = 300, linewidths = 5)
plt.show()


# ## Clustering Documents

# In[9]:

corpus = ["My name is Aryaman and I'm the best dabber ever.",
          "When I grow up I'm gonna dab like Aryaman",
          "Amay is a big boy.",
          "Big boys like to dab a lot.",
          "Words are weird, dab dab."]


# In[12]:

from sklearn.feature_extraction.text import CountVectorizer
count_vect = CountVectorizer(stop_words = 'english')
Z = count_vect.fit_transform(corpus)
Z.todense()


# In[13]:

vocab = count_vect.get_feature_names()
print(vocab)


# In[14]:

from sklearn.feature_extraction.text import TfidfVectorizer
vectorizer = TfidfVectorizer(stop_words = 'english')
X = vectorizer.fit_transform(corpus)
X.todense()


# In[15]:

k = 2
from sklearn.metrics.pairwise import cosine_similarity
dist = 1 - cosine_similarity(X)
model = KMeans(n_clusters = k)
model.fit(X)


# In[16]:

print("Top terms per cluster:\n")
order_centroids = model.cluster_centers_.argsort()[:, ::-1]
terms = vectorizer.get_feature_names()
for i in range(k):
    print("Cluster %i:" % i, end = '')
    for ind in order_centroids[i, :3]:
        print(' %s,' % terms[ind], end = '')
    print("")


# ## IMDB Synopses

# In[17]:

# Import the data set into a Panda data frame
import pandas as pd
from io import StringIO
import requests

act = requests.get('https://docs.google.com/spreadsheets/d/1udJ4nd9EKlX_awB90JCbKaStuYh6aVjh1X6j8iBUXIU/export?format=csv')
dataact = act.content.decode('utf-8') # To convert to string for Stringio
frame = pd.read_csv(StringIO(dataact))


# In[18]:

print(frame)


# In[19]:

# Loop over each synopsis and append its content to a list of string named 'corpus' 
corpus = []
for i in range(0, frame["Synopsis"].size):
    corpus.append(frame["Synopsis"][i])


# In[20]:

# Create tf–idf matrix
from sklearn.feature_extraction.text import TfidfVectorizer
vectorizer = TfidfVectorizer(stop_words = 'english', min_df = 0.2)
# min_df = 0.2 means that the term must be in at least 20% of the documents
X = vectorizer.fit_transform(corpus)


# In[27]:

k = 2 # Define the number of clusters in which we want to partion our data
# Define the proper notion of distance to deal with documents
from sklearn.metrics.pairwise import cosine_similarity
dist = 1 - cosine_similarity(X)
# Run the algorithm kmeans
model = KMeans(n_clusters = k)
model.fit(X);


# In[28]:

no_words = 4 # Number of words to print per cluster
order_centroids = model.cluster_centers_.argsort()[:, ::-1] # Sort cluster centers by proximity to centroid
terms = vectorizer.get_feature_names()
labels = model.labels_ # Get labels assigned to each data

print("Top terms per cluster:\n")
for i in range(k):
    
    print("Cluster %d movies:" % i, end='')
    for title in frame["Title"][labels == i]:
        print(' %s,' % title, end='')
    print() #add a whitespace

    print("Cluster %d words:" % i, end='') 
    for ind in order_centroids[i, :no_words]:
        print (' %s' % terms[ind], end=','),
    print()
    print()


# Machine learning is forging ahead, look at AlphaGo and Google! Deep learning can do so much humans can.
