#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <list>

using namespace std;
using namespace cv;

list <Mat> GetImageList(string videoFileName, int chopDistance){
	list <Mat> res;
	VideoCapture cap;
	cap.open(videoFileName);	
	int cnt = 0;
	while (1){	
		Mat frame;
		cap >> frame;
		if (!frame.data) break;
		cnt++;
		if (cnt % chopDistance == 0) res.push_back(frame);		
	}
	return res;
}

list <Mat> ResizeImageList(list <Mat> inputList, int newWidth, int newHeight){
	list <Mat> res;
	for (list <Mat>::iterator it = inputList.begin(); it != inputList.end(); it++){
		Mat tt = *it;
		resize(tt, tt, Size(newWidth, newHeight));
		res.push_back(tt);
	}
	return res;
}

list <Mat> ImageListToGrayscale(list<Mat> inputList){
	list <Mat> res;
	for (list <Mat>::iterator it = inputList.begin(); it != inputList.end(); it++){
		Mat tt = *it;
		cvtColor(tt, tt, CV_BGR2GRAY);
		res.push_back(tt);
	}
	return res;
}

string change(int x){
	string temp;
	while (x > 0){
		temp = char(x%10 + 48) + temp;
		x /= 10;
	}
	return temp;
}

void SaveImageList(list <Mat> inputList, string folderName){
	string temp = "MD " + folderName;
	system(temp.c_str());
	folderName += "\\";
	int i = 0;
	for (list <Mat>::iterator it = inputList.begin(); it != inputList.end(); it++){
		i++;
		imwrite(folderName + change(i) + ".png", *it);
	}
}

int main() {
	string inpath, outpath;
	cout << "Input path: "; cin >> inpath;
	cout << "Output path: "; cin >> outpath;
	list <Mat> ans;
	ans = GetImageList(inpath, 5);
	cout << ans.size();
	ans = ResizeImageList(ans, 200, 200);
	cout << ans.size();
	ans = ImageListToGrayscale(ans);
	cout << ans.size();
	SaveImageList(ans, outpath);	
	return 0;
}