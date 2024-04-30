#include "./message.h"
#include "./3rdPartyLibs/jWrite.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *find_yesterday(void) {

  time_t timestamp = time(NULL);
  struct tm *tm = localtime(&timestamp);
  int day = tm->tm_wday;
  if (day == 0)
    day = 7;
  day -= 1;
  char *temp = malloc(20);
  if (day == 0)
    sprintf(temp, "2.8.0");
  else
    sprintf(temp, "2.8.%d", day);
  char *res = strdup(temp);
  free(temp);
  return res;
}

char *parse_value(char *str) {
  char *value;
  value = strchr(str, '(');
  if (value != NULL) {
    value++;
    char *end = strchr(value, ')');
    if (end != NULL) {
      *end = '\0';
      char *result = strdup(value);
      return result;
    }
  }
  return NULL;
}

bool parse_bool(char *str) {
  char *value;
  value = strchr(str, ':');
  if (value != NULL) {
    value++; // skip the '('
    if (*value == '1') {
      return true;
    }
  }
  return false;
}

char *create_message(char *total, char *yesterday, bool relaystatus) {
  char *timedate = create_timestamp();
  char *json = malloc(sizeof(char) * 300); // allocate memory
  jwOpen(json, 300, JW_OBJECT, JW_PRETTY); // open root node as object
  jwObj_string("date", timedate);
  jwObj_object("consumption");
  jwObj_double("total", atof(total));            // writes "key":"value"
  jwObj_double("previous_day", atof(yesterday)); // writes "int":1
  jwEnd();                                       // end the array
  jwObj_bool("relay_status", relaystatus);
  jwEnd();   // end the array
  jwClose(); // close root object - done
  free(timedate);
  return json;
}

char *create_timestamp(void) {
  time_t timestamp = time(NULL);
  struct tm *tm = localtime(&timestamp);
  char *timedate = malloc(sizeof(char) * 40); // allocate memory
  sprintf(timedate, "%.2d.%.2d.%.4d %.2d:%.2d:%.2d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
  return timedate;
}
