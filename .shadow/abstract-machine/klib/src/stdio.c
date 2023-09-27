#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#define max 999999

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
int avsnprintf(char *out,size_t n,const char *fmt,va_list ap,bool stdout);
char* itoa(int value, char* str, int base) {
    if (base != 10) {
        return NULL; // 当前只支持十进制
    }

    char* start = str;
    bool isNegative = false;

    // 处理0的情况
    if (value == 0) {
        *str++ = '0';
        *str = '\0';
        return start;
    }

    // 处理负数
    if (value < 0) {
        isNegative = true;
        value = -value;
    }

    // 从低到高为每个数字转换为字符
    while (value != 0) {
        int remainder = value % base;
        *str++ = remainder + '0';
        value /= base;
    }

    // 如果数字是负的，添加负号
    if (isNegative) {
        *str++ = '-';
    }

    *str = '\0';

    // 翻转字符串
    char* end = str - 1;
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }

    return str;
}


int printf(const char *fmt, ...) {
  va_list args;
  va_start(args,fmt); 
  int len = avsnprintf(NULL,max,fmt,args,true);
  va_end(args);
 
  return len;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return avsnprintf(out,max,fmt,ap,false);
}

int sprintf(char *out, const char *fmt, ...) {
  va_list args;
  va_start(args,fmt); 
  int len = avsnprintf(out,max,fmt,args,false);
  va_end(args);
  return len;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  va_list args;
  va_start(args,fmt);
  int len = avsnprintf(out,n,fmt,args,false);
  va_end(args);
  return len;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  return avsnprintf(out,n,fmt,ap,false);
}
int to_std_or_cat_size(char *out,char *value,size_t n,bool stdout){
  //如果要输出的大小超过了size，那么就输出size大小的字符
  // n - l > 0
  int len = 0;
  if(!stdout){
    while(*out){
      out++;
    }
  }
  char *walker = value;
  while(*walker && n > 0){
    if (stdout)
    {
      putch(*walker++);
    }else{
      *out++ = *walker++;
    }
    len++;
    n--;
  }
  return len;
}

int to_std_or_cat(char *out,char *value,bool stdout){
  if (stdout){
    putstr(value);
    return strlen(value);
  }
  strcat(out,value);
  return strlen(value);
}

char a = '%';

int avsnprintf(char *out,size_t n,const char *fmt,va_list ap,bool stdout){
  const char *walker = fmt;

  bool is_formater = false;
  int len = 0;

  while(*walker && n > 0){
    if(*walker == '\0'){
      break;
    }
    if(is_formater){
      char *value = "";
      if(*walker == 'd'){
        char buffer[20];
        int int_value = va_arg(ap,int);
        itoa(int_value,buffer,10);
        value = buffer;
      }
      if(*walker == 's'){
        value = va_arg(ap,char*);
      }
      if(*walker == '%'){
        value = &a;
      }
      int l = to_std_or_cat_size(out,value,n,stdout);
      n = n - l;
      len = len + l;
      is_formater = false;
    }else{
      if(*walker == '%'){
        is_formater = true;
        walker++;
        continue;
      }
      len ++;
      n--;
      putch(*walker);
    }
    walker++;
  }
  return len;
}

#endif
