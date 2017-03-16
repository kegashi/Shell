#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

//ユーザの入力(lineのアドレス)と引数を入れるargv配列のアドレスを受け取る
//
int parse(char *line, char *argv[]){
	int argc, i;
	argc = 0;
	//先頭にスペースが入った時に省く
	while (*line && *line <= ' ') *line++ = '\0';
	while (*line) {
		argv[argc++] = line;
		while (*line && *line > ' ') line++;
		while (*line && *line <= ' ') *line++ = '\0';
	}
	argv[argc] = NULL;
	return argc;
}

int builtin(char *argv[], int pid){
	if(pid == 0 && (!strcmp(argv[0], "cd") || !strcmp(argv[0], "echo")|| !strcmp(argv[0], "exit"))) return 1;
	//cdの場合
	if(!strcmp(argv[0], "cd\0")){
		char pathname_before[512];
		char pathname_after[512];
		getcwd(pathname_before, 510);
		chdir(argv[1]);
		getcwd(pathname_after, 510); 
		if(!strcmp(pathname_before, pathname_after)){
			printf("No such file or directory.\n");		
		}
		return 1;
	//echoの場合
	}else if(!strcmp(argv[0], "echo\0")){
		int i = 1;
		while(argv[i] != NULL){
			printf("%s ", argv[i]);
			i++;
		}
		printf("\n");
		return 1;
	//exitの場合
	}else if(!strcmp(argv[0], "exit\0")){
		exit(1);
	}
	return 0;
}

int execute(int argc, char *argv[]){
	int pid, status, i;
	pid = fork();
	//printf("[fork直後] pid = %d\n", pid);
	//フォークがミスった時
	if(pid < 0) {
		printf("fork error\n");
		exit(1);
	}
	//親プロセスでビルトインコマンドを実行
	if(pid > 0){
		//printf("[親] pid = %d\n", pid);
		builtin(argv,pid);
		/*if(!builtin(argv, pid)){
			printf("親プロセスでビルト実行\n");	
		}*/	
	}
	//子プロセスの場合
	if(pid == 0) {
		//ビルトインコマンドかどうかを確かめて、違ったら実行
		//printf("[子] pid = %d\n", pid);
		if(!builtin(argv, pid)){
			char path[512] = "/bin/";
			strcat(path, argv[0]);
			if(*argv[argc - 1] == '&'){
				argv[argc - 1] = NULL;		
			}
			execve(path, argv, NULL);
			//printf("%s error\n", argv[0]);
		}
		exit(1);
	}
	//親プロセスの場合
	//もし, 子プロセスが終了していない and 最後が&じゃない
	//printf("[While前] pid = %d\n", pid);
	/*if(*argv[argc - 1] != '&'){
		//printf("[if文中] pid = %d\n", pid);
		while(wait(&status) != pid);
	}*/
	while(*argv[argc - 1] != '&' && wait(&status) != pid);
	//printf("[While後] pid = %d\n", pid);
	return 1;
}

int main(){
	char line[512];
	char *argv[16];
	char pathname[512];
	int argc, i;

	for (;;) {
		getcwd(pathname, 510);
		printf("%s> ",pathname);
		fgets(line, 512, stdin);
		argc = parse(line, argv);
		/*for(i = 0; i < 15; i++){
			printf("argv[%d]=%s\n", i, argv[i]);
		}*/
		if(argc != 0) execute(argc, argv);
	}
}
