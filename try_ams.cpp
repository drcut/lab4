#include <iostream>
#include <cstdio>
using namespace std;
int main()
{

    int a = 1,b = 1,c = 0;  
    	char d[]={5, 5, 5, 5, 5, 5, 5, 5}; 
	char clr[]={65,66,65,66,65,66,65,66,65,66,65,66,65,66,65,66,65,66,65,66,65,66,65,66,}; // 24 bytes
	__asm__(
	"movq %%mm1, %0\n\t"
	"mov %%cx, 3\n\t"
	"mov %%rsi, 0\n\t"
	"L1: movq %%mm0, 0(%%rsi,%1,1)\n\t"
	"paddb %%mm0, %%mm1\n\t"
	"movq 0(%1,%%rsi,1), %%mm0\n\t"
	"add %%esi, 8\n\t"
	"loop L1\n\t"
	"emms\n\t"
	:"=r"(d)
	:"r"(clr)
	);
}
/*
若命令共涉及n个操作数，则第1个输出操作数（the first output operand）
被编号为0，第2个output operand编号为1，依次类推，
最后1个输入操作数（the last input operand）则被编号为n-1
*/