#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	cv::VideoCapture cap("test.mp4"); // open the video file
	if(!cap.isOpened())  // check if we succeeded
        return -1;

    for(;;)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from video file

        cv::imshow("Video Player", frame);
        if(cv::waitKey(30) >= 0) break;
    }
	
    return 0;
}
