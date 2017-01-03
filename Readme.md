## Introduction

The NetPeer plugin provide a tcp client function to connect to tcp server. You can connect to a tcp server and handle all the message packets in blueprint, No need c++. It's very easy to connect to you exist server project with the `NetPeer` .

## Features

* All in blueprint, No need c++.
* Support all the fundamental data type, like `int8`,`int16` ,`int64` etc.
* Support the `User Defined Struct` in blueprint.
* Use  [MessagePack](http://msgpack.org/) to pack and unpack the net message in `NetPeer`, `MessagePack` is small, fast and easy to used in your server project.
* Support `Latent` to easy handle the message packet.
* Create more than one TCP connections
* Include automation test.

## Directories 

* Client - Contains the ue4 test project and the NetPeer plugin.
  * Plugins - Contains the `NetPeer` plugin.
* Server - Contains a tcp server project for testing. 

## Example

1. Execute the `Server/CPlusPlusTcpServer/SimpleTcpServer/Release/SimpleTcpServer.exe`

2. Open the `Client/MakeSocket.uproject` with ue4.

3. Play the level `TestNetPeer`

4. Click `Connect To Server` and check the logs on screen.  

   > The `SimpleTcpServer.exe ` must be in the same machine with ue4, or you must modify the `Server Ip` in `MainMenuWB` to the `SimpleTcpServer.exe ` machine's  ip.

## Use  

* All functions under `NetPeer` Category in blueprint.

* The `MyGameInstance` and `UI/MainMenuWB` blueprint show how to use `NetPeer`.

  1. Construct a `Netpeer` instance with `Construct Object from class` blueprint function.
  2. Connect to a tcp server with `Connect` blueprint function
  3. Create a user defined struct to match your server message data struct.
  4. Bind user message handler with `Bind Net Message` blueprint function and your defined struct to handle message.   

  > You can handle the system message like `Reconnecting`,`Reconnect Successed` etc with `Bind Sys Message` blueprint function.  

  ​
