0.  GIF files only support 256 colors. BMP and JPEG 16.8 million (2<sup>24</sup>) colors, and generally so does PNG. PNG can support up to 2<sup>48</sup> (more than 280 trillion) colors, however.
1.  GIFs support animation.
2.  Lossless formats lose no image quality when compressed, while lossy formats do.
3.  JPEG and GIF are lossy formats.
4.  The file isn't actually erased, but is made overwritable. The data can still be recovered, even when overwritten. Sometimes, the file's name is merely removed from the directory.
5.  The best way is to destroy the hard drive or render it unreadable. The next best method is to overwrite the files with random patterns, making it unrecoverable.
6.  `<stdint.h>` provides fixed-width integers type definitions. Instead of saying `int i = 1`, you could say `int8_t i = 1`, specifying that you need 8 bits of memory for `i` and that `i` is a signed integer, meaning it can only be 0 or greater.
7.  It can be used to make sure that you have enough memory for your integers. This can be useful when initializing very large numbers, or if you only need positive numbers for a certain integer (in which case `INT_MAX` is twice as large).
8.  A `BYTE` is 8 bits (1 byte), a `DWORD` is 32 bits (4 bytes), a `LONG` is 32 bits (4 bytes), and a `WORD` is 16 bits (2 bits).
9.  The first two bytes of any BMP are `BM`, represented as `0x42 0x4d` in hex and `66 77` is decimal.
10. `biSize` is the number of bytes needed for the `BITMAPINFOHEADER` structure, while `bfSize` is the size of the actual bitmap file in bytes.
11. It means that the bitmap file is encoded from top to bottom and left to right.
12. `biBitCount` in the `BITMAPINFOHEADER` struct encodes the number of bits per pixel.
13. There are several reasons. The filename may be invalid in the OS (e.g. it includes \n on Windows). The user may not have permissions to the file, or it might be read-only.
14. The third argument to `fread` is the number of objects (or structs) to be read. In our case, we read the `BITMAPINFOHEADER` and then the `BITMAPFILEHEADER`, which are individual structs.
15. (4 - (3 * 3) % 4) % 4 = (4 - 9 % 4) % 4 = (4 - 1) % 4 = **3**
16. It moves the program to a certain point in the file.
17. It sets the start point of the movement to the current position in the file.
18. Rick Astley! Great rickroll...
