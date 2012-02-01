#include "Utils.h"

int ftokpos;
char* ftokstr;
char temp[20];

int fstricmp(char* s1,char* s2)
{
	int res = 1;
	int i=0;
	while(s1[i]!=0&&s2[i]!=0)
	{
		if (ftolower(s1[i])!=ftolower(s2[i]))
			res = 0;
		i++;
	}
	if (s1[i] != s2[i]) return 0; //End of string
	return res;

}

char ftolower(char c)
{
	if(c>='A'&&c<='Z')
		c=c - 'A' + 'a';
	return c;
}

int fatoi(char* str)
{
int sum=0,i;
if (str == 0) return 0;
if (str[0]<'0'&&str[0]>'9')
	return -1; //It is string
	for(i=0;str[i];i++)
	{
		if(str[i]>='0'&&str[i]<='9')
			sum=sum*10+(str[i]-'0');
	}

return sum;
}

int fstrcpy(const char* s,char* d)
{
	int i;
	if (d == 0) return -1; //No target

	if (s==0) //No source
	{
		d[0]=0;
		return -2;
	}
	for(i=0;s[i];i++)
		d[i] = s[i];
	d[i] = 0;
	return 0;
}

char* fstrtok(char* s,char c)
{
int i;
if (s!=0)
{
	ftokpos = 0;
	ftokstr = s;
}
else
	s = ftokstr;
if (s[ftokpos]==0) //If it is alredy in end of string
	return 0;		// NULL

	for(i=0;s[ftokpos]!=c&&s[ftokpos]!=0;ftokpos++,i++)
	{
		temp[i] = s[ftokpos];
	}
	temp[i] = 0;
	while(s[ftokpos]==c) // Ignore this char
		ftokpos++;

	return temp;
}





