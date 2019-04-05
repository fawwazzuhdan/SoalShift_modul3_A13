#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

int wait;
pthread_t thread[2];

void* ps(void *arg){
    pthread_t id = pthread_self();
    if(pthread_equal(id,thread[0]))
    {
        system("ps -aux | head -n 11 | tail -n 10 > /home/fawwaz/Documents/FolderProses1/SimpanProses1.txt");
        wait--;
    }
    else if(pthread_equal(id, thread[1]))
    {
        system("ps -aux | head -n 11 | tail -n 10 > /home/fawwaz/Documents/FolderProses2/SimpanProses2.txt");
        wait--;
    }
    
    
}

void* zip(void *arg){
    pthread_t id = pthread_self();
    if(pthread_equal(id, thread[0]))
    {
        system("zip -j /home/fawwaz/Documents/FolderProses1/KompresProses1.zip /home/fawwaz/Documents/FolderProses1/SimpanProses1.txt");
        remove("/home/fawwaz/Documents/FolderProses1/SimpanProses1.txt");
        wait--;
    }
    else if(pthread_equal(id, thread[1]))
    {
        system("zip -j /home/fawwaz/Documents/FolderProses2/KompresProses2.zip /home/fawwaz/Documents/FolderProses2/SimpanProses2.txt");
        remove("/home/fawwaz/Documents/FolderProses2/SimpanProses2.txt");
        wait--;
    }
}

void* unzip(void *arg){
    pthread_t id = pthread_self();
    if(pthread_equal(id, thread[0]))
    {
        system("unzip /home/fawwaz/Documents/FolderProses1/KompresProses1.zip -d /home/fawwaz/Documents/FolderProses1/");
        wait--;
    }
    else if(pthread_equal(id, thread[1]))
    {
        system("unzip /home/Penunggu/Documents/FolderProses2/KompresProses2.zip -d /home/Penunggu/Documents/FolderProses2/");system("unzip /home/fawwaz/Documents/FolderProses2/KompresProses2.zip -d /home/fawwaz/Documents/FolderProses2/");
        wait--;
    }
}

int main(){
    int i, err;
    wait=2;
    for(i = 0; i < 2; i++)
    {
        err = pthread_create(&thread[i], NULL, ps, NULL);
        if(err!=0)
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		// else
		// {
		// 	printf("\n create thread success\n");
		// }
    }

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    while(wait > 0);
    
    wait=2;
    for(i = 0; i < 2; i++)
    {
        err = pthread_create(&thread[i], NULL, zip, NULL);
        if(err!=0)
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		// else
		// {
		// 	printf("\n create thread success\n");
		// }
    }

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    while(wait > 0);

    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);

    wait=2;
    for(i = 0; i < 2; i++)
    {
        err = pthread_create(&thread[i], NULL, unzip, NULL);
        if(err!=0)
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		// else
		// {
		// 	printf("\n create thread success\n");
		// }
    }

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    while(wait > 0);

    return 0;
}