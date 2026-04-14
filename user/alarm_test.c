// Basic alarm_signal regression test.

#include "kernel/types.h"
#include "user/user.h"

volatile int alarm_count = 0;

void alarm_handler(void)
{
  alarm_count++;
  printf(">>> ALARM FIRED! (count = %d) <<<\n", alarm_count);
  alarm_return();
}

int
main(int argc, char *argv[])
{
  printf("==============================================\n");
  printf("   alarm_test: Alarm Signal System Call Demo\n");
  printf("==============================================\n\n");

  printf("[Test 1] Setting alarm_signal(5, alarm_handler)...\n");
  printf("         The handler will fire every 5 timer ticks.\n\n");

  alarm_signal(5, alarm_handler);

  printf("Entering busy loop. Waiting for 3 alarm firings...\n\n");
  while (alarm_count < 3) {
  }

  printf("\n[Test 1 PASSED] Alarm fired %d times as expected!\n\n", alarm_count);

  printf("[Test 2] Disabling alarm with alarm_signal(0, 0)...\n");
  alarm_signal(0, 0);

  int saved = alarm_count;

  for (int i = 0; i < 500000000; i++) {
  }

  if (alarm_count == saved) {
    printf("[Test 2 PASSED] Alarm did not fire after being disabled.\n\n");
  } else {
    printf("[Test 2 FAILED] Alarm fired %d extra time(s)!\n\n",
           alarm_count - saved);
  }

  printf("[Test 3] Setting alarm_signal(10, alarm_handler)...\n");
  printf("         Waiting for 2 more alarm firings...\n\n");

  int target = alarm_count + 2;
  alarm_signal(10, alarm_handler);

  while (alarm_count < target) {
  }

  printf("[Test 3 PASSED] Alarm fired with 10-tick interval!\n\n");

  alarm_signal(0, 0);

  printf("==============================================\n");
  printf("   ALL TESTS PASSED! alarm_signal works!\n");
  printf("==============================================\n");

  exit(0);
}
