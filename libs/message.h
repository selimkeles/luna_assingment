#ifndef MESSAGE
#define MESSAGE

#include <stdbool.h>

// typedef struct
// {
//   double totalConsumption;
//   double tariff1;
//   double tariff2;
//   double tariff3;
//   double consumptionMonday;
//   double consumptionTuesday;
//   double consumptionWednesday;
//   double consumptionThursday;
//   double consumptionFriday;
//   double consumptionSaturday;
//   double consumptionSunday;
//   bool relay_status
// }OBIS_t;

char *find_yesterday(void);
char *create_message(char *total, char *yesterday, bool relaystatus);
char *create_timestamp(void);
char *parse_value(char *str);
bool parse_bool(char *str);
#endif
