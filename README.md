This code print the 50 pixels with highest pixel values from an image.

There is a 16-bit grayscale image example in the same folder. (Example.tif)
This code compiles and runs under Ubuntu 14.04 with libtiff.

Assumption:
1. We deal with a TIFF image.
2. If there are several 50th largest values, we pick the later pixels (with higher y position then higher x position).
3. The width, height and the number of pixels are under 2^32.

To run the code:
```
gcc readimage.c -ltiff -o read
./read Example.tif
```

The Result.png shows this code runs and prints the result.

Chengtao Wang, 10/18/2016
