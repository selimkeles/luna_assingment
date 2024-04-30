# Assignment

In this assignment we ask to simulate getting some values from a smart meter, preparing a message for the server with the values from meter and sending it to a server. Please indicate how to build project in our environment and also how we can see the packages on server side. Please refer to "Requirements" section of this document for details.

Server side can be our local machine. So we can listen for some port and your application run on the same machine. Please tell us about how to do this on your way.

Below files are given to you.

- libmeter.a: A static library to simulate reading from meters. This library is compiled for x86_64 platform. So contact us if this library isn't work for your environment or you need to use a different platform.
- libmeter.h: Header file of the library.

## How to Submit Project

Please clone or download this project and do your development and create your documents in your own repository. Then you can send us the link of your repository.

## Preliminary Information

### OBIS Codes

Information in the smart meters are stored and read with OBIS codes, some kind of object numbers. Below you can find some (pseudo) OBIS codes. They are applicable for this assignment.

OBIS    | Description
---     | ---
1.8.0   | Total consumption (in kWh, floating point number)
1.8.1   | Consumption in tariff 1 (in kWh, floating point number)
1.8.2   | Consumption in tariff 2 (in kWh, floating point number)
1.8.3   | Consumption in tariff 3 (in kWh, floating point number)
2.8.0   | Daily consumption on last Monday (in kWh, floating point number)
2.8.1   | Daily consumption on last Tuesday (in kWh, floating point number)
2.8.2   | Daily consumption on last Wednesday (in kWh, floating point number)
2.8.3   | Daily consumption on last Thursday (in kWh, floating point number)
2.8.4   | Daily consumption on last Friday (in kWh, floating point number)
2.8.5   | Daily consumption on last Saturday (in kWh, floating point number)
2.8.6   | Daily consumption on last Sunday (in kWh, floating point number)
1.9.0   | Internal relay status (no unit, boolean, 0 or 1)

### Reading OBIS Codes via Library

Reading something from meter can be emulated with the library. This is done by calling ***getValueFromMeter*** function. First parameter is output buffer that this function will fill. Second parameter is the value that being requested. This parameter could be one of these;
- "readout". This request will fill output buffer with following obis codes
    - 1.8.0
    - 1.8.1
    - 1.8.2
    - 1.8.3
- Directly one of the obis codes below
    - "2.8.0"
    - "2.8.1"
    - "2.8.2"
    - "2.8.3"
    - "2.8.4"
    - "2.8.5"
    - "2.8.6"
    - "1.9.0"

Function will fill result with following format
```
OBIS(value)
```
or for readout
```
OBIS1(value1)|OBIS2(value2)|...
```

## Requirements for this assignment
1. Get following information from meter.
    - Total consumption
    - Consumption of previous calendar day
    - Internal relay status
2. Format this values as a JSON message as follows;
    ```json
    {
        "date" : "13.11.2022 20:28:43",
        "consumption" :
        {
            "total" : 12345.678,
            "previous_day" : 123.45
        },
        "relay_status" : true
    }
    ```
3. Encrypt this JSON string with AES.
4. Send encrypted message using socket functions.

## Deliverables
1. Source code (in a git repository).
2. Environment information and building instructions.
3. Your way to listen and get encrypted message. So we can see your project running.
4. AES encryption information and key that you use.

Nice to have
- Unit tests
