#include "csapp.h"

#define MAXARGS 128

/* Function prototypes */
void eval(char *cmdline);
int parseline(const char *cmdline, char **argv);
int builtin_command(char **argv);
void unix_signal_handler(int sig);

/* Global variables */
char prompt[MAXLINE] = "sh257> ";

int main(int argc, char **argv) {
    /* Set up the signal handler */
    Signal(SIGINT, unix_signal_handler);

    /* Check for custom prompt */
    if (argc > 2 && strcmp(argv[1], "-p") == 0) {
        strcpy(prompt, argv[2]);
    }

    char cmdline[MAXLINE]; /* Command line */

    while (1) {
        /* Read */
        printf("%s", prompt);
        Fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);

        /* Evaluate */
        eval(cmdline);
    } 
}

/* Evaluate the command line */
void eval(char *cmdline) {
    char *argv[MAXARGS]; /* Argument list execvp() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    int status;          /* Exit status of child process */

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
        return;   /* Ignore empty lines */

    if (!builtin_command(argv)) { 
        if ((pid = Fork()) == 0) {   /* Child runs user job */
            if (execvp(argv[0], argv) < 0) {
                printf("Execution failed (in fork)\n");
                printf("%s: Command not found.\n", argv[0]);
                exit(1);
            }
        }

        /* Parent waits for child to terminate */
        if (waitpid(pid, &status, 0) < 0)
            unix_error("waitpid error");

        /* Print exit status */
        if (WIFEXITED(status)) {
            printf("Process exited with status code %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) {
    if (!strcmp(argv[0], "exit")) { /* exit command */
        printf("Terminated\n");
        fflush(stdout);
        exit(0);
    }
    if (!strcmp(argv[0], "pid")) { /* pid command */
        printf("pid: %d\n", getpid());
        return 1;
    }
    if (!strcmp(argv[0], "ppid")) { /* ppid command */
        printf("ppid: %d\n", getppid());
        return 1;
    }
    if (!strcmp(argv[0], "help")) { /* help command */
        printf("**********************************************************************\n");
        printf("A Custom Shell for CMSC 257\n");
        printf("Developer: Abhinav Prathipati\n");
        printf("Usage:\n");
        printf("  - To change shell prompt: <executable> -p <prompt>\n");
        printf("**********************************************************************\n");
        printf("BUILTIN COMMANDS:\n");
        printf("  exit   : Exits the shell\n");
        printf("  pid    : Prints the process ID of the shell\n");
        printf("  ppid   : Prints the parent process ID of the shell\n");
        printf("  help   : Displays usage information\n");
        printf("SYSTEM COMMANDS:\n");
        printf("  Prompt user to use man pages for system commands\n");
        return 1;
    }
    if (!strcmp(argv[0], "cd")) { /* cd command */
        if (argv[1]) {
            if (chdir(argv[1]) < 0) {
                printf("cd: %s: No such file or directory\n", argv[1]);
            }
        } else {
            char cwd[MAXLINE];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Current working directory: %s\n", cwd);
            } else {
                perror("getcwd() error");
            }
        }
        return 1;
    }
    return 0;                     /* Not a builtin command */
}

/* Parse the command line and build the argv array */
int parseline(const char *cmdline, char **argv) {
    static char array[MAXLINE]; /* Holds local copy of command line */
    char *buf = array;          /* Pointer that traverses command line */
    char *delim;                /* Points to first space delimiter */
    int argc;                   /* Number of args */
    int bg;                     /* Background job? */

    strcpy(buf, cmdline);
    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0)  /* Ignore blank line */
        return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}

/* Signal handler for SIGINT (CTRL+C) */
void unix_signal_handler(int sig) {
    /* Do nothing, just ignore the signal */
    return;
}
