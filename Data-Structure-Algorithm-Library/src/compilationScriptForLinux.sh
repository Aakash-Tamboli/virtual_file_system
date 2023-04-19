gcc -c *.c -I ../include
ar rcs ../lib/liblinuxDsAlgo.a *.o
rm *.o
