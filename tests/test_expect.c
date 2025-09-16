#include <stdbool.h>
#include "macrotools/test.h"

DESCRIBE(test_expect, "test_expect") {
    IT("evaluates generic expressions") {
        EXPECT(0x1234 == 0x1234);
    }

    IT("evaluates boolean expressions") {
        EXPECT_TRUE(1);
        EXPECT_TRUE(100);
        EXPECT_TRUE(-1);
        EXPECT_FALSE(0);

        EXPECT_TRUE(true);
        EXPECT_FALSE(false);
    }

    IT("evaluates pointer expressions") {
        int a = 42;
        int *p = &a;
        EXPECT_POINTER_EQ(p, &a);
        EXPECT_POINTER_NE(p, NULL);
    }

    IT("evaluates signed expressions") {
        EXPECT_SIGNED_GT(5, -5);
        EXPECT_SIGNED_GE(5, -5);
        EXPECT_SIGNED_GE(5, 5);
        EXPECT_SIGNED_LT(-5, 5);
        EXPECT_SIGNED_LE(-5, 5);
        EXPECT_SIGNED_LE(-5, -5);
        EXPECT_SIGNED_CLOSE_TO(100, 102, 2);
        EXPECT_SIGNED_NOT_CLOSE_TO(100, 103, 2);
    }

    IT("evaluates unsigned expressions") {
        EXPECT_EQ(5, 5);
        EXPECT_NE(5, 6);
        EXPECT_UNSIGNED_GT(6, 5);
        EXPECT_UNSIGNED_GE(6, 5);
        EXPECT_UNSIGNED_GE(5, 5);
        EXPECT_UNSIGNED_LT(5, 6);
        EXPECT_UNSIGNED_LE(5, 6);
        EXPECT_UNSIGNED_LE(5, 5);
        EXPECT_UNSIGNED_CLOSE_TO(100, 102, 2);
        EXPECT_UNSIGNED_NOT_CLOSE_TO(100, 103, 2);
    }

    IT("evaluates floating point expressions") {
        EXPECT_FLOATING_GT(5.0, -5.0);
        EXPECT_FLOATING_GE(5.0, -5.0, 0.001);
        EXPECT_FLOATING_GE(5.0, 5.0, 0.001);
        EXPECT_FLOATING_LT(-5.0, 5.0);
        EXPECT_FLOATING_LE(-5.0, 5.0, 0.001);
        EXPECT_FLOATING_LE(-5.0, -5.0, 0.001);
        EXPECT_FLOATING_CLOSE_TO(100.0, 102.0, 2.0);
        EXPECT_FLOATING_NOT_CLOSE_TO(100.0, 103.0, 2.0);
    }

    IT("evaluates string expressions") {
        EXPECT_STRING_EQ("hello", "hello", 5);
        EXPECT_STRING_NOT_EQ("hello", "world", 5);
    }

    IT("evaluates buffer expressions") {
        const unsigned char buf1[] = { 0x01, 0x02, 0x00, 0x04, 0x05 };
        const unsigned char buf2[] = { 0x01, 0x02, 0x00, 0x04, 0x05 };
        const unsigned char buf3[] = { 0x01, 0x02, 0x00, 0x02, 0x01 };
        EXPECT_BUFFER_EQ(buf1, buf2, sizeof(buf1));
        EXPECT_BUFFER_NOT_EQ(buf1, buf3, sizeof(buf1));
    }
}
