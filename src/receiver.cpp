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



// int main(int, char**) 
// {


//     int         sokt;
//     char*       serverIP = "192.168.0.201";
//     int         serverPort = 4097;


//     struct  sockaddr_in serverAddr;
//     socklen_t           addrLen = sizeof(struct sockaddr_in);


//     if ((sokt = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
//     {
//         std::cerr << "socket() failed" << std::endl;
//     }


//     serverAddr.sin_family = PF_INET;
//     serverAddr.sin_addr.s_addr = inet_addr(serverIP);
//     serverAddr.sin_port = htons(serverPort);

//     if (connect(sokt, (sockaddr*)&serverAddr, addrLen) < 0) 
//     {
//         std::cerr << "connect() failed!" << std::endl;
//     }


//     cv::Mat frame;
//     frame = cv::Mat::zeros(720 , 1280, CV_8UC3);    
//     int frameSize = frame.total() * frame.elemSize();
//     uchar *iptr = frame.data;
//     int bytes = 0;
//     int key;

//     cv::namedWindow("Client", cv::WINDOW_AUTOSIZE);

//     while (key != 'q') 
//     {

//         if ((bytes = recv(sokt, iptr, frameSize , MSG_WAITALL)) == -1) 
//         {
//             std::cerr << "recv failed, received bytes = " << bytes << std::endl;
//         }
        
//         cv::imshow("Client", frame); 
      
//         if (key = cv::waitKey(10) >= 0) break;
//     }   

//     close(sokt);





//    return 0;
// }


int main(int, char**) 
{


    int         sokt;
    char*       serverIP = "fc94:ebb:4bfb:956c:b466:e73f:8a11:5f14";
    int         serverPort = 4097;


    struct  sockaddr_in6 serverAddr;
    socklen_t           addrLen = sizeof(struct sockaddr_in6);

    


    if ((sokt = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    {
        std::cerr << "socket() failed" << std::endl;
    }


    serverAddr.sin6_family = AF_INET6;
    // inet_pton(AF_INET6, "::1", &serverAddr.sin6_addr);
    inet_pton(AF_INET6, serverIP, &serverAddr.sin6_addr);

    serverAddr.sin6_port = htons(serverPort);

    if (connect(sokt, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) 
    {
        std::cerr << "connect() failed!" << std::endl;
        perror("connect()");
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