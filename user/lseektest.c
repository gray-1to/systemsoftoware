#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"
int main() {
    printf("lseektest start\n");
    unlink("lseekfile");

    char buffer[64];

    int fd = open("lseekfile", O_CREATE | O_WRONLY | O_TRUNC);
    write(fd, "abcdefghijklmnopqrstuvwxyz", 26);
    close(fd);

    int fd2 = open("lseekfile", O_RDWR);
    // read(fd2, buffer, sizeof(buffer));
    // printf("%s\n", buffer);
    int lseek_result = lseek(fd2, 0, SEEK_SET);
    if(lseek_result == -1){
        printf("lseektest error: first lseek failed\n");
        close(fd2);
        exit(1);
    }
    int n = read(fd2, buffer, sizeof(buffer));
    if(n == 0){
        printf("lseektest error: first file read failed\n");
        close(fd2);
        exit(1);
    }
    if(buffer[0] != 'a'){
        printf("lseektest error: first test failed. read %c. expected a\n", buffer[0]);
        printf("%d\n",(int)buffer[0] );
        close(fd2);
        exit(1);
    }
    
    lseek_result = lseek(fd2, 4, SEEK_SET);
    if(lseek_result == -1){
        printf("lseektest error: second lseek failed\n");
        close(fd2);
        exit(1);
    }
    n = read(fd2, buffer, 1);
    if(n != 1){
        printf("lseektest error: second file read failed\n");
        close(fd2);
        exit(1);
    }
    if(buffer[0] != 'e'){
        printf("lseektest error: second test failed. read %c. expected e\n", buffer[0]);
        close(fd2);
        exit(1);
    }
    
    lseek_result = lseek(fd2, -2, SEEK_CUR);
    if(lseek_result == -1){
        printf("lseektest error: third lseek failed\n");
        close(fd2);
        exit(1);
    }
    n = read(fd2, buffer, 1);
    if(n != 1){
        printf("lseektest error: third file read failed\n");
        close(fd2);
        exit(1);
    }
    if(buffer[0] != 'd'){
        printf("lseektest error: third test failed. read %c. expected d\n", buffer[0]);
        close(fd2);
        exit(1);
    }
    
    lseek_result = lseek(fd2, 0, SEEK_CUR);
    if(lseek_result == -1){
        printf("lseektest error: forth lseek failed\n");
        close(fd2);
        exit(1);
    }
    n = read(fd2, buffer, 1);
    if(n != 1){
        printf("lseektest error: forth file read failed\n");
        close(fd2);
        exit(1);
    }
    if(buffer[0] != 'e'){
        printf("lseektest error: forth test failed. read %c. expected e\n", buffer[0]);
        close(fd2);
        exit(1);
    }
    
    lseek_result = lseek(fd2, 0, SEEK_END);
    if(lseek_result == -1){
        printf("lseektest error: fifth lseek failed\n");
        close(fd2);
        exit(1);
    }
    write(fd2, "hello", 5);
    lseek_result = lseek(fd2, 0, SEEK_SET);
    n = read(fd2, buffer, sizeof(buffer));
    if(n != 31){
        printf("lseektest error: fifth file read failed. file length is %d\n", n);
        close(fd2);
        exit(1);
    }

    lseek_result = lseek(fd2, 0, SEEK_END);
    int end_offset = lseek_result;
    lseek_result = lseek(fd2, 100, SEEK_END);
    if(lseek_result - end_offset != 100){
        printf("lseektest error: sixth lseek failed. sub is %d\n", lseek_result - end_offset);
        close(fd2);
        exit(1);
    }
    close(fd2);
    

    unlink("lseekfile");
    printf("lseektest finished\n");
    exit(0);
}
