#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_SIZE 1024

int main() {
int shmid;
key_t key;
char *shm, *s;

if ((key = ftok(".", 'R')) == -1) {
perror("ftok");
exit(1);
}

if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
perror("shmget");
exit(1);
}

if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
perror("shmat");
exit(1);
}

s = shm;
for (int i = 1; i <= 10; i++) {
int num = rand() % 100;
sprintf(s, "%d", num);
s += sizeof(int);
printf("Отправлено число: %d\n", num);
sleep(1);
}

if (shmdt(shm) == -1) {
perror("shmdt");
exit(1);
} 
