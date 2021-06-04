#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iso646.h>

struct Arr{
    void* values;
    int count;
    size_t forcreate;
    void* (*SQR)(void*);
};

void* memory;

struct Arr* Create(int count, size_t forcreate, void* memory){
    struct Arr* arr = malloc(sizeof(struct Arr));
    arr->count = count;
    arr->forcreate = forcreate;
    arr->values = malloc(forcreate*count);
    for(size_t i=0; i < (size_t)count; i++){
        int8_t* pos = (int8_t*)arr->values + i*forcreate;
        memcpy((void*)pos, memory, forcreate);
    }
    return arr;
}

struct Arr* IntCreate(int count,size_t forcreate){
    memory=malloc(forcreate);
    *(int*)memory = 1;
    struct Arr* ResArr = Create(count,forcreate,memory);
    for (size_t i = 0; i < (size_t)count;i++)
    {
        if(scanf("%d",(int*)(ResArr->values+i*(forcreate)))!=1){
            free((int*)ResArr->values);
            free(ResArr);
            free(memory);
            return 0;
        }
    }
    free(memory);
    return ResArr;
}

struct Complex{
    double Re;
    double Im;
};

struct Arr* ComplexCreateRe(int count, size_t forcreate) {
    memory = malloc(forcreate);
    *(double *) memory = 1;
    struct Arr *ResArr = Create(count, forcreate, memory);
    for (size_t i = 0; i < (size_t) count; i++) {
        if (scanf("%lf", (double *) (ResArr->values + i * (forcreate))) != 1) {
            free((double *) ResArr->values);
            free(ResArr);
            free(memory);
            return 0;
        }
    }
    free(memory);
    return ResArr;
}

struct Arr* ComplexCreateIm(int count, size_t forcreate) {
    memory = malloc(forcreate);
    *(double *) memory = 1;
    struct Arr *ResArr = Create(count, forcreate, memory);
    for (size_t i = 0; i < (size_t) count; i++) {
        if (scanf("%lf", (double *) (ResArr->values + i * (forcreate))) != 1) {
            free((double *) ResArr->values);
            free(ResArr);
            free(memory);
            return 0;
        }

    }
    free(memory);
    return ResArr;
}

int is_real_more_than_im(struct Complex* example){
    if (example->Re > example->Im){
        return 1;
    }
    return 0;
}

int is_even(int example){
    if(example%2 == 0){
        return 1;
    }else{
        return 0;
    }
}

struct Arr* ComplexWhere(struct Arr* example, int(*is_real_more_than_im)(double)){
    int sizeofRes = 0;
    for (int i = 0; i < example->count; ++i){
        if(is_real_more_than_im(*(double*)(example->values + i*example->forcreate)) == 1)
            sizeofRes++;
    }
    if (sizeofRes == 0){
        return 0;
    }
    struct Arr* Res;
    memory = malloc(example->forcreate);
    *(double*)memory = 1;
    Res = Create(sizeofRes,example->forcreate,memory);
    int index = 0;
    for (int i = 0; i < example->count;i++)
    {
        if(is_real_more_than_im(*(double*)(example->values + i*example->forcreate)) == 1){
            *(double*)(Res->values+index*(Res->forcreate)) = *(double*)(example->values+i*(example->forcreate));
            index++;
        }
    }
    free(memory);
    return Res;
}

struct Arr* IntWhere(struct Arr* example,int(*is_even)(int)){
    int sizeofRes = 0;
    for (int i = 0; i < example->count; ++i)
    {
        if(is_even(*(int*)(example->values + i*example->forcreate)) == 1)
            sizeofRes++;
    }
    if (sizeofRes == 0){
        return 0;
    }
    struct Arr* Res;
    memory = malloc(example->forcreate);
    *(int*)memory = 1;
    Res = Create(sizeofRes,example->forcreate,memory);
    int index = 0;
    for (int i = 0; i < example->count;i++)
    {
        if(is_even(*(int*)(example->values + i*example->forcreate)) == 1){
            *(int*)(Res->values+index*(Res->forcreate)) = *(int*)(example->values+i*(example->forcreate));
            index++;
        }
    }
    free(memory);
    return Res;
}

struct Arr* ConcatenationComplex(struct Arr* first, struct Arr* second){
    struct Arr* Res;
    memory = malloc(first->forcreate);
    *(double*)memory = 1;
    Res = Create(first->count+second->count,first->forcreate,memory);
    int index = 0;
    for (int i = 0; i < first->count; ++i)
    {
        *(double*)(Res->values + index*Res->forcreate) = *(double*)(first->values + i*first->forcreate);
        index++;
    }
    for (int i = 0; i < second->count; ++i)
    {
        *(double*)(Res->values + index*Res->forcreate) = *(double*)(second->values + i*second->forcreate);
        index++;
    }
    return Res;
}


struct Arr* ConcatenationInt(struct Arr* first,struct Arr* second){
    struct Arr* Res;
    memory = malloc(first->forcreate);
    *(int*)memory = 1;
    Res = Create(first->count+second->count,first->forcreate,memory);
    int index = 0;
    for (int i = 0; i < first->count; ++i)
    {
        *(int*)(Res->values + index*Res->forcreate) = *(int*)(first->values + i*first->forcreate);
        index++;
    }
    for (int i = 0; i < second->count; ++i)
    {
        *(int*)(Res->values + index*Res->forcreate) = *(int*)(second->values + i*second->forcreate);
        index++;
    }
    return Res;
}

void* SQRComplex(struct Complex* example){
    double a = example->Re;
    double b = example->Im;
    *(double*)example = a*b;
    return (void*)(example);
}

void* SQRInt(void* example){
    int a = *(int*)example;
    int b = *(int*)example;
    *(int*)example = a*b;
    return (void*)(example);
}

void MapInt(struct Arr* example,void*(*SQR)(void*)){
    for (int i = 0; i < example->count; ++i)
    {
        *(int*)(example->values + i*(example->forcreate))=*(int*)(SQR((int*)(example->values + i*(example->forcreate))));
    }
}

void MapComplex(struct Arr* example,void*(*SQR)(void*)){
    for (int i = 0; i < example->count; ++i)
    {
        *(double*)(example->values + i*(example->forcreate))=*(double*)(SQR((double*)(example->values + i*(example->forcreate))));
    }
}


void PrintArrayInt(struct Arr* arr){

    for (int i = 0; i < arr->count; ++i)
    {
        printf("%d ",*(int*)(arr->values+i*arr->forcreate));
    }
}

void PrintArrayComplex(struct Arr* arr){
    for (int i = 0; i < arr->count; ++i)
    {
        printf("%lf ",*(double*)(arr->values+i*arr->forcreate));
    }
}

int main(void)
{
    int N, M;
    struct Arr* first;
    struct Arr* second;
    struct Arr* firstIm;
    struct Arr* secondIm;
    struct Arr* firstRe;
    struct Arr* secondRe;
    struct Arr* Wh1;
    struct Arr* Wh2;
    struct Arr* Con;
    printf("\t\t\t INTEGER VALUES\n");
    printf("Size of first array:\n");
    if(scanf("%d",&N)!=1){
        printf("\t\t\terror\n");
        return -1;
    }
    printf("Enter %d values for first array", N);
    first = IntCreate(N, (sizeof(int)));
    if(first == 0){
        printf("\t\t\terror\n");
        free(first);
        free(memory);
        return -1;
    }

    printf("size of second array :\n");
    if(scanf("%d",&M)!=1){
        free((int*)(first->values));
        free(first);
        free(memory);
        printf("\t\t\tINVALID INPUT ! ! !\n");
        return -1;
    }

    printf("Enter %d values for second array:\n",M);
    second = IntCreate(M,(sizeof(int)));
    if(second == 0){
        printf("\t\t\tINVALID INPUT ! ! !\n");
        free(second);
        free((int*)(first->values));
        free(first);
        free(memory);
        return -1;
    }

    printf("Where is even?(first)\n");
    Wh1 = IntWhere(first,is_even);
    if(Wh1==0){
        printf(" no one even number\n");
    }else{
        PrintArrayInt(Wh1);
    }
   printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    printf("Where is even?(second)\n");
    Wh2 = IntWhere(second,is_even);
    if(Wh2==0){
        printf("no one even number\n");
    }else{
        PrintArrayInt(Wh2);
    }
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    Con = ConcatenationInt(first,second);
    printf("first array :\n");
    PrintArrayInt(first);
    printf("\nsecond array :\n");
    PrintArrayInt(second);
    printf("\n");
    printf("Concatenation of first and second :\n");
    PrintArrayInt(Con);
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    printf("Map for first :\n");//демонстрация работы функции MapInt
    MapInt(first,SQRInt);
    PrintArrayInt(first);
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");


    printf("Map for second :\n");//демонстрация работы функции MapInt
    MapInt(second,SQRInt);
    PrintArrayInt(second);
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    free((int*)(first->values));
    free((int*)(second->values));
    if(Wh1!=0){
        free((int*)(Wh1->values));
        free(Wh1);
    }
    if(Wh2!=0){
        free((int*)(Wh2->values));
        free(Wh2);
    }
    free((int*)(Con->values));
    free(first);
    free(second);
    free(Con);
    free(memory);

    //////////////////////////////////////////////////////////////////////////////////////////

    printf("\t\t\t COMPLEX VALUES\n");

    printf("size of first:\n");
    if(scanf("%d",&N)!=1){
        printf("\t\t\terror\n");
        return -1;
    }
    printf("Enter %d values for first array:\n",N);
    firstIm = ComplexCreateIm(N,(sizeof(double)));
    if(firstIm == 0){
        printf("\t\t\terror\n");
        free(first);
        free(memory);
        return -1;
    }
    firstRe = ComplexCreateRe(N,(sizeof(double)));
    if(firstIm == 0){
        printf("\t\t\terror\n");
        free(first);
        free(memory);
        return -1;
    }

    printf("size of second:\n");
    if(scanf("%d",&M)!=1){
        free((double*)(first->values));
        free(first);
        free(memory);
        printf("\t\t\terror\n");
        return -1;
    }
    printf("Enter %d values for second array:\n",M);
    secondIm = ComplexCreateIm(M,(sizeof(double)));
    if(second == 0){
        printf("\t\t\terror\n");
        free(second);
        free((double*)(first->values));
        free(first);
        free(memory);
        return -1;
    }
    secondRe = ComplexCreateRe(M,(sizeof(double)));
    if(second == 0){
        printf("\t\t\terror\n");
        free(second);
        free((double*)(first->values));
        free(first);
        free(memory);
        return -1;
    }
    printf("which one is bigger\n");
    Wh1 = ComplexWhere(first,is_real_more_than_im);
    if(Wh1==0){
        printf("mod of Re is smaller than mod of Im\n");
    }else{
        PrintArrayComplex(Wh1);
    }
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    printf("which on is bigger\n");
    Wh2 = ComplexWhere(second,is_real_more_than_im);
    if(Wh2==0){
        printf("mod of Re is smaller than mod if Im\n");
    }else{
        PrintArrayComplex(Wh2);
    }
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    Con = ConcatenationComplex(first,second);
    printf("first array :\n");
    PrintArrayComplex(first);
    printf("\nsecond array :\n");
    PrintArrayComplex(second);
    printf("\n");
    printf("Concatenation of first and second :\n");
    PrintArrayComplex(Con);
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    printf("Map for first :\n");
    MapComplex(first,SQRComplex);
    PrintArrayComplex(first);
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    printf("Map for second :\n");
    MapComplex(second,SQRComplex);
    PrintArrayComplex(second);
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");


    free((double*)(first->values));
    free((double*)(second->values));
    if(Wh1!=0){
        free((double*)(Wh1->values));
        free(Wh1);
    }
    if(Wh2!=0){
        free((double*)(Wh2->values));
        free(Wh2);
    }
    free((double*)(Con->values));
    free(first);
    free(second);
    free(Con);
    free(memory);

    return 0;
}