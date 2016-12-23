0.  Pneumonoultramicroscopicsilicovolcanoconiosis is one of the longest words in the English language; it's a lung condition. It has the largest possible length (45 chars) for a word in our spellchecker.
1.  It returns total resource usage (CPU time, RAM, stack usage, etc.) for the whole program, individual functions, threads, etc.
2.  16, all different measures of resource usage.
3.  We find the resource usage before and after something is run (eg. checking a single word, memory loading and unloading time) and calculate returns the time used by the operation. We are also constantly updating before and after with usage data. Plus, we don't need make a bunch of variables; the pointers are always THERE.
4.  The for-loop begins by getting the next character in the file. Then it checks if the character is alphanumeric (if it is it adds it to the current word being checked) and if it is too long (>45 chars; skips it if it is). Then it goes on to check if the char is a number, skipping if it is. In all other cases, the character must be a space! This means that the current word is over; main proceeds to spellcheck the word (while using calculate to find the time used) and prints if it is not in the dictionary. The cycle continues until the EOF.
5.  If we rely on `fscanf` then we can't check for non-alphabetic characters and whether the word is too long.
6.  The whole point is that we're checking if the word is misspelled, not modifying it. Const tells the function not to change the value the pointers references.
7.  My implementation uses a linked list organized in a hash table. The hash function I use makes the word lowercase, and then typecasts the first `char` of the word to an `int`, and finally subtracts `(int) 'a'` from it and adds 1. The struct I use for each node in the linked list is:

    ```c
    typedef struct node
    {
        char word[LENGTH + 1];
        struct node* next;
    }
    node;
    ```

8. It was pretty slow; *much, much* slower than the CS50 staff implementation.
9. I made it about 2-3 times faster by using a hash function I found online. By increasing the number of buckets, I halved made it 5-6 times faster, because linked lists take a long time to traverse. The average staff time (average time to spell check a file) was 0.133 seconds.
    | `NUM_BUCKETS` | Average time (`./bench`) |
    | :------------ | :----------------------- |
    | 10 | N/A |
    | 50 | N/A |
    | 100 | 8.269 |
    | 200 | |
    | 500 | |
    | 1000 | |
    | 2000 | 0.560 |
    | 5000 | 0.317 |
    | 10000 | 0.243 |
    | 20000 | 0.227 |
    | 25000 | 0.218 |
    | 35000 | 0.200 |
    | 40000 | 0.207 |
    | 45000 | 0.213 |
    | 50000 | 0.198 |
    | 100000 | 0.208 |
    | 200000 | 0.225 |
10.
