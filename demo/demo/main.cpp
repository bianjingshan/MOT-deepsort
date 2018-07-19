
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include "deepsort.h"
#include "VCATime.h"
#include "VCAImage.h"

typedef std::vector<DS_DetectObjects> FRAMES;
static FRAMES frames;
static int frame_index=0;
static Scalar array_color[8]=
{
g_red,
g_cyan,
g_gray,
g_white,
g_green,
g_blue,
g_yellow,
g_pinkish_red
};

bool LoadDetection(char *p_file_name)
{
	FILE *fp=NULL;
	fp=fopen(p_file_name, "rb");
	if(NULL == fp)
	{
		printf("File %s not exist!", p_file_name);
		return false;
	}
	int current_frame_index=0;
	char line_buffer[1024];
	DS_DetectObject temp_object;
	DS_DetectObjects detections;
	detections.clear();
	frames.clear();
	frame_index=0;
	int read_frame_index, reserved;
	float read_rect[4], read_confidence;
	while(1)
	{
		if(NULL!=fgets(line_buffer, sizeof(line_buffer), fp))
		{
			sscanf(line_buffer, "%d,%d,%f,%f,%f,%f,%f", 
				&read_frame_index, 
				&reserved, 
				&read_rect[0],
				&read_rect[1],
				&read_rect[2],
				&read_rect[3],
				&read_confidence
				);
			if(current_frame_index!=read_frame_index)
			{
				frames.push_back(detections);
				detections.clear();
				current_frame_index=read_frame_index;
			}
			temp_object.class_id=0;
			temp_object.confidence=read_confidence;
			temp_object.x=read_rect[0];
			temp_object.y=read_rect[1];
			temp_object.width=read_rect[2];
			temp_object.height=read_rect[3];
			detections.push_back(temp_object);
		}
		else
		{
			frames.push_back(detections);
			detections.clear();
			current_frame_index=0;
			break;
		}
	}
	fclose(fp);
	return true;
}

bool ReadFrame(DS_DetectObjects &detections)
{
	if(frame_index>=frames.size())
	{
		return false;
	}
	detections=frames[frame_index];
	frame_index++;
	return true;
}

int main(int argc, char* argv[])
{
	DS_Tracker h_tracker=DS_Create();
	if(NULL==h_tracker)
	{
		printf("DS_CreateTracker error.\n");
		return 0;
	}
	int frame_count=0;
	CTickTime tick_time; 

	if(argc<4)
	{
		printf("Parameter error.\n");
		return 0;
	}
	Size image_size;
	image_size.width=atoi(argv[2]);
	image_size.height=atoi(argv[3]);
	bool show_image_en=false;
	if(argc>=5)
	{
		if(0==strcasecmp(argv[4], "-show"))
		{
			show_image_en=true;
		}
	}
	if(!LoadDetection(argv[1]))
	{
		return 0;
	}
	printf("%s\n", argv[1]);
	Mat show_image;
	if(show_image_en)
	{
		printf("Image Size: %dx%d\n", image_size.width, image_size.height);
		show_image.create(image_size.height, image_size.width, CV_8UC3);
	}
	DS_DetectObjects detect_objects;
	DS_TrackObjects track_objects;

	tick_time.Start();
	while(ReadFrame(detect_objects))
	{
		DS_Update(h_tracker, detect_objects, track_objects);

		if(show_image_en)
		{
			show_image.setTo(g_black);
		}
		for(int iloop=0;iloop<track_objects.size();iloop++) 
		{
			//printf("%d(%d,%d,%d,%d)\n", track.track_id,(int)output_box(0),(int)output_box(1),(int)output_box(2),(int)output_box(3));
			Rect temp_rect;
			temp_rect.x=track_objects[iloop].x;
			temp_rect.y=track_objects[iloop].y;
			temp_rect.width=track_objects[iloop].width;
			temp_rect.height=track_objects[iloop].height;
			if(show_image_en)
			{
				char caption[32];
				sprintf(caption, "%d", track_objects[iloop].track_id);
				ShowTagRMCT(show_image, temp_rect, caption, array_color[track_objects[iloop].track_id%8], 1, false);
			}
		}
		if(show_image_en)
		{
			imshow("DeepSort", show_image);
			cvWaitKey(40);
		}
		frame_count++;
	}

	printf("Frame count: %d\n", frame_count);
	printf("Going time: %f\n", tick_time.GoingTime());
	printf("Speed: %f\n", frame_count*1000.0/tick_time.GoingTime());
	printf("\n");
	return 0;
}
