# Week 4

<!-- toc orderedList:0 depthFrom:1 depthTo:6 -->

- [Week 4](#week-4)
	- [Volkswagen](#volkswagen)
	- [Circularity & Recursion](#circularity-recursion)
	- [Swapping Variables](#swapping-variables)
	- [Debugging](#debugging)
	- [Memory](#memory)
		- [GetString() and friends](#getstring-and-friends)
- [Week 4, continued](#week-4-continued)
	- [Images](#images)
	- [Structs](#structs)
	- [Pointers](#pointers)
	- [Fixing Swap](#fixing-swap)
		- [Binky](#binky)

<!-- tocstop -->

## Volkswagen
*Volkswagen* cheated emissions testing with rigged software that detected when it was being tested and reduced exhaust.

They used a **defeat device**, and emitted 40x the nitrogen oxide limit.

What kind of software would they use? Probably something like this...

```
if being tested
  turn full emissions controls on
else
  don't
```

Lesson being, you can't trust any software.

## Circularity & Recursion
Remember the binary search pseudocode?

```
pick up phone book
open to middle of phone book
look at name
if "Smith" is among name
  call Mike
else if "Smith" is earlier in the book
  open to middle of left half of book
  go to line 3
else if "Smith" is later in book
  open to middle of right half of book
  go to line 3
else
  give up
```

C actually has a go to function, like we have in this pseudocode. However, it can interrupt the control flow of the program. Instead, we can do this:

```
pick up phone book
open to middle of phone book
look at name
if "Smith" is among name
  call Mike
else if "Smith" is earlier in the book
  search for Mike in left half of book
else if "Smith" is later in book
  search for Mike in right half of book
else
  give up
```

Since the problem is halved each time, we can recursively call the function without running forever.

*Note,* `i += j` *adds j to i.*

## Swapping Variables
To swap values, we need a temporary variable, `tmp`.

```{c}
void swap(int a, int b)
{
  int tmp = a;
  a = b;
  b = tmp;
}
```

You can also use the bitwise operator `XOR` and swap 8-bit ints.

```{c}
void swap(int a, int b)
{
  a = a ^ b;
  b = b ^ a;
  a = a ^ b;
}
```

But wait... if we use `swap` to swap two values in `main`, it just swaps its duplicates! How do we fix this? We'll see this later.

## Debugging
Let's familiarize ourselves with **GDB**, the GNU project debugger.

Some things to notice:
- **local variable** - the variables in our program, and their values in realtime
- **breakpoints** - lines to pause at in the program
- **call stack** - what functions are running at the moment?

## Memory
- **stack** - a chunk of RAM that functions have access to when called

*Remember, variables are delimited by* `\0`*!*

### GetString() and friends
`GetString()` is actually just a pointer! It doesn't store the actual string, just its address in the memory of the computer.

**The training wheels are off!!** (No more `{c}s50.h`)

Really, `string` doesn't exist, instead we'll use `{c}har*`.

# Week 4, continued

## Images
Images are made up of *pixels*; enhancing is actually pretty much useless.

An example file format is *bitmap*, wherein a series of 1's and 0's translate to an image.

![bitmap, smiley face](http://www.brackeen.com/vga/images/img00023.gif)

However, this image lacks color. The best way to implement color is to use more than just one bit.

For examples, JPEGS. These use *RGB values*. A JPEG's signature is always `255 216 255`.

| RGB    | 255 | 216 | 255 |
| :----- | :-- | :-- | :-- |
| Binary | 1111 1111 | 1101 1000 | 1111 1111 |
| Hex    | f f | d 8 | f f |
|        | 0xff | 0xd8 | 0xff |

All file formats are binary under the hood.

## Structs
Variables often have other data associated with them. For example, a list of students may be stored with a dorm and an ID.

We could keep separate arrays, like this:

```{c}
string names[3];
string dorms[3];
int ids[3];
```

This is unwieldy. This is where structs come in.

```{c}
typedef struct
{
    string name;
    string dorm;
}
student;
```

We define our own datatype `student`! Normally this would be stored in a header file, and then included like `#include "something.h"` (because it's in your own directory).

*A quick note: constants are defined as* `#define CONSTANT VALUE`*.*

Now we have this:

```{c}
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

// number of students
#define STUDENTS 3

int main(void)
{
    // declare students
    student students[STUDENTS];

    // populate students with user's input
    for (int i = 0; i < STUDENTS; i++)
    {
        printf("Student's name: ");
        students[i].name = GetString();

        printf("Student's dorm: ");
        students[i].dorm = GetString();
    }

    // save students to disk
    FILE* file = fopen("students.csv", "w");
    if (file != NULL)
    {
        for (int i = 0; i < STUDENTS; i++)
        {
            fprintf(file, "%s,%s\n", students[i].name, students[i].dorm);
        }
        fclose(file);
    }

    // free memory
    for (int i = 0; i < STUDENTS; i++)
    {
        free(students[i].name);
        free(students[i].dorm);
    }
}
```

Definitions:

- `students[i].name` - store the property `name` of the `student`
- `FILE*` - a file
- `fopen("students.csv", "w")` - open `students.csv` and write to the file
  - `"r"` - read
  - `"a"` - append
- `NULL` - general error
- `fprintf` - print to a file
- `free` - free memory

## Pointers
Remember the mom comparision that failed earlier? Here is the fixed version:

```{c}
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // get line of text
    printf("Say something: ");
    char* s = GetString();

    // get another line of text
    printf("Say something: ");
    char* t = GetString();

    // try to compare strings
    if (s != NULL && t != NULL)
    {
        if (strcmp(s, t) == 0)
        {
            printf("You typed the same thing!\n");
        }
        else
        {
            printf("You typed different things!\n");
        }
    }
}
```

Here's a new function: `strcmp`. It compares strings' actual values, not just the addresses.

Remember: if you have two pointers pointing to the same value, and if you change the value of one pointer, then the other pointers as well.

To avoid this, you need to duplicate the value that the pointer is pointing to.

```{c}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // first pointer
    char* pointer1 = "mom";

    // second pointer; we initialize it with 4 bytes
    char* pointer2 = malloc((strlen(pointer1) + 1) * sizeof(char));

    // for good measure
    if (pointer2 == NULL)
    {
      return 1;
    }

    // duplicate the bytes
    for (int i = 0, n = strlen(pointer1); i <= n; i++)
    {
        pointer2[i] = pointer1[i];
    }

    /* do other stuff... */
}
```

Here's a different way to duplicate the bytes in the loop:

```{c}
// pointer2[i] = pointer1[i];
*(pointer2 + i) - *(pointer1 + i);
```

In this case, the `*` is the dereference operator, saying **go to the actual value**.

The `+ i` is pointer arithmetic; it's just moving forward in the memory.

## Fixing Swap
Remember how the original implementation of `swap` only changed the copies that were contained within that one function? No we can change the original values with pointers!

```{c}
void swap(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
```

Improved:

```{c}
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

Now, the addresses of `x` and `y` need to be passed. So, we do this:

```{c}
swap(&x, &y);
```

### Binky

REMEMBER TO GIVE THE POINTER A POINTEE!

```{c}
int main(int argc, char *argv[]) {
    int* x;
    x = malloc(sizeof(int));
    *x = 42;
}
```
