#include <stdio.h>
#include <string.h>
int jumpChar(const char *string, int *index, char Char) {
  while (string[*index] == ' ') {
    index++;
  }
  return *index;
}
int jumpNULL(const char *string, int *index) {
  while (string[*index] == ' ' || string[*index] == '\n') {

    index++;
  }
  return *index;
}
int indexCharInString(const char *string, int length, const char target) {
  int i;
  for (i = 0; i < length; i++) {
    if (string[i] == target) {
      { return i; }
    }
  }
  return -1;
}
int sliceString(const char *string, int index, int length) { return 0; }

int indexStringInString(const char *string, int length, const char *target) {
  int index = 0;
  index = indexCharInString(string + index, length - strlen(target), target[0]);
  while (memcmp(string + index, target, strlen(target)) != 0) {
    if (index > length) {
      return -1;
    } else {
      index++;
      index =
          indexCharInString(string + index, length - strlen(target), target[0]);
    }
  }
  return index;
}

int main() {
  char json[] = "{\"int1\":1,\"str1\":\"2\",\"double1\":3.14,\"bool1\":true,"
                "\"char1\":48,\"null1\":null,\"array1\":[\"string\",1,null,"
                "true,false,3.14],\"json1\":{\"id\":0,\"status\":200}}";
  struct json1 {
    int int1;
    char *str1;
    double double1;
    _Bool bool1;
    char char1;
    void *null1;
    void **array1;
    struct json1 *next;
  };
  int strindex = 0;
  jumpNULL(json, &strindex);
  if (json[strindex] != '{') {
    printf("json parse failed");
  } else {
    strindex++;
    jumpNULL(json, &strindex);
    if (json[strindex] != '"') {
      { jumpNULL(json, &strindex); }
    }
    if (json[strindex] != '"') {
      printf("json parse failed");
    } else {
    }
  }
}