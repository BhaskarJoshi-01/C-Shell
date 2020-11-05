char home[150], cmdlist[20][150], prevdir[150], his_path[250];
int backpointer, mypid;
int exst;
void pwd();
void addhis(char *);
void history(char **);
void inithist();
void exhis();
void green();
void blue();
void reset();
char **splitargs(char *);

//bghand.c
void bghand(char **);
//
int checkand(char **);
//setenv.c
void seten(char **);
void unseten(char **);
//
void nightswatch(char **);

void logical(char *);
int logicalexec(char *);
int checklogical(char **);

void pinfo(char **);
void echo(char **);
void unimplemented(char **, int);
void print_promt();
int cd(char **);
void getdir();
//sighnd.c
void sigquit();
void sigtstp(int);
void ctrlchnd(int);
//
char *commandexec(char *);
void ls(char **);
struct hist
{
    int histins, histed;
    char history[20][100];
};
struct bid
{
    int pid, index, status;
    char *command;
};

void unimplemented(char **, int);
void backquit(int sig);
//jobs.c
void kjobs(char **);
void jobs(char **);
void fg(char **);
//

//overkill.c
void killemall(char **);
//
struct hist his;
struct bid backarray[128];
////////////////

char currpromt[250];

void execute(char *);

//redir.c
void tagpiper(char *);
//

struct bid runproc;
