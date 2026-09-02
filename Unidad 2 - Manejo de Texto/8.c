#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int CorroborarEmail(char*);

int main()
{
    char *mail;
    int flag=0;
    mail = calloc(50, sizeof(char));
    printf("\nDigite el mail: ");
    scanf("%s",mail);
    flag = CorroborarEmail(mail);
    while(flag==0)
    {
        printf("\nEmail erroneo. Digite otro: ");
        scanf("%s",mail);
        flag = CorroborarEmail(mail);
    }
}

int CorroborarEmail(char * email)
{
    int i=0, flag=0;
    while(i<strlen(email) && flag == 0)
    {
        if(*(email+i) == '@')
        {
            flag = 1;
        }
        else
            i++;
    }
    return flag;
}