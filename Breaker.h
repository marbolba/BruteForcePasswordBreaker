#pragma once

#include<iostream>
#include<string>
#include"Service.h"
#include <thread>
#include <vector>
#include <mutex>
#include <time.h>

using namespace std;

class Breaker
{
private:
    int maxStrLen=5;        //default password length
    int alreadyTested=0;

    bool _isFound;
    string _foundPassword;
    string _tryPass;
    Service _service;
    const static int _signsNumber=62;
    char _signsTable[_signsNumber]={    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                        '0','1','2','3','4','5','6','7','8','9'};
    int nr_threads;
    thread* threadsArray;

    time_t start_time;
    time_t end_time;


    inline bool getAllPossibilities(string prefix,int lenRemaining);//optimalization #1
    void killAllThreads();
    bool breakingProcedure();
public:
    Breaker(Service thisService);
    ~Breaker();
    void startBreaking();
    void setMaxPasswordLength(int);
    string getFoundPassword(){return _foundPassword;}
};
