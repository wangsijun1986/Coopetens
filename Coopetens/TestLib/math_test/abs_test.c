/*
 * abs.c
 *	功能:求整数的绝对值
 *	用法：int abs(int i);
 *  Created on: Sep 30, 2016
 *      Author: gordonwang
 */

#include <stdio.h>
#include <math.h>

extern void test_abs(){
	printf("please enter value that you will calculation.");
	int value;
	char str[8];
	scanf("%s", &str);
	value = atoi(str);
	printf("Your input value is %d, it absolute value is %d\n",value,abs(value));
}

