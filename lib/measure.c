#include <stdio.h>
#include <time.h>

static struct timespec before;

void measure_init_() {
  // do nothing
}

void measure_start_() {
  clock_gettime(CLOCK_MONOTONIC, &before);
}

void measure_stop_() {
  struct timespec after;
  clock_gettime(CLOCK_MONOTONIC, &after);
  unsigned long long duration =
      (after.tv_sec - before.tv_sec) * 1e9 +
      (after.tv_nsec - before.tv_nsec);
  printf("Runtime = %llu nanosecs\n", duration);
}
