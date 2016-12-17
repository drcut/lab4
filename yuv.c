/*
本模板仅供参考
*/
//#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
//using namespace std;

#define Width 1920
#define Height 1080
#define size 1920*1080
#define ssize (3*1920*1080)>>1
char buf[ssize]={};
char newbuf[ssize]={};
int pixels[ssize] ={};
char *name[]={"1.yuv","4.yuv","7.yuv","10.yuv","13.yuv","16.yuv","19.yuv","22.yuv","25.yuv","28.yuv",
    "31.yuv","34.yuv","37.yuv","40.yuv","43.yuv","46.yuv","49.yuv","52.yuv","55.yuv","58.yuv",
    "61.yuv","64.yuv","67.yuv","70.yuv","73.yuv","76.yuv","79.yuv","82.yuv","85.yuv","88.yuv",
    "91.yuv","94.yuv","97.yuv","100.yuv","103.yuv","106.yuv","109.yuv","112.yuv","115.yuv","118.yuv",
    "121.yuv","124.yuv","127.yuv","130.yuv","133.yuv","136.yuv","139.yuv","142.yuv","145.yuv","148.yuv",
    "151.yuv","154.yuv","157.yuv","160.yuv","163.yuv","166.yuv","169.yuv","172.yuv","175.yuv","178.yuv",
    "181.yuv","184.yuv","187.yuv","190.yuv","193.yuv","196.yuv","199.yuv","202.yuv","205.yuv","208.yuv",
    "211.yuv","214.yuv","217.yuv","220.yuv","223.yuv","226.yuv","229.yuv","232.yuv","235.yuv","238.yuv",
    "241.yuv","244.yuv","247.yuv","250.yuv","253.yuv"};
int process_without_simd();
int process_with_mmx();
int process_with_sse();
int process_with_avx();

 int convertYUVtoARGB(char y, char u, char v, int A) {
    char r,g,b;
    
    r = y + (char)1.140f*v;
    g = y - (char)(0.394f*u +0.581f*v);
    b = y + (char)2.032f*u;
    r = r>255? 255 : r<0 ? 0 : r;
    g = g>255? 255 : g<0 ? 0 : g;
    b = b>255? 255 : b<0 ? 0 : b;
    
    r = (A*r)/256;
    g = (A*g)/256;
    b = (A*b)/256;
    return 0x00000000 | (r<<16) | (g<<8) | b;
}
int main(){
    int time1 = process_without_simd();
    printf("process_without_simd time: %d \n", time1);
	return 0;
}


int process_without_simd(){
    clock_t start,end;
    start = clock();
	int time = 0;

    int A;
    FILE *fr;
    if((fr = fopen("dem1.yuv","r"))==NULL){
        printf("can't open yuv.\n");
        return 0;
    }
    fread(buf,sizeof(char),ssize,fr);
    fclose(fr);
    int offset = size;
    char u,v,y1,y2,y3,y4;
    for(A=1;A<256;A=A+3){
        for(int i=0, k=0; i < size; i+=2, k+=1) {
            y1 = buf[i]&0xff;
            y2 = buf[i+1]&0xff;
            y3 = buf[Width+i]&0xff;
            y4 = buf[Width+i+1]&0xff;
            
            u = buf[offset+k]&0xff;
            v = buf[offset+k+Width]&0xff;
            //need for yuv pic be more precise
            u = u-128;
            v = v-128;
            
            pixels[i] = convertYUVtoARGB(y1, u, v, A);
            pixels[i+1] = convertYUVtoARGB(y2, u, v, A);
            pixels[Width+i] = convertYUVtoARGB(y3, u, v, A);
            pixels[Width+i+1] = convertYUVtoARGB(y4, u, v, A);
            
            //RGB to new yuv
            newbuf[i] = 0.299f*(pixels[i]>>16&0xff)+0.587f*(pixels[i]>>8&0xff)+0.114f*(pixels[i]&0xff);
            newbuf[i+1]= 0.299f*(pixels[i+1]>>16&0xff)+0.587f*(pixels[i+1]>>8&0xff)+0.114f*(pixels[i+1]&0xff);
            newbuf[Width+i] = 0.299f*(pixels[Width+i]>>16&0xff)+0.587f*(pixels[Width+i]>>8&0xff)+0.114f*(pixels[Width+i]&0xff);
            newbuf[Width+i+1] = 0.299f*(pixels[Width+i+1]>>16&0xff)+0.587f*(pixels[Width+i+1]>>8&0xff)+0.114f*(pixels[Width+i+1]&0xff);
            newbuf[offset+k] = -0.147f*(pixels[i]>>16&0xff)-0.289f*(pixels[i]>>8&0xff)+0.436f*(pixels[i]&0xff);
            newbuf[offset+k+Width] = 0.615f*(pixels[i]>>16&0xff)-0.515f*(pixels[i]>>8&0xff)-0.100f*(pixels[i]&0xff);
            
            if (i!=0 && (i+2)%Width==0)
                i+=Width;
        }
        FILE *fw = fopen(name[(A-1)/3],"w");
        fwrite(newbuf,sizeof(newbuf),1,fw);
        fclose(fw);
    }
    end =clock();
    time = (int)((end - start)/1000);//count by second / ms ?
    return time;
}

int process_with_mmx(){
	int time = 0;

	/*处理过程*/

	return time;
}

int process_with_sse(){
	int time = 0;

	/*处理过程*/

	return time;
}

int process_with_avx(){
	int time = 0;
	/*处理过程*/


	return time;
}