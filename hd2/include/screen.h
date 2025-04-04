char esc_seq[3] = {0x1b, '[', '\0'};
#define scr_curs(row, col) printf("%s%d;%dH", esc_seq, row, col)
#define scr_home()         scr_curs(1,1)
#define scr_eol()          printf("%s0K", esc_seq)
#define scr_eos()          printf("%s0J", esc_seq)
#define scr_clear()        printf("%s2J", esc_seq)
