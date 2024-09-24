#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/cuda.hpp> 

#include <thread>

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h> 
#include <string.h>



// int main(int, char**) 
// {


//     int localSocket,remoteSocket, port= 4097;

//     struct sockaddr_in localAddr, remoteAddr;
//     int addrLen = sizeof(struct sockaddr_in);
//     localSocket = socket(AF_INET , SOCK_STREAM , 0);
//     // localSocket = socket(AF_INET6 , SOCK_STREAM , 0);
//     if (localSocket == -1)
//     {
//          perror("socket() call failed!!");
//     }  

//     localAddr.sin_family = AF_INET;
//     localAddr.sin_addr.s_addr = INADDR_ANY;
//     localAddr.sin_port = htons( port );


//     int reuse = 1;
//     int result = setsockopt(localSocket,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));

//     if( bind(localSocket,(struct sockaddr *)&localAddr , sizeof(localAddr)) < 0) 
//     {
//          perror("Can't bind() socket");
//          exit(1);
//     }
    
//     //Listening
//     listen(localSocket , 3);
    
//     std::cout <<  "Waiting for connections...\n"
//               <<  "Server Port:" << port << std::endl;



//     remoteSocket = accept(localSocket, (struct sockaddr *)&remoteAddr, (socklen_t*)&addrLen);  
//     //std::cout << remoteSocket<< "32"<< std::endl;
//     if (remoteSocket < 0) {
//         perror("accept failed!");
//         exit(1);
//     } 
//     std::cout << "Connection accepted" << std::endl;





//     cv::VideoCapture camera(0); 
//     if (!camera.isOpened()) 
//     {
//         std::cerr << "ERROR: Could not open camera" << std::endl;
//     }

//     cv::namedWindow("Server", cv::WINDOW_AUTOSIZE);
//     cv::Mat frame;

//     int fps = camera.get(cv::CAP_PROP_FPS);
//     std::cout << "fps: " << fps << "\n";

//     int frameSize;
//     int bytes = 0;

//     while (1) 
//     {
//         camera >> frame;  

//         if (frame.rows > 0)
//         {
//             // std::cout << "frame " << frame.rows << " " << frame.cols << "\n";

//             frameSize = frame.total() * frame.elemSize();
//             // std::cout << "frameSize: " << frameSize << "\n";
//             cv::imshow("Server", frame);
//             cv::waitKey(10);
//             send(remoteSocket, frame.data, frameSize, 0);
//             if (cv::waitKey(10) == 27)
//             {
//                break;
//             }

//         }

//     }
    

    
//     return 0;
// }





int main(int, char**) 
{


    int localSocket,remoteSocket, port= 4097;

    struct sockaddr_in6 localAddr, remoteAddr;
    int addrLen = sizeof(struct sockaddr_in);


    localSocket = socket(AF_INET6 , SOCK_STREAM , 0);

    if (localSocket == -1)
    {
         perror("socket() call failed!!");
    }  

    localAddr.sin6_family = AF_INET6;
    localAddr.sin6_addr = in6addr_any;
    localAddr.sin6_port = htons( port );


    int reuse = 1;
    int result = setsockopt(localSocket,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));

    if( bind(localSocket,(struct sockaddr *)&localAddr , sizeof(localAddr)) < 0) 
    {
         perror("Can't bind() socket");
         exit(1);
    }
    
    //Listening
    listen(localSocket , 3);
    
    std::cout <<  "Waiting for connections...\n"
              <<  "Server Port:" << port << std::endl;



    remoteSocket = accept(localSocket, (struct sockaddr *)&remoteAddr, (socklen_t*)&addrLen);  
    //std::cout << remoteSocket<< "32"<< std::endl;
    if (remoteSocket < 0) {
        perror("accept failed!");
        exit(1);
    } 
    std::cout << "Connection accepted" << std::endl;





    cv::VideoCapture camera(0); 
    if (!camera.isOpened()) 
    {
        std::cerr << "ERROR: Could not open camera" << std::endl;
    }

    cv::namedWindow("Server", cv::WINDOW_AUTOSIZE);
    cv::Mat frame;

    int fps = camera.get(cv::CAP_PROP_FPS);
    std::cout << "fps: " << fps << "\n";

    int frameSize;
    int bytes = 0;

    while (1) 
    {
        camera >> frame;  

        if (frame.rows > 0)
        {
            // std::cout << "frame " << frame.rows << " " << frame.cols << "\n";

            frameSize = frame.total() * frame.elemSize();
            // std::cout << "frameSize: " << frameSize << "\n";
            cv::imshow("Server", frame);
            cv::waitKey(10);
            send(remoteSocket, frame.data, frameSize, 0);
            if (cv::waitKey(10) == 27)
            {
               break;
            }

        }

    }
    

    
    return 0;
}
