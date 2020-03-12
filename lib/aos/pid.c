#include <aos/aos.h>
#include <aos/pid.h>

domainid_t next_pid = 0;

struct pid_node* allocated_list = NULL;
struct pid_node* free_list = NULL;

void init_pid(void) {
    struct pid_node *current = malloc(sizeof(struct pid_node));
    free_list = current;
    current->pid = 0;

    // For 65K pids, iterate from 1 to 1 << 16
    for (int i = 1; i < 1200; i++ ) {
        struct pid_node *next = malloc(sizeof(struct pid_node));
        next->pid = i;
        current->next = next;
        current = next; 
    }
}

char *find_name(domainid_t pid) {
    struct pid_node *current = allocated_list;
    while (current != NULL && current->pid != pid) {
        current = current->next;
    }
    if (current != NULL) {
        return current->name;
    }
    return NULL;
}

domainid_t add_pid(char *name, coreid_t core) {
    struct pid_node* free = free_list;
    if (free == NULL) {
        // need to return some error - reached limit for number of processes
    }
    free_list = free_list->next;

    free->core = core;
    free->name = name;
    
    free->next = allocated_list; 
    allocated_list = free;

    return allocated_list->pid;
}

void remove_pid(domainid_t pid) {
    struct pid_node *current = allocated_list;
    struct pid_node *prev = current;

    if (current->pid == pid) {
        allocated_list = current->next;
        current->next = free_list;
        free_list = current;
        return;
    }
    
    current = current->next;
    while (current != NULL) {
        if ( current->pid == pid ) {
            prev->next = current->next;
            current->next = free_list;
            free_list = current;
            return;
        }
    }

    debug_printf("remove_pid: pid not found: %d\n", pid);
}

void debug_pid_lists(void) {
    debug_printf("\ndebug_pid_lists:\n");

    struct pid_node *current = allocated_list;
    size_t size = 0; 

    debug_printf("Allocated list: \n");
    while (current != NULL) {
        debug_printf("pid: %d\n", current->pid);
        debug_printf("name: %s\n", current->name);
        debug_printf("core: %d\n", current->core);
        size++;
        current = current->next;
    }

    debug_printf("Allocated size: %d\n", size);
    current = free_list;
    size = 0; 
    
    debug_printf("Free list: \n");
    while (current != NULL) {
        // debug_printf("pid: %d\n", current->pid);
        // debug_printf("name: %s\n", current->name);
        // debug_printf("core: %d\n", current->core);
        size++;
        current = current->next;
    }
    debug_printf("Free size: %d\n", size);
    debug_printf("Free head pid: %d\n", free_list->pid);
    debug_printf("Free next pid: %d\n", free_list->next->pid);
}

void test_pid(void) {
    debug_printf("\n\ntest_pid:\n");
    debug_pid_lists();
    char *name = find_name(0);
    if (name != NULL) {
        debug_printf("pid: %d name: %s\n", 0, name);
    }
    else {
        debug_printf("process pid %d doesn't exist\n", 1);
    }

    name = find_name(1);
    if (name != NULL) {
        debug_printf("pid: %d name: %s\n", 1, name);
    }
    else {
        debug_printf("process pid %d doesn't exist\n", 1);
    }

    name = find_name(2);
    if (name != NULL) {
        debug_printf("pid: %d name: %s\n", 1, name);
    }
    else {
        debug_printf("process pid %d doesn't exist\n", 1);
    }

    remove_pid(0);
    remove_pid(2);
    debug_pid_lists();
    add_pid("init", 0);
    debug_pid_lists();
}
