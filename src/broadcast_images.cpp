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


int main(int argc, char* argv[])
{

    bool ip4_address = true;

    if (argc <= 2)
    {
        if (argc == 2)
        {
            if (strcmp(argv[1], "IP6") == 0)
            {
                ip4_address = false;
                std::cout << "Broadcasting images over IP6 address\n";
            }
            else
            {
                std::cout << "Broadcasting images over IP4 address\n";
            }
        }
        else
        {
            std::cout << "Broadcasting images over IP4 address\n";
        }
    }
    else
    {
        std::cout << "Usage is ./broadcasr_images [IP4 or IP6]\n";
        std::cout << "Since input arguments are more than required, hence exiting the code\n";
        exit(1);
    }


    int localSocket, remoteSocket, port= 4097;



    struct sockaddr_in localAddr_ip4, remoteAddr_ip4;
    int addrLen_ip4 = sizeof(struct sockaddr_in);
    if (ip4_address)
    {
        localSocket = socket(AF_INET , SOCK_STREAM , 0);
        if (localSocket == -1)
        {
            perror("socket() call failed!!");
        }  

        localAddr_ip4.sin_family = AF_INET;
        localAddr_ip4.sin_addr.s_addr = INADDR_ANY;
        localAddr_ip4.sin_port = htons( port );

        int reuse = 1;
        int result = setsockopt(localSocket, SOL_SOCKET, SO_REUSEADDR, &reuse,sizeof(reuse));

        if( bind(localSocket, (struct sockaddr *)&localAddr_ip4, addrLen_ip4) < 0) 
        {
            perror("Can't bind() socket");
            exit(1);
        }

        listen(localSocket , 3);

        std::cout <<  "Waiting for connections...\n"
                  <<  "Server Port:" << port << std::endl;

        remoteSocket = accept(localSocket, (struct sockaddr *)&remoteAddr_ip4, (socklen_t*)&addrLen_ip4);  
        if (remoteSocket < 0) 
        {
            perror("accept failed!");
            exit(1);
        } 
        std::cout << "Connection accepted" << std::endl;
    }


    struct sockaddr_in6 localAddr_ip6, remoteAddr_ip6;
    int addrLen_ip6 = sizeof(struct sockaddr_in6);
    if (ip4_address == false)
    {
        localSocket = socket(AF_INET6 , SOCK_STREAM , 0);
        if (localSocket == -1)
        {
            perror("socket() call failed!!");
        }

        localAddr_ip6.sin6_family = AF_INET6;
        localAddr_ip6.sin6_addr = in6addr_any;
        localAddr_ip6.sin6_port = htons( port );

        int reuse = 1;
        int result = setsockopt(localSocket,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));

        if( bind(localSocket,(struct sockaddr *)&localAddr_ip6, addrLen_ip6) < 0) 
        {
            perror("Can't bind() socket");
            exit(1);
        }

        listen(localSocket , 3);
        
        std::cout <<  "Waiting for connections...\n"
                  <<  "Server Port:" << port << std::endl;


        remoteSocket = accept(localSocket, (struct sockaddr *)&remoteAddr_ip6, (socklen_t*)&addrLen_ip6);  
        if (remoteSocket < 0) {
            perror("accept failed!");
            exit(1);
        } 
        std::cout << "Connection accepted" << std::endl;
    }





    


    

    cv::VideoCapture camera(0); 
    if (!camera.isOpened()) 
    {
        std::cerr << "ERROR: Could not open camera" << std::endl;
    }

    cv::namedWindow("Server", cv::WINDOW_AUTOSIZE);
    cv::Mat frame;

    int fps = camera.get(cv::CAP_PROP_FPS);

    int frameSize;
    int bytes = 0;

    while (1) 
    {
        camera >> frame;  

        if (frame.rows > 0)
        {
            frameSize = frame.total() * frame.elemSize();
            cv::imshow("Server", frame);
            cv::waitKey(10);
            send(remoteSocket, frame.data, frameSize, 0);
            if (cv::waitKey(10) == 27)
            {
               break;
            }

        }

    }
    
    close(localSocket);
    
    return 0;
}
