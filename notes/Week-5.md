---
title: Week 5
author: Aryaman Arora
date: November 5, 2016
subtitle: More about pointers and memory, and some new data structures!
output:
  tufte::tufte_html:
    highlight: pygments
---

```{r setup, include=FALSE}
knitr::opts_chunk$set(eval=FALSE)
```

## Pointers, continued

```{marginfigure}
An `unsigned int` only uses positive numbers (and 0).

`*=` multiples the number by some factor. Other forms exist, like `/=`.

`sscanf` basically "analyzes" a line.
```

```{c}
##include <stdio.h>

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

***

Let's look at linked lists agains: what's so great about them? **They can be dynamically resized**.

### Searching Linked Lists
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

### Stacks
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

What if you go beyond `CAPACITY`? Whelp, nothing you can do, since you can't resize this array. Here's a better implementation:

```{c}
typedef struct
{
		int* numbers;
		int size;
}
stack;
```

Here, we just store the address of the first number. When invoking this, however, you will need `malloc`.

### Queues
```{c}
typedef struct
{
		int front;
		int numbers[CAPACITY]
		int size;
}
queue;
```

enqueue
: add to the leftmost available bit

dequeue
: remove first value, decrement `size`, increment `front`

The `%` (modulo) operator helps to implement circularity in the queue.

Here's a dynamic implementation:

```{c}
typedef struct
{
		int front;
		int* numbers;
		int size;
}
queue;
```

## Memory and Heaps
[](http://i.imgur.com/ryoTZfk.png)

When you are calling a function, it is added to the stack; it gets a slice of its own memory.

But guess what; there's more memory at the top of the memory! This is the heap. When you call `malloc` you get some memory from the heap.

But isn't this dangerous? The stack and heap might clash in a computer with finite memory.

### Buffer Overflow
```{c}
##include <string.h>

void f(char* bar) // takes one string, bar
{
		char c[12]; // 12-byte array
		strncpy(c, bar, strlen(bar)); // copy bar into c
}

int main (int argc, char* argv[])
{
		f(argv[1]); // gives f argv[1]
}
```

This is all fine if `bar` is less than 11 chars (+ `\0`). But what if we use something longer? Well, since this is in the heap, it will overwrite `*bar` (which is below it). Furthermore, C also stores the return address of the functions called in memory. What if the attacker is smart and is able to rewrite this address and access other memory!

This is a **buffer overflow attack**.

## Linked Lists
Back to the horribly inefficient $O(n)$ linked list. There is a way to achieve $O(log n)$ and even $O(1)$ efficiency though...

In a traditional array, you would use binary search. This is a **tree**, and is logarithmic.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/d/da/Binary_search_tree.svg/200px-Binary_search_tree.svg.png)

```{c}
typedef struct node
{
		int n;
		struct node* left;
		struct node* right;
}
node;

bool search(int n, node* tree)
{
		if (tree == NULL)
		{
				return false;
		}
		else if (n < tree->n)
		{
				return search(n, tree->left)
		}
		else if (n > tree->n)
		{
				return search(n, tree->right)
		}
		else
		{
				return true;
		}
}
```

## Compression
Everything can be compressed, especially images and video. But what about text!!?

In ASCII, each letter is 8 bits, even for the less popular letters. Why not encode popular letters as smaller values?

This exists: morse code. However, this isn't efficient; it's ambiguous because you need spaces/gaps.

```
    (1.0)
   /    \
0 /      \ 1
 /        \
(0.55)       \
/    \        \
0 /      \ 1      \
/        \        \
(0.35)       \        \
/    \        \        \
0 /      \ 1      \        \
/        \        \        \
(0.2)        \        \        \
/   \         \        \        \
0 /     \ 1       \        \        \
/       \         \        \        \
(0.1)     (0.1)     (0.15)    (0.2)    (0.45)
B         C         D         A        E
```

### Hash Tables
A hash table is just a table of values; look at input and categorize it.

linear probing
: one value for the hash table; linear

separate chaining
: each value in the table is a linked list!

## Tries
A trie (retrieval) is a tree. Each child is an array however.

![](images/download.png)

This is $O(1)$! The search time is proportional to length of the input. This is *the holy grail of running time*.


[^notes]: [Official Notes](http://cdn.cs50.net/2015/fall/lectures/5/m/notes5m/notes5m.html)
