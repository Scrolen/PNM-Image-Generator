#include "libpnm.h"
#include <string.h>


int program1(struct PBM_Image *, int width, int height, char *, int format);
int program2(struct PGM_Image *, int width, int height, char *, int format);
int program3(struct PPM_Image *, int width, int height, char *, int format);

int main(int argc, char *argv[]){

    struct PBM_Image pbmImage;
    struct PGM_Image pgmImage;
    struct PPM_Image ppmImage;
    
    int type, width, height, format;

    char * imgName = argv[4];

    if(argc != 6)
    {
        printf("Error: Incorrect number of arguments provided. Five arguments are required.");
        return 0;
    }

    type = atoi(argv[1]);
    width = atoi(argv[2]);
    height = atoi(argv[3]);
    format = atoi(argv[5]);


    /* COMMAND LINE ARGUMENTS ERROR HANDLING */

 
    if (type != 1 && type != 2 && type != 3)
    {
        printf("Error: Image type code must be 1, 2, or 3. (1 for pbm, 2 for pgm, or 3 for ppm");
        return 0;
    }

    if(type == 1 || type == 2)
    {
        if (width < 4 || width % 4 != 0)
        {
            printf("Error: Image width of pbm and pgm images must be divisible by 4 and greater than or equal to 4");
            return 0;
        }
    }
    if (type == 3)
    {
        if (width < 6 || width % 6 != 0)
        {
            printf("Error: Image width of ppm images must be divisible by 6 and greater than or equal to 6");
            return 0;
        }
        
    }
    if (height < 4 || height % 4 != 0)
    {
        printf("Error: Image height must be divisible by 4 and greater than or equal to 4.");
        return 0;
    }
    
    if (format != 0 && format != 1)
    {
        printf("Error: Image format must be 0 for ASCII or 1 for raw.");
        return 0;
    }

    /* END OF ARGUMENTS ERROR HANDLING*/


    // If Else block to determine what function to use
    if (type==1)
    {
        program1(&pbmImage, width, height, imgName, format);

    }else if (type==2)
    {
        program2(&pgmImage, width, height, imgName, format);
        
    }else if (type==3)
    {
        program3(&ppmImage, width, height, imgName, format);
    }


    return 0;
}


/* FUNCTIONS FOR PROGRAMS */

int program1(struct PBM_Image * pbmImage ,int width, int height, char * name, int format){

    int i, j;
    int z = height/4;
    int y = width/4;

    float slope, rise;


    create_PBM_Image(pbmImage, width, height);

    // Section that draws the black background
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width ; j++)
        {
            pbmImage->image[i][j] = 1;
        }
        
    }
    // Section that draws the white box
    for (i = z; i < height-z; i++)
    {
        for (j = y; j < width-y ; j++)
        {
            pbmImage->image[i][j] = 0;
        }
        
    }

    /*Drawing the 2 diagonal Lines*/
    if (width >= height)   // if width is greater than height loop along width
    {
        slope = (float)z/(float)y;
        rise = z;

        for (i = 0; i < y*2; i++)
        {
            pbmImage->image[(int)rise][i+y] = 1;
            pbmImage->image[(int)rise][width-y-i-1] = 1;
            rise = rise + slope;
    
        }

    }
    else if (height > width) // if height is greater than width loop along height
    {
        slope = (float)y/(float)z;
        rise = y;

        for (i = 0; i < 2*z; i++)
        {
            pbmImage->image[i+z][(int)rise]=1;
            pbmImage->image[height-z-i-1][(int)rise]=1;

            rise = rise + slope;
            
        
        }

    }
    /*End of drawing the 2 diagonal lines*/
    
    save_PBM_Image(pbmImage, name, format); //Save the generated image
    free_PBM_Image(pbmImage);  //Free memory from the image

    return 0;
}


// Function for drawing program 2
int program2(struct PGM_Image * pgmImage, int width, int height, char * name, int format){

    int i, j;
    int z = height/4;
    int y = width/4;

    float grayIncH, grayIncV, gray, slope, rise;

    create_PGM_Image(pgmImage, width, height, 255);


    // Section that draws the black background
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width ; j++)
        {
            pgmImage->image[i][j] = 0;
        }
        
    }

    slope = (float)z/(float)y; // slope
    rise = z;
    grayIncV = 255/(float)y; // value to increment gray color by

    gray = 255;



    // For loop to draw bottom and top triangle
    for (i = y; i < width-(2*y); i++)
    {
        for (j = rise; j < height-rise ; j++)
        {
            pgmImage->image[j][i] = gray;
            pgmImage->image[j][width - i - 1] = gray;
        }

        rise = rise + slope;
        gray = gray - grayIncV;
        
    }

    slope = (float)y/(float)z;
    rise = y;
    grayIncH = 255/(float)z;

    gray = 255;

    // For loop to draw right and left triangles
    for (i = z; i < height-(2*z); i++)
    {
        for (j = rise; j < width-rise ; j++)
        {
            pgmImage->image[i][j] = gray;
            pgmImage->image[height -i][j] = gray;
        }

        rise = rise + slope;
        gray = gray - grayIncH;
        
    }

    save_PGM_Image(pgmImage, name, format); // Save the pgm image
    free_PGM_Image(pgmImage); // free memory used


    return 0;

}

// Function used to draw program3 images
int program3(struct PPM_Image * ppmImage, int width, int height, char * name, int format){

    int i ,j, k, l, halfW, thirdW, halfH;

    float colorInc, r1, r2, r3, g1, g2, g3, b1, b2, b3, gray1, gray2;

    struct PGM_Image pgmRed, pgmGreen, pgmBlue;
    

    create_PPM_Image(ppmImage, width, height, 255); // Creating the ppm Image

    halfW = width/2;  // half width of im age
    thirdW = width/3;
    halfH = height/2;

    // STARTING VALUES FOR EACH SECTION OF THE IMAGE
    r1 = 255;
    g1 = 0;
    b1 = 0;

    r2 = 255;
    g2 = 255;
    b2 = 255;

    r3 = 0;
    g3 = 0;
    b3 = 255;

    gray1 = 0;
    gray2 = 255;
    // END OF STARTING VALUES FOR EACH SECTION OF THE IMAGE


    colorInc = 255/(float)halfH;  // Amount to increment the color value


    // for loop to draw the top half of the image
    for (i = 0; i < halfH; i++)
    {
        // For loop to draw red section
        for (j = 0; j < thirdW ; j++)
        {
            ppmImage->image[i][j][0] = r1;
            ppmImage->image[i][j][1] = g1;
            ppmImage->image[i][j][2] = b1;
        }
        // For loop to draw green section
        for (k = thirdW; k < (2*thirdW) ; k++)
        {
            ppmImage->image[i][k][0] = r2;
            ppmImage->image[i][k][1] = g2;
            ppmImage->image[i][k][2] = b2;
        }
        //For loop to draw blue section
        for (l = 2*thirdW; l < width ; l++)
        {
            ppmImage->image[i][l][0] = r3;
            ppmImage->image[i][l][1] = g3;
            ppmImage->image[i][l][2] = b3;
        }

        g1 = g1 + colorInc;
        b1 = b1 + colorInc;

        r2 = r2 - colorInc;
        b2 = b2 - colorInc;

        r3 = r3 + colorInc;
        g3 = g3 + colorInc;

        
    }

    // for loop to draw bottom half of the image
    for (i = halfH; i < height; i++)
    {
        for (j = 0; j < halfW ; j++)
        {
            ppmImage->image[i][j][0] = gray1;
            ppmImage->image[i][j][1] = gray1;
            ppmImage->image[i][j][2] = gray1;
        }
        for (k = halfW; k < width ; k++)
        {
            ppmImage->image[i][k][0] = gray2;
            ppmImage->image[i][k][1] = gray2;
            ppmImage->image[i][k][2] = gray2;
        }

        gray1 = gray1 + colorInc;
        gray2 = gray2 - colorInc;

        
    }

    save_PPM_Image(ppmImage, name, format); // save the ppm image

    copy_PPM_to_PGM(ppmImage, &pgmRed, 0); // copy ppm to pgm red value
    copy_PPM_to_PGM(ppmImage, &pgmGreen, 1); // copy ppm to pgm green value
    copy_PPM_to_PGM(ppmImage, &pgmBlue, 2); // copy ppm to pgm blue value

    // save all the converted pgm images
    save_PGM_Image(&pgmRed,"ppm_to_pgm_RED.pgm", format); 
    save_PGM_Image(&pgmGreen,"ppm_to_pgm_GREEN.pgm", format);
    save_PGM_Image(&pgmBlue,"ppm_to_pgm_BLUE.pgm", format);

    // free memory used by images
    free_PGM_Image(&pgmRed);
    free_PGM_Image(&pgmGreen);
    free_PGM_Image(&pgmBlue);
    free_PPM_Image(ppmImage);

    return 0;

}