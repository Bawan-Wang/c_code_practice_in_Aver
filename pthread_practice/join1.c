#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10
void *thread_function(void*);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

void main(){

   pthread_t thread_id[NTHREADS];
   int i,j;

   for(i = 0; i < NTHREADS; i++){
      pthread_create( &thread_id[i], NULL, thread_function, NULL);
   }

   for(i = 0; i < NTHREADS; i++){
      pthread_join( thread_id[i], NULL);
   }

   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   printf("Final counter value: %d\n", counter);
}

void *thread_function(void *dummyPtr){
   
   printf("Thread number %ld\n",pthread_self());
   pthread_mutex_lock( &mutex1 );
   counter++;
   pthread_mutex_unlock( &mutex1 );

}


