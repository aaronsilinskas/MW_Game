#include <Arduino.h>
#include <unity.h>

#include "mw/time.h"

#define TEST_ITERATIONS 10

void assertTimeWithinTolerance(uint64_t expected, uint64_t actual)
{
    uint64_t delta = abs(actual - expected);
    TEST_ASSERT_LESS_OR_EQUAL(1, delta);
}

void test_current_time_is_captured()
{
    Time t;

    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        uint64_t expectedTimeMs = millis();

        timeEllapsed(&t);

        assertTimeWithinTolerance(expectedTimeMs, t.currentTimeMs);
    }
}

void test_ellapsed_time_starts_at_zero()
{
    Time t;

    timeEllapsed(&t);

    TEST_ASSERT_EQUAL(0, t.ellapsedMs);
}

void test_ellapsed_time_between_updates()
{
    Time t;
    uint64_t delayBetweenTestsMs = random(50) + 1;
    timeEllapsed(&t);

    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        delay(delayBetweenTestsMs);
        timeEllapsed(&t);

        assertTimeWithinTolerance(delayBetweenTestsMs, t.ellapsedMs);
    }
}

void setup()
{
    delay(4000);

    UNITY_BEGIN();

    RUN_TEST(test_current_time_is_captured);
    RUN_TEST(test_ellapsed_time_starts_at_zero);
    RUN_TEST(test_ellapsed_time_between_updates);

    UNITY_END();
}

void loop()
{
}
