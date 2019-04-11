#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>


#define _DEBUG_
//#define _LOG_

using namespace std;

/* 日志级别 */
#define LOG_LEVEL_FATAL   (4)
#define LOG_LEVEL_ERROR   (3)
#define LOG_LEVEL_WARN    (2)
#define LOG_LEVEL_INFO    (1)
#define LOG_LEVEL_DEBUG   (0)

/* 日志记录级别 */
static const char *log_level_str[5] = {
    "DEBUG", "INFO", "WARN", "ERROR", "FATAL",
};

#define LOG_INFO(level, ...) \
    log_message(level, NULL, 0, \
        __FILE__, __LINE__, __VA_ARGS__)

/**
 * 向指定文件描述符记录日志
 *
 * @param fd        日志输出文件描述符
 * @param level     日志记录级别
 * @param data      待记录的二进制数据
 * @param data_len  data长度
 * @param file      记录日志的文件名(__FILE__)
 * @param line      记录日志的行号(__LINE__)
 * @param fmt       日志记录格式与内容
 */
static inline void
log_to_fd(int fd, int level, unsigned char *data, int data_len,
    const char *file, const int line, const char *fmt, va_list args)
{
    time_t current_time;
    struct tm t;
    char log_buff[1024];
    char *log_buff_pos = log_buff;
    int address = 0, index = 0, loc, remain, printed;

    /* 获取系统当前时间 */
    current_time = time(NULL);
    localtime_r(&current_time, &t);

    /* 格式化日志头部 */
    remain = sizeof(log_buff);
    printed = snprintf(log_buff_pos, remain,
        "[%4d/%02d/%02d %02d:%02d:%02d] [%s] [%u] [%s:%d] ",
         t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min,
         t.tm_sec, log_level_str[level], getpid(), file, line);

    log_buff_pos += printed;
    remain -= printed;

    /* 添加日志信息 */
    printed = vsnprintf(log_buff_pos, remain, fmt, args);

    log_buff_pos += printed;
    remain -= printed;

    /* 添加换行符 */
    printed = snprintf(log_buff_pos, remain, "\n");

    log_buff_pos += printed;
    remain -= printed;

    #ifdef _DEBUG_
        write(STDERR_FILENO, log_buff, log_buff_pos - log_buff);
    #endif
    
    #ifdef _LOG_
    /* 写入日志文件 */
    write(fd, log_buff, log_buff_pos - log_buff);
    #endif   
    
}
   
/**
 * 日志记录
 *
 * @param level     日志记录级别
 * @param data      待记录的二进制数据
 * @param data_len  data长度
 * @param file      记录日志的文件名(__FILE__)
 * @param line      记录日志的行号(__LINE__)
 * @param fmt       日志记录格式与内容
 */ 
static inline void log_message(int level, unsigned char *data, int data_len,
    const char *file, const int line, const char *fmt, ...)
{
    char *filename = (char*)"log.txt";
    static int log_fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0644);

    va_list ap;

    va_start(ap, fmt);
    log_to_fd(log_fd, level, data, data_len, file, line, fmt, ap);
    va_end(ap);        
}



#endif
