#ifndef H_ERRORMAN_INCLUDED
#define  H_ERRORMAN_INCLUDED

//how many messages can be stored.
#define ERROR_MANAGER_MAX_MESSAGES 32

//how big can single message be
#define ERROR_MANAGER_MAX_MESSAGE_LENGTH 256



void errorManagerDumpMessages();
void addErrorMessage(const char *);
int errorManagerInitate();
void errorManagerDispose();

#endif // !H_ERRORMAN_INCLUDED