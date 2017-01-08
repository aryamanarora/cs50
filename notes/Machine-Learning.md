---
date: January 7, 2017
---

# Machine Learning

- We are now transitioning to a higher-level language, Python. It can be used to write a backend of a web server. Python can also be very powerful in data analysis, especially machine learning.
- Python is extremely readable. Even if you don't know it, you can read it. In fact, it is often compared to pseudocode, making it easy to learn.

## What is Machine Learning?

- uses
    - Machine learning is more than just robots or artificial intelligence. Some of its applications are search engines, image recognition, voice recognition, and natural language processing.
    - algorithms, applications
    - images, language; what we're doing
- **input to output**
    - what is in an image?
    - what is a text about?
    - infer hidden structures in data
        - *we don't know the structure!*
        - that's the algorithm's job
        - **training data** - input and output stuff

## Image Classification

- *labeled training set* - points with labels
    ```
    <--•--•-•--------------•-•-•-•-->
       0  0 0              ? 6 6 6
    ```
    - *test point* - what does it represent?
    - **minimal distance** - what is it closer to? nearest neighbour?
    - **nearest neighbour classifier**
        - also in two dimensions
        - ![](http://www.emgu.com/wiki/images/KNearest.png)
- can we map an image on a point in space?
    - **yes!**
    - 64-dimensional space (8x8)
    - $d = \sqrt{\delta{x}^2 + \delta{y}^2 + ... + \delta{n}^2}

### Supervised Learning
- two categories, supervised has labels, unsupervised does not
- see notebooks for more

### Deep Learning
The nearest neighbour classifier is not that great with actual image classification. It has a 30% accuracy. The reasons are:

- they are colored images
- 32x32 size
- more options (10)
- viewpoint variation, etc.

It's a lot harder. Most sophisticated algorithms group pixel togethers, interpolating between them. The hierarchy of feauture representation in *deep learning* is:

0. Pixels
1. Edges
2. Object parts
3. Objects

This technology relies on neural networks, and it's been a game changer. It was proposed in the 80s but has really been put to use in the last 5 years, thanks to new technology. Some tools for deep learning are:

- *TensorFlow* by Google in Python
- *Deep Dream Generator*

Deep learning achieves **95%** accuracy of the CIFAR-10 database, almost as good as a human. Is this good enough though? Depends. What about self-driving cars? Autopilot in Tesla cars for example rely on deep learning too. The 5% can be dangerous.

## Text Clustering
- algroithm that groups texts together
