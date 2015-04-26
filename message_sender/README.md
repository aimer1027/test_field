take care , in order to save compile time ,
I write only a series of compile file : configure.in and Makefile.am
so when you try to run the client/client.cpp by ./build.sh 
or server/server.cpp by ./build.sh you must make sure that 
only one server.cpp server2.cpp (client.cpp client2.cpp ) in the current path

run ./build.sh or just run command autoscan under the path with two main function .cpp file will cause a confusion to the compiler
server.cpp and client.cpp are one pair
server2.cpp and client2.cpp are in one pair

you know that autoscan can scan all the .cpp files in current executing command path ,
so , one simple way to keep just one .cpp file in current path 
you can mv server2.cpp server2.cpp.bak to prevent 'autoscan' command scan the server2.cpp which contains another main entry function in it

--------------------------------------------
here is how to use this program 
1. change path to server first 

2. mv server.cpp server.cpp.bak

3. ./build.sh to compile and link all the source files
   if everything goes well, you will get a executable file with the name of message_sender_server

4. run server by command
   ./message_sender_server
   now , the server is running ,eventhough nothing print out on screen

5. open a new terminal console , change path to client 
   
   mv client.cpp client.cpp.bak
  
6. compile files with the command : ./build 
   if everything goes right , you can find a executable binary file with the name of message_sender_client

7. run client by command 
   ./message_sender_client
   then , you will see the prompted message 'input message' input from keyboard

8. change server running terminal , you will see the {"message data:"+ the message input by you}

ps : do not forget chmod of you build.sh shell script
