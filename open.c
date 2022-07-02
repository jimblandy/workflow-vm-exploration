#include <linux/hw_breakpoint.h> /* Definition of HW_* constants */
#include <linux/perf_event.h>    /* Definition of PERF_* constants */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>         /* Definition of SYS_* constants */
#include <unistd.h>

int perf_event_open(struct perf_event_attr *attr,
                    pid_t pid, int cpu, int group_fd, unsigned long flags)
{
  return syscall(SYS_perf_event_open, attr, pid, cpu, group_fd, flags);
}

int main(int argc, char **argv) {
  struct perf_event_attr attrs;
  memset(&attrs, 0, sizeof(attrs));
  attrs.exclude_kernel = 1;
  attrs.exclude_hv = 1;
  attrs.exclude_idle = 1;
  attrs.type = PERF_TYPE_SOFTWARE;
  attrs.config = PERF_COUNT_SW_CONTEXT_SWITCHES;

  int status = perf_event_open(&attrs, 0, -1, -1, PERF_FLAG_FD_NO_GROUP);
  if (status < 0) {
    perror("perf_event_open failed");
    exit(1);
  }

  printf("success: %d", status);
  return 0;
}
