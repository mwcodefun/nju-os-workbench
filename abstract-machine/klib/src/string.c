#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len = 0;
  const char *walker = s;
  while (*walker && *walker != '\0') {
    walker++;
    len++;
  }   
  return len;
}

char *strcpy(char *dst, const char *src) {
   char *s = dst;

  while ((*dst++ = *src++))
    ;

  return s;

}

char *strncpy(char *dst, const char *src, size_t n) {
  char *ans = dst;
  while(n > 0 && *src){
    if (*src == '\0'){
      *dst = *src;
      break;
    }
    *dst++ = *src++;
    n--;
  }
  while(n > 0){
    *dst++ = '\0';
    n--;
  }
  return ans;
}

char *strcat(char *dst, const char *src) {
  char *ans = dst;
  while(*dst){
    dst++;
  }
  while ((*dst++ = *src++));
  return ans;
}

char *strncat(char *dst,const char *src,size_t n){
  char *ans = dst;
  while(*dst){
    dst++;
  }

  while ((*dst++ = *src++) && n-- > 0);
  return ans;
}


int strcmp(const char *s1, const char *s2) {
   while (*s1 == *s2) {
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
   while (*s1 == *s2 && n > 0) {
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
        n--;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

void *memset(void *s, int c, size_t n) {
  unsigned char *p = s;
  while(n--){
    *p++ = (unsigned char)c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  const unsigned char *s = src;
  unsigned char *d = dst;
  if(d > s && (d - s) < n){
    s += n;
    d += n;
    while(n--){
      *(--d) = *(--s);
    }
  }else{
    while(n--){
      *d++ = *s++;
    }

  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  unsigned char *s = (unsigned char *)in;
  unsigned char *d = (unsigned char *)out;
  while(n--){
    *d++ = *s++;
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *b1;
  const unsigned char *b2;
  b1 = (const unsigned char *)s1;
  b2 = (const unsigned char *)s2;

  while(n--){
    if (*b1 != *b2){
      return *b1 - *b2;
    }
    b1++;
    b2++;
  }
  return 0;
}

#endif
