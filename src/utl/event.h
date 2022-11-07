#ifndef __RNV_EVENT_H__
#define __RNV_EVENT_H__

#include <SDL2/SDL.h>

#include "oab.h"


typedef enum
{
    RNV_EV_QUEUE_DELETE,
    RNV_EV_QUEUE_HOLD,
} RNV_EventFlag;

typedef enum
{
    RNV_FIRSTEVENT = 0,
    /* map events */
    RNV_EV_MAP = 0x64,
    RNV_EV_MAP_MOVE,
    RNV_LASTEVENT = 0xFFFF
} RNV_EventType;

typedef struct RNV_MapEvent
{
    uint16_t type;
    u_int32_t mx;
    u_int32_t my;
} RNV_MapEvent;

typedef struct RNV_Event
{
    uint16_t type;
    RNV_MapEvent map;
} RNV_Event;

typedef struct RNV_EventQueue
{
    u_int32_t ev_c;
    u_int32_t ev_qc;
    RNV_Event events[];
} RNV_EventQueue;


/* handles events and start over event handlers */
void RNV_HandleEvents(void);

RNV_EventQueue * RNV_EventQueueCreate(void);

u_int32_t RNV_EventPoll(RNV_Event *event, u_int8_t flag);

u_int32_t RNV_EventPollType(RNV_Event *event, uint16_t type, u_int8_t flag);

void RNV_EventPush(RNV_Event event);

void RNV_EventRemoveFromQueue(u_int32_t e_k);

void RNV_EventRemoveTypeFromQueue(uint16_t type);

void RNV_EventQueueDelete(void);

void RNV_EventQueueReset(void);

#endif /* !__RNV_EVENT_H__ */
