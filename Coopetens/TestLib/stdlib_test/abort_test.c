/*
 * abort.c
 *	功能：异常终止一个进程
 *	用法：void abort(void);
 *  Created on: Sep 30, 2016
 *      Author: gordonwang
 */

#include <stdio.h>
#include <stdlib.h>

extern void test_abort(){
	FILE *fp;

	printf("准备打开 nofile.txt\n");
	fp = fopen( "nofile.txt","r" );

	if(fp == NULL)
	{
	  printf("准备终止程序\n");
	  abort();
	}

	printf("准备关闭 nofile.txt\n");
	fclose(fp);
}
