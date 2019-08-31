#include <stdio.h>
#include <vector>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	//read image
	cv::Mat image = cv::imread("test.png") ;
	cv::Mat image_ref = cv::imread("histogram_ref_image.png") ;
	
	cv::Mat find_image ;
	image.copyTo(find_image) ;

	//histogram
	std::vector<cv::Mat> bgr_planes;
	cv::split( image_ref, bgr_planes );

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;
	cv::Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	cv::calcHist( &bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange);
	cv::calcHist( &bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange);
	cv::calcHist( &bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange);

	double minVal; 
	double maxVal; 
	cv::Point minLoc; 
	cv::Point maxLoc;

	
	double maxVal_bue; 
	cv::minMaxLoc( bgr_planes[0], &minVal, &maxVal_bue, &minLoc, &maxLoc );
	
	double maxVal_green; 
	cv::minMaxLoc( bgr_planes[1], &minVal, &maxVal_green, &minLoc, &maxLoc );

	double maxVal_red; 
	cv::minMaxLoc( bgr_planes[2], &minVal, &maxVal_red, &minLoc, &maxLoc );	

	int hist_h = 	cv::max(maxVal_red, cv::max(maxVal_bue, maxVal_green)) ;
	int hist_w = 256 ;
	int bin_w = cvRound( (double) hist_w/histSize );
	
	cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

	/// Draw for each channel
	for( int i = 1; i < histSize; i++ )
	{
		cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) , cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ), cv::Scalar( 255, 0, 0), 2, 8, 0  );
		cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) , cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ), cv::Scalar( 0, 255, 0), 2, 8, 0  );
		cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) , cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ), cv::Scalar( 0, 0, 255), 2, 8, 0  );
	}

	/// Display
	
	cv::imshow("calcHist_ref", image_ref );
	cv::imshow("calcHist", histImage );
	cv::waitKey(1) ;
	  
	while(1)
	{
		if( !find_image.empty() )
		{
			for( int y=0 ; y<find_image.rows ; y++ )
			{
				for( int x=0 ; x<find_image.cols ; x++ )
				{				
					unsigned char blue = find_image.at<cv::Vec3b>(y, x)[0] ; 
					unsigned char green = find_image.at<cv::Vec3b>(y, x)[1] ;	
					unsigned char red = find_image.at<cv::Vec3b>(y, x)[2] ; 

					if( red > 180 && red < 220 &&
						green > 130 && green < 170 &&
						blue > 70 && blue < 110 )
					{
						//image.at<cv::Vec3b>(y, x)[0] ; 
						//image.at<cv::Vec3b>(y, x)[1] ;	
						//image.at<cv::Vec3b>(y, x)[2] ; 
					}
					else
					{
						find_image.at<cv::Vec3b>(y, x)[0] = 0  ; 
						find_image.at<cv::Vec3b>(y, x)[1] = 0 ;	
						find_image.at<cv::Vec3b>(y, x)[2] = 0 ; 
					}
				}
			}
						
			cv::imshow("original", image) ;
			cv::imshow("find_yellow_line", find_image) ;
			
			char c = cv::waitKey(1) ;

			if( c == 'q' || c == 'Q' )
			{
				break ;
			}
		}
		else
		{
			break ;
		}
	}
	
    return 0;
}
