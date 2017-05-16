**** Jason's Net code README ****
I probably made this much more complicated than it needs to be, but 
that's because I'm trying to adhere to the code conventions that I've 
learned of up till now.

Action games use UDP, because UDP is much faster, and you usually
only really care about the latest input from the user. Waiting for old
input to arrive does you no good if the server won't process your new
input that's trying to avoid immediately dying in the here and now
(or at least your version of the here and now; more on that later).

So, given that I needed to use UDP sockets, that means connectionless
communication. One way only, no way to confirm that data gets to where 
it's supposed to go, or in the order it's supposed to arrive. That
being said, I chose to initially go with blasting packets to/from the
client(s) and server, on the assumption that if the last packet didn't
make it, the next packet will (with more up to date info).

So I made some classes, including the following:
UDPSocket (does the actual sending/receiving)
Clientpacket (contains input)
Serverpacket (contains coords/gameover)
Clientlink (sends/receives on client side)
Serverlink (sends/receives on server side)

I then made some dummy executables that make use of these classes,
named clientmain.cpp and servermain.cpp. The dummy executables are
supposed to simulate a very simple game, on top of which we can add
your code (or place my classes into your code -- I don't care either
way).

The Clientlink sends Clientpackets and receives Serverpackets. As
you'd expect, the Serverlink sends Serverpackets and receives
Clientpackets. The main difference between the two is that Serverlink
sends THE SAME packet to two clients. Clients update the server with
input, and the server updates the clients with position and gameover
status, as well as client connection status:

0 = no clients connected
1 = 1 client connected
2 = 1 client connected, 1 client missing (no packets in a while)
3 = 2 clients fully connected (recent packets for both)

I do have logic included for client disconnects/packet timeouts. We
can pretty easily change it to suit our needs. I also included logic
on the client side for server disconnects.

To use:

I made a makefile. Simply download everything into a directory and
type 'make all'. You will then see a 'client' and 'server' executable.

Usage:
server [local port]
client [local port] [server ip] [server port]

Examples (server must be started first):
server 50001
client 50010 192.168.1.8 50001
client 50011 192.168.1.8 50001

To exit either program, use ctrl-c.

Questions, email jlmcanally@gmail.com. I can do a youtube demo if
necessary.