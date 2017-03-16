#include <stdio.h>
#include <string.h>

//not used
void swap(int *p, int *q){
	int x;
	x = *p;
	*p = *q;
	*q = x;
}

void lower(char *s){ //*sはbufの配列の1番目のアドレスを示す
	int i;
	//printf("%lu", strlen(s));
	for(i = 0; i < strlen(s); i++){
		if(s[i]>=65&&s[i]<=90){
			s[i]=s[i]+32;		
		}else if(s[i]>=96&&s[i]<=122){
			s[i]=s[i]-32;		
		}
	}
}

int main(){
	char buf[100];
	//gets(buf);
	fgets(buf, 80, stdin);
	lower(buf);	
	puts(buf);
}
