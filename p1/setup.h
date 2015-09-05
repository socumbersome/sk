#ifndef __SETUP_H_
#define __SETUP_H_

#define MYMAXTTL 30
#define PACKETS 3 // must be >= 3 ! Because we make use of
// inequality x > binary_len(x) for x >= 3. On the other hand, PACKETS cannot be
// too big due to limited icmp_seq length (no idea how big though).
#define SEQ_SHIFT PACKETS // "explains (sheds light on...)" above caveats
#define WAITING_TIME 1000 // in msec

#endif
