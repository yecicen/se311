//============================================================================// Name        : LAB10.cpp
// Author      : Yunus Emre Çiçen
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;
class MyException{
public:
	void message(){
		cout<<"MyException has occured"<<endl;
	}
};
void Subs(int num1, int num2)
{
	if(num1 <0 || num2 <0)
		throw 1.5;
	else if(num2>num1)
		throw 'a';
	cout<<num1-num2;
}

int main() {
	int num1, num2;
	cout << "enter two integers that are positive:" <<endl;
	cin >>num1 >> num2;
	try{
		Subs(num1, num2);
		try{
			if(num1>100 || num2> 100){
				MyException e;
				throw e;
			}
		}
		catch(MyException e){e.message();}
	}
	catch(double){cout<<"Numbers negative"<<endl;}
	catch(char){cout<<"Num2 bigger than num1"<<endl;}
	return 0;
}
