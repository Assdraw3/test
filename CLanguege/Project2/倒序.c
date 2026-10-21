#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void use(char* arr,int len)
{
	int left = 0;
	int right = len;
	char temp = '\0';
	while (left < right)
	{
		temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		left++;
		right--;
	}


}
void rad(char* arr, int left)
{
	int right = left;
	while (1)
	{
		if (arr[right] != ' ' && arr[right] != '\0')
		{
			right++;
		}
		else if(arr[right] == ' ')
		{
			arr[right] = '\0';
			rad(arr, right + 1);
			//use(arr + left, right - left-1);
			printf("%s ",arr+left);
			break;
		}
		else
		{
			//use(arr+left, right - left-1);
			printf("%s ", arr + left);
			break;
		}
	}
	
}
int main()
{
	char arr[] = "I want to go home.";
	rad(arr, 0);




	return 0;
}
