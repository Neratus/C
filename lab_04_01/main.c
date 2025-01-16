#include "my_str.h"
#include <string.h>

int main(void)
{
    int count = 0;
    int passed = 0;
    int not_passed = 0;
    {
        char *s1 = "Hello there";
        char *t1 = "e";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s1 = "0123456789";
        char *t1 = "369";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s1 = "I am char";
        char *t1 = "ino";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s1 = "Searching for a space";
        char *t1 = " ";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s1 = "Nothing here";
        char *t1 = "usa";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s1 = "";
        char *t1 = "hello";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s1 = "";
        char *t1 = "";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s1 = "Nothing here";
        char *t1 = "";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s1 = "We have to cook";
        char *t1 = "kkk";
        if (my_strpbrk(s1, t1) == strpbrk(s1, t1)) 
            passed++;
        count++;
    }
    {
        char *s2 = "Delicious";
        char *t2 = "lic";
        if (my_strspn(s2, t2) == strspn(s2, t2)) 
            passed++;
        count++;
    }
    {
        char *s2 = "lllloooo";
        char *t2 = "l";
        if (my_strspn(s2, t2) == strspn(s2, t2)) 
            passed++;
        count++;
    }
    {
        char *s2 = "i love code";
        char *t2 = "I";
        if (my_strspn(s2, t2) == strspn(s2, t2)) 
            passed++;
        count++;
    }
    {
        char *s2 = "no option";
        char *t2 = "help";
        if (my_strspn(s2, t2) == strspn(s2, t2)) 
            passed++;
        count++;
    }
    {
        char *s2 = "Nothing";
        char *t2 = "";
        if (my_strspn(s2, t2) == strspn(s2, t2)) 
            passed++;
        count++;
    }
    {
        char *s2 = "";
        char *t2 = "hi";
        if (my_strspn(s2, t2) == strspn(s2, t2)) 
            passed++;
        count++;
    }
    {
        char *s2 = "";
        char *t2 = "";
        if (my_strspn(s2, t2) == strspn(s2, t2)) 
            passed++;
        count++;
    }
    {
        char *s2 = "            O";
        char *t2 = " ";
        if (my_strspn(s2, t2) == strspn(s2, t2)) 
            passed++;
        count++;
    }
    {
        char *s3 = "We have to code";
        char *t3 = "d";
        if (my_strcspn(s3, t3) == strcspn(s3, t3)) 
            passed++;
        count++;
    }
    {
        char *s3 = "Something something ";
        char *t3 = " ";
        if (my_strcspn(s3, t3) == strcspn(s3, t3)) 
            passed++;
        count++;
    }
    {
        char *s3 = "This is fine";
        char *t3 = "a";
        if (my_strcspn(s3, t3) == strcspn(s3, t3)) 
            passed++;
        count++;
    }
    {
        char *s3 = "This is not fine";
        char *t3 = "This";
        if (my_strcspn(s3, t3) == strcspn(s3, t3)) 
            passed++;
        count++;
    }
    {
        char *s3 = "";
        char *t3 = "Hi";
        if (my_strcspn(s3, t3) == strcspn(s3, t3)) 
            passed++;
        count++;
    }
    {
        char *s3 = "How are you?";
        char *t3 = "";
        if (my_strcspn(s3, t3) == strcspn(s3, t3)) 
            passed++;
        count++;
    }
    {
        char *s3 = "";
        char *t3 = "";
        if (my_strcspn(s3, t3) == strcspn(s3, t3)) 
            passed++;
        count++;
    }
    {
        char *s4 = "123456789";
        char t4 = '4';
        if (my_strchr(s4, t4) == strchr(s4, t4)) 
            passed++;
        count++;
    }
    {
        char *s4 = "do I now image";
        char t4 = 'i';
        if (my_strchr(s4, t4) == strchr(s4, t4)) 
            passed++;
        count++;
    }
    {
        char *s4 = "Python";
        char t4 = 'C';
        if (my_strchr(s4, t4) == strchr(s4, t4)) 
            passed++;
        count++;
    }
    {
        char *s4 = "I love linux";
        char t4 = 'l';
        if (my_strchr(s4, t4) == strchr(s4, t4)) 
            passed++;
        count++;
    }
    {
        char *s4 = "Hi";
        char t4 = 0;
        if (my_strchr(s4, t4) == strchr(s4, t4)) 
            passed++;
        count++;
    }
    {
        char *s4 = "";
        char t4 = 'o';
        if (my_strchr(s4, t4) == strchr(s4, t4)) 
            passed++;
        count++;
    }
    {
        char *s4 = "Last letter in";
        char t4 = 'n';
        if (my_strchr(s4, t4) == strchr(s4, t4)) 
            passed++;
        count++;
    }
    {
        char *s5 = "I exist";
        char t5 = 'e';
        if (my_strrchr(s5, t5) == strrchr(s5, t5)) 
            passed++;
        count++;
    }
    {
        char *s5 = "Excel is in exam";
        char t5 = 'e';
        if (my_strrchr(s5, t5) == strrchr(s5, t5)) 
            passed++;
        count++;
    }
    {
        char *s5 = "I have a sandwich";
        char t5 = 'b';
        if (my_strrchr(s5, t5) == strrchr(s5, t5)) 
            passed++;
        count++;
    }
    {
        char *s5 = "Space   ";
        char t5 = ' ';
        if (my_strrchr(s5, t5) == strrchr(s5, t5)) 
            passed++;
        count++;
    }
    {
        char *s5 = "Imagine text";
        char t5 = 0;
        if (my_strrchr(s5, t5) == strrchr(s5, t5)) 
            passed++;
        count++;
    }
    {
        char *s5 = "";
        char t5 = 'o';
        if (my_strrchr(s5, t5) == strrchr(s5, t5)) 
            passed++;
        count++;
    }
    not_passed = count - passed;
    printf("Количество проваленных тестов: %d \n", not_passed);
    return not_passed;
}
