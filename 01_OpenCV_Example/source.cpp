#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	cv::Mat read_image = cv::imread("test.png") ;

	cv::imshow("test", read_image) ;
	cv::waitKey(0) ;
	
	return 0 ;
}
