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

<img width="239" alt="Screen Shot 2022-05-27 at 11 37 44 AM" src="https://user-images.githubusercontent.com/74621126/170732525-cd458e63-4853-47de-94ac-a0a316058075.png">

### Images that are generated
The Images generated for each type (ppm, pgm, pbm) all look a certain way. Below are examples of how each image type generated will look. Note: Images in Readme are screenshots of original images since Readme does not support .pbm, .pgm, .ppm
#### PBM Image:

    ./main 1 240 240 pbm_image.pbm 0

<img width="239" alt="Screen Shot 2022-05-27 at 11 37 44 AM" src="https://user-images.githubusercontent.com/74621126/170732525-cd458e63-4853-47de-94ac-a0a316058075.png">

#### PGM Image:

    ./main 2 240 240 pgm_image.pgm 0
 
<img width="239" alt="Screen Shot 2022-05-27 at 11 39 26 AM" src="https://user-images.githubusercontent.com/74621126/170732828-b8c875d1-e60a-4604-9766-1f619fd3929b.png">

#### PPM Image:

    ./main 3 240 240 ppm_image.ppm 0

<img width="240" alt="Screen Shot 2022-05-27 at 11 41 14 AM" src="https://user-images.githubusercontent.com/74621126/170733049-55060e54-87f1-4cb7-a570-e01559e8ad6f.png">

 3 other Images are also generated when generating PPM images which are the 3 gray images (Red, Green, Blue)

