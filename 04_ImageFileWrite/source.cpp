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

		char key = cv::waitKey(30) ;
		
		if( key == 'S' || key == 's' ) 
		{
			//save
			cv::imwrite("save.png", frame) ;
		}
        else if( key == 'q' || key == 'Q' )
		{
			break ;
        }
    }
	
    return 0;
}
