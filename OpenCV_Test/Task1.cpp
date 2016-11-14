#include <list>
#include <string>
#include <iostream>
using namespace std;

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
using namespace cv;

#define List list
#define Image Mat

List<Image> GetImageList(string videoFileName, int chopDistance)
{
	List<Image> outputList;
	VideoCapture video(videoFileName);
	Image frame, img;
	int counter(chopDistance);
	while (true)
	{
		video >> frame;
		if (!frame.data) break;
		if (counter == chopDistance)
		{
			img = frame.clone();
			outputList.push_back(img);
			counter = 0;
		}
		else counter++;
	}
	return outputList;
}

List<Image> ResizeImageList(List<Image> inputList, int newWidth, int newHeight)
{
	List<Image> outputList;
	Image img;
	Size newSize(newWidth, newHeight);
	for (auto it : inputList)
	{
		img = it.clone();
		resize(img, img, newSize);
		outputList.push_back(img);
	}
	return outputList;
}

List<Image> ImageListToGrayscale(List<Image> inputList)
{
	List<Image> outputList;
	Image img;
	for (auto it : inputList)
	{
		img = it.clone();
		cvtColor(img, img, CV_RGB2GRAY);
		outputList.push_back(img);
	}
	return outputList;
}

void SaveImageList(List<Image> inputList, string folderName)
{
	folderName += "\\";
	string path = "md " + folderName;
	system(path.c_str());
	int counter = 0;
	for (auto it : inputList)
	{		
		path = folderName + to_string(counter++) + ".jpg";
		imwrite(path, it);
	}
}

int main()
{
	string path;
	cout << "Enter path to video file: ";
	getline(cin, path);

	List<Image> frames = GetImageList(path, 50);
	cout << "Enter path to store video frames: ";
	getline(cin, path);
	SaveImageList(frames, path);

	List<Image> resizedImages = ResizeImageList(frames, 500, 500);
	cout << "Enter path to store resized images: ";
	getline(cin, path);
	SaveImageList(resizedImages, path);

	List<Image> grayImages = ImageListToGrayscale(frames);
	cout << "Enter path to store grayscale images: ";
	getline(cin, path);
	SaveImageList(grayImages, path);

	return 0;
}