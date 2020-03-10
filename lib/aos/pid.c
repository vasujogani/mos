#include <aos/aos.h>
#include <aos/pid.h>

domainid_t next_pid = 0;

struct pid_node* pid_list = NULL;

char *find_name(domainid_t pid) {
    struct pid_node *current = pid_list;
    while (current != NULL && current->pid != pid) {
        current = current->next;
    }
    if (current != NULL) {
        return current->name;
    }
    return NULL;
}

domainid_t add_pid(char *name, coreid_t core) {
    struct pid_node *pid = malloc(sizeof(struct pid_node));
    pid->pid = next_pid++;
    pid->core = core;
    pid->name = name;

    if (pid_list == NULL) {
        pid_list = pid;
    } else {
        pid->next = pid_list;
        pid_list = pid;
    }

    return pid_list->pid;
}
