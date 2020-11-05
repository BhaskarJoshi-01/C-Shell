bhash : main.o cmdhandle.o implemented/echo.o nightswatch.o implemented/pwd.o	unimplemented.o implemented/history.o implemented/cd.o implemented/ls.o implemented/pinfo.o new_cmd/bghand.o new_cmd/sighnd.o new_cmd/jobs.o new_cmd/overkill.o new_cmd/redir.o new_cmd/setenv.o new_cmd/logical.o
	gcc  ./cmdhandle.o implemented/pwd.o  implemented/cd.o implemented/ls.o  implemented/pinfo.o ./unimplemented.o implemented/history.o ./main.o ./nightswatch.o implemented/echo.o  new_cmd/bghand.o new_cmd/sighnd.o new_cmd/jobs.o new_cmd/overkill.o new_cmd/redir.o new_cmd/setenv.o   new_cmd/logical.o -o bhash


main.o : main.c
		gcc -c  main.c

cmdhandle.o : cmdhandle.c
		gcc -c cmdhandle.c


implemented/echo.o : implemented/echo.c
		gcc  -c implemented/echo.c -o implemented/echo.o

nightswatch.o : nightswatch.c
		gcc -c nightswatch.c

implemented/pwd.o : implemented/pwd.c
		gcc -c implemented/pwd.c -o implemented/pwd.o

unimplemented.o : unimplemented.c 
		gcc -c unimplemented.c

implemented/history.o : implemented/history.c
		gcc -c implemented/history.c -o implemented/history.o

implemented/cd.o : implemented/cd.c 
		gcc -c implemented/cd.c -o implemented/cd.o 

implemented/ls.o : implemented/ls.c
		gcc -c implemented/ls.c -o implemented/ls.o

implemented/pinfo.o : implemented/pinfo.c
		gcc -c implemented/pinfo.c -o implemented/pinfo.o

new_cmd/bghand.o:new_cmd/bghand.c
		gcc -c new_cmd/bghand.c -o new_cmd/bghand.o

new_cmd/jobs.o:new_cmd/jobs.c
		gcc -c new_cmd/jobs.c -o new_cmd/jobs.o

new_cmd/overkill.o: new_cmd/overkill.c
		gcc -c new_cmd/overkill.c -o new_cmd/overkill.o

new_cmd/redir.o:new_cmd/redir.c
		gcc -c new_cmd/redir.c -o new_cmd/redir.o

new_cmd/setenv.o:new_cmd/setenv.c
		gcc -c new_cmd/setenv.c -o new_cmd/setenv.o

new_cmd/sighnd.o:new_cmd/sighnd.c
		gcc -c new_cmd/sighnd.c -o new_cmd/sighnd.o
new_cmd/logical.o:new_cmd/logical.c
		gcc -c new_cmd/logical.c -o new_cmd/logical.o

clean:
		rm -r *.o implemented/*.o  new_cmd/*.o  bhash 
