#include<iostream>
#include<string>
#include"Breaker.h"
#include"Service.h"

using namespace std;

int main()
{
    cout<<"Start..."<<endl<<"Please type password: ";
    string pass;
    cin>>pass;

//setting service to break
    Service service;
    service.setPassword(pass);
//setting and starting breakers
    Breaker passwordBreaker(service);
    //passwordBreaker.setMaxPasswordLength(5);
    passwordBreaker.startBreaking();
    cout<<"Znalezione haslo to: "<<passwordBreaker.getFoundPassword()<<endl;

}
