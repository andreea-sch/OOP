#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;
int conv (const char * str)
{
    long numar=0,x=1;
    int n=strlen(str);
    for(int i=n-2;i>=0;i--)
    {
        numar = numar + (str[i] - '0') * x;
        x*=10;
    }
    return numar;
}

int main()
{
    long S=0;
    char line[1024];
    FILE *fp = fopen("init.txt","r");

    //Checks if file is empty
    if( fp == NULL ) {
        printf("N-am reusit sa gasim fisierul");
    }
    while((fgets(line,1024,fp))!=0)
    S=S+conv(line);
     cout<<S;
    return 0;
}
