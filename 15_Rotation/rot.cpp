#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	//read image
	cv::Mat image = cv::imread("test.png") ;

	cv::Mat dst;
    cv::Point2f center(image.cols/2., image.rows/2.);    

	int angle = 45 ;
    cv::Mat r_mat = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::warpAffine(image, dst, r_mat, cv::Size(image.cols, image.rows));

	cv::imshow("src", image) ;
	cv::imshow("rot", dst) ;
	
	cv::waitKey(0);
	
    return 0;
}
