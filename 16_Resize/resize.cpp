#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	//read image
	cv::Mat image = cv::imread("test.png") ;

	cv::Mat down_scale ;
	cv::resize(image, down_scale, cv::Size(), 0.5, 0.5) ;

	cv::Mat up_scale ;
	cv::resize(image, up_scale, cv::Size(image.cols*1.5, image.rows*1.5)) ;
	
	cv::imshow("src", image) ;
	cv::imshow("down_scale", down_scale) ;
	cv::imshow("up_scale", up_scale) ;
	
	cv::waitKey(0);
	
    return 0;
}
