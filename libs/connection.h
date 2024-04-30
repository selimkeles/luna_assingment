#ifndef CONNECTION
#define CONNECTION

int start_connection(int portno);
int write_to_port(char *buffer, int len);
int end_connection(void);
#endif
