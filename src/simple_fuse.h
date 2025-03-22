#pragma once

#define FUSE_USE_VERSION 31
#include <errno.h>
#include <fuse3/fuse.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义文件内容
static const char *hello_content = "Hello from FUSE 3.16!\n";

// 获取文件/目录属性
static int demo_getattr(const char *path, struct stat *stbuf,
                        struct fuse_file_info *fi) {
  (void)fi;
  memset(stbuf, 0, sizeof(struct stat));

  if (strcmp(path, "/") == 0) {                 // 根目录
    stbuf->st_mode = S_IFDIR | 0755;            // 目录权限
    stbuf->st_nlink = 2;                        // 链接数（目录默认2）
  } else if (strcmp(path, "/hello.txt") == 0) { // 文件
    stbuf->st_mode = S_IFREG | 0444;            // 只读文件
    stbuf->st_nlink = 1;
    stbuf->st_size = strlen(hello_content); // 文件大小
  } else {
    return -ENOENT; // 其他路径返回“不存在”
  }
  return 0;
}

// 读取目录内容（仅根目录）
static int demo_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                        off_t offset, struct fuse_file_info *fi,
                        enum fuse_readdir_flags flags // 新增参数
) {
  (void)offset; // 明确标记未使用的参数（避免编译器警告）
  (void)fi;
  (void)flags; // 如果暂时不使用 flags，也需声明

  if (strcmp(path, "/") != 0) {
    return -ENOENT;
  }

  // 填充目录项（例如根目录下的文件）
  filler(buf, ".", NULL, 0, (enum fuse_fill_dir_flags)0);  // 当前目录
  filler(buf, "..", NULL, 0, (enum fuse_fill_dir_flags)0); // 上级目录
  filler(buf, "hello.txt", NULL, 0, (enum fuse_fill_dir_flags)0); // 文件项

  return 0;
}

// 读取文件内容
static int demo_read(const char *path, char *buf, size_t size, off_t offset,
                     struct fuse_file_info *fi) {
  if (strcmp(path, "/hello.txt") != 0)
    return -ENOENT;

  std::cout << "测试内存泄露 ..." << std::endl;
  int *p = new int[5];
  (void)p;

  size_t len = strlen(hello_content);
  if (offset >= len)
    return 0; // 偏移超出内容长度

  // 计算实际可读取的数据量
  if (offset + size > len)
    size = len - offset;
  memcpy(buf, hello_content + offset, size);
  return size;
}

// 定义 FUSE 操作函数表
static struct fuse_operations demo_ops = {
    .getattr = demo_getattr,
    .read = demo_read,
    .readdir = demo_readdir,
};