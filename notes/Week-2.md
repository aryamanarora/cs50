# Week 2

## Bugs
**Bugs** are mistakes in programs that affect how they run, sometimes breaking them. Here's an example of a buggy program:

~~~~c
/**
 * Prints 10 z's.
 */

#include <stdio.h>

int main(void)
{
  for (int i = 0; i <= 10; i++)
    printf("z");
}
~~~~

It actually prints out 11 z's, because of our mistake in the for loop; we should be using `<`, because it is zero-indexed.

By the way, this is a **one-off error**.

## Functions
We can go beyond `main` to build our own functions. Chances are that you'll only need `main` for a small project; as your project gets bigger, defining other functions will make coding easier by abstracting away the hard stuff. *Here's a simple example*:

~~~~c
#include <cs50.h>
#include <stdio.h>

// prototype
void PrintName(string name);

int main(void)
{
    printf("Your name: ");
    string s = GetString();
    PrintName(s);
}

/**
 * Says hello to someone by name.
 */
void PrintName(string name)
{
    printf("hello, %s\n", name);
}
~~~~

There are other examples of this; go to [CS50's online notes](http://cdn.cs50.net/2015/fall/lectures/2/m/notes2m/notes2m.html#functions) for more. This should be sufficient for now.

There are two functions here: `main` and `PrintName`. `PrintName` appears to take a `string` and print it to `stdout` as "hello, `string`". `main` asks for a name and then invokes `PrintName`.

Notice we called the `PrintName` twice. The first one is the **prototype**, to tell `clang` that the function exists somewhere.

Also notice that it is `void PrintName`, not `int PrintName`. In this case, the **return type** of `PrintName` is void; it returns nothing.

### Scope
~~~~c
#include <cs50.h>
#include <stdio.h>

// prototype
int GetPositiveInt();

int main(void)
{
    int n = GetPositiveInt();
    printf("Thanks for the %i!\n", n);
}

/**
 * Gets a positive integer from a user.
 */
int GetPositiveInt(void)
{
    int n;
    do
    {
        printf("Please give me a positive int: ");
        n = GetInt();
    }
    while (n < 1);
    return n;
}
~~~~

In this example, there are two `int n`s. How!? Well, the **scope** of `n` in both cases is different; there's one that's restricted to `main` and another restricted to `GetPositiveInt`. This way, they don't cause bugs.

We can also declare *global variables* by putting them outside of any braces, but this isn't good practice.

## Strings
A **string** is actually just an array of chars.

| char [| 1  | 2  | 3  | 4  | 5  | 6  | ]  |
| :-    | :- | :- | :- | :- | :- | :- | :- |
|       | s  | t  | r  | i  | n  | g  |    |

You can access each individual character. Let's look at an example.

~~~~c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // get line of text
    string s = GetString();

    // print string, one character per line
    for (int i = 0; i < strlen(s); i++)
    {
        printf("%c\n", s[i]);
    }
}
~~~~

`strlen` gets the length of the string `s`. The loop appears to print out each letter one by one on a new line, using regular **array notation**, `s[i]`.

So, if we use our first example, `string`, `s[0]` would be `s`, `s[1]` would be `t`, and so on.

## Typecasting
**Typecasting** is converting one data type to another. For example, the `char` A is equivalent to the `int` 65, its ASCII representation.

So, this code

~~~~c
#include <stdio.h>

int main(void)
{
    int i = 65;
    printf("%c: %i\n", (char) i, i);
}
~~~~

would print out

~~~~bash
A: 65
~~~~
