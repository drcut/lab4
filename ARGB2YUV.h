 /*int convertARGBtoYUV(int r, int g, int b) {  
    int r,g,b;  
    r = y+1.140*v;
    g = y-0.394*u-0.581*v;
    b = y+2.032*u;
    r = r>255? 255 : r<0 ? 0 : r;  
    g = g>255? 255 : g<0 ? 0 : g;  
    b = b>255? 255 : b<0 ? 0 : b;  
    r=(alpha*r)/256;
    g=(alpha*g)/256;
    b=(alpha*b)/256;
    return 0xff000000 | (r<<16) | (g<<8) | b;  
}  */
 char* ARGB2YUV(int* data, int width, int height) {  
    int size = width*height;  
    int offset = size;  
    char* yuv_pic=new char[size*3];
    for(int i=0, k=0; i < size; i+=2, k+=1) { 
    	 int pixel = data[k];
    	 int r = pixel&0x00ff0000;
    	 int g = pixel&0x0000ff00;
    	 int b = pixel&0x000000ff;
    	 int y = 0.299*r+0.587*g+0.114*b;
    	 int u =0.492*(b-y);
    	 int v = 0.877*(r-y);
    	 yuv_pic[i] = (char)y;
    	 yuv_pic[offset + i] = (char)u;
    	 yuv_pic[offset + i + width] = (char)v;
    	 if (i!=0 && (i+2)%width==0)  
            	 	i+=width;    
    }
    return yuv_pic;
}  
