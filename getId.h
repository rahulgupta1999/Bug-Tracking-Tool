#include<stdio.h>
#include<sys/time.h>

char getId()
{
        int i=rand();

        struct timeval t;
        int id;
        gettimeofday(&t,NULL);
        id = (t.tv_sec * 1000 * 1000) + (t.tv_usec * 1000) << 42;
        id |= (i % 16777216) << 24;
       char id2[20], id3[20]="Bg";
	   itoa(id,id2,10);
	   strcat(id3,id2);
	   return id3;
}
