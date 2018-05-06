#include <cstdlib>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <string.h>
#include <string>
#include "TCPClient.h"

using namespace std;

int main(int argc, char** argv) {
   
    char *servername = "127.0.0.1";
    int port = 1955;
    
    TCPClient tcp;
    if(!tcp.setup(servername,port)) {
        cout << "Connecting failed" << endl;
        return EXIT_FAILURE;
    }
    
    string status = tcp.receive();
    cout << "You are now " << status << endl;
    
    string variable;
    
    cout << "enter value" << endl;
    cin >> variable;
    
    std::string id = "2";     // get from pos to the end
    
    string json_set= "{\"jsonrpc\": \"2.0\", \"method\": \"Store_Val\", \"params\": \""+variable+"\" ,\"id\": \""+id+"\"}";
     cout << "Sending:" << json_set << endl;
        //Get value frequently.
        tcp.Send(json_set);
           
        //Receive the string containing the value
        string rec = tcp.receive();
        if( rec != "" )
        {
                cout << "Server Response: " << rec;
        }
   
    string json_get= "{\"jsonrpc\": \"2.0\", \"method\": \"Read_Latest_Val\", \"id\": \""+id+"\"}";

    return 0;
}

