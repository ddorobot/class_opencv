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
	cv::Canny( detected_edges, detected_edges, 50, 200, 3 );

	std::vector<cv::Vec2f> lines;
	cv::HoughLines(detected_edges, lines, 1, CV_PI/180, 50, 0, 0 );

	cv::Mat line_mat ;
	image.copyTo(line_mat) ;
	for( int i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		
		cv::line( line_mat, pt1, pt2, cv::Scalar(0,0,255), 1);
	}

	cv::imshow("edge", detected_edges) ;
	cv::imshow("input", image) ;
	cv::imshow( "line", line_mat );

	cv::waitKey(0);
	
    return 0;
}
