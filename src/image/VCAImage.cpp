#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <math.h> 
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

#include "VCAImage.h"
#define VCA_SPRINTF_S snprintf
Scalar g_red(0, 0, 255);
Scalar g_cyan(255, 255, 0);
Scalar g_gray(200, 200, 200);
Scalar g_white(255, 255, 255);
Scalar g_black(0, 0, 0);
Scalar g_green(0, 255, 0);
Scalar g_yellow(0, 255, 255);
Scalar g_pinkish_red(255, 0, 255);
Scalar g_blue(255, 0, 0);


void ShowTagColor(Mat &input_image, Point *p_pt, const char *p_msg_buffer, Scalar color, bool show_tag_bg)
{
	Rect msg_rect;

	msg_rect.width=(int)((float)strlen(p_msg_buffer)*(float)5.2)+3;
	msg_rect.height=13;
	msg_rect.x=p_pt->x;
	msg_rect.y=p_pt->y;
	if(msg_rect.x<0)
	{
		msg_rect.x=0;
	}
	if(msg_rect.y<0)
	{
		msg_rect.y=0;
	}
	if((msg_rect.x+msg_rect.width)>input_image.cols)
	{
		msg_rect.x=input_image.cols-msg_rect.width;
	}
	if((msg_rect.y+msg_rect.height)>input_image.rows)
	{
		msg_rect.y=input_image.rows-msg_rect.height;
	}
	if(show_tag_bg)
	{
		rectangle(input_image,msg_rect,color,-1, CV_AA);
		putText(input_image, p_msg_buffer, cvPoint(msg_rect.x,msg_rect.y+9),CV_FONT_HERSHEY_SIMPLEX,(double)0.3,Scalar(0,0,0),1,CV_AA);
	}
	else
	{
		putText(input_image, p_msg_buffer, cvPoint(msg_rect.x,msg_rect.y+9),CV_FONT_HERSHEY_SIMPLEX,(double)0.3,color,1,CV_AA);
	}
}


void ShowTagRMCT(Mat &input_image, Rect &o_rect, const char *p_msg_buffer, Scalar o_scalar, int thickness, bool show_position, bool show_tag_bg, int tag_position)
{
	char msg_buffer[256];
	Point tag_pt;
	int offset_length=0;

	memset(msg_buffer, 0, sizeof(msg_buffer));
	if(p_msg_buffer)
	{
		offset_length+=VCA_SPRINTF_S(msg_buffer, sizeof(msg_buffer)-offset_length, "%s", p_msg_buffer);
	}
	if(show_position)
	{
		offset_length+=VCA_SPRINTF_S(&msg_buffer[offset_length], sizeof(msg_buffer)-offset_length, "%s(%u,%u,%u,%u)", p_msg_buffer, o_rect.x, o_rect.y, o_rect.width, o_rect.height);
	}
	if(offset_length>0)
	{
		offset_length+=VCA_SPRINTF_S(&msg_buffer[offset_length], sizeof(msg_buffer)-offset_length, "  ");
	}

	tag_pt.x=o_rect.x;
	if(tag_position==0)
	{
		tag_pt.y=o_rect.y-13;
	}
	else if(tag_position==1)
	{
		tag_pt.y=o_rect.y;
	}
	else if(tag_position==2)
	{
		tag_pt.y=o_rect.y+o_rect.height-13;
	}
	else if(tag_position==3)
	{
		tag_pt.y=o_rect.y+o_rect.height;
	}
	rectangle(input_image, o_rect, o_scalar, thickness, CV_AA);
	ShowTagColor(input_image, &tag_pt, msg_buffer, o_scalar, show_tag_bg);
}



