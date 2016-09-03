#include "gtest/gtest.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern "C" int directions(char *directions_pointer, int count);
extern "C" int regwrapper(char *directions_pointer, int count);
extern "C" int (*target_function)(char *, int);
extern "C" int bad_register;

TEST(directions, output0) {
    target_function = directions;

    // redirect stdout to a file
    int fd = creat("/tmp/stdout.txt", 0644);
    ASSERT_TRUE(fd >= 0);
    int oldout = dup(1);
    ASSERT_TRUE(oldout >= 0);
    int ok = dup2(fd, 1);
    ASSERT_TRUE(ok >= 0);
    ok = close(fd);
    ASSERT_TRUE(ok >= 0);

    char list[] = {0};
    int n = regwrapper(list, 0);
    dup2(oldout, 1);
    close(oldout);
    EXPECT_EQ(0, bad_register);
    EXPECT_EQ(0, n);

    // read the output file
    FILE *fp = fopen("/tmp/stdout.txt", "r");
    ASSERT_FALSE(fp == NULL);
    const int maxSize = 256;
    char buffer[maxSize+1];
    size_t size = fread(buffer, 1, maxSize, fp);
    ok = fclose(fp);
    ASSERT_EQ(0, ok);

    // check the output
    EXPECT_EQ(0, size);
    buffer[size] = 0;
    EXPECT_STREQ("", buffer);
}

TEST(directions, output1) {
    target_function = directions;

    // redirect stdout to a file
    int fd = creat("/tmp/stdout.txt", 0644);
    ASSERT_TRUE(fd >= 0);
    int oldout = dup(1);
    ASSERT_TRUE(oldout >= 0);
    int ok = dup2(fd, 1);
    ASSERT_TRUE(ok >= 0);
    ok = close(fd);
    ASSERT_TRUE(ok >= 0);

    char list[] = {4};
    int n = regwrapper(list, 1);
    dup2(oldout, 1);
    close(oldout);
    EXPECT_EQ(0, bad_register);
    EXPECT_EQ(0, n);

    // read the output file
    FILE *fp = fopen("/tmp/stdout.txt", "r");
    ASSERT_FALSE(fp == NULL);
    const int maxSize = 256;
    char buffer[maxSize+1];
    size_t size = fread(buffer, 1, maxSize, fp);
    ok = fclose(fp);
    ASSERT_EQ(0, ok);

    // check the output
    EXPECT_EQ(16, size);
    buffer[size] = 0;
    EXPECT_STREQ("go to the start\n", buffer);
}

TEST(directions, output4) {
    target_function = directions;

    // redirect stdout to a file
    int fd = creat("/tmp/stdout.txt", 0644);
    ASSERT_TRUE(fd >= 0);
    int oldout = dup(1);
    ASSERT_TRUE(oldout >= 0);
    int ok = dup2(fd, 1);
    ASSERT_TRUE(ok >= 0);
    ok = close(fd);
    ASSERT_TRUE(ok >= 0);

    char list[] = {5,4,0,6};
    int n = regwrapper(list, 4);
    dup2(oldout, 1);
    close(oldout);
    EXPECT_EQ(0, bad_register);
    EXPECT_EQ(0, n);

    // read the output file
    FILE *fp = fopen("/tmp/stdout.txt", "r");
    ASSERT_FALSE(fp == NULL);
    const int maxSize = 256;
    char buffer[maxSize+1];
    size_t size = fread(buffer, 1, maxSize, fp);
    ok = fclose(fp);
    ASSERT_EQ(0, ok);

    // check the output
    EXPECT_EQ(56, size);
    buffer[size] = 0;
    EXPECT_STREQ("you are finished!\ngo to the start\nup\ninvalid directions\n", buffer);
}

TEST(directions, output6) {
    target_function = directions;

    // redirect stdout to a file
    int fd = creat("/tmp/stdout.txt", 0644);
    ASSERT_TRUE(fd >= 0);
    int oldout = dup(1);
    ASSERT_TRUE(oldout >= 0);
    int ok = dup2(fd, 1);
    ASSERT_TRUE(ok >= 0);
    ok = close(fd);
    ASSERT_TRUE(ok >= 0);

    char list[] = {4, 1, 1, 2, 3, 5};
    int n = regwrapper(list, 6);
    dup2(oldout, 1);
    close(oldout);
    EXPECT_EQ(0, bad_register);
    EXPECT_EQ(0, n);

    // read the output file
    FILE *fp = fopen("/tmp/stdout.txt", "r");
    ASSERT_FALSE(fp == NULL);
    const int maxSize = 256;
    char buffer[maxSize+1];
    size_t size = fread(buffer, 1, maxSize, fp);
    ok = fclose(fp);
    ASSERT_EQ(0, ok);

    // check the output
    EXPECT_EQ(55, size);
    buffer[size] = 0;
    EXPECT_STREQ("go to the start\ndown\ndown\nleft\nright\nyou are finished!\n", buffer);
}
