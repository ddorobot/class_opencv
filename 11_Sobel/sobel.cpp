#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	//read image
	cv::Mat image = cv::imread("test.png") ;
	  
	cv::GaussianBlur( image, image, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );

	/// Convert it to gray
	cv::Mat src_gray ;
	cv::cvtColor( image, src_gray, cv::COLOR_BGR2GRAY  );

	/// Generate grad_x and grad_y
	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;

	int scale = 1;
  	int delta = 0;
  
	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	cv::Sobel( src_gray, grad_x, CV_16S, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( grad_x, abs_grad_x );

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	cv::Sobel( src_gray, grad_y, CV_16S, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( grad_y, abs_grad_y );

	/// Total Gradient (approximate)
	cv::Mat grad ;
	cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

	cv::imshow( "Sobel", grad );

	cv::waitKey(0);
	
    return 0;
}
