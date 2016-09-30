/*
 * main.c
 *
 *  Created on: Sep 28, 2016
 *      Author: gordonwang
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "TestLib/stdlib_test/abort_test.h"

#define NUM_PTHREADS 5
int currentOff = 1;

void* say_hello(void* args)
{
	printf("当前线程: %d ",*(int *)args);
	//pthread_exit(NULL);
	return 0;
}

int fibonaci(int i)
{
   if(i == 0)
   {
      return 0;
   }
   if(i == 1)
   {
      return 1;
   }
   return fibonaci(i-1) + fibonaci(i-2);
}

void sighandler(int signum)
{
   printf("捕获信号 %d，跳出...\n", signum);
   exit(1);
}

void test_fibonacci(){
	for(int i=0;i<10;i++){
		printf("%d \t",fibonaci(i));
	}
}

void runningProgram(int id){
	switch(id){
		case 1:
			test_abort();
			break;
		case 2:
			test_fibonacci();
			break;
		default:
			currentOff = 0;
			printf("正在推出程序");
			break;
	}
}

int main(void)
{
	//int num = NUM_PTHREADS*20;
	const char *programList = "1.异常终止一个进程\n"
			"2.斐波那契数列\n";
	printf(programList);
	int id;
	char *str;
	while(currentOff){
		printf("Please enter a number to running this program.\n");
		scanf("%s",str);
		id = atoi(str);
		printf("This is your input value:%s\n",str);
		runningProgram(id);
	}

	//pthread_t pthreads[NUM_PTHREADS];
	//int txt[NUM_PTHREADS];

	/*

	 */

	/*
	signal(SIGINT, sighandler);

	int i =0;

	while(1){
		printf("开始数数：%d \r\n",i++);
		sleep(1);
	}
	 */

	/*
	for(int i=0;i<NUM_PTHREADS;i++){
		txt[i] = i;
		//创建线程
		int ret = pthread_create(&pthreads[i],NULL,say_hello,(void *)&(txt[i]));
		if(ret!=0){
			printf("出错了");
		}
	}
	*/
	//终止线程
	//pthread_exit(NULL);

	return(0);

}
