#include"Breaker.h"

Breaker::Breaker(Service thisService)
{
    _service=thisService;
    _isFound=false;
    _foundPassword="";
    _tryPass="";
    nr_threads = thread::hardware_concurrency();
}
Breaker::~Breaker()
{
    if(threadsArray!=NULL)
    delete [] threadsArray;
}
void Breaker::setMaxPasswordLength(int len){this->maxStrLen=len;}
inline bool Breaker::getAllPossibilities(string prefix,int lenRemaining)
{
    if(_isFound)                                    //optimalization #3
        return true;

    if(lenRemaining<(maxStrLen-alreadyTested))      //optimalization #2
        if(_service.auth(prefix))
        {
            _isFound=true;
            _foundPassword=prefix;
            try{
            killAllThreads();
            }catch(...){}
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
    return false;
}
void Breaker::killAllThreads()
{
    {
        for(int i=0;i<nr_threads;i++)
            threadsArray[i].detach();
    }
    //for(int i=0;i<1000;i++){cout<<".";}
    delete []threadsArray;
    //threadsArray=NULL;
    cout<<"koniec"<<endl;
}
bool Breaker::breakingProcedure()
{
    threadsArray=new thread[nr_threads];    //init table each time

    cout<<"breaking using "<<nr_threads<<" threads..."<<endl;
    for(int i=0;i<_signsNumber;i++)
    {
        string tmp;tmp.push_back(_signsTable[i]);
        int thr_nr=i%nr_threads;
        cout<<"thread "<<thr_nr<<" does "<<_signsTable[i]<<"..."<<endl;

        threadsArray[thr_nr]=thread(&Breaker::getAllPossibilities,this,tmp,maxStrLen-1);

        try{
            if(thr_nr==nr_threads-1)
            {
                for(int i=0;i<nr_threads;i++)
                    if(!_isFound)
                        threadsArray[i].join();
            }
        }catch(...){}
        if(!_foundPassword.empty())
            break;
    }
    if(!_foundPassword.empty())
    {
        end_time=time(NULL);
        cout<<"***END BREAKING*** in time: "<<end_time-start_time<<"(s)"<<endl;
        return true;
    }
    else
    {
        cout<<"***INTERATE LETTER***"<<endl;
        try{
        killAllThreads();
        }catch(...){}
        return false;
    }
}
void Breaker::startBreaking()
{
    start_time=time(NULL);
	if(breakingProcedure())    //default for passwords of length 5
        return;

    maxStrLen++;
    for(maxStrLen;maxStrLen<10;maxStrLen++)         //10 is max letters to check!
    {
        alreadyTested=maxStrLen-1;
        cout<<"maxStrLen="<<maxStrLen<<", alreadyTested="<<alreadyTested<<endl;
        if(breakingProcedure())
            return;
    }
}
