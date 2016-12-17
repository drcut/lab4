#include <fstream>
#include <iostream>
#include "YUV2ARGB2YUV.h"
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <stdio.h>
using namespace std;
int main()
{
	int height = 1080;
	int width = 1920;
    int char_num = (height*width*3)>>1;
    cout<<"run picture processing 1 or 2?"<<endl;
    int index;
    cin>>index;
    if(index==1){
	  char* yuv_1 = new char[(1080*1920*3)>>1];//source image
      char* yuv_2 = new char[(1080*1920*3)>>1];//dest image
	  ifstream fin;
	  fin.open("dem2.yuv",ios::binary);
      fin.read(yuv_1, char_num);
	  fin.close();
	  ofstream fout;
	  for(int A=1;A<256;A=A+3) {
	     	printf("%d\n",A);
		    YUV2ARGB2YUV(yuv_1,yuv_2,1920,1080,A);
            char name[10];
            sprintf(name,"%d.yuv",(A-1)/3);
            printf("%s",name);
		    fout.open(name,ios::binary);
            fout.write(yuv_2,char_num);
		    fout.close();
	  }
    }
    else{
        char* yuv_0 = new char[(1080*1920*3)>>1];//source image 1
        char* yuv_1 = new char[(1080*1920*3)>>1];//source image 2
        char* yuv_2 = new char[(1080*1920*3)>>1];//dest image
        ifstream fin;
        fin.open("dem2.yuv",ios::binary);
        fin.read(yuv_0, char_num);
        fin.close();
        ifstream fin1;
        fin1.open("dem1.yuv",ios::binary);
        fin1.read(yuv_1, char_num);
        fin1.close();
        ofstream fout;
        for(int A=1;A<256;A=A+3) {
            printf("%d\n",A);
            YUV2ARGB2YUV_add(yuv_0,yuv_1,yuv_2,1920,1080,A);
            char name[10];
            sprintf(name,"add%d.yuv",(A-1)/3);
            printf("%s",name);
            fout.open(name,ios::binary);
            fout.write(yuv_2,char_num);
            fout.close();
        }
    }
	return 0;
}