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

	cv::line(image, ori_pts[0], ori_pts[1], cv::Scalar(0,0,255), 2) ;
	cv::line(image, ori_pts[1], ori_pts[2], cv::Scalar(0,0,255), 2) ;
	cv::line(image, ori_pts[2], ori_pts[3], cv::Scalar(0,0,255), 2) ;
	cv::line(image, ori_pts[3], ori_pts[0], cv::Scalar(0,0,255), 2) ;
	cv::imshow("input", image) ;

	cv::line(ipm_image, dst_vertices[0], dst_vertices[1], cv::Scalar(0,0,255), 2) ;
	cv::line(ipm_image, dst_vertices[1], dst_vertices[2], cv::Scalar(0,0,255), 2) ;
	cv::line(ipm_image, dst_vertices[2], dst_vertices[3], cv::Scalar(0,0,255), 2) ;
	cv::line(ipm_image, dst_vertices[3], dst_vertices[0], cv::Scalar(0,0,255), 2) ;
	cv::imshow("ipm", ipm_image) ;
	
	cv::waitKey(0);
	
    return 0;
}
