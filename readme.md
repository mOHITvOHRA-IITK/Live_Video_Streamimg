# Live Video Streamimg
This repo contains the code for streaming the camera (or Laptop webcam) data over a TCP/IP protocol via c++ sockey commands. The codes are written to stream the videos over IP4 as well IP6 addresses. 


## Requiremets
	Make sure you have [OpenCV](https://opencv.org/get-started/) installed.
	Make sure you have [g++](https://linuxhint.com/install-and-use-g-on-ubuntu/) installed. 
	Make Sure you have [cmake](https://cgold.readthedocs.io/en/latest/first-step/installation.html) installed on your machine.
	
	
## Steps to create the executables
* Download the repository.
* Build the executables in `bin` folder by running following commands:
		cd Live_Video_Streamimg/build
		cmake ..
		make



## Running the executables
* To execute the server, run the executable with following command:
		cd Live_Video_Streamimg/bin
		./broadcast_images

by default, the server will broadcast with IP4 address. If need to transfer data over IP6 address, use the command with arguments
		./broadcast_images IP6
		
* To execute the client, run the executable with following command:
		cd Live_Video_Streamimg/bin
		./receiver

by default, the receiver/client will receive use the server IP4 address which is 127.0.0.1, that is localhost address. But to specify the server IP4/IP6 address, pass the server IP address in arguments.
		./receiver [IP4 or IP6 address]

Please note that [If the servers use IPv6, clients can use either IPv6 or IPv4] (https://www.ibm.com/docs/en/csfdcd/7.1?topic=z-ipv4-ipv6-addressing).
