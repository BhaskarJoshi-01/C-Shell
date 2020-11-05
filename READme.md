Welcome to bhash! - Bhaskar's Shell...
(bhash : BHAskar SHell) 
<!-- The READme.md has been updated after assignment 3. This assignment is my implemendation of bash written in C. I have fulfilled the conditions which are asked in the question pdf. -->

The shell can be initialized by running "make ./bhash" in the terminal.
This will make *.o files and and an executable file shell which could be run by using "./bhash" command. And to remove the *.o files and bhash shell file use "make clean" in the terminal.  
The codes for assignment 3 are in new_cmd folder.

In brief of the tasks which are implemented and asked:
- This is a shell prompt which displays <username@host:cur_dir> and the path is relative to home .
- Semicolon makes the command into two tokens. So it can take any number of valid arguments seperated by semicolon .
- The directory from where the shell  is invoked is taken as the home directory.
-The commands like cd,pwd,ls,pinfo,echo are implemented from scratch.
-Ampercent (&) is used to to run any command in background.
-nightswatch and history are also implemented which are the bonus part of the assignment.
-Shell can be exited by using quit or exit command 

The files such as cd.c,ls.c,pwd.c,pinfo.c,history.c and echo.c are indide implemented folder

Files used:
1. main.c : it contains int main(),getdir() and print_promt() functions with various colours function.the concept is calling print_prompt() function to display the username and host with current directory and it then takes input form the user it then calls cmdhandle.c. The signal for ctrl+c , ctrl+z ,ctrl+\ are also handled such that the terminal does not closes.The exit codes for bonus 2 are also implemented here before the print_prompt with the help of global variable exit_status (exst). 

2. cmdhandle.c : it has splitcmd() to split command into tokens having semicolon, splitargs() to seperate and store the arguments , execute() is to call built in command , checkand() is for checking if command contains & or not and finally commandexec() which is used to execute above functions. I am also checking @ and $ through checklogical().

3. cd.c :it implemends cd and it also executes cd -(Bonus 1),cd ~

4. pwd.c : it implemends pwd command

5. pinfo.c : it implemends pinfo and prints processes related to shell and gives output as asked in assigment pdf 

6. ls.c : really lengthy and most complex part of the code which took  days to debug and correct. it has ls function , filter and get_printinfo() . ls basically raises flags for -l , -a , -la/-al and displays total block of 1024 bytes occupied by the directory in corresponding colours and well spaced.

7. echo.c : it implemends echo functions just does the things as required in assignment pdf and moodle forum.

8. history.c : it stores history of 20 commands and prints 10 at a time if no argument is specified and prints desired history if argument is less than 20 . if argument is greater than 20 then it just loops over the 20 commands stored.

9. unimplemented.c : contains unimplemented() and backquit() functions. handles commands which are not manually implemented and also handles background processed and printing when it is killed.

10. nightswatch.c :contains nightwatch(),interrupt(),keydown() and newborn() and if valid arguments are given it starts a timer and calls newborn or interrupt and if q is pressed it quits . interrupt prints the # of times keyboard interrupted CPUs and newborn   tells the process of last created pid.

11. bghand.c : it containd a funtion bghand which is called from cmdhandle.c and it implements bg command.

12. jobs.c : it contains the function jobs(),chekallkill(),fg(),kjob() which opens jobs, check if all jobs are stopped , moves a command to foreground,kills a job with its job no.

13. logical.c : it contains two functions and the third bonus is implemented in this part .

14. overkill.c : it contains a function for killing all the jobs 

15. redir.c :it handles the piping and redirection of the command given.

16. setenv.c : it sets global variable which can be checked through printenv

17. sighnd.c : it contains three signal handlers for ctrl+c,ctrl+z and the segfault that was occuring on ctrl+\ was also handled 


18. headerfile.h : it contains  the above mentioned files and has functions listed in above files.

