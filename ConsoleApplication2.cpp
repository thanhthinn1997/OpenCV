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
	Mat NewFrame;
	int n = inputList.size();
	for (int i = 0; i < n; i++)
	{
		resize(inputList.front(), NewFrame, size);
		inputList.pop_front();
		temp.push_front(NewFrame);
	}
	return temp;
}

list<Mat> ImageListToGrayscale(list<Mat> inputList)
{
	list<Mat> temp;
	Mat newframe;
	int n = inputList.size();
	for (int i = 0; i < n; i++)
	{
		cvtColor(inputList.front(), newframe, CV_RGB2GRAY);
		inputList.pop_front();
		temp.push_front(newframe);
	}
	return temp;
}

void SaveImageList(list<Mat> inputList, string folderName)
{
	folderName += "\\";
	string linkfile = "md" + folderName;
	system(linkfile.c_str());
	int n = inputList.size();
	for (int i = 0; i < n; i++)
	{
		imwrite(folderName + to_string(i) + ".png", inputList.front());
		inputList.pop_front();
	}
}

int main()
{
	string input, output;
	cout << "Input: "; cin >> input;
	cout << "Output: "; cin >> output;
	list<Mat> temp;
	temp = GetImageList(input, 10);
	cout << temp.size();
	temp = ResizeImageList(temp, 300, 300);
	temp = ImageListToGrayscale(temp);
	SaveImageList(temp, output);
    return 0;
}

