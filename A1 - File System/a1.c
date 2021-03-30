#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

int listRecursive(char *path, int OK)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    dir = opendir(path); //deschid directorul
    if (dir == NULL)
    { //daca dir e NULL nu s-a putut deschide directorul
        printf("ERROR\n");
        perror("Nu s-a putut deschide directorul!");
        return -1;
    }
    //folosim variabila OK pentru a afisa SUCCESS doar o data la inceput
    if (OK == 0)
    {
        printf("SUCCESS\n");
        OK = 1;
    }
    //daca s-a putut deschide, incepem sa parcurgem recursiv fisierul
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            //snprintf - formeaza calea completa catre un fisier, asta ca sa putem folosi lstst/stat
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            { //lstat pute in statbuf metadatele fiserului curent
                if (S_ISDIR(statbuf.st_mode))
                { //daca intalnim un director apelam functia findString
                    printf("%s\n", fullPath);
                    listRecursive(fullPath, OK);
                }
                else
                { //daca e un alt tip de fisier il afisam
                    printf("%s\n", fullPath);
                }
            }
        }
    }
    //inchidem directorul descris
    if (closedir(dir) != 0)
    {
        perror("Eroare la inchiderea directorului!\n");
        return -1;
    }
    return 0;
}

int list(char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        perror("Nu s-a putut deschide directorul!");
        return -1;
    }
    printf("SUCCESS\n");
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            printf("%s\n", fullPath);
        }
    }
    if (closedir(dir) != 0)
    {
        perror("Eroare la inchiderea directorului!\n");
        return -1;
    }
    return 0;
}

int listSmaller(char *path, ssize_t size_value, int ok, int val)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        perror("Nu s-a putut deschide directorul!");
        return -1;
    }
    if (val == 0)
    {
        printf("SUCCESS\n");
        val = 1;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            {
                //folosim variabila ok pentru a putea folosi aceiasi functie si pentru varianta recursiva
                if (ok == 1)
                {
                    if (S_ISDIR(statbuf.st_mode))
                    {
                        listSmaller(fullPath, size_value, ok, val);
                    }
                }
                if (S_ISREG(statbuf.st_mode))
                {
                    int fd = open(fullPath, O_RDONLY);
                    if (fd == -1)
                    { //verificam daca s-a deschis fisierul
                        perror("Nu s-a putut deschide fisierul");
                        return -1;
                    }
                    ssize_t size = 0;
                    //mutam cursorul la finalul fisierului pentru a calcula dimensiunea acestuia
                    size = lseek(fd, 0, SEEK_END);
                    lseek(fd, 0, SEEK_SET);
                    if (size < size_value)
                        printf("%s\n", fullPath);
                    close(fd);
                }
            }
        }
    }
    if (closedir(dir) != 0)
    {
        perror("Eroare la inchiderea directorului!\n");
        return -1;
    }
    return 0;
}

int listString(char *path, char string[], int ok, int val)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        perror("Nu s-a putut deschide directorul!");
        return -1;
    }
    if (val == 0)
    {
        printf("SUCCESS\n");
        val = 1;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            {
                int l_name = strlen(entry->d_name);
                int l_string = strlen(string);
                char name[30];
                //punem in variabila name numele fisierului
                strcpy(name, entry->d_name);
                int j = 0;
                int nr = 0;
                //comparam ultimele l_string caractere din numele fisierului cu sirul primit ca parametru
                //folosim variabila nr pentru a numara caracterele egale
                for (int i = l_name - l_string; i < l_name; i++)
                {
                    if (string[j] == name[i])
                    {
                        nr++;
                    }
                    j++;
                }
                //daca nr este egal cu lungimea sirului primit ca parametru,
                //numele fisierului se termina cu caracterele din sirul respectiv
                if (nr == l_string)
                    printf("%s\n", fullPath);
                //folosim ok pentru varianta recursiva a functiei
                if (ok == 1)
                {
                    if (S_ISDIR(statbuf.st_mode))
                    {
                        listString(fullPath, string, ok, val);
                    }
                }
            }
        }
    }
    if (closedir(dir) != 0)
    {
        perror("Eroare la inchiderea directorului!\n");
        return -1;
    }
    return 0;
}

int parse(char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    { //verificam daca s-a deschis fisierul
        perror("Nu s-a putut deschide fisierul");
        return -1;
    }

    //citim magic
    char magic[2];
    if (read(fd, magic, 2) != 2)
    {
        perror("Eroare la citirea din fisier! ");
        close(fd);
        return -1;
    }
    if (magic[0] != 'G' || magic[1] != '7')
    { //testam daca versiunea e buna = G7
        printf("ERROR\n");
        printf("wrong magic\n");
        close(fd);
        return -1;
    }
    //citim version
    lseek(fd, 4, SEEK_SET);
    int version;
    if (read(fd, &version, 4) != 4)
    {
        perror("Eroare la citirea din fisier! ");
        close(fd);
        return -1;
    }
    //verificam daca versiunea e corecta, daca nu afisam o eroare
    if (version < 32 || version > 116)
    {
        printf("ERROR\n");
        printf("wrong version\n");
        close(fd);
        return -1;
    }

    //citim numarul de sectiuni
    lseek(fd, 8, SEEK_SET);
    int nr_of_sections = 0;
    if (read(fd, &nr_of_sections, 1) != 1)
    {
        perror("Eroare la citirea din fisier! ");
        close(fd);
        return -1;
    }
    //verificam daca numarul de sectiuni este unul corespunzator, afisam o eroare in caz contrar
    if (nr_of_sections < 5 || nr_of_sections > 15)
    {
        printf("ERROR\n");
        printf("wrong sect_nr\n");
        close(fd);
        return -1;
    }

    //validam tipul sectiunilor
    int current = 28;
    lseek(fd, current, SEEK_SET);
    int type;
    int nr = 0;
    //trebuie sa validam toate tipurile sectiunilor: verificam tipul lor si le numaram pe cele
    //care corespund, si la final facem o comparatie intre numarul total de sectiuni si cele
    //care corespund, in caz de inegalitate afisam o eroare
    for (int i = 0; i < nr_of_sections; i++)
    {
        if (read(fd, &type, 4) != 4)
        {
            perror("Eroare la citirea din fisier!");
            close(fd);
            return -1;
        }
        if (type == 88 || type == 11 || type == 60 || type == 96 || type == 48 || type == 19 || type == 51)
        {
            nr++;
        }
        current = current + 31;
        lseek(fd, current, SEEK_SET);
    }
    if (nr != nr_of_sections)
    {
        printf("ERROR\n");
        printf("wrong sect_types\n");
        close(fd);
        return -1;
    }
    //daca nu am gasit nici o eroare in ceea ce priveste validarea fiserului afisam datele acestuia
    printf("SUCCESS\n");
    printf("version=%d\n", version);
    printf("nr_sections=%d\n", nr_of_sections);
    lseek(fd, 9, SEEK_SET);
    char name[20] = {0};
    int size;
    for (int i = 0; i < nr_of_sections; i++)
    {
        printf("section%d: ", i + 1);
        if (read(fd, &name, 19) != 19)
        {
            perror("Eroare la citirea din fisier!");
            close(fd);
            return -1;
        }
        printf("%s ", name);
        if (read(fd, &type, 4) != 4)
        {
            perror("Eroare la citirea din fisier!");
            close(fd);
            return -1;
        }
        printf("%d ", type);
        lseek(fd, 4, SEEK_CUR);
        if (read(fd, &size, 4) != 4)
        {
            perror("Eroare la citirea din fisier!");
            close(fd);
            return -1;
        }
        printf("%d\n", size);
    }
    close(fd);
    return 0;
}

//functie care verifica daca fisierul primit ca parametru este de tipul SF
//afiseaza 0 in caz afirmativ si -1 in caz contrar
int verificareSF(char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    { //verificam daca s-a deschis fisierul
        perror("Nu s-a putut deschide fisierul");
        return -1;
    }
    //citim magic
    char magic[2];
    if (read(fd, magic, 2) != 2)
    {
        perror("Eroare la citirea din fisier! ");
        close(fd);
        return -1;
    }
    if (magic[0] != 'G' || magic[1] != '7')
    { //testam daca versiunea e buna = G7
        return -1;
    }
    //citim version
    lseek(fd, 4, SEEK_SET);
    int version;
    if (read(fd, &version, 4) != 4)
    {
        perror("Eroare la citirea din fisier! ");
        close(fd);
        return -1;
    }
    if (version < 32 || version > 116)
    {
        return -1;
    }
    //citim numarul de sectiuni
    lseek(fd, 8, SEEK_SET);
    int nr_of_sections = 0;
    if (read(fd, &nr_of_sections, 1) != 1)
    {
        perror("Eroare la citirea din fisier! ");
        close(fd);
        return -1;
    }
    if (nr_of_sections < 5 || nr_of_sections > 15)
    {
        return -1;
    }
    //validam tipul sectiunilor
    int current = 28;
    lseek(fd, current, SEEK_SET);
    int type;
    int nr = 0;
    for (int i = 0; i < nr_of_sections; i++)
    {
        if (read(fd, &type, 4) != 4)
        {
            return -1;
        }
        //printf("%d  ", type);
        if (type == 88 || type == 11 || type == 60 || type == 96 || type == 48 || type == 19 || type == 51)
        {
            nr++;
        }
        current = current + 31;
        lseek(fd, current, SEEK_SET);
    }
    //printf("\n");
    if (nr != nr_of_sections)
    {
        return -1;
    }
    close(fd);
    return 0;
}

int findall(char *path, int OK)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        printf("invalid directory path\n");
        return -1;
    }
    if (OK == 0)
    {
        OK = 3;
        printf("SUCCESS\n");
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            {
                if (S_ISDIR(statbuf.st_mode))
                {
                    findall(fullPath, OK);
                }
                else if (S_ISREG(statbuf.st_mode))
                {
                    //testam sa vedem daca fiserul este de tipul SF
                    if (verificareSF(fullPath) == 0)
                    {
                        int fd = open(fullPath, O_RDONLY);
                        if (fd == -1)
                        {
                            perror("Nu s-a putut deschide fisierul");
                            return -1;
                        }
                        lseek(fd, 8, SEEK_SET);
                        int nr_of_sections = 0;
                        //citim numarul de sectiuni
                        if (read(fd, &nr_of_sections, 1) != 1)
                        {
                            perror("Eroare la citirea din fisier! 1");
                            close(fd);
                            return -1;
                        }
                        lseek(fd, 28, SEEK_SET);
                        int type;
                        int nr = 0;
                        //parcurgem toate sectiunile si citim tipul acestora,
                        //daca intalnim o sectiune cu tipul 51 o numaram,
                        //daca la final nr>0 afisam calea spre acest fisier
                        for (int i = 0; i < nr_of_sections; i++)
                        {
                            if (read(fd, &type, 4) != 4)
                            {
                                perror("Eroare la citirea din fisier! 2");
                                close(fd);
                                return -1;
                            }
                            if (type == 51)
                            {
                                nr++;
                            }
                            lseek(fd, 27, SEEK_CUR);
                        }
                        if (nr > 0)
                            printf("%s\n", fullPath);
                        close(fd);
                    }
                }
            }
        }
    }
    //inchidem directorul descris
    if (closedir(dir) != 0)
    {
        perror("Eroare la inchiderea directorului!\n");
        return -1;
    }
    return 0;
}

int extract(char *path, int section, int line)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("ERROR\n");
        printf("invalid file\n");
        return -1;
    }
    //verificam daca avem un fisier de tipul SF
    if (verificareSF(path) == 0)
    {
        lseek(fd, 8, SEEK_SET);
        int nr_of_sections = 0;
        if (read(fd, &nr_of_sections, 1) != 1)
        {
            perror("Eroare la citirea din fisier! 1");
            close(fd);
            return -1;
        }
        //daca numarul sectiunii primite ca parametru este mai mare decat numarul de
        //sectiuni ale fisierului se afiseaza o eroare
        if (section > nr_of_sections)
        {
            printf("ERROR\n");
            printf("invalid section\n");
            close(fd);
            return -1;
        }
        lseek(fd, 32, SEEK_SET);
        int offset;
        int size;
        //citim offset-ul si size-ul pentru sectiunea primita ca parametru
        for (int i = 0; i < nr_of_sections; i++)
        {
            if (i + 1 == section)
            {
                if (read(fd, &offset, 4) != 4)
                {
                    perror("Eroare la citirea din fisier! 2");
                    close(fd);
                    return -1;
                }
                if (read(fd, &size, 4) != 4)
                {
                    perror("Eroare la citirea din fisier! 2");
                    close(fd);
                    return -1;
                }
                break;
            }
            lseek(fd, 31, SEEK_CUR);
        }
        //citim continutul sectiunii noastre intr-un buffer de dimensiunea acesteia
        lseek(fd, offset, SEEK_SET);
        char *buffer = malloc(sizeof(char) * (size + 1));
        char *linie = malloc(sizeof(char) * (size + 1));
        int nr = 1;
        int j = 0;
        int ok = 0;
        if (read(fd, buffer, size) != size)
        {
            perror("Eroare la citirea din fisier! 2");
            close(fd);
            return -1;
        }
        //am considerat ca liniile se numara incepand de la linia cu numarul 1
        if (line <= 0)
        {
            printf("ERROR\n");
            printf("invalid line\n");
            return -1;
        }
        //variabila nr va memora numarul liniei curente
        //in variabila linie memoram linia curenta
        for (int i = size - 1; i >= 0; i--)
        {
            //daca nr este egal cu linia pe care dorm sa o citim,
            //afisam continutul variabilei linie
            if (buffer[i] == 10 && buffer[i - 1] == 13 && nr == line)
            {
                nr++;
                i--;
                printf("SUCCESS\n");
                ok = 1;
                char *var = malloc(sizeof(char) * (j + 1));
                strncpy(var, linie, j);
                printf("%s\n", var);
                j = 0;
                free(var);
                break;
            }
            //cand avem o linie noua resetam variabila j care tine dimensiunea liniei curente,
            //cand se ajunge la finalul acesteia
            if (buffer[i] == 10 && buffer[i - 1] == 13)
            {
                nr++;
                j = 0;
                i--;
            }
            linie[j] = buffer[i];
            j++;
        }
        //verificam daca numarul liniei primite ca parametru este mai mare decat numarul de linii din sectiune
        //in caz afirmativ afisam o eroare
        if (line > nr)
        {
            printf("ERROR\n");
            printf("invalid line\n");
            return -1;
        }
        //daca ok este 0 inseamna ca trebuie sa afisam ultima linie
        if (ok == 0)
        {
            printf("SUCCESS\n");
            char *var = malloc(sizeof(char) * (j + 1));
            strncpy(var, linie, j);
            printf("%s\n", var);
            free(var);
        }

        free(buffer);
        free(linie);
    }
    close(fd);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc >= 2)
    {
        //-----VARIANT----
        if (strcmp(argv[1], "variant") == 0)
        {
            printf("78690\n");
        }
        //-----LIST-----
        if (strcmp(argv[1], "list") == 0)
        {
            //introducem doar un argument, path-ul
            if (argc == 3)
            {
                char *path;
                path = strtok(argv[2], "="); //a o sa tina cuv path
                if (strcmp(path, "path") == 0)
                { //daca argumentul e path, apelam functia list
                    path = strtok(NULL, "=");
                    list(path);
                }
            }
            //introducem doua argumente
            if (argc == 4)
            {
                if (strcmp(argv[2], "recursive") == 0 && strstr(argv[3], "path") != NULL)
                {
                    char path[1024];
                    sscanf(argv[3], "path=%s", path);
                    listRecursive(path, 0);
                }
                if (strcmp(argv[3], "recursive") == 0 && strstr(argv[2], "path") != NULL)
                {
                    char path[1024];
                    sscanf(argv[2], "path=%s", path);
                    listRecursive(path, 0);
                }
                if (strstr(argv[2], "path") != NULL)
                {
                    char path[512];
                    sscanf(argv[2], "path=%s", path);
                    if (strstr(argv[3], "size_smaller=") != NULL)
                    {
                        int number = 0;
                        sscanf(argv[3], "size_smaller=%d", &number);
                        listSmaller(path, number, 0, 0);
                    }
                    if (strstr(argv[3], "name_ends_with=") != NULL)
                    {
                        char string[30];
                        sscanf(argv[3], "name_ends_with=%s", string);
                        listString(path, string, 0, 0);
                    }
                }
                if (strstr(argv[3], "path") != NULL)
                {
                    char path[512];
                    sscanf(argv[3], "path=%s", path);
                    if (strstr(argv[2], "size_smaller=") != NULL)
                    {
                        int number = 0;
                        sscanf(argv[2], "size_smaller=%d", &number);
                        listSmaller(path, number, 0, 0);
                    }
                    if (strstr(argv[2], "name_ends_with=") != NULL)
                    {
                        char string[30];
                        sscanf(argv[2], "name_ends_with=%s", string);
                        listString(path, string, 0, 0);
                    }
                }
            }
            if (argc == 5)
            {
                //recursive + path + size/end
                if (strcmp(argv[2], "recursive") == 0 && strstr(argv[3], "path") != NULL)
                {
                    char path[1024];
                    sscanf(argv[3], "path=%s", path);
                    //size
                    if (strstr(argv[4], "size_smaller=") != NULL)
                    {
                        int number = 0;
                        sscanf(argv[4], "size_smaller=%d", &number);
                        listSmaller(path, number, 1, 0);
                    }
                    //end
                    if (strstr(argv[4], "name_ends_with=") != NULL)
                    {
                        char string[30];
                        sscanf(argv[4], "name_ends_with=%s", string);
                        listString(path, string, 1, 0);
                    }
                }
                //path + recursive + size/end
                if (strcmp(argv[3], "recursive") == 0 && strstr(argv[2], "path") != NULL)
                {
                    char path[1024];
                    sscanf(argv[2], "path=%s", path);
                    //size
                    if (strstr(argv[4], "size_smaller=") != NULL)
                    {
                        int number = 0;
                        sscanf(argv[4], "size_smaller=%d", &number);
                        listSmaller(path, number, 1, 0);
                    }
                    //end
                    if (strstr(argv[4], "name_ends_with=") != NULL)
                    {
                        char string[30];
                        sscanf(argv[4], "name_ends_with=%s", string);
                        listString(path, string, 1, 0);
                    }
                }
                //path + size/end + recursive
                if (strcmp(argv[4], "recursive") == 0 && strstr(argv[2], "path") != NULL)
                {
                    char path[1024];
                    sscanf(argv[2], "path=%s", path);
                    //size
                    if (strstr(argv[3], "size_smaller=") != NULL)
                    {
                        int number = 0;
                        sscanf(argv[3], "size_smaller=%d", &number);
                        listSmaller(path, number, 1, 0);
                    }
                    //end
                    if (strstr(argv[3], "name_ends_with=") != NULL)
                    {
                        char string[30];
                        sscanf(argv[3], "name_ends_with=%s", string);
                        listString(path, string, 1, 0);
                    }
                }
                //recursive + size/end + path
                if (strcmp(argv[2], "recursive") == 0 && strstr(argv[4], "path") != NULL)
                {
                    char path[1024];
                    sscanf(argv[4], "path=%s", path);
                    //size
                    if (strstr(argv[3], "size_smaller=") != NULL)
                    {
                        int number = 0;
                        sscanf(argv[3], "size_smaller=%d", &number);
                        listSmaller(path, number, 1, 0);
                    }
                    //end
                    if (strstr(argv[3], "name_ends_with=") != NULL)
                    {
                        char string[30];
                        sscanf(argv[3], "name_ends_with=%s", string);
                        listString(path, string, 1, 0);
                    }
                }
                //size/end + path + recursive
                if (strcmp(argv[4], "recursive") == 0 && strstr(argv[3], "path") != NULL)
                {
                    char path[1024];
                    sscanf(argv[3], "path=%s", path);
                    //size
                    if (strstr(argv[2], "size_smaller=") != NULL)
                    {
                        int number = 0;
                        sscanf(argv[2], "size_smaller=%d", &number);
                        listSmaller(path, number, 1, 0);
                    }
                    //end
                    if (strstr(argv[2], "name_ends_with=") != NULL)
                    {
                        char string[30];
                        sscanf(argv[2], "name_ends_with=%s", string);
                        listString(path, string, 1, 0);
                    }
                }
                //size/end + recursive + path
                if (strcmp(argv[3], "recursive") == 0 && strstr(argv[4], "path") != NULL)
                {
                    char path[1024];
                    sscanf(argv[4], "path=%s", path);
                    //size
                    if (strstr(argv[2], "size_smaller=") != NULL)
                    {
                        int number = 0;
                        sscanf(argv[2], "size_smaller=%d", &number);
                        listSmaller(path, number, 1, 0);
                    }
                    //end
                    if (strstr(argv[2], "name_ends_with=") != NULL)
                    {
                        char string[30];
                        sscanf(argv[2], "name_ends_with=%s", string);
                        listString(path, string, 1, 0);
                    }
                }
            }
        }
        //-----------PARSE-----------
        if (argc == 3)
        {
            if (strcmp(argv[1], "parse") == 0 && strstr(argv[2], "path=") != NULL)
            {
                char path[512];
                sscanf(argv[2], "path=%s", path);
                parse(path);
            }
        }

        //----------FINDALL------------
        if (argc == 3)
        {
            if (strcmp(argv[1], "findall") == 0 && strstr(argv[2], "path=") != NULL)
            {
                char path[512];
                sscanf(argv[2], "path=%s", path);
                findall(path, 0);
            }           
        }

        //--------EXTRACT--------
        if (argc == 5)
        {
            if (strcmp(argv[1], "extract") == 0)
            {
                int section;
                int line;
                char path[512];
                if (strstr(argv[2], "path=") != NULL)
                {
                    sscanf(argv[2], "path=%s", path);
                    //path + section + line
                    if (strstr(argv[3], "section=") != NULL && strstr(argv[4], "line=") != NULL)
                    {
                        sscanf(argv[3], "section=%d", &section);
                        sscanf(argv[4], "line=%d", &line);
                        extract(path, section, line);
                    }
                    //path + line + section
                    if (strstr(argv[4], "section=") != NULL && strstr(argv[3], "line=") != NULL)
                    {
                        sscanf(argv[4], "section=%d", &section);
                        sscanf(argv[3], "line=%d", &line);
                        extract(path, section, line);
                    }
                }
                if (strstr(argv[2], "section=") != NULL)
                {
                    sscanf(argv[2], "section=%d", &section);
                    //section + path +line
                    if (strstr(argv[3], "path=") != NULL && strstr(argv[4], "line=") != NULL)
                    {
                        sscanf(argv[3], "path=%s", path);
                        sscanf(argv[4], "line=%d", &line);
                        extract(path, section, line);
                    }
                    //section + line + path
                    if (strstr(argv[4], "path=") != NULL && strstr(argv[3], "line=") != NULL)
                    {
                        sscanf(argv[4], "path=%s", path);
                        sscanf(argv[3], "line=%d", &line);
                        extract(path, section, line);
                    }
                }
                if (strstr(argv[2], "line=") != NULL)
                {
                    sscanf(argv[2], "line=%d", &line);
                    //line + path + section 
                    if (strstr(argv[3], "path=") != NULL && strstr(argv[4], "section=") != NULL)
                    {
                        sscanf(argv[3], "path=%s", path);
                        sscanf(argv[4], "section=%d", &section);
                        extract(path, section, line);
                    }
                    //line + section + path 
                    if (strstr(argv[4], "path=") != NULL && strstr(argv[3], "section=") != NULL)
                    {
                        sscanf(argv[4], "path=%s", path);
                        sscanf(argv[3], "section=%d", &section);
                        extract(path, section, line);
                    }
                }
            }
        }
    }
    return 0;
}