#include <fstream>
#include <iostream>
#include "YUV2ARGB.h"
using namespace std;
int main()
{
	//1920*1080
	int height = 1920;
	int width = 1080;
	int* argb_pic = new int[height*width];
	char* yuv_pic = new char[height*width*3];
	ifstream fin;
	fin.open("dem1.yuv");
	int i = 0;
	while(fin>>yuv_pic[i++]);
	for(int A=1;A<256;A=A+3)
	{
		argb_pic = YUV2ARGB(yuv_pic,1080,1920,A);
	}
}