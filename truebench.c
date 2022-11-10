/*
GPLv2 License: Copyright (C) (2016) Kiran Kankipati (kiran.kankipati@gmail.com) All Rights Reserved.
TrueBench is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License Version 2, and not any other version, as published by the Free Software Foundation.
TrueBench is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.You should have received a copy of the GNU General Public License along with TrueBench; see the file COPYING.
If not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
#include <stdio.h> 
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*****************IMPORTANT WARNING************************************************************************************
* do not (or avoid) self compilation for generic x86_64 tests. Instead use the pre-compiled binary uploaded online.
  - compile if you use any non-standard ARM/MIPS or any special hardware.

* do not compile with any special gcc compiler optimization settings.
  - compile with standard default settings such as: $ gcc -o truebench truebench.c
  
* evaluate your compiled TrueBench binary via: $ objdump -D truebench

* do not modify the dummy_load() API under any circumstances. Since this will contaminate your overall test result
  with respect to available/existing TrueBench benchmarks. 

* once your TrueBench benchmark(s) are done kindly submit your screen output to me: kiran.kankipati@gmail.com
***********************************************************************************************************************/

#define VERSION 11
#define RELEASE "10-Sep-2016"
#define MAXBYTES 1000000
#define ITERATIONS 1000000
char dummy_result=0;
char dummy_result2=0;
char dummy_buf[MAXBYTES];
char dummy_buf2[MAXBYTES];
void dummy_load()
{	int i;
	for(i=0;i<ITERATIONS;i++)
	{	memset(dummy_buf2, i, MAXBYTES);
		memcpy(dummy_buf, dummy_buf2, MAXBYTES);
	}
	dummy_result=dummy_buf[60];
	dummy_result2=dummy_buf2[60];
}

int main() {
    struct timeval start, end;
    unsigned long long secs_used, millis_used, micros_used;

	 printf("\n\nTrueBench-%d :: Release: %s :: (c)2016 :: Author: Kiran Kankipati\n", VERSION, RELEASE);
	 printf("\nStarting TrueBench system benchmark test.\n");
	 printf("It may take several minutes/hours to complete depending upon your system.\n\n");

    gettimeofday(&start, NULL);
//----------------LOAD
    dummy_load();
//----------------LOAD
    gettimeofday(&end, NULL);

    secs_used=(end.tv_sec - start.tv_sec);
    micros_used= ((secs_used*1000000) + end.tv_usec) - (start.tv_usec);
    millis_used=micros_used/1000;

    printf("Elapsed Duration:\n");
    printf("in Seconds: %llu\n",secs_used);
    printf("in Milliseconds: %llu\n",millis_used);
    printf("in Microseconds: %llu\n",micros_used);

	 printf("--------------------------------------------------------\n");
	 printf("CPU Info:\n");
	 system("cat /proc/cpuinfo | grep model | grep name | uniq| sed 's/ \\+/ /g' | sed 's/: /:/g' |cut -d ':' -f 2");
	 system("CORES=`cat /proc/cpuinfo | grep model | grep name | wc | sed 's/ \\+/ /g' | cut -d ' ' -f 2` ; echo $CORES cores/threads");

    printf("\n\n--------------------------------------------------------\n");
    printf("dummy_result=%d\n", (int)dummy_result);
	 printf("dummy_result2=%d\n", (int)dummy_result2);
    return 0;
}
