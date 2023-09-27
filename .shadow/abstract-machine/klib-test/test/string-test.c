#include <klib.h>
#include <assert.h>
#include <stdio.h>

int test_strlen(){
    char *a = "hello world";
    assert(strlen(a) == 11);
    assert(strlen(a) != 0);
    return 0;
}

void test_strncpy(){
    char a[] = "helloworld";
    char b[10];
    strncpy(b,a,5);
}

void test_strcat(){
    char a[100] = "hello";
    char b[] = "world";
    strcat(a,b);
}

int test_strcpy(){
    char a[30];
    char b[] = "worldnasdf"; 
    strcpy(a,b);
    assert(strlen(a) == strlen(b));

    char *i = a;
    char *j = b;
    while(*i){
        assert(*i++ == *j++);
    }
    return 0;

}

void test_strcmp(){
    char a[] = "hello";
    char b[] = "hello";
    assert(strcmp(a,b) == 0);
    char c[] = "helloa";
    assert(strcmp(a,c) < 0);
    char d[] = "a";
    char e[] = "e";
    assert(strcmp(e,d) > 0);
}

void test_printf(){
    printf("x=%d\n",0);
    printf("x=%s\n","gggg");
    printf("x=%d\n",100);
}

void test_vprintf(){
    char buffer[100];
    sprintf(buffer,"hello%d\n",10);
    printf(buffer);
}

int main(){
    // printf("test\n");
    test_strlen();
    test_strcpy();
    test_strncpy();
    test_strcat();
    test_strcmp();
    test_printf();
    // test_vprintf();
    return 0;
}