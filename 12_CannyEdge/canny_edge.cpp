#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	cv::Mat detected_edges ;
	
	//read image
	cv::Mat image = cv::imread("test.png") ;
	  
	// Convert it to gray
	cv::Mat src_gray ;
	cv::cvtColor( image, src_gray, cv::COLOR_BGR2GRAY  );

	/// Reduce noise with a kernel 3x3
	cv::GaussianBlur( src_gray, detected_edges, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );

	/// Canny detector
	cv::Canny( detected_edges, detected_edges, 100, 200, 3 );

	cv::imshow("input", image) ;
	cv::imshow( "Canny Edge", detected_edges );

	cv::waitKey(0);
	
    return 0;
}
