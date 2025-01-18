#ifndef _OBJECT_H_
#define _OBJECT_H_ 

typedef enum {
    STATE_INIT,
    STATE_RUNNING,
    STATE_DONE
} state_t;

typedef struct {
    char name[64];
    state_t state;
    unsigned int value;
    // unsigned int data_blob[256];
} object_t;

#endif /* _OBJECT_H_ */