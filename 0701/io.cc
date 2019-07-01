#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>
using namespace std;

void SetNonBlock(int fd){
    int fl = fcntl(fd,F_GETFL);
    if(fl < 0){
        return;
    }
    fcntl(fd,F_SETFL,fl|O_NONBLOCK);
}

int main(){
    std::string s;
    SetNonBlock(0);
    while(1){
        cin>>s;
        cout<<s<<std::endl;
        cout<<"AAAAAA"<<endl;
        sleep(1);
    }
    return 0;
}
