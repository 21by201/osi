#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>

void reverse_string(char *str) {
    int length = strlen(str);
    int i, j;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void reverse_filename(char* filename) {
    char* dot = strrchr(filename, '.');  // find the last dot in the filename
    if (dot != NULL) {  // if there is a dot, reverse only the filename before it
        int i = 0;
        int j = dot - filename - 1;
        while (i < j) {
            char temp = filename[i];
            filename[i] = filename[j];
            filename[j] = temp;
            i++;
            j--;
        }
    } else {  // if there is no dot, reverse the entire filename
        reverse_string(filename);
    }
}

void reverse_file_contents(char* filename) {
    FILE* fp = fopen(filename, "rb+");
    if(fp == NULL) {
        printf("\nError in Opening the file, %s", filename);
        return;
    }
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    char* contents = (char*)malloc(file_size * sizeof(char));
    fseek(fp, 0, SEEK_SET);
    fread(contents, file_size, 1, fp);
    reverse_string(contents);
    fseek(fp, 0, SEEK_SET);
    fwrite(contents, file_size, 1, fp);
    fclose(fp);
}

void copyFile(char* source, char* target) {
    char ch;
    FILE *fs, *ft;
    fs = fopen(source, "r");
    if(fs == NULL) {
        printf("\nError in Opening the file, %s", source);
        return;
    }
    ft = fopen(target, "w");
    if(ft == NULL) {
        printf("\nError in Opening the file, %s", target);
        return;
    }
    ch = fgetc(fs);
    while(ch != EOF) {
        fputc(ch, ft);
        ch = fgetc(fs);
    }
    fclose(fs);
    fclose(ft);
    reverse_file_contents(target);
}

void copyDirectory(char* sourceDir, char* targetDir) {
    DIR *dir;
    struct dirent *ent;
    struct stat st;
    char sourcePath[1000], targetPath[1000], reversedName[1000];
    dir = opendir(sourceDir);
    if(dir == NULL) {
        printf("\nError in Opening the directory, %s", sourceDir);
        return;
    }
    while((ent = readdir(dir)) != NULL) {
        sprintf(sourcePath, "%s/%s", sourceDir, ent->d_name);
        sprintf(reversedName, "%s", ent->d_name);
        reverse_filename(reversedName);
        sprintf(targetPath, "%s/%s", targetDir, reversedName);
        if(stat(sourcePath, &st) == 0 && S_ISREG(st.st_mode)) {
            copyFile(sourcePath, targetPath);
            printf("\nCopied file: %s", ent->d_name);
        }
    }
    closedir(dir);
}

char* create_reversed_directory(char* dirname) {
    char* basenam = basename(dirname);
    char basename_[1000];
    strcpy(basename_, basenam);
    reverse_string(basename_);

    char* newdirname = malloc(strlen(dirname) + 1);
    strcpy(newdirname, dirname);
    char* lastSlash = strrchr(newdirname, '/');
    if (lastSlash == NULL) {
        printf("Error: invalid directory\n");
        exit(1);
    }
    *(lastSlash + 1) = '\0';

    char* newbasename = malloc(strlen(basename_) + 1);
    strcpy(newbasename, basename_);

    char* newdir = malloc(strlen(newdirname) + strlen(newbasename) + 1);
    sprintf(newdir, "%s%s", newdirname, newbasename);
    mkdir(newdir, 0777);

    //free(newdir);
    free(newbasename);
    free(newdirname);

    return newdir;
}

int main() {
    char* sourceDir = "/home/valera54/osi";
    char targetDir[1000];
    sprintf(targetDir, "%s", create_reversed_directory(sourceDir));
    copyDirectory(sourceDir, targetDir);
    printf("\nFinished copying all files.");
    return 0;
}
