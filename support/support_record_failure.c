/* Global test failure counter.
   Copyright (C) 2016-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <support/check.h>
#include <support/support.h>
#include <support/test-driver.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <atomic.h>

/* This structure keeps track of test failures.  The counter is
   incremented on each failure.  The failed member is set to true if a
   failure is detected, so that even if the counter wraps around to
   zero, the failure of a test can be detected.

   The init constructor function below puts *state on a shared
   annonymous mapping, so that failure reports from subprocesses
   propagate to the parent process.  */
struct test_failures
{
  unsigned int counter;
  unsigned int failed;
};
static struct test_failures *state;

static __attribute__ ((constructor)) void
init (void)
{
  void *ptr = mmap (NULL, sizeof (*state), PROT_READ | PROT_WRITE,
                    MAP_ANONYMOUS | MAP_SHARED, -1, 0);
  if (ptr == MAP_FAILED)
    {
      printf ("error: could not map %zu bytes: %m\n", sizeof (*state));
      exit (1);
    }
  /* Zero-initialization of the struct is sufficient.  */
  state = ptr;
}

void
support_record_failure (void)
{
  if (state == NULL)
    {
      write_message
        ("error: support_record_failure called without initialization\n");
      _exit (1);
    }
  /* Relaxed MO is sufficient because we are only interested in the
     values themselves, in isolation.  */
  atomic_store_release (&state->failed, 1);
  atomic_fetch_add_release (&state->counter, 1);
}

int
support_report_failure (int status)
{
  if (state == NULL)
    {
      write_message
        ("error: support_report_failure called without initialization\n");
      return 1;
    }

  /* Relaxed MO is sufficient because acquire test result reporting
     assumes that exiting from the main thread happens before the
     error reporting via support_record_failure, which requires some
     form of external synchronization.  */
  bool failed = atomic_load_relaxed (&state->failed);
  if (failed)
    printf ("error: %u test failures\n",
            atomic_load_relaxed (&state->counter));

  if ((status == 0 || status == EXIT_UNSUPPORTED) && failed)
    /* If we have a recorded failure, it overrides a non-failure
       report from the test function.  */
    status = 1;
  return status;
}

void
support_record_failure_reset (void)
{
  /* Only used for testing the test framework, with external
     synchronization, but use release MO for consistency.  */
  atomic_store_relaxed (&state->failed, 0);
  atomic_fetch_add_release (&state->counter, 0);
}

int
support_record_failure_is_failed (void)
{
  /* Relaxed MO is sufficient because we need (blocking) external
     synchronization for reliable test error reporting anyway.  */
  return atomic_load_relaxed (&state->failed);
}
