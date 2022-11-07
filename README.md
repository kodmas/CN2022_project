# CN2022_project

* To generate binary executable file, command is make(makefile is written)
* To clean binary executable file, command is make clean(makefile is written)
* The source codes are server.c ,client.c and content.html.
* For objective 1, message transfer between server and client to operate in local
    1. command ./Server
    2. another console with comman ./Client
    3. Port number is explicitly determined in the source code, will be improved in phase 2

* For objective 2, personal profile
    1. command ./Server
    2. Use any browser as client
    3. It can currently be operated locally, will be improved in phase 2
    4. The personal file is shown on the browser page(content.html is sent through socket)