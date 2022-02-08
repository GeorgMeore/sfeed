#include <sys/ioctl.h>

#undef  OK
#define OK  (0)

char *clr_eol = "\x1b[K";
char *clear_screen = "\x1b[H\x1b[2J";
char *cursor_address = "\x1b[%ld;%ldH";
char *cursor_normal = "\x1b[?25h"; /* DECTCEM (in)Visible cursor */
char *cursor_invisible = "\x1b[?25l"; /* DECTCEM (in)Visible cursor */
char *eat_newline_glitch = (void *)1;
char *enter_ca_mode = "\x1b[?1049h"; /* smcup */
char *exit_ca_mode = "\x1b[?1049l"; /* rmcup */
char *save_cursor = "\x1b""7";
char *restore_cursor = "\x1b""8";
char *exit_attribute_mode = "\x1b[0m";
char *enter_bold_mode = "\x1b[1m";
char *enter_dim_mode = "\x1b[2m";
char *enter_reverse_mode = "\x1b[7m";

int
setupterm(char *term, int fildes, int *errret)
{
	return OK;
}

char *
tparm(char *s, long p1, long p2, ...)
{
	static char buf[32];

	if (s == cursor_address) {
		snprintf(buf, sizeof(buf), s, p1 + 1, p2 + 1);
		return buf;
	}

	return (char *)s;
}
