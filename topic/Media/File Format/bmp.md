---
categories:
  - Singles
title: BMP file format
date: 2023-03-01T14:06:42+08:00
draft: false
include_toc: true
url-root: bmp
---

# BMP file format

 *image file 1440x900.bmp* ![1440x900.bmp](1440x900.bmp) 
```bash
-rw-rw-r-- 1 lull lull 3888054 Mar  1 14:08 1440x900.bmp
-rw-rw-r-- 1 lull lull 3888000 Mar  1 14:08 1440x900.rgb
```

    3888000 = 1440*900*3

.rgb 是裸rgb数据，在yuvview 指定 BGR8 1440*900 之后可以看到如.bmp一样的正常图像

<br/>
开始分析 .bmp 文件
八进制编辑器打开bmp，我们只关注 前54个字节

| Offset hex | Offset dec |  Size   | Example | Purpose |
| :--------: | :--------: | :-----:| :-----: | :--: |
|     00     |     0       | 2 bytes | 0x42 0x4D| The [header field](https://en.wikipedia.org/wiki/File_format#Magic_number) used to identify the BMP and DIB file is `0x42 0x4D` in [hexadecimal](https://en.wikipedia.org/wiki/Hexadecimal), same as `BM` in ASCII. The following entries are possible:BMWindows 3.1x, 95, NT, ... etc.BAOS/2 struct bitmap arrayCIOS/2 struct color iconCPOS/2 const color pointerICOS/2 struct iconPTOS/2 pointer |
|     02     |     2      | 4 bytes |  0xB6533B(小端序3888054)|              The size of the BMP file in bytes               |
|     06     |     6      | 2 bytes |  | Reserved; actual value depends on the application that creates the image, if created manually can be 0 |
|     08     |     8      | 2 bytes |  | Reserved; actual value depends on the application that creates the image, if created manually can be 0 |
|     0A     |     10     | 4 bytes |0x36  | The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found. |

 00 处指出头类型为 Windows Bitmap Header
 
 0A处指出的头长度 0x36=54， 这就是这个bmp文件头的长度
 
 <br/>
 于是我们接着看 Windows Bitmap Header

| Offset (hex) | Offset (dec) | Size (bytes) |      | [Windows BITMAPINFOHEADER](https://en.wikipedia.org/wiki/BMP_file_format#cite_note-bmp-2) |
| :----------: | :----------: | :----------: | ---- | :----------------------------------------------------------: |
|      0E      |      14      |      4       |  0x28=40    |            the size of this header, in bytes (40)            |
|      12      |      18      |      4       | 0xA0050000=1440 |         the bitmap width in pixels (signed integer)          |
|      16      |      22      |      4       | 0x84030000=900 |         the bitmap height in pixels (signed integer)         |
|      1A      |      26      |      2       | 0x0100     |            the number of color planes (must be 1)            |
|      1C      |      28      |      2       | 0x1800=24 | the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32. |
|      1E      |      30      |      4       |  | the compression method being used. See the next table for a list of possible values |
|      22      |      34      |      4       | 0x80533B00=1440*900=3888000 | the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps. |
|      26      |      38      |      4       |      | the horizontal resolution of the image. (pixel per metre, signed integer) |
|      2A      |      42      |      4       |      | the vertical resolution of the image. (pixel per metre, signed integer) |
|      2E      |      46      |      4       |      | the number of colors in the color palette, or 0 to default to 2*n* |
|      32      |      50      |      4       |      | the number of important colors used, or 0 when every color is important; generally ignored |


Bitmap的头分两部分： 
* Bitmap file header: 12 字节
* Window Bitmap Header: 40 字节
1. 第一部分的头长度是标准，其中的前两个字段指定接下来的第二段头的标准
2. 第二段头中指定该段头的长度

两部分加起来就是.bmp文件（带有bitmap头）相对于 原始rgb文件的 增量大小


**参考**
[BMP file format wiki](https://en.wikipedia.org/wiki/BMP_file_format#:~:text=A%20device%2Dindependent%20bitmap%20(DIB,independent%20part%20of%20the%20name).)

