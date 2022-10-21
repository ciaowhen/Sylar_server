//
// Created by user on 2022/10/20.
//

#ifndef SYLAR_SERVER_LOG_H
#define SYLAR_SERVER_LOG_H

#include <string>
//#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
//#include <stdarg.h>
#include <map>
#include <memory>

/*
 * @brief 使用流式方式将日志级别level的日志写入到logger
 */

#define SYLAR_LOG_LEVEL(logger, level) \
        if(logger->getLevel() <= level)\
            sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
            _FILE_, _LINE_, 0, sylar::GetThreadId(),\
            sylar::GetFiberId(), time(0), sylar::Thread::GetName()))).getSS()

namespace sylar{

    class Logger;
    class LoggerManager;

    /*
     * @brief 日志级别
     */

    class LogLevel
    {
    public:
        /*
         * @brief 定义日志级别枚举
         */
        enum Level
        {
            UNKNOW = 0,             //未知级别
            DEBUG = 1,              //DEBUG级别
            INFO = 2,               //INFO级别
            WARN = 3,               //WARN级别
            ERROR = 4,              //ERROR级别
            FATAL = 5,              //FATAL级别
        };

        /*
         * @brief 将日志级别转换成文本输出
         * @param[in] level 日志级别
         */
        static const char* ToString(LogLevel::Level level);

        /*
         * @brief 将文本转换成日志级别
         * @param[in] str 日志级别文本
         */
        static LogLevel::Level FromString(const std::string& str);
    };

    /*
     * @brief 日志事件
     */

    class LogEvent
    {
    public:
        typedef std::shared_ptr<LogEvent> ptr;

        /*
         * @brief 构造函数
         * @param[in]   logger          日志器
         * @param[in]   level           日志级别
         * @param[in]   file            文件名
         * @param[in]   line            文件行号
         * @param[in]   elapse          程序启动依赖的耗时（毫秒）
         * @param[in]   thread_id       线程id
         * @param[in]   fiber_id        协程id
         * @param[in]   time            日志事件（秒）
         * @param[in]   thread_name     线程名称
         */
        LogEvent();

        /*
        * @brief 返回文件名
        */
        const char* GetFile() const {return m_file;}

        /*
        * @brief 返回行号
        */
        int32_t GetLine() const {return m_line;}

        /*
        * @brief 返回耗时
        */
        uint32_t GetElapse() const {return m_elapse;}

        /*
        * @brief 返回线程id
        */
        uint32_t GetThreadId() const {return m_thread_id;}

        /*
        * @brief 返回协程id
        */
        uint32_t GetFiberId() const {return m_fiber_id;}

        /*
        * @brief 返回时间
        */
        uint64_t GetTime() const {return m_time;}

        /*
        * @brief 返回线程名
        */
        const std::string& GetThreadName() const {return m_thread_name;}

        /*
        * @brief 返回日志内容
        */
        std::string GetContent() const {return m_ss.str();}

        /*
        * @brief 返回日志器
        */
        std::shared_ptr<Logger> GetLogger() const {return m_logger;}

        /*
        * @brief 返回日志级别
        */
        LogLevel::Level GetLevel() const {return m_level;}

        /*
        * @brief 返回日志内容字符串流
        */
        std::stringstream& getSS() {return m_ss;}

        /*
        * @brief 格式化写入日志内容
        */
        void format(const char* fmt, ...);

        /*
        * @brief 格式化写入日志内容
        */
        void format(const char* fmt, va_list al);

    private:
        //文件名
        const char* m_file = nullptr;
        //行号
        int32_t m_line = 0;
        //程序启动开始到现在的毫秒数
        uint32_t m_elapse = 0;
        //线程ID
        uint32_t m_thread_id = 0;
        //协程ID
        uint64_t m_fiber_id = 0;
        //时间戳
        uint32_t m_time = 0;
        //线程名称
        std::string m_thread_name;
        //日志内容流
        std::stringstream m_ss;
        //日志器
        std::shared_ptr<Logger> m_logger;
        //日志等级
        LogLevel::Level m_level;
    };


}


#endif //SYLAR_SERVER_LOG_H
