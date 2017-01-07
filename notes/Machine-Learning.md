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
