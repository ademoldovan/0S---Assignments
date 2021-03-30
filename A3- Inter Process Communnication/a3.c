#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define FIFO_NAME_1 "RESP_PIPE_78690"
#define FIFO_NAME_2 "REQ_PIPE_78690"

int error_create_shm(int fd_w)
{
    int a1 = 10;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "CREATE_SHM", 10) != 10)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 5;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "ERROR", 5) != 5)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int success_create_shm(int fd_w)
{
    int a1 = 10;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "CREATE_SHM", 10) != 10)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 7;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "SUCCESS", 7) != 7)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int error_write_to_shm(int fd_w)
{
    int a1 = 12;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "WRITE_TO_SHM", 12) != 12)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 5;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "ERROR", 5) != 5)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int success_write_to_shm(int fd_w)
{
    int a1 = 12;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "WRITE_TO_SHM", 12) != 12)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 7;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "SUCCESS", 7) != 7)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int error_map_file(int fd_w)
{
    int a1 = 8;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "MAP_FILE", 8) != 8)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 5;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "ERROR", 5) != 5)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int success_map_file(int fd_w)
{
    int a1 = 8;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "MAP_FILE", 8) != 8)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 7;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "SUCCESS", 7) != 7)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int error_read_from_file_offset(int fd_w)
{
    int a1 = 21;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "READ_FROM_FILE_OFFSET", 21) != 21)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 5;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "ERROR", 5) != 5)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int success_read_from_file_offset(int fd_w)
{
    int a1 = 21;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "READ_FROM_FILE_OFFSET", 21) != 21)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 7;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "SUCCESS", 7) != 7)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}
int error_read_from_file_section(int fd_w)
{
    int a1 = 22;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "READ_FROM_FILE_SECTION", 22) != 22)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 5;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "ERROR", 5) != 5)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int success_read_from_file_section(int fd_w)
{
    int a1 = 22;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "READ_FROM_FILE_SECTION", 22) != 22)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 7;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "SUCCESS", 7) != 7)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int error_read_from_logical_space(int fd_w)
{
    int a1 = 30;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "READ_FROM_LOGICAL_SPACE_OFFSET", 30) != 30)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 5;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "ERROR", 5) != 5)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int success_read_from_logical_space(int fd_w)
{
    int a1 = 30;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "READ_FROM_LOGICAL_SPACE_OFFSET", 30) != 30)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    a1 = 7;
    if (write(fd_w, &a1, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "SUCCESS", 7) != 7)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    return 1;
}

int main(int argc, char **argv)
{
    //creeaza un pipe denumit RESP_PIPE_7860
    if (mkfifo(FIFO_NAME_1, 0600) != 0)
    {
        printf("ERROR\ncannot create the response pipe\n");
        return 1;
    }
    //deschide in citire un pipe REQ_PIPE_78690
    int fd_r = -1;
    fd_r = open(FIFO_NAME_2, O_RDONLY);
    if (fd_r == -1)
    {
        printf("ERROR\ncannot open the request pipe\n");
        unlink(FIFO_NAME_1);
        return 1;
    }
    //deschide in scriere pipe-ul RESP_PIPE_78690
    int fd_w = -1;
    fd_w = open(FIFO_NAME_1, O_WRONLY);
    if (fd_w == -1)
    {
        perror("Could not open FIFO_WRITE!");
        close(fd_r);
        unlink(FIFO_NAME_1);
        return 1;
    }
    //scrie "7CONNECT" in pipe -ul "RESP_PIPE_78690"

    int a = 7;
    if (write(fd_w, &a, 1) != 1)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    if (write(fd_w, "CONNECT", 7) != 7)
    {
        perror("Could not write into pipe!");
        return 1;
    }
    printf("SUCCESS\n");

    char *shared = NULL;
    char *request = NULL;
    int shmFd;
    char *file = NULL;
    char *mapFile = NULL;
    int fdMap = -1;
    int dimOfMapFile = 0;
    unsigned int nrOfSections = 0;
    for (;;)
    {
        //citim requestul: prima data size-ul , apoi stringul
        unsigned int size = 0;
        if (read(fd_r, &size, sizeof(char)) != sizeof(char))
        {
            perror("Could not read from pipe!");
            return 1;
        }

        request = (char *)malloc(size * sizeof(char));
        if (request == NULL)
        {
            perror("Could not allocate memory");
            return -1;
        }
        if (read(fd_r, request, size) != size)
        {
            perror("Could not read from pipe!");
            return -1;
        }
        request[size] = 0;
        if (strcmp(request, "EXIT") == 0)
        {
            munmap(shared, sizeof(char) * 2187741);
            munmap(mapFile, sizeof(char) * dimOfMapFile);
            shared = NULL;
            shm_unlink("/ZQB58nd");
            close(fd_r);
            close(fd_w);
            unlink(FIFO_NAME_1);
            break;
        }

        //comanda PING -> scriem PING PONG 78690
        if (strcmp(request, "PING") == 0)
        {
            int sz = 4;
            if (write(fd_w, &sz, 1) != 1)
            {
                perror("Could not write into pipe!");
                return 1;
            }
            if (write(fd_w, "PING", 4) != 4)
            {
                perror("Could not write into pipe!");
                return 1;
            }
            if (write(fd_w, &sz, 1) != 1)
            {
                perror("Could not write into pipe!");
                return 1;
            }
            if (write(fd_w, "PONG", 4) != 4)
            {
                perror("Could not write into pipe!");
                return 1;
            }
            unsigned int b = 78690;
            if (write(fd_w, &b, 4) != 4)
            {
                perror("Could not write into pipe!");
                return 1;
            }
        }

        //--------------CREATE SHM----------------------
        if (strcmp(request, "CREATE_SHM") == 0)
        {
            unsigned int memorySize = 0;
            if (read(fd_r, &memorySize, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }

            shmFd = shm_open("/ZQB58nd", O_CREAT | O_RDWR | O_TRUNC, 0664);
            if (shmFd < 0)
            {
                //eroare
                error_create_shm(fd_w);
            }
            ftruncate(shmFd, memorySize);
            shared = (char *)mmap(0, memorySize, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
            if (shared == (void *)-1)
            {
                //eroare
                error_create_shm(fd_w);
                shm_unlink("/ZQB58nd");
            }
            //succes
            success_create_shm(fd_w);
        }

        //------------------WRITE TO SHM------------------
        if (strcmp(request, "WRITE_TO_SHM") == 0)
        {
            //citim offset si value din pipe
            unsigned int offset, value;
            if (read(fd_r, &offset, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            if (read(fd_r, &value, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            //verificam daca datele sunt corecte
            if (offset < 0 || offset > 2187741)
            {
                //eroare
                error_write_to_shm(fd_w);
            }
            if ((offset + sizeof(size)) > 2187741)
            {
                //eroare
                error_write_to_shm(fd_w);
            }
            //trebuie sa scriem in memoria partajata
            memcpy(&shared[offset], (void *)&value, 4);
            success_write_to_shm(fd_w);
        }

        //------------------MAP FILE------------------
        if (strcmp(request, "MAP_FILE") == 0)
        {
            unsigned int sizeOfFile = 0;
            if (read(fd_r, &sizeOfFile, 1) != 1)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            file = (char *)malloc(sizeOfFile * sizeof(char));
            if (read(fd_r, file, sizeOfFile * sizeof(char)) != sizeOfFile * sizeof(char))
            {
                perror("Could not read from pipe!");
                return -1;
            }
            file[sizeOfFile] = 0;
            //mapare fisier in memorie
            fdMap = open(file, O_RDONLY);
            if (fdMap == -1)
            {
                error_map_file(fd_w);
            }
            dimOfMapFile = lseek(fdMap, 0, SEEK_END);
            lseek(fdMap, 0, SEEK_SET);
            int a = 2187743;
            mapFile = (char *)mmap(&a, dimOfMapFile, PROT_READ, MAP_PRIVATE, fdMap, 0);
            if (mapFile == (void *)-1)
            {
                error_map_file(fd_w);
                close(fdMap);
            }
            success_map_file(fd_w);
            free(file);
        }

        //--------------READ FROM FILE OFFSET--------------
        if (strcmp(request, "READ_FROM_FILE_OFFSET") == 0)
        {
            //citim din pipe offset si nrOfBytes
            unsigned int offset, nrOfBytes;
            if (read(fd_r, &offset, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            if (read(fd_r, &nrOfBytes, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }

            if (mapFile != (void *)(-1))
            {
                if ((offset + nrOfBytes) > dimOfMapFile)
                {
                    error_read_from_file_offset(fd_w);
                }
                else
                {
                    char *values = (char *)malloc((nrOfBytes + 1) * sizeof(char));
                    memcpy(values, (mapFile + offset), nrOfBytes);
                    //scriem in memoria partajata
                    memcpy(shared, values, nrOfBytes);
                    success_read_from_file_offset(fd_w);
                    free(values);
                }
            }
            else
            {
                error_read_from_file_offset(fd_w);
            }
        }

        //--------------READ FROM FILE SECTION--------------
        if (strcmp(request, "READ_FROM_FILE_SECTION") == 0)
        {
            //citim din pipe sectionNr,  offset si nrOfBytes
            unsigned int sectionNr, offset, nrOfBytes;
            if (read(fd_r, &sectionNr, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            if (read(fd_r, &offset, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            if (read(fd_r, &nrOfBytes, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            //citim din fisierul mapat magic, version... pentru a verifica ca fisierul SF este valid
            char *magic = (char *)malloc(sizeof(char) * 3);
            unsigned int version;
            unsigned int sectionOffset;
            unsigned int sectionSize;

            memcpy(magic, mapFile, 2);
            magic[2] = 0;
            memcpy(&version, mapFile + 4, 4);
            memcpy(&nrOfSections, mapFile + 8, 1);
            printf("%d\n", nrOfSections);
            if (magic[0] == 'G' && magic[1] == '7' && version >= 32 && version <= 116 && nrOfSections >= 1 && nrOfSections <= 17 && sectionNr <= nrOfSections)
            {
                //avem un fisier sf valid
                //adresa de la care citim offsetul sectiunii noastre
                int off = 32 + 31 * (sectionNr - 1);

                memcpy(&sectionOffset, mapFile + off, 4);
                memcpy(&sectionSize, mapFile + off + 4, 4);

                if (sectionSize < nrOfBytes + offset)
                {
                    error_read_from_file_section(fd_w);
                }
                else
                {
                    char *values = (char *)malloc((nrOfBytes + 1) * sizeof(char));
                    memcpy(values, (mapFile + sectionOffset + offset), nrOfBytes);
                    memcpy(shared, values, nrOfBytes);
                    success_read_from_file_section(fd_w);
                    free(values);
                }
            }
            else
            {
                //nu avem un fisier sf valid
                error_read_from_file_section(fd_w);
            }
        }

        //--------------READ FROM LOGICAL SPACE OFFSET--------------
        if (strcmp(request, "READ_FROM_LOGICAL_SPACE_OFFSET") == 0)
        {
            //citim din pipe logicalOffset si nrOfBytes
            unsigned int logicalOffset, nrOfBytes;
            if (read(fd_r, &logicalOffset, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            if (read(fd_r, &nrOfBytes, 4) != 4)
            {
                perror("Could not read from pipe!");
                return 1;
            }
            char *magic = (char *)malloc(sizeof(char) * 3);
            unsigned int version;
            memcpy(magic, mapFile, 2);
            magic[2] = 0;
            memcpy(&version, mapFile + 4, 4);
            memcpy(&nrOfSections, mapFile + 8, 1);
            if (magic[0] == 'G' && magic[1] == '7' && version >= 32 && version <= 116 && nrOfSections >= 1 && nrOfSections <= 17)
            {
                //avem un fisier sf valid
                int off = 32;
                int readOffset = 0; //adresa de la care citesc nrOfBytes
                int current = 0;
                int bytes = 0;
                int copieBytes = 0;
                int cat = 0;
                int ok = 0;
                for (int i = 0; i < nrOfSections; i++)
                {
                    memcpy(&readOffset, mapFile + off, 4);  //ofsetul sectiunii
                    memcpy(&current, mapFile + off + 4, 4); //size ul sectiunii;
                    cat = current / 2048;
                    bytes = bytes + (cat + 1) * 2048;
                    if (logicalOffset >= copieBytes && logicalOffset <= bytes)
                    {
                        char *values = (char *)malloc((nrOfBytes + 1) * sizeof(char));
                        memcpy(values, (mapFile + readOffset + (logicalOffset - copieBytes)), nrOfBytes);
                        memcpy(shared, values, nrOfBytes);
                        success_read_from_logical_space(fd_w);
                        free(values);
                        ok = 1;
                        break;
                    }
                    copieBytes = bytes;
                    off = off + 31;
                }
                if (ok == 0)
                {
                    error_read_from_logical_space(fd_w);
                }
            }
            else
            {
                //nu avem un fisier sf valid
                error_read_from_logical_space(fd_w);
            }
        }
        free(request);
    }
    return 0;
}