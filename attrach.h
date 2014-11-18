/* Attrach.h
 * by James Rubingh
 * james@wrive.com
 */

#define VERSION "0.1.0"

// default to 20MB file
#define DEFAULT_MAX_FILE_SIZE 20971520
#define DEFAULT_CHUNK_SIZE 2048
#define ATTR_BASE_NAME "attrach%u"
#define ATTR_BASE_NAME_LENGTH 7

//names are attrach0 - attrach123456789012, etc.
#define ATTR_LENGTH 25

#define ATTRACH_ERR_SWITCH 1
#define ATTRACH_ERR_USAGE 2
#define ATTRACH_ERR_ATTACH 3
#define ATTRACH_ERR_RETRIEVE 4
#define ATTRACH_ERR_FILE 5
#define ATTRACH_ERR_READ 6
#define ATTRACH_ERR_FILE_OUT 7
#define ATTRACH_ERR_REMOVE 8

#define ATTRACH_VERBOSE_ON 420

typedef unsigned char byte;

void show_usage();
void error_exit(int);
int attach_file(char *, char *);
int chunk_and_attach(char *, byte *, int);
int retrieve_file(char *, char *);
int main(int, char**);

int verbose_flag = 0;
char attribute_name[] = "attrach";
