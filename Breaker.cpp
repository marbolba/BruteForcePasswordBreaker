#include"Breaker.h"

Breaker::Breaker(Service thisService)
{
    _service=thisService;
    _isFound=false;
    _foundPassword="";
    _tryPass="";
    nr_threads = thread::hardware_concurrency();
    threadsArray=new thread[nr_threads];
}
Breaker::~Breaker()
{
    delete [] threadsArray;
}
bool Breaker::getAllPossibilities(string prefix,int lenRemaining)
{
    //cout<<prefix<<", ";
    if(_service.auth(prefix))
    {
        cout<<"found pass: "<<prefix<<endl;
        _foundPassword=prefix;
        //killAllThreads();
        return true;
    }

    if(lenRemaining==0)
    {
        return false;
    }

    for(int i=0;i<_signsNumber;i++)
    {
        if(getAllPossibilities(prefix+_signsTable[i],lenRemaining-1))
            return true;
    }
}
void Breaker::killAllThreads()
{
    threadsArray[0].detach();
    threadsArray[1].detach();
    threadsArray[2].detach();
    threadsArray[3].detach();
    threadsArray[4].detach();
    threadsArray[5].detach();
    threadsArray[6].detach();
    threadsArray[7].detach();
}
void Breaker::startBreaking()
{
    int maxStrLen=5;


    //int nr_threads = thread::hardware_concurrency();
    //thread threadsArray[nr_threads];
	cout<<"breaking using "<<nr_threads<<" threads..."<<endl;


    for(int i=0;i<_signsNumber;i++)
    {
        string tmp;tmp.push_back(_signsTable[i]);
        int thr_nr=i%nr_threads;
        cout<<"thread "<<thr_nr<<" does "<<_signsTable[i]<<"..."<<endl;

        threadsArray[thr_nr]=thread(&Breaker::getAllPossibilities,this,tmp,maxStrLen-1);

        if(thr_nr==7)
        {
            threadsArray[0].join();
            threadsArray[1].join();
            threadsArray[2].join();
            threadsArray[3].join();
            threadsArray[4].join();
            threadsArray[5].join();
            threadsArray[6].join();
            threadsArray[7].join();
        }
    }
}
