## Welcome to bhash! 
  
    Bhaskar's Shell...     ( bhash : BHAskar SHell ) 


* [Getting Started](#getting-started)
* [Features](#features)
* [Command usage and Testing](#command-usage-and-testing)
* [Highlights of content of Files involved](#brief)
* [Bug Reporting](#bug-reporting)
* [Important Commands/Structs/Files](#commands)
* [Feature Request](#feature-request)
* [Features Not Supported](#not-features)
<a id = "getting-started">
</a>

## Getting Started
The shell can be initialized by running "make ./bhash" in the terminal.
This will make *.o files and and an executable file shell which could be run by using "./bhash" command. And to remove the *.o files and bhash shell file use "make clean" in the terminal. 

![running_bhash_with_clean](https://github.com/BhaskarJoshi-01/bhash/blob/main/Assets/running_bash_with_clean.gif)

There you are ready to go !!! 
Check out the features that could be used !


<a id="features">
</a>

## Features
* Display

    When my code is executed , a shell  prompt like  ```<username@system_name:curr_dir>``` appears as seen in linuxOS.

    ![running_bhash](https://github.com/BhaskarJoshi-01/bhash/blob/main/Assets/running_bhash.gif)

    Obviously, <strike>UserName and System Name is not hardcoded lol !! </strike>  xD

* Location of Home

    The directory from which the shell is invoked is the home directory of the shell and is indicated by "~".
    
    If the user executes "cd" i.e change dir then the corresponding change is reflected in the shell as well. 

    ```Example: If shell executable resides in '/home/user/Desktop/bhash' then on executing 'cd ..', the command prompt should display '/home/user/Desktop' as the cwd.```

* Exit Codes

    Exit codes indicate whether a process exited normally, or encountered an error. I have displayed them for all external commands, as well as implementing them for internal commands.

    Information about the previous command's exit code is displayed alongside the next prompt as :') if the command exited successfully, or as :'( if it encountered an error.

    The above two scenarios are captured below ^_^

    ![location_home](https://github.com/BhaskarJoshi-01/bhash/blob/main/Assets/location_home.gif)


* Builtin Commands

    The commands like `cd` , `pwd` , `ls` , `pinfo` , `echo` are implemented from scratch. `Ampercent (&)` is used to to run any command in background. 

* Multiple Commands

    Semicolon makes the command into two tokens. So **it can take any number of valid arguments seperated by semicolon**.
    Shell can be exited by using quit or exit command

* Tracks History

    It tracks history upto 20 commands and stores it in .history file. Deletion of this file is completely harmless except the history will not be tracked!

<a id="command-usage-and-testing">
</a>

## Command usage and Testing

Details on most of my commands can be found on man page or you can use `man command_name ` on shell to get the info of the command. 

* cd 

    cd command in linux known as change directory command. It is used to change current working directory.

    ![cd](https://github.com/BhaskarJoshi-01/bhash/blob/main/Assets/cd.gif)

* pwd

    pwd stands for Print Working Directory. It prints the path of the working directory, starting from the root. pwd is shell built-in command(pwd). The usage is shown with `cd` the above !

* pinfo
    
    is user-friendly, console-based viewer for Info documents
    
    ![pinfo](https://github.com/BhaskarJoshi-01/bhash/blob/main/Assets/pinfo.gif)

* echo 
    
    As this was part of assignment , I implemented this as it was required. We were to print the text after echo directly, and not caring about quotes - this feature is not like the original linux shell

    ![echo](https://github.com/BhaskarJoshi-01/bhash/blob/main/Assets/echo.gif)

* history

    It displays 10 past commands and stores upto 20 commands. (for assignment purpose we were supposed to store 20 commands)
    But we can display upto 20 commands.
    Let us consider we have only 11 commands stored in history but we give history 12 as command , it will only display 11 commands.
    But if we have already entered more than 20 commands, it will display latest 20 commands!


    ![history](https://github.com/BhaskarJoshi-01/bhash/blob/main/Assets/history.gif)
 

<a id = "brief">
</a>


## Highlights of content of Files involved


In brief of the tasks which are implemented:
 


Files are as shown below ( and so are most of the commands !! ) : 
1. main.c :

    It contains int main(),getdir() and print_promt() functions with various colours function. The concept is calling print_prompt() function to display the username and host with current directory and it then takes input form the user it then calls cmdhandle.c. The signal for ctrl+c , ctrl+z ,ctrl+\ are also handled such that the terminal does not closes.The exit codes  are also implemented here before the print_prompt with the help of global variable exit_status (exst). 

2. cmdhandle.c : 

    It has splitcmd() to split command into tokens having semicolon.

    splitargs() to seperate and store the arguments .

    execute() is to call built in command .
    checkand() is for checking if command contains & or not and finally commandexec() which is used to execute above functions. 
    
    I am also checking @ and $ through checklogical(). [Part of assignment !]

3. cd.c :

    It implemends cd and it also executes cd -,cd ~, cd . and cd ..

4. pwd.c : 
    
    It  has the implemendation of  pwd command

5. pinfo.c : 

    it implemends pinfo and prints processes related to shell 

6. ls.c : 

    It has ls function , filter and get_printinfo() . ls basically raises flags for -l , -a , -la/-al and displays total block of 1024 bytes occupied by the directory in corresponding colours and well spaced.

7. echo.c :
    
    It implemends echo functions just does the things.

8. history.c :

    It stores history of 20 commands and prints 10 at a time if no argument is specified and prints desired history if argument is less than 20 . If argument is greater than 20 then it just loops over the 20 commands stored.

9. unimplemented.c : 
    
    Contains unimplemented() and backquit() functions. handles commands which are not manually implemented and also handles background processed and printing when it is killed.

10. nightswatch.c :
    
    contains nightwatch(),interrupt(),keydown() and newborn() and if valid 
    arguments are given it starts a timer and calls newborn or interrupt and if q is pressed it quits . interrupt prints the number of times keyboard interrupted CPUs and newborn   tells the process of last created pid.

11. bghand.c : 
    
    It containd a funtion bghand which is called from cmdhandle.c and it implements bg command.

12. jobs.c :
    
    It contains the function jobs(),chekallkill(),fg(),kjob() which opens jobs, check if all jobs are stopped , moves a command to foreground,kills a job with its job no.

13. logical.c : 
    
    It contains two functions and the third bonus is implemented in this part .

14. overkill.c :
    
    It contains a function for killing all the jobs 

15. redir.c :
    
    It handles the piping and redirection of the command given.

16. setenv.c :
    
    It sets global variable which can be checked through printenv

17. sighnd.c :
    
    It contains three signal handlers for ctrl+c,ctrl+z and the segfault that was occuring on ctrl+\ was also handled 

18. headerfile.h : 
    
    It contains  the above mentioned files and has functions listed in above files.

<a id = "not-features">
</a>

## Features Not Supported
bhash does not support the following yet:

    `tab` completion
    Support for quoting and escape sequences
    User profiles
    Command recamming by pressing `up` key
    and maybe a lot more...

<a id = "bug-reporting">
</a>

## Bug Reporting

Please feel free to [open an issue](https://github.com/BhaskarJoshi-01/bhash/issues) if you find any bug .




<a id = "commands">
</a>

## Important Commands/Structs/Files

Useful commands/structs/files :

`uname, hostname, signal, waitpid, getpid, kill, execvp, strtok, fork, getopt, readdir, opendir, readdir, closedir, sleep, watch, struct stat, struct dirent,/proc/interrupts, /proc/loadavg , getenv, signal, dup, dup2, wait, waitpid, getpid, kill, execvp, malloc, strtok, fork, setpgid, setenv , getchar etc.`


<a id = "feature-request">
</a>

## Feature Request

Please feel free to [open an issue](https://github.com/BhaskarJoshi-01/bhash/issues) if you want to request some additional features.

Connect me on [LinkedIn](https://www.linkedin.com/in/bhaskar-joshi-968a591a4/), I would love to hear from you!
