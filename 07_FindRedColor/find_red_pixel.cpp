#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int main(void)
{
	//read image
	cv::Mat image = cv::imread("test.png") ;
	
	cv::Mat find_image ;
	image.copyTo(find_image) ;
	
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

					if( red >200 && green <128 && blue<128)
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
			cv::imshow("find_red", find_image) ;
			
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
