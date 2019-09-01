#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	//read image
	cv::Mat image = cv::imread("test.png") ;
	cv::Mat image_trans = cv::imread("test2.png") ;
	
	//copy
	cv::Rect roi(0,0,image_trans.cols, image_trans.rows) ;
	image_trans.copyTo(image(roi)) ;

	roi.x += 200 ;
	roi.y += 200 ;

	image_trans.copyTo(image(roi)) ;

	cv::imshow("trans", image) ;
	
	cv::waitKey(0);
	
    return 0;
}
