typedef enum {
	SYS_IDLE, SYS_START_UP, SYS_STOP, SYS_STREAM, SYS_ERROR
} SystemState;

typedef struct{
	SystemState state;
}DISCOVERY_FSM;

void setSystemState(DISCOVERY_FSM* discovery, SystemState state);
