#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	//read image
	cv::Mat image = cv::imread("test.png") ;

	//perspctive
	cv::Point2f dst_vertices[4];
	int dest_width = image.cols ;
	int dest_height = image.rows ;
	int ipm_width = 100 ;
	int ipm_height = 200 ;

	cv::Point center(image.cols/2, image.rows/2) ;
	dst_vertices[0] = cv::Point(center.x-ipm_width/2, image.rows - ipm_height);
	dst_vertices[1] = cv::Point(center.x+ipm_width/2, image.rows - ipm_height);
	dst_vertices[2] = cv::Point(center.x+ipm_width/2, image.rows);
	dst_vertices[3] = cv::Point(center.x-ipm_width/2, image.rows);
	
	cv::Point2f ori_pts[4] ;
	ori_pts[0] = cv::Point2f(center.x-20, image.rows-150) ;
	ori_pts[1] = cv::Point2f(center.x+20, image.rows-150) ;
	ori_pts[2] = cv::Point2f(center.x+180, image.rows) ;
	ori_pts[3] = cv::Point2f(center.x-180, image.rows) ;
	
	cv::Mat warpMatrix = cv::getPerspectiveTransform(ori_pts, dst_vertices);

	cv::Size candidate_size(dest_width, dest_height);
	cv::Mat ipm_image ;
	cv::warpPerspective(image, ipm_image, warpMatrix, candidate_size, cv::INTER_LINEAR);
	
	// Convert it to gray
	cv::Mat src_gray ;
	cv::cvtColor( ipm_image, src_gray, cv::COLOR_BGR2GRAY  );

	/// Reduce noise with a kernel 3x3
	cv::Mat detected_edges ;
	cv::GaussianBlur( src_gray, detected_edges, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );

	/// Canny detector
	cv::Canny( detected_edges, detected_edges, 30, 200, 3 );

	//houph line detector
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(detected_edges, lines, 1, CV_PI/180, 50, 0, 0 );

	cv::Mat line_mat ;
	ipm_image.copyTo(line_mat) ;
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
	cv::imwrite( "line_1.png", line_mat );
	
	ipm_image.copyTo(line_mat) ;
	for( int i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];

		float degree  = theta*(180.0/CV_PI) ;
		
		if( fabs(degree) < 10 )
		{
			cv::Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000*(-b));
			pt1.y = cvRound(y0 + 1000*(a));
			pt2.x = cvRound(x0 - 1000*(-b));
			pt2.y = cvRound(y0 - 1000*(a));
			
			cv::line( line_mat, pt1, pt2, cv::Scalar(0,0,255), 1);
		}
	}
	
	cv::imwrite( "line_2.png", line_mat );
	
	
	cv::imwrite("input.png", image) ;
	cv::imwrite("ipm.png", ipm_image) ;
	cv::imwrite( "CannyEdge.png", detected_edges );
	
	cv::waitKey(0);
	
    return 0;
}
