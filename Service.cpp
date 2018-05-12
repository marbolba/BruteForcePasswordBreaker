#include"Service.h"

void Service::setPassword(string pass)
{
    if(_password.empty())        //temporary, later check authorisation, sesion etc.
    {
        cout<<"setting pass: "<<pass<<" ..."<<endl;
        _password=pass;
    }
    else
        cout<<"you can't reset password"<<endl;
}
bool Service::auth(string pass)
{
    if(!pass.compare(_password))
    {
        cout<<"AUTHORISATION GRANTED!"<<endl;
        return true;
    }
    return false;
}
