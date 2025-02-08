#ifndef COLOR_H
# define COLOR_H
# include <stdio.h>

# define RESET_ALL "\033[0m"
# define RESET_BOLD "\033[21m"
# define RESET_DIM "\033[22m"
# define RESET_UNDERLINED "\033[24m"
# define RESET_BLINK "\033[25m"
# define RESET_REVERSED "\033[27m"
# define RESET_HIDDEN "\033[28m"

# define BOLD "\033[1m"
# define DIM "\033[2m"
# define UNDERLINED "\033[4m"
# define BLINK "\033[5m"
# define REVERSED "\033[7m"
# define HIDDEN "\033[8m"

# define FG_DEFAULT "\033[39m"
# define FG_BLACK "\033[30m"
# define FG_RED "\033[31m"
# define FG_GREEN "\033[32m"
# define FG_YELLOW "\033[33m"
# define FG_BLUE "\033[34m"
# define FG_MAGENTA "\033[35m"
# define FG_CYAN "\033[36m"
# define FG_LGRAY "\033[37m"
# define FG_DGRAY "\033[90m"
# define FG_LRED "\033[91m"
# define FG_LGREEN "\033[92m"
# define FG_LYELLOW "\033[93m"
# define FG_LBLUE "\033[94m"
# define FG_LMAGENTA "\033[95m"
# define FG_LCYAN "\033[96m"
# define FG_WHITE "\033[97m"

# define BG_DEFAULT "\033[49m"
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_LGRAY "\033[47m"
# define BG_DGRAY "\033[100m"
# define BG_LRED "\033[101m"
# define BG_LGREEN "\033[102m"
# define BG_LYELLOW "\033[103m"
# define BG_LBLUE "\033[104m"
# define BG_LMAGENTA "\033[105m"
# define BG_LCYAN "\033[106m"
# define BG_WHITE "\033[107m"

// Variable indicating initialization state
extern bool is_initializing;

// Function to set the color
void set_color(int color_code)
{
    // Store old state and change is_initializing flag
    bool old_is_initializing = is_initializing;
    is_initializing = true;
    
    // Print the color code using ANSI escape sequences
    printf("\033[%dm", color_code);
    
    // Restore the old state of the initialization flag
    is_initializing = old_is_initializing;
}

// Helper function to reset color
void reset_color()
{
    printf(RESET_ALL);
}
void set_color(const char* color_code)
{
    printf("%s", color_code);
}

#endif
