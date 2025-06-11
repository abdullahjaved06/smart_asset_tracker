#ifndef _FLASH_H
#define _FLASH_H

#define LOG_LEN 128

#include <stdarg.h>

void initFS(void);
int initFsLog(bool eraseLog);
int __printf_like(1, 2) writeFsLog(char *fmt, ...);
void printFsLog();
void resetFsLog();
ssize_t getFsLogChunk(size_t offset, char *out_buffer, size_t max_size);
size_t getFsLogSize(void);
int unlinkFlashFile(const char *filename);
int openFlashFile(const char *fname);
int closeFlashFile(int file_handle);
ssize_t readBlockFS(int file_handle, void *buf, size_t size);
ssize_t writeBlockFS(int file_handle, void *buf, size_t size);
int bootCount();
void suspendFlash();
void resumeFlash();

bool cloudDataFileExists(void);
int cloudDataFileWrite(const void *src, uint32_t len, uint32_t offset);
int cloudDataFileRead(void *dst, uint32_t len, uint32_t offset);
void cloudDataFileDelete(void);

#endif