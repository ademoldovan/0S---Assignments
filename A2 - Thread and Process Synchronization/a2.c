#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "a2_helper.h"

typedef struct
{
    int process;
    int thread;
    sem_t *semafor;
} TH_STRUCT_4;

typedef struct
{
    int process;
    int thread;
} TH_STRUCT;

pthread_mutex_t protect = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t th1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t th5 = PTHREAD_COND_INITIALIZER;
int start_1 = 0;
int start_5 = 0;

void *threadFunctionP3(void *param)
{
    TH_STRUCT *s = (TH_STRUCT *)param;

    if (s->thread == 5)
    {
        pthread_mutex_lock(&protect);
        while (start_1 == 0)
        {
            pthread_cond_wait(&th5, &protect);
        }
        pthread_mutex_unlock(&protect);
    }
    info(BEGIN, s->process, s->thread);

    if (s->thread == 1)
    {
        pthread_mutex_lock(&protect);
        start_1 = 1;
        pthread_cond_signal(&th5);
        while (start_5 == 0)
        {
            pthread_cond_wait(&th1, &protect);
        }
        pthread_mutex_unlock(&protect);
    }

    info(END, s->process, s->thread);
    if (s->thread == 5)
    {
        pthread_mutex_lock(&protect);
        start_5 = 1;
        pthread_cond_signal(&th1);
        pthread_mutex_unlock(&protect);
    }

    return NULL;
}

void *threadFunctionP7(void *param)
{
    TH_STRUCT *s = (TH_STRUCT *)param;
    info(BEGIN, s->process, s->thread);
    info(END, s->process, s->thread);
    return NULL;
}

int n = 0;

sem_t semafor_p4;

void *limited_area_P4(void *unused)
{
    TH_STRUCT_4 *s = (TH_STRUCT_4 *)unused;
    sem_wait(&semafor_p4);
    info(BEGIN, s->process, s->thread);

    info(END, s->process, s->thread);
    sem_post(&semafor_p4);
    return NULL;
}

int main()
{
    init();

    info(BEGIN, 1, 0);
    int exitStatus = 0;
    pid_t pid2, pid3, pid4, pid5, pid6, pid7, pid8, pid9;

    pid2 = fork();
    if (pid2 == -1)
    {
        perror("Could not create child process");
        return -1;
    }
    else if (pid2 == 0)
    {
        info(BEGIN, 2, 0);
        info(END, 2, 0);
        exit(0);
    }
    else
    {
        waitpid(pid2, &exitStatus, 0);
    }
    pid3 = fork();
    if (pid3 == -1)
    {
        perror("Could not create child process");
        return -1;
    }
    else if (pid3 == 0)
    {
        info(BEGIN, 3, 0);
        pthread_t tid3[5];
        TH_STRUCT s[5];
        for (int i = 1; i <= 5; i++)
        {
            s[i - 1].process = 3;
            s[i - 1].thread = i;
        }
        //cream cele  5 threaduri in procesul P3
        for (int i = 1; i <= 5; i++)
        {
            if (pthread_create(&tid3[i - 1], NULL, threadFunctionP3, &s[i - 1]) != 0)
            {
                perror("Eroare la crearea thread-ului!\n");
                return -1;
            }
        }
        for (int i = 0; i < 5; i++)
        {
            pthread_join(tid3[i], NULL);
        }

        info(END, 3, 0);
        exit(0);
    }
    else
    {
        waitpid(pid3, &exitStatus, 0);
    }
    pid4 = fork();
    if (pid4 == -1)
    {
        perror("Could not create child process");
        return -1;
    }
    else if (pid4 == 0)
    {
        info(BEGIN, 4, 0);
        //procesul P4 creeaza 43 de threaduri

        //initializez semafoarele pentru bariera
        sem_init(&semafor_p4, 0, 6);
        //atribute proprii pentru fiecare thread, numarul procesului si al threadului
        TH_STRUCT_4 s[43];
        //cream cele 43 de thread-uri
        pthread_t threads[43];
        for (int i = 0; i < 43; i++)
        {
            s[i].process = 4;
            s[i].thread = i + 1;
            pthread_create(&threads[i], NULL, limited_area_P4, &s[i]);
        }
        for (int i = 0; i < 43; i++)
        {
            pthread_join(threads[i], NULL);
        }
        sem_destroy(&semafor_p4);

        pid5 = fork();
        if (pid5 == -1)
        {
            perror("Could not create child process");
            return -1;
        }
        else if (pid5 == 0)
        {
            info(BEGIN, 5, 0);
            pid6 = fork();
            if (pid6 == -1)
            {
                perror("Could not create child process");
                return -1;
            }
            else if (pid6 == 0)
            {
                info(BEGIN, 6, 0);
                info(END, 6, 0);
                exit(0);
            }
            else
            {
                waitpid(pid6, &exitStatus, 0);
            }
            info(END, 5, 0);
            exit(0);
        }
        else
        {
            waitpid(pid5, &exitStatus, 0);
        }

        pid7 = fork();
        if (pid7 == -1)
        {
            perror("Could not create child process");
            return -1;
        }
        else if (pid7 == 0)
        {
            info(BEGIN, 7, 0);

            pthread_t tid7[4];
            TH_STRUCT s[4];
            for (int i = 1; i <= 4; i++)
            {
                s[i - 1].process = 7;
                s[i - 1].thread = i;
            }
            //cream cele  4 threaduri in procesul P7

            for (int i = 1; i <= 4; i++)
            {
                if (pthread_create(&tid7[i - 1], NULL, threadFunctionP7, &s[i - 1]) != 0)
                {
                    perror("Eroare la crearea thread-ului!\n");
                    return -1;
                }
            }
            for (int i = 0; i < 4; i++)
            {
                pthread_join(tid7[i], NULL);
            }

            info(END, 7, 0);
            exit(0);
        }
        else
        {
            waitpid(pid7, &exitStatus, 0);
        }

        pid8 = fork();
        if (pid8 == -1)
        {
            perror("Could not create child process");
            return -1;
        }
        else if (pid8 == 0)
        {
            info(BEGIN, 8, 0);
            pid9 = fork();
            if (pid9 == -1)
            {
                perror("Could not create child process");
                return -1;
            }
            else if (pid9 == 0)
            {
                info(BEGIN, 9, 0);
                info(END, 9, 0);
                exit(0);
            }
            else
            {
                waitpid(pid9, &exitStatus, 0);
            }
            info(END, 8, 0);
            exit(0);
        }
        else
        {
            waitpid(pid8, &exitStatus, 0);
        }

        info(END, 4, 0);
        exit(0);
    }
    else
    {
        waitpid(pid4, &exitStatus, 0);
    }

    pthread_mutex_destroy(&protect);
    pthread_cond_destroy(&th1);
    pthread_cond_destroy(&th5);
    info(END, 1, 0);

    return 0;
}
