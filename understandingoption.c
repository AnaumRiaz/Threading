#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

int
main(int argc, char **argv)
{
    int c;
    int digit_optind = 0;

   while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"add",     required_argument, 0,  0 },
            {"append",  no_argument,       0,  0 },
            {"delete",  required_argument, 0,  0 },
            {"verbose", no_argument,       0,  0 },
            {"create",  required_argument, 0, 'c'},
            {"file",    required_argument, 0,  0 },
            {0,         0,                 0,  0 }  //last is 0s by requirement
        };

       c = getopt_long(argc, argv, "abc:d:012",
                 long_options, &option_index);
        if (c == -1)
            break;
       printf("we are getting c as %c and %d\n", c, c);
    
       switch (c) {
        case 0:
            printf("anaum: value of c: %d\n", c);
            printf("here!option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

       case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
              printf("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf("inside2option %c\n", c);
            break;

       case 'a':
            printf("option a\n");
            break;

       case 'b':
            printf("option b\n");
            break;

       case 'c':
            printf("option c with value '%s'\n", optarg);
            break;

       case 'd':
            printf("option d with value '%s'\n", optarg);
            break;

       case '?':
            printf("we are getting a question mark yo");
            break;

       default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

   if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

   exit(EXIT_SUCCESS);
}



/*
//this is for command line arguments that start with -
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int flags, opt;
    int nsecs, tfnd;
  printf("start of prog: optind is %d\n", optind);

    nsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "nt:")) != -1) {
       printf("inside the switch with opt %c and optind %d\n", opt, optind);
        switch (opt) {
        case 'n':
            flags = 1;
            break;
        case 't':
            nsecs = atoi(optarg);
            tfnd = 1;
            break;
        default: // '?'
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    printf("end of looop: optind is %d\n", optind);
    }

   printf("flags=%d; tfnd=%d; optind=%d\n", flags, tfnd, optind);

   if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

   printf("name argument = %s\n", argv[optind]);


   exit(EXIT_SUCCESS);
} */
