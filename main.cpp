#include <fstream>
#include <iostream>
#include "YUV2ARGB.h"
#include "ARGB2YUV.h"
#include <cstdlib>
#include <cmath>
#include <cstdio>
using namespace std;
int main()
{
	//1920*1080
	int height = 1920;
	int width = 1080;
	int* argb_pic;
	char* yuv_pic = new char[height*width*3];
	ifstream fin;
	fin.open("dem1.yuv",ios::binary);
	char output_name[6] = "q1_n";
	int char_num = 0;
	while(fin>>yuv_pic[char_num++]);
	fin.close();
	printf("char num=%d\n",char_num);
	ofstream fout;
	for(int A=1;A<256;A=A+3)
	{
		printf("YUV2ARGB\n");
		argb_pic = YUV2ARGB(yuv_pic,1080,1920,A);
		printf("ARGB2YUV\n");
		yuv_pic =  ARGB2YUV(argb_pic,1080,1920);
		fout.open("q1_out.yuv",ios::binary);
		for(int i = 0;i<char_num;i++)fout<<yuv_pic[i];
		fout.close();
		return 0;
	}
	return 0;
}