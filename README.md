# messaging-on-ports
A simple program to send messages via terminal using open ports
To run these programs, run these commands on your linux terminal.
First open four different terminals.
Then compile and run the get1.c and get2.c programs in the two terminals ------- gcc get1.c -o get1  (comiling) -------./get1   (run).
Then in the other two terminals compile and run the send1.c and send2.c programs.


Functionality: So basically the send1 program is sending messages on port number 1234 which is received by port 1234 (using get1 program) , and similarly send2 program is sending messages on port 1235 which is received by port 1235 (using get2 program).
