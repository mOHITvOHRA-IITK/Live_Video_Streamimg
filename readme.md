# Live Video Streamimg
This repo contains the code for streaming the camera (or Laptop webcam) data over a TCP/IP protocol via c++ sockey commands. The codes are written to stream the videos over IP4 as well IP6 addresses. 


## Requiremets

	Make sure you have [OPenCV](https://opencv.org/get-started/) installed.
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
		
	* To execute the client, run the executable with following command:
		cd Live_Video_Streamimg/bin
		./receiver
