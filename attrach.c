/* Attrach
 * store files in the extended attributes on os x
 * by James Rubingh
 * james@wrive.com
 * 査読をお願いします
 *
 */

#include <sys/xattr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include<errno.h>

#include "attrach.h"

int attach_file(char * const source, char * const target)
{
    FILE *inf;
    const char attr_name[] = ATTR_NAME;
    int size = DEFAULT_MAX_FILE_SIZE;
    byte *buffer;
    int bytes_read;

    if (!(buffer = (byte *) malloc(sizeof(byte) * DEFAULT_MAX_FILE_SIZE))) {
        error_exit(ERR_FILE);
    }

    if (!(inf = fopen(source, "r+"))) {
        error_exit(ERR_FILE);
    }
    bytes_read = fread(buffer, sizeof(byte), size, inf);

    printf("%d\n", bytes_read);

    if (setxattr(target, attr_name, buffer, bytes_read, 0, XATTR_CREATE)) {
        free(buffer);
        error_exit(ERR_FILE); 
    }

    free(buffer);

    fclose(inf);
    return 0;
}

int retrieve_file(char *source, char *target)
{
    FILE *of, *tf;
    byte *buffer;
    int bytes_read;
    const char attr_name[] = ATTR_NAME;

    buffer = (byte *) malloc(sizeof(byte) * DEFAULT_MAX_FILE_SIZE);

    if (!(of = fopen(target, "w+"))) {
        error_exit(ERR_FILE);
    }

    if (!(bytes_read = getxattr(source, attr_name, buffer, sizeof(byte) * DEFAULT_MAX_FILE_SIZE, 0, XATTR_SHOWCOMPRESSION))) {
        error_exit(ERR_RETRIEVE); 
    }

    if (!(tf = fopen(target, "r+"))) {
        error_exit(ERR_FILE_OUT); 
    }

    fwrite(buffer, sizeof(byte), bytes_read, tf);

    return 0;
}

void error_exit(int err)
{
    char generic_fail[] = "Error happened";
    char attach_fail[] = "File Couldn't Be Attached";
    char retrieve_fail[] = "File Couldn't Be Retrieved :(";
    char file_fail[] = "File Couldn't Be Opened :(";
    char file_out_fail[] = "OutFile Couldn't Be Opened :(";

    char *error_message = generic_fail;

    switch (err) {
        case ERR_FILE_OUT:
            error_message = file_out_fail;
            break;
        case ERR_FILE:
            error_message = file_fail;
            break;
        case ERR_ATTACH:
            error_message = attach_fail;
            break;
        case ERR_RETRIEVE:
            error_message = retrieve_fail;
            break;
        case ERR_USAGE:
            show_usage();
            break;
        case ERR_SWITCH:
            //let getopt handle it
            exit(1);
            break;
        default:
            error_message = generic_fail;
    }

    printf("Error: %s\n", error_message);

    exit(1);
}

void show_version()
{
    printf("%s\n", VERSION);
}

void show_usage()
{
    printf("attrach [options] attach <hidefile> <targetfile>\n");
    printf("attrach [options] get <targetfile> <saveasfile>\n");
    printf(" options:\n");
    printf(" --verbose\n");
    printf(" --version\n");
    printf(" --help\n");
}

int main( int ac, char* av[])
{

    int c;

    while (1) 
    {
        int option_index = 0;
        static struct option long_options[] = {
            {"verbose", 0, 0, 'v'},
            {"version", 0, 0, 'V'},
            {"help", 0, 0, 'h'},
            {0, 0, 0, 0}
        };

        if (ac < 4 || ac > 4)
            error_exit(ERR_USAGE);

        c = getopt_long (ac, av, "vVh",
                long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 'V':
                show_version();
                exit(0);
                break;
            case 'h':
                show_usage();
                break;
            case 'v':
                verbose = 420;
                break;
            default:
                /* invalid switch, so failing */
                error_exit(ERR_SWITCH);
        }
    }

    if (!strcmp(av[1], "attach")){
        if (attach_file(av[2], av[3])) {
            printf("made it\n");
            error_exit(ERR_ATTACH);
        }
    } else if (!strcmp(av[1], "get")) {
        if (retrieve_file(av[2], av[3])) {
            error_exit(ERR_RETRIEVE);
        }
    } else {
        show_usage(); 
        exit(1);
    }

    return 0;
}

