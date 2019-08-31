#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	cv::VideoCapture cap(0); // open the default camera device
	if(!cap.isOpened())  // check if we succeeded
        return -1;

    for(;;)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera

        cv::imshow("CAMERA", frame);
        if(cv::waitKey(30) >= 0) break;
    }
	
    return 0;
}
