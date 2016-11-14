// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <list>
#include <iostream>
#include "opencv2\imgproc\imgproc.hpp"
#include <sstream>

using namespace cv;
using namespace std;

list<Mat> GetImageList(string videoFileName, int chopDistance)
{
	VideoCapture cap(videoFileName);
	int framecount(cap.get(CV_CAP_PROP_FRAME_COUNT));
	list<Mat> temp;
	for (int i = 0; i < framecount; i += chopDistance)
	{
		Mat frame;
		cap.set(CV_CAP_PROP_POS_FRAMES, i);
		cap >> frame;
		temp.push_back(frame);
	}
	return temp;
}

list<Mat> ResizeImageList(list<Mat> inputList, int newWidth, int newHeight)
{
	list<Mat> temp;
	Size size(newWidth, newHeight);
	for (list<Mat>::iterator i = inputList.begin(); i !=inputList.end(); ++i)
	{
		Mat NewFrame;
		resize(*i, NewFrame, size);
		temp.push_back(NewFrame);
	}
	return temp;
}

list<Mat> ImageListToGrayscale(list<Mat> inputList)
{
	list<Mat> temp;
	for (list<Mat>::iterator i = inputList.begin(); i != inputList.end(); ++i)
	{
		Mat newframe;
		cvtColor(*i, newframe, CV_RGB2GRAY);
		temp.push_back(newframe);
	}
	return temp;
}

void SaveImageList(list<Mat> inputList, string folderName)
{
	folderName += "\\";
	string linkfile = "md" + folderName;
	system(linkfile.c_str());
	int temp = 0;
	for (list<Mat>::iterator i = inputList.begin(); i != inputList.end(); ++i)
	{
		imwrite(folderName + to_string(temp) + ".png", *i);
		temp++;
	}
}

int main()
{
	string input, output;
	cout << "Input: "; cin >> input;
	cout << "Output: "; cin >> output;
	list<Mat> temp;
	temp = GetImageList(input, 10);
	//cout << temp.size();
	temp = ResizeImageList(temp, 300, 300);
	temp = ImageListToGrayscale(temp);
	SaveImageList(temp, output);
    return 0;
}

