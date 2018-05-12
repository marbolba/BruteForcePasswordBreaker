#pragma once

#include<iostream>
#include<string>

using namespace std;

class Service
{
private:
    string _password;
public:
    Service(){}
    void setPassword(string pass);
    bool auth(string pass);

};
