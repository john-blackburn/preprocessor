#define WARN_IF(EXP) do { if (EXP) fprintf (stderr, "Warning: " #EXP "\n"); } while (0)

WARN_IF (x==0);  // do { if (x == 0) fprintf (stderr, "Warning: " "x == 0" "\n"); } while (0);
