#include <stdio.h>

int main(){
	int i, j, n;
	
	printf("数値を入力して下さい>");
	scanf("%d", &n);
	for (i = 1; i <= n; i++){
		printf("M");
		for(j = 1; j <= 2 * n - 5; j++){
			if((j == i - 1 || j == 2 * n - 5 - i + 2) && i != n) {
				printf("M");		
			}else{
				printf(" ");		
			}
		}
		printf("M\n");
	}		
}
