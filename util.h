#include <sys/types.h>

#include <stdio.h>

#ifdef __OpenBSD__
#include <unistd.h>
#else
#define pledge(p1,p2) 0
#define unveil(p1,p2) 0
#endif

#undef strcasestr
char *strcasestr(const char *, const char *);
#undef strlcat
size_t strlcat(char *, const char *, size_t);
#undef strlcpy
size_t strlcpy(char *, const char *, size_t);

#ifndef SFEED_DUMBTERM
#define PAD_TRUNCATE_SYMBOL    "\xe2\x80\xa6" /* symbol: "ellipsis" */
#define UTF_INVALID_SYMBOL     "\xef\xbf\xbd" /* symbol: "replacement" */
#else
#define PAD_TRUNCATE_SYMBOL    "." /* symbol: "ellipsis" */
#define UTF_INVALID_SYMBOL     "?" /* symbol: "replacement" */
#endif

/* feed info */
struct feed {
	char         *name;     /* feed name */
	unsigned long totalnew; /* amount of new items per feed */
	unsigned long total;    /* total items */
	/* sfeed_curses */
	char         *path;     /* path to feed or NULL for stdin */
	FILE         *fp;       /* file pointer */
};

/* URI */
struct uri {
	char proto[48];     /* scheme including ":" or "://" */
	char userinfo[256]; /* username [:password] */
	char host[256];
	char port[6];       /* numeric port */
	char path[1024];
	char query[1024];
	char fragment[1024];
};

enum {
	FieldUnixTimestamp = 0, FieldTitle, FieldLink, FieldContent,
	FieldContentType, FieldId, FieldAuthor, FieldEnclosure, FieldCategory,
	FieldLast
};

/* hint for compilers and static analyzers that a function exits */
#ifndef __dead
#define __dead
#endif

__dead void err(int, const char *, ...);
__dead void errx(int, const char *, ...);

int uri_format(char *, size_t, struct uri *);
int uri_hasscheme(const char *);
int uri_makeabs(struct uri *, struct uri *, struct uri *);
int uri_parse(const char *, struct uri *);

void parseline(char *, char *[FieldLast]);
void printutf8pad(FILE *, const char *, size_t, int);
int  strtotime(const char *, time_t *);
void xmlencode(const char *, FILE *);
