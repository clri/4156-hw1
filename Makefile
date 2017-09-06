
dynlib: objsect.c objsym.c
	cc -fPIC -c -o objsect.o objsect.c
	cc -fPIC -c -o objsym.o objsym.c
	cc -shared -o libobjdata.so objsect.o objsym.o
