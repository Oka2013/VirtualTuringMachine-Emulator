#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct VirtualTM {
    unsigned int noc;
    unsigned int head;
    unsigned int ccid;
    int* cards;
    bool* tape;
};

bool getElement(int memchunk, int id) {
    return 1 & (memchunk >> id);
}

struct VirtualTM* newVTM(unsigned int noc) {
    struct VirtualTM* newvtm = (struct VirtualTM*)malloc(sizeof(struct VirtualTM));

    newvtm->noc = noc;
    newvtm->head = 512;
    newvtm->ccid = 1;
    newvtm->tape = (bool*)calloc(1024, sizeof(bool));
    newvtm->cards = (int*)calloc(noc, sizeof(int));

    return newvtm;
}

void stepVTM(struct VirtualTM* vtm) {
    short ccard = vtm->cards[vtm->ccid - 1] << !vtm->tape[vtm->head] * 16 >> 16;
    vtm->tape[vtm->head] = getElement(ccard, 0);
    vtm->head += getElement(ccard, 1) * 2 - 1;
    vtm->ccid = ccard >> 2;
}

void emulateVTM(struct VirtualTM* vtm) {
    while (vtm->ccid) {
        stepVTM(vtm);
    }
}

unsigned int countNOC(char* content) {
    int count = 1;
    for (int i = 0; i < strlen(content); i++) {
        content += content[i] == '\n';
    }
}

void applyLine(int* card, char* line) {
    int pown = 1;
    for (int i = strlen(line) - 1; i > 0; pown >>= 1, i--) {
        if (line[i] == ' ') {pown = 131072;}
        else {*card += (line[i] - 48) * pown;}
    }
}

void applyContent(struct VirtualTM* vtm, char* content) {
    int c = 0;
    for (int i = 0; content[i]; i++) {
        if (content[i] == '\n') {
            content[i] = '\0';
            applyLine(vtm->cards + c++, content);
            content += i + 1;
            i = 0;
        }
    }
}

int main() {
    long size;
    FILE* fptr;
    char filename[64] = "\0";
    char content[256] = "\0";

    printf("Enter your codes file (filename.txt) : ");
    scanf("%s", filename);
        
    fptr = fopen(filename, "r");

    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    fread(content, sizeof(char), size, fptr);
    
    struct VirtualTM* vtm = newVTM(countNOC(content));

    applyContent(vtm, content);

    emulateVTM(vtm);

    for (int i = 0; i < 1024; i++) {
        printf("%d ", vtm->tape[i]);
    }
}
