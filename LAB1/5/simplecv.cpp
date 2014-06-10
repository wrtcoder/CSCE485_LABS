#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

//#include "opencv2\opencv.hpp" 

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace cv;
using namespace std;

// Default resolution is 360p
#define VRES_ROWS (180)
#define HRES_COLS (320)

#define ESC_KEY (27)

// Buffer for highest resolution visualization possible
unsigned char imagebuffer[1440*2560*3]; // 1440 rows, 2560 cols/row, 3 channel

int main(int argc, char **argv)
{
    int hres = HRES_COLS;
    int vres = VRES_ROWS;
    int frameCnt=0;

    
    Mat basicimage(vres, hres, CV_8UC3, imagebuffer);
    Mat sizeimage(vres, hres, CV_8UC3, imagebuffer);
     
    printf("hres=%d, vres=%d\n", hres, vres);

    // interactive computer vision loop 
    namedWindow("Profile Visualization", CV_WINDOW_AUTOSIZE);

    // read in default image
    basicimage = imread("Cactus360p.jpg", CV_LOAD_IMAGE_COLOR);
    
   //resize image
   resize(basicimage,basicimage,sizeimage.size());


    // Check for invalid input
    if(!basicimage.data)  
    {
        printf("Could not open or find the refernece starting image\n");
        exit(-1);
    }


    // Create an IplImage mapping onto the basicimage Mat object
    IplImage basicimageImg = basicimage;



//begin drawing yellow border, marking each single pixel with yellow 

    //left border, 4px wide 180px long
    for(int i = 0; i < 4; i++)
    {
	for(int j = 0; j < 180; j++)
	{
	    basicimage.at<cv::Vec3b>(j,i)[0]= 0;
	    basicimage.at<cv::Vec3b>(j,i)[1]= 255;
	    basicimage.at<cv::Vec3b>(j,i)[2]= 255;
        }
    }

    //right border, 4px wide 180px long
    for(int i = 315; i < 320; i++)
    {
	for(int j = 0; j < 180; j++)
	{
   	   basicimage.at<cv::Vec3b>(j,i)[0]= 0;
	   basicimage.at<cv::Vec3b>(j,i)[1]= 255;
	   basicimage.at<cv::Vec3b>(j,i)[2]= 255;
	}
    }

    //top, 320px long 4px wide
    for(int i = 0; i < 320; i++)
    {
	for(int j = 0; j < 4; j++)
	{
	   basicimage.at<cv::Vec3b>(j,i)[0]= 0;
	   basicimage.at<cv::Vec3b>(j,i)[1]= 255;
	   basicimage.at<cv::Vec3b>(j,i)[2]= 255;
	}
    }

    //bottom, 320px long 4px wide
    for(int i = 0; i < 320; i++)
    {
	for(int j = 175; j < 180; j++)
	{
   	   basicimage.at<cv::Vec3b>(j,i)[0]= 0;
	   basicimage.at<cv::Vec3b>(j,i)[1]= 255;
	   basicimage.at<cv::Vec3b>(j,i)[2]= 255;
	}
    }


//VERTICAL CROSS-HAIR 
    for(int i = 160; i < 161; i++)
    {
	for(int j = 0; j < 180; j++)
	{
	   basicimage.at<cv::Vec3b>(j,i)[0]= 0;
	   basicimage.at<cv::Vec3b>(j,i)[1]= 255;
	   basicimage.at<cv::Vec3b>(j,i)[2]= 255;
	}
    }

//HORIZONTAL CROSS-HAIR 
   for(int i = 0; i < 320;i++)
   {
    for(int j = 90; j < 91; j++)
	{
	   basicimage.at<cv::Vec3b>(j,i)[0]= 0;
	   basicimage.at<cv::Vec3b>(j,i)[1]= 255;
	   basicimage.at<cv::Vec3b>(j,i)[2]= 255;
	}
    }




    // Interactive LOOP
    //
    while(1)
    {
        frameCnt++;

        // Write a zero value into the image buffer
        //
        basicimageImg.imageData[frameCnt] = (unsigned char)0;

        imshow("Profile Visualization", basicimage);  

        // set pace on shared memory sampling in msecs
        char c = cvWaitKey(10);

        if(c == ESC_KEY)
        {
            exit(1);
        }

    }
 
    return 1;

}
