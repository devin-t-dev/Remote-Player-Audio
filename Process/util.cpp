#include <iostream>
#include <cstring> //strcpy
#include "util.h"
#include <math.h>
char * toChar(std::string Stringa)
{
	//Stringa=Archivio->lista[Archivio->puntatore];
	char * result = new char [Stringa.length()+1];
	std::strcpy (result, Stringa.c_str());
	return result;
}
std::string utilGetName(std::string percorso)
{
	std::string temp;
	for (int i=0;i<percorso.length();i++) {
		if (percorso[i]=='/')
		{
				temp="";
				continue;
		}
		if (percorso[i]=='.') {break;}//ToDO: I punti dentro il file possono esistere anche non per l'estensione!
		temp+=percorso[i];
	}
	return temp;
}
/*int toInt(std::string Stringa)
{
	int value = atoi(Stringa.c_str());
	return value;
}*/

inline int mypow(int a, int b)
{
    if (b==0) return 1;
    if (a==0) return 0;
    return a*mypow(a, b-1);
}

char * FromIntToChar(int num)
{
	const int n=int(log(num)/log(10)+1);
	char* num_string=new char[n];
	num_string[n]='\0';
	for (int i=n-1, j=0; i>=0; i--, j++)
	{
		num_string[j]=int(num%int(mypow(10, i+1)))/int(mypow(10, i))+'0';
	}
	return num_string;
}
