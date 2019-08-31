#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	//read image
	cv::Mat image = cv::imread("test.png") ;
	  
	while(1)
	{
		//Blur the image with 3x3 Gaussian kernel
		cv::Mat image_blurred_with_3x3_kernel;
		cv::GaussianBlur(image, image_blurred_with_3x3_kernel, cv::Size(3, 3), 0);
	
		//Blur the image with 5x5 Gaussian kernel
		cv::Mat image_blurred_with_5x5_kernel;
		cv::GaussianBlur(image, image_blurred_with_5x5_kernel, cv::Size(5, 5), 0);
	
		// Show our images inside the created windows.
		cv::imshow("original", image);
		cv::imshow("3x3", image_blurred_with_3x3_kernel);
		cv::imshow("5xx5", image_blurred_with_5x5_kernel);
	
		cv::waitKey(0); // Wait for any keystroke in the window

		break ;
	}
	
    return 0;
}
