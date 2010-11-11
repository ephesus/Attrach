/* Attrach.h
 * by James Rubingh
 * james@wrive.com
 */

#define VERSION "0.0.0"

// default to 20MB file
#define DEFAULT_MAX_FILE_SIZE 20971520
#define ATTR_NAME "attrach"

#define ERR_SWITCH 1
#define ERR_USAGE 2
#define ERR_ATTACH 3
#define ERR_RETRIEVE 4
#define ERR_FILE 5
#define ERR_READ 6
#define ERR_FILE_OUT 7

typedef unsigned char byte;

void show_usage();
void error_exit(int);
int attach_file(char *, char *);
int retrieve_file(char *, char *);
int main(int, char**);

int verbose = 0;

