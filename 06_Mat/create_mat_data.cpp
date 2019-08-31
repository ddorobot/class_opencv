#include <stdio.h>

//opencv header
#include "opencv2/opencv.hpp"

int g_mouse_x = -1 ;
int g_mouse_y = -1 ;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if( event == cv::EVENT_LBUTTONDOWN )
	{
		//g_mouse_x = x ;
		//g_mouse_y = y ;
		
		//printf("Left button of the mouse is clicked - position (%d, %d)\n", x , y);
	}
	else if( event == cv::EVENT_RBUTTONDOWN )
	{
		//printf("Right button of the mouse is clicked - position (%d, %d)\n", x , y);
	}
	else if( event == cv::EVENT_MBUTTONDOWN )
	{
		//printf("Middle button of the mouse is clicked - position (%d, %d)\n", x , y);
	}
	else if( event == cv::EVENT_MOUSEMOVE )
	{
		g_mouse_x = x ;
		g_mouse_y = y ;
		
		//printf("Mouse move over the window - position (%d, %d)\n", x , y);
	}
}

int main(void)
{
	//create mat
	cv::Mat image = cv::Mat(cv::Size(640,480), CV_8UC3) ;
	image = 0 ;

	//red mat
	cv::Mat image_red = cv::Mat(cv::Size(640,480), CV_8UC3) ;
	image_red = cv::Scalar(0,0,255) ;

	//green mat
	cv::Mat image_green = cv::Mat(cv::Size(640,480), CV_8UC3) ;
	image_green = cv::Scalar(0,255,0) ;

	//blue mat
	cv::Mat image_blue = cv::Mat(cv::Size(640,480), CV_8UC3) ;
	image_blue = cv::Scalar(255,0,0) ;
	
	//Create a window
    cv::namedWindow("RGB", 1);

     //set the callback function for any mouse event
    cv::setMouseCallback("RGB", CallBackFunc, NULL);

	while(1)
	{
		if( !image.empty() )
		{
			if( g_mouse_x >= 0 && g_mouse_y >= 0 && g_mouse_x < image.cols && g_mouse_y < image.rows )
			{
				unsigned char blue = 0 ; 
				unsigned char green = 0 ;  
				unsigned char red = 255 ; 

				image.at<cv::Vec3b>(g_mouse_y, g_mouse_x)[0] = blue ; 
				image.at<cv::Vec3b>(g_mouse_y, g_mouse_x)[1] = green ;  
				image.at<cv::Vec3b>(g_mouse_y, g_mouse_x)[2] = red ; 

				printf("mouse position (%d, %d) : RGB(%d, %d, %d)\n", g_mouse_x , g_mouse_y, red, green, blue);
			}
			
			cv::imshow("RGB", image) ;
			cv::imshow("red", image_red) ;
			cv::imshow("green", image_green) ;
			cv::imshow("blue", image_blue) ;
			
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
