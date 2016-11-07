---
title: Week 5
author: Aryaman Arora
date: November 5, 2016
abstract: More about pointers and memory, and some new data structures!
---

# Week 5

<!-- toc orderedList:0 depthFrom:1 depthTo:6 -->

- [Week 5](#week-5)
	- [Pointers, continued](#pointers-continued)
		- [Aside about some syntax](#aside-about-some-syntax)
	- [Memory](#memory)
	- [Data Structures](#data-structures)
		- [Stacks and Queues](#stacks-and-queues)
- [Week 5, continued](#week-5-continued)
	- [Searching Linked Lists](#searching-linked-lists)
	- [Stacks](#stacks)

<!-- tocstop -->

## Pointers, continued

```{c}
int main(void)
{
    // initialize two addresses of ints
    int* x;
    int* y;

    // give me some memory for x
    x = malloc(sizeof(int));

    *x = 42;
    *y = 13;

    y = x;
    *y = 13;
}
```

Behold, `scanf`! This is the actual `GetString()`, `GetInt`, etc.

```{c}
int x;
scanf("%i", &x);
```

Same for:

```{c}
char* x;
scanf("%s", x)
```

Here, `x` is already a pointer, so we don't need `&x`.

But... this will cause a segmentation fault! We might alter something that we don't have access to in memory.

Even if we use, say `char x[16]`, we might need more memory. So, we, might use `char x[1000]`. But what if we need more? This can get out of hand quickly, and is wasteful.

This is where `realloc` comes in, and good ol' `cs50.h`. There's a lot hidden in there[^notes]. Basically, the library just adds memory iteratively as it needs it.

### Aside about some syntax

An `unsigned int` only uses positive numbers (and 0).

`*=` multiples the number by some factor. Other forms exist, like `/=`.

`sscanf` basically "analyzes" a line.

## Memory
All the code I've written so far is *buggy*. I've been getting memory but not `free()`ing it (until pset4)! This is not a big deal since all the programs that we've made have been small, but this can slow down the computer in bigger programs.

How do you find memory leaks? `valgrind`!

```
valgrind --leak-check=full ./program
```

Here's an example of a buggy program:

```{c}
int f(void)
{
    int* x = malloc(10 * sizeof(int));
    // uh oh ... zero-indexing!
    x[10] = 0;
    // hey, we aren't freeing x!
}

int main(void)
{
    f();
    return 0;
}
```

Hint: `valgrind` will help you.

Fixed:
```{c}
int f(void)
{
    int* x = malloc(10 * sizeof(int));
    x[9] = 0; // allowed
    free(x); // no memory leaks
}

int main(void)
{
    f();
    return 0;
}
```

![xkcd Pointers](https://imgs.xkcd.com/comics/pointers.png)

## Data Structures
Arrays are good in C for storing data, but *you can't change the size of the array* (unlike some higher-level languages).

Instead, we can start making our own data structures. This is where **linked lists** come in.

```{mermaid}
graph LR
subgraph one
    first --- ptr1
end
subgraph two
    second --- ptr2
end
subgraph three
    third --- ptr3
end
head --> first
ptr1 --> second
ptr2 --> third
ptr3 --> NULL
```

Let's start with the first rectangle. How would we implement this? Structs!

```{c}
typedef struct node
{
    int n;
    struct node* next;
}
node;
```

Here, we're recursively defining a node. (The reason we're using `struct node*` is because C reads top to bottom and left to right, and it doesn't node what a `node` is until it reads the whole thing).

To insert a new node, you can just make the last node point to your new node. If you want to insert in the middle, make the new node point at the first node, and *then* make `head` point to the new node. This way, we don't lose the rest of the list.

This is amazing! Some cons though:
- thrice the size (pointer (8 bytes) + `int`)
- traverse list one by one; give up bracket `[]` notation

### Stacks and Queues

(Trust me, you'll need this) Think about stacks of trays; this is a LIFO (last in first out) data structure.

Further, there are queues, which are FIFO (first in first out).

# Week 5, continued
Let's look at linked list against: what's so great about them? **They can be dynamically resized**.

## Searching Linked Lists
```{c}
typedef struct node
{
    int n;
    struct node* next;
}
node;

// make some list...

bool search(int n, node* list)
{
    node* ptr = list;
    while (ptr != NULL) // NULL demarcates end of list
    {
        if (ptr->n == n) // if this matches our number
        {
            return true;
        }
        ptr = ptr -> next // go to next node
    }
    return false;
}
```

## Stacks
```{c}
typedef struct
{
    int numbers[CAPACITY]; // array of some numbers
    int size; // size?
}
stack;
```

Stacks have two main functions: `push` and `pop`. **`push`** adds something to the stack at the leftmost part and increments size.

**`pop`** removes the last added value ($\text{size} - 1$). Actually, we reduce size, but we don't remove anything; the computer *just forgets*.

What if you go beyond `CAPACITY`? Whelp, nothing you can do.

[^notes]: [Official Notes](http://cdn.cs50.net/2015/fall/lectures/5/m/notes5m/notes5m.html)
