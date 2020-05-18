#define COMMAND(NAME)  { #NAME, NAME ## _command }

struct command commands[] =
{
  COMMAND (quit),   // { "quit", quit_command },
  COMMAND (help),   //   { "help", help_command },
};
