#include "./streamHandler.h"
#include "./3rdPartyLibs/libmeter.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./message.h"
#include "./connection.h"
#include "./encryption.h"

void init(int argc, char *argv[]) {
  if (initializeMeterComm() != SUCCESS) {
    printf("Couldn't initialized metering device\n\n");
    exit(0);
  }
  if (argc < 3) {
    printf("Usage: %s <port> <scan time in seconds>\n", argv[0]);
    exit(0);
  }
  int portno = atoi(argv[1]);
  start_connection(portno);
  printf("connection started at local port: %d\n", portno);
  int scantime = atoi(argv[2]);
  if (scantime < 5) {
    scantime = 5;
  }
  printf("stream started with %d sec broadcasting\n", scantime);
  handle_stream(scantime);
  end_connection();
}

void handle_stream(int scantime) {
  clock_t startTime = clock();
  clock_t finishTime = scantime * CLOCKS_PER_SEC;
  while (1) {
    if (clock() > startTime + finishTime) {
      if (scan_metering_device()) {
        startTime = clock();
      }
    }
  }
}

int scan_metering_device(void) {
  char input_buff[200];
  getValueFromMeter(input_buff, "readout");
  char *total_usage = parse_value(input_buff);

  if (total_usage != NULL) {

    char *yesterday = find_yesterday();
    getValueFromMeter(input_buff, yesterday);
    free(yesterday);
    char *yesterday_usage = parse_value(input_buff);
    if (yesterday_usage != NULL) {
      getValueFromMeter(input_buff, "1.9.0");
      bool relaystatus = parse_bool(input_buff);
      char *output = create_message(total_usage, yesterday_usage, relaystatus);
      printf("json:\n%s", output);
      encrypt_data(output, strlen(output));
      printf("\n\nafterencrypt:\n%s", output);
      int res = write_to_port(output, strlen(output));
      encrypt_data(output, strlen(output));
      printf("\n\nafterdecrypt:\n%s", output);
      free(output);
      free(total_usage);
      free(yesterday_usage);
      return res;
    } else {
      return 0;
    }
    free(total_usage);
  } else {
    return 0;
  }
}
