Go to the directory where Makefile is present
Run "make -f Makefile"
To start the shell, run "./main"

Following are the functionalities my shell has:
pwd,cd,echo,setenv,unsetenv,jobs,kjob,fg,bg,overkill,quit
Other valid commands are handled through execvp, and appropriate error messages are displayed wherever necessary.
Ctrl-C and Ctrl-Z handle the interrupts as mentioned in the assignment

Bonus tasks
Remindme has been implemented
Clock has been implemented ( clock -t <freq> -n <duration>)

Other bonus
Different types of single and double quote commands have been handled in echo

