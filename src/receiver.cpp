#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/cuda.hpp> 

#include <thread>

#include <iostream>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h> 
#include <string.h>


int main(int argc, char* argv[])
{
    bool ip4_address = true;


    char* serverIP = "127.0.0.1";   // default IP4 address for local server.


    switch(argc) 
    {
        case 1:
        {
            std::cout << "Connecting to server over IP4 address\n";
            break;
        }

        case 2:
        {
            int argv_len = 0, j=0;
            while (argv[1][j] !=NULL)
            {
                argv_len += 1;
                j += 1;
            }
            serverIP = argv[1];
            if (argv_len > 15)
            {
                ip4_address = false;
                std::cout << "Connecting to server over IP6 address\n";
            }
            else
            {
                std::cout << "Connecting to server over IP4 address\n";
            }
            break;
        }

        default:
        {
            std::cout << "Usage is ./receiver [ip address (IP4 or IP6) of the server]\n";
            std::cout << "Since input arguments are more than required, hence exiting the code\n";
            exit(1);
        }
    
    }
        
    int sokt, serverPort = 4097;

    if (ip4_address)
    {

        struct  sockaddr_in serverAddr_ip4;
        socklen_t addrLen_ip4 = sizeof(struct sockaddr_in);


        if ((sokt = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
        {
            std::cerr << "socket() failed" << std::endl;
        }

        serverAddr_ip4.sin_family = PF_INET;
        serverAddr_ip4.sin_addr.s_addr = inet_addr(serverIP);
        serverAddr_ip4.sin_port = htons(serverPort);

        if (connect(sokt, (sockaddr*)&serverAddr_ip4, addrLen_ip4) < 0) 
        {
            std::cerr << "connect() failed!" << std::endl;
            perror("connect()");
            exit(1);
        }

    }


    if (ip4_address == false)
    {
        struct  sockaddr_in6 serverAddr_ip6;
        socklen_t addrLen_ip6 = sizeof(struct sockaddr_in6);
        if ((sokt = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) < 0) 
        {
            std::cerr << "socket() failed" << std::endl;
        }

        serverAddr_ip6.sin6_family = AF_INET6;
        inet_pton(AF_INET6, serverIP, &serverAddr_ip6.sin6_addr);
        serverAddr_ip6.sin6_port = htons(serverPort);

        if (connect(sokt, (sockaddr*)&serverAddr_ip6, addrLen_ip6) < 0) 
        {
            std::cerr << "connect() failed!" << std::endl;
            perror("connect()");
        }

    }





    cv::Mat frame;
    frame = cv::Mat::zeros(720 , 1280, CV_8UC3);    
    int frameSize = frame.total() * frame.elemSize();
    uchar *iptr = frame.data;
    int bytes = 0;
    int key;

    cv::namedWindow("Client", cv::WINDOW_AUTOSIZE);

    while (key != 'q') 
    {


        if ((bytes = recv(sokt, iptr, frameSize , MSG_WAITALL)) == -1) 
        {
            // std::cerr << "recv failed, received bytes = " << bytes << std::endl;
        }
        
        cv::imshow("Client", frame); 
      
        if (key = cv::waitKey(10) >= 0) break;
    }   

    close(sokt);




   return 0;
}