// Prepare new version

#ifndef UTIL_H_
#define UTIL_H_

#define htons(x) ( ((x) << 8) | (((x) >> 8)&0xFF) )
#define ntohs(x) htons(x)

#define htonl(x) ( ((x) << 24 & 0xFF000000UL) | \
                   ((x) << 8 & 0x00FF0000UL) | \
                   ((x) >> 8 & 0x0000FF00UL) | \
                   ((x) >> 24 & 0x000000FFUL) )
#define ntohl(x) htonl(x)

#endif /* UTIL_H_ */
