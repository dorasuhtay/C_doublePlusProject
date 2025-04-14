#ifndef ISLEEP_H_INCLUDED
#define ISLEEP_H_INCLUDED
/*
extern int isleep(long msec);
extern int isleepfor(long msec);
*/
#ifdef unix
 #include <sys/time.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <pthread.h>
#endif

#ifdef _WIN32
 #include <windows.h>
#endif

inline int isleepfor(long msec)
{
    #ifdef _WIN32
    SleepEx(msec, false);
    return 0;
    #endif
}


inline int isleep(long msec)
{
	#ifdef _WIN32
   SleepEx(msec, true);
   return 0;
   #endif

   #ifdef unix
   fd_set wset,rset,eset;
   struct timeval timeout;
   FD_ZERO(&rset);
   FD_ZERO(&wset);
   FD_ZERO(&eset);
   timeout.tv_sec  = msec / 1000;
   timeout.tv_usec = (msec % 1000) * 1000;
   select(1,&rset,&wset,&eset,&timeout);
   return 0;
   #endif

   #ifdef __VMS
   struct timespec interval;
   interval.tv_sec  =  msec / 1000;
   interval.tv_nsec = (msec % 1000) * 1000 * 1000; // wait msec msec
   pthread_delay_np(&interval);
   return 0;
   #endif
}

#endif // ISLEEP_H_INCLUDED
