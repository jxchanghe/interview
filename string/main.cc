#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"
#include <string.h>
#include <assert.h>


void test_qhstring_case1()
{
	const int MAXARRAYSIZE = 20;
	char testString[][100] = {
		{""},
		{"1"},
		{"1233jyii"}
	};

	int rows = sizeof(testString) / sizeof(testString[0]);
	int ret = 0;

	int i = 0;
	for (; i < rows; i++)
	{
		qh::string str1(testString[i]);
		qh::string str2(str1);
		
		int curStrLen = strlen(testString[i]);
		qh::string str3(testString[i], curStrLen);
		
		qh::string str4;
		str4 = str1;
		
		qh::string *pStrArray[MAXARRAYSIZE] = {NULL};
		int curArraySize = 0;
		
		pStrArray[curArraySize++] = &str1;
		pStrArray[curArraySize++] = &str2;
		pStrArray[curArraySize++] = &str3;
		pStrArray[curArraySize++] = &str4;
		
		int j = 0;
		for(; j < curArraySize; j++)
		{
			if (curStrLen != pStrArray[j]->size())
			{
				ret += 1;
				assert(0);
			}
				
			if(strcmp(testString[i], pStrArray[j]->data()) != 0 )
			{
				ret += 1;
				assert(0);
			}
				
			char c = (*pStrArray[j])[curStrLen * 2];
			if (c != '\0')
			{
				ret += 1;
				assert(0);
			}
				
			c = (*pStrArray[j])[curStrLen];
			if (c != '\0')
			{
				ret += 1;
				assert(0);
			}
				
			(*pStrArray[j])[0] = '\0';
			if(strlen(pStrArray[j]->data()) != 0)
			{
				ret += 1;
				assert(0);
			}
			
		}
		
	}

	if (!ret)
	{
		printf("Test case 1 passed!\r\n");
	}
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
	test_qhstring_case1();
#ifdef WIN32
    system("pause");
#endif
	return 0;
}