# My Solution to the assignment
This is a solution for the assignment given by LUNA for reading values from metering device using API called libmeter. 

I have used some 3rd party libraries to perform: creating JSON strings, 16byte AES encryption. I couldn't implement unit test since I started little messy with the project but it could added in the feature. 

Also there are points that written so specific like using libmeter APIs. It could have written as full scan using X-MACROS but since assignment wanted only couple of parameters from the meter I wrote it that way. 

This program assumes that someone listens to the port that provided to connect and server started for that port. I written very simple plain server for that port where you can find in ```server``` directory.

More info about assignment may be found in ```assignment.md``` file.


## Directory Structure
```
luna_assignment/
├── libs
│   ├── 3rdPartyLibs
│   │   ├── aes.c
│   │   ├── aes.h
│   │   ├── jWrite.c
│   │   ├── jWrite.h
│   │   ├── libmeter.a
│   │   └── libmeter.h
│   ├── connection.c
│   ├── connection.h
│   ├── encryption.c
│   ├── encryption.h
│   ├── encyrption.o
│   ├── message.c
│   ├── message.h
│   ├── streamHandler.c
│   └── streamHandler.h
├── main.c
├── makefile
└── README.md
```

3rdPartyLibs includes JSON, AES and MeteringDevice libraries. Files modified according to the our usage. 

```connection.h``` includes server connection APIs,

```encryption.h``` includes AES encryption APIs,

```streamHandler.h``` includes streaming APIs,

## Build and Usage

Assuming you are using gcc c compiler using terminal command:
```make all``` will build everything in both UNIX and Windows systems.

You can use created luna assignment file like that:

```./luna_assignment <port_no> <broadcasting_seconds> ```

Minimum broadcasting second is 5 which will scan metering device datas and will return to the port specified.

> [Warning]  
> Using port numbers lower than 2000 will require sudo priviliges and may be occupied by OS. Using 8080 or 8081 recommended.

> [Warning]  
> This program will abort if no connection provided by the port specified.

Example Usage:
```
./luna_assignment 8081 5
```


## Encryption

In this project CTR mode of operation AES used since we are encrypting JSON file and I do not want padding. In debug spec you can observe original message, encryted message, decrypted message(Which is basically encrypting again since we using CTR mode).

KEY:
```
9876543210101112
```

CTR IV:
```
0123456789101112
```

> [Note]  
> Changing KEY's and resetting IV after certain bytes delivered is important for the security but it is more complicated and needs agreement of the both client and server side.

## Testing and Listening

Unit tests does not provided sorry about that but couldn't think about that much complicated project at the beginning and also needed to change directory structure at the development. You can test communication processes as I mentioned earlier via using server script that procided ind ```server``` directory.

Usage:
```
./server <port_no>
```

> [Important]  
> You must start server before executing the project.