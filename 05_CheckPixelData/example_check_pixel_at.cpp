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
	//read image
	cv::Mat read_image = cv::imread("test.png") ;
	
	//Create a window
    cv::namedWindow("RGB", 1);

     //set the callback function for any mouse event
    cv::setMouseCallback("RGB", CallBackFunc, NULL);

	while(1)
	{
		if( !read_image.empty() )
		{
			if( g_mouse_x >= 0 && g_mouse_y >= 0 && g_mouse_x < read_image.cols && g_mouse_y < read_image.rows )
			{
				unsigned char blue = read_image.at<cv::Vec3b>(g_mouse_y, g_mouse_x)[0] ; 
				unsigned char green = read_image.at<cv::Vec3b>(g_mouse_y, g_mouse_x)[1] ;  
				unsigned char red = read_image.at<cv::Vec3b>(g_mouse_y, g_mouse_x)[2] ; 

				printf("mouse position (%d, %d) : RGB(%d, %d, %d)\n", g_mouse_x , g_mouse_y, red, green, blue);
			}
			
			cv::imshow("RGB", read_image) ;
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
