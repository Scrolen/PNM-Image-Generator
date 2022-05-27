# PNM Image Generator
This program was created to generate PNM (PPM,PGM,PBM) images. It makes use of the pnm_library.
To Compile:

    gcc -o main main.c libpnm.c
This will create an executable named main. In order to run the program, five arguments must be provided.

 1. Image type code (1 for pbm, 2 for pgm, 3 for ppm)
 2. Image Width
 3. Image Height
 4. Output Image Name (Must have extension added to name [.pbm, .pgm, .ppm])
 5. Image Format Code (0 for ASCII or 1 for Raw)

### Constraints on The Image Dimensions
-   The image width of *pbm* and *pgm* images must be divisible by 4 and greater than or equal to 4.
-   The image width of *ppm* images must be divisible by 6 and greater than or equal to 6.
-   The image height of all images must be divisible by 4 and greater than or equal to 4.

Example Usage:

    ./main 1 240 240 pbm_image.pbm 0
Output:

### Images that are generated
The Images generated for each type (ppm, pgm, pbm) all look a certain way. Below are examples of how each image type generated will look.
#### PBM Images:
#### PGM Images:
#### PPM Images:
