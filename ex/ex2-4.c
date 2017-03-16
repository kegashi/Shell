#include <stdio.h>

int main(){
	int i, j, n;
	
	printf("数値を入力して下さい>");
	scanf("%d", &n);
	for (i = 1; i <= n; i++){
		for(j = 1; j< n - i + 1; j++){
			printf("　");		
		}
		for(j = 1; j <= i; j++){
			printf("SFC ");
		}
		printf("\n");
	}		
}
