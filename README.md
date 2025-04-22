# holbertonschool-simple_shell
<img align="center" alt="What the Shell GIF" width="1000" src="https://media2.giphy.com/media/v1.Y2lkPTc5MGI3NjExNG5wNHRhc3ZvandqbzdoaWpmYzRndGQwcW4zZWw5YndjOXlpb3E1ZSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/jlcqOX60nkPvzAfkZM/giphy.gif">
 
 A Simple Shell project
A Shell is an computer programm that gives an interface to the users to access to operating system services. It allows the users to communicate with the exploitation system kernel to execute commands, run programs, manage files and processes, and automate tasks.

This project is a simple implementation of this interface, reproducing a few functions of it.

🖥️Informations
This project was compiled with $ gcc -Wall -Werror -Wextra -pedantic *.c -o Shell on Ubuntu 20.04 LTS.

It is fully written in Betty coding standards.

🚀 Installation
First, be sure to have:

GCC installed on your system.
Ubuntu 20.04 LTS (or equivalent).
This program was designed for Linux systems. It was tested functionnal on a Mac M2 (Apple Silicon) and can cause segmentation fault with this architecture.

You can install the simple shell by cloning this repo: https://github.com/loufi84/holbertonschool-simple_shell

Next you can compile the files with this command: gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o Shell

Finally you can run our Shell writing: ./Shell

💻️ Exemples d'utilisation :

➡️ ls -l: <br>
simple_shell> ls -l <br>
total 184 <br>
-rw-r--r-- 1 delphes delphes    247 Apr 22 09:37  AUTHORS <br>
-rw-r--r-- 1 delphes delphes 111925 Apr 22 09:23 'Flowchart Shell.png' <br>
-rw-r--r-- 1 delphes delphes   1743 Apr 22 10:12  README.md <br>
-rwxr-xr-x 1 delphes delphes  21952 Apr 22 10:49  Shell <br>
-rw-r--r-- 1 delphes delphes    519 Apr 18 11:55  _getenv.c <br>
-rw-r--r-- 1 delphes delphes   1635 Apr 22 10:16  _getline.c <br>
-rw-r--r-- 1 delphes delphes    494 Apr 18 14:53  comments_handling.c <br>
-rw-r--r-- 1 delphes delphes   1785 Apr 18 18:16  helper_funcs.c <br>
-rw-r--r-- 1 delphes delphes    444 Apr 18 10:19  helper_funcs2.c <br>
-rw-r--r-- 1 delphes delphes    496 Apr 22 10:33  main.c <br>
-rw-r--r-- 1 delphes delphes   1427 Apr 21 10:59  man_simple_shell <br>
-rwxr-xr-x 1 delphes delphes   1485 Apr 18 10:26  path_handling.c <br>
-rw-r--r-- 1 delphes delphes   1091 Apr 18 18:16  shell.h <br>
-rw-r--r-- 1 delphes delphes    897 Apr 18 11:50  what_is_cmd.c <br>

➡️  echo: <br>
simple_shell> echo Shell is great <br>
Shell is great <br>

![Flowchart](https://github.com/loufi84/holbertonschool-simple_shell/blob/Features/Simple%20Shell%20flowchart.png)
