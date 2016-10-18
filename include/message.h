#ifndef _message_h_
#define _message_h_

#include <stdint.h>

#include "user.h"

typedef struct {
	uint64_t _channel_id;
	uint64_t _message_id;
	const char* _contents;
	user_info_t* _sender;
} message_t;

#endif /* _message_h_ */