 int convertYUVtoARGB(int y, int u, int v,int alpha) {  
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
}  
 int* YUV2ARGB(char* data, int width, int height,int alpha) {  
    int size = width*height;  
    int offset = size;  
    int* pixels = new int[size];  
    int u, v, y1, y2, y3, y4;  
    // i along Y and the final pixels  
    // k along pixels U and V  
    for(int i=0, k=0; i < size; i+=2, k+=1) {  
        y1 = data[i  ]&0xff;  
        y2 = data[i+1]&0xff;  
        y3 = data[width+i  ]&0xff;  
        y4 = data[width+i+1]&0xff;  
   
        u = data[offset+k  ]&0xff;  
        v = data[offset+k+width]&0xff;  
        u = u-128;  
        v = v-128;  
   
        pixels[i  ] = convertYUVtoARGB(y1, u, v ,alpha);  
        pixels[i+1] = convertYUVtoARGB(y2, u, v,alpha);  
        pixels[width+i  ] = convertYUVtoARGB(y3, u, v,alpha);  
        pixels[width+i+1] = convertYUVtoARGB(y4, u, v,alpha);  
   
        if (i!=0 && (i+2)%width==0)  
            i+=width;  
    }  
    return pixels;  
}  
