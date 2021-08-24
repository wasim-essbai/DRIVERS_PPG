typedef enum {
	SYS_IDLE, SYS_START_UP, SYS_STOP, SYS_STREAM, SYS_ERROR
} State;

typedef struct{
	State state;
}DISCOVERY_FSM;
