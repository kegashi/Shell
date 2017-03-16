#include <stdio.h>

int fib(int num){
	if(num > 1){
		return fib(num -1) + fib(num - 2);		
	}else{
		return 1;		
	}
}

int main(){
	//int x;
	int i;
	//printf("数字を入力してください>");
	//scanf("%d", &x);
	for(i = 0; i <= 100; i++){
		printf("fib(%d)=%d\n", i, fib(i));
	}
}
