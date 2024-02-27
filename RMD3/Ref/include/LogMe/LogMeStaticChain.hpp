#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

namespace LogMe
{
    enum logging_level {
        Critical = 10,
        Error    = 20,
        Warn     = 30,
        Info     = 40,
        Debug    = 50
    };


    template <class Container>
    void format_container(std::ostream& os, const Container& c, char delim1, char delim2) {
        auto b = std::begin(c);
        auto e = std::end(c);
        if (b == e) {
            os << delim1 << delim2;
            return;
        }
        os << delim1 << *b;
        for (++b; b != e; ++b)
            os << ',' << *b;
        os << delim2;
    }

    template <class Next = void> // Liste chainée statique
    struct FormatterBase {
        // Par default on passe au suivante
        template <class ArgType>
        static void format(std::ostream& os, const ArgType& data) { Next::format(os, data); }
    };

    template <> // Queue de file (quand next = null) -> dernier fallback
    struct FormatterBase<void> {
        template <class ArgType>
        static void format(std::ostream& os, const ArgType& data) { os << data; }
    };


    // Default formatter
    struct DefaultFormatter : FormatterBase<void> {
        using FormatterBase<void>::format; // Obligé (raison obscure du C++ sur les règles de lookup)

        template <class T>
        static void format(std::ostream& os, const std::vector<T>& data) { format_container(os, data, '[', ']'); }

        template <class T>
        static void format(std::ostream& os, const std::list<T>& data) { format_container(os, data, '[', ']'); }
    };

    template <class FormatterPolicy = DefaultFormatter>
    class Logger
    {
        std::ofstream m_os;
        logging_level m_level = Info;

        public:
            Logger() = default;
            Logger(const std::string& path) : m_os{path} {}

            void set_debug_level(logging_level level) { m_level = level; }

            template <typename ArgType>
            void log(logging_level level, const ArgType& msg) {
                if (level <= m_level) {
                    FormatterPolicy::format(std::cerr, msg);
                    if (m_os.is_open())
                        FormatterPolicy::format(m_os, msg);
                } 
            }

            template <typename ArgType> void debug(const ArgType& msg) { log(Debug, msg); }
            template <typename ArgType> void info(const ArgType& msg) { log(Info, msg); }
            template <typename ArgType> void warn(const ArgType& msg) { log(Warn, msg); }
            template <typename ArgType> void critical(const ArgType& msg) { log(Critical, msg); }
            template <typename ArgType> void error(const ArgType& msg) { log(Error, msg); }
    };


    // Part 2 (Default logger)
    namespace internal {
        inline Logger<> m_default_logger;
    }


    void set_debug_level(logging_level level); 
    template <typename ArgType> void debug(const ArgType& msg) { internal::m_default_logger.debug(msg); }
    template <typename ArgType> void info(const ArgType& msg) { internal::m_default_logger.info(msg); }
    template <typename ArgType> void warn(const ArgType& msg) { internal::m_default_logger. warn(msg); }
    template <typename ArgType> void critical(const ArgType& msg) { internal::m_default_logger.critical(msg); }
    template <typename ArgType> void error(const ArgType& msg) { internal::m_default_logger.error(msg); }



    // Part 3 (Stream Logger -> Pattern Adapter)
    template <class FormatterPolicy = DefaultFormatter>
    class StreamLogger
    {
        Logger<FormatterPolicy>         m_logger;
        logging_level                   m_flag = Info;

        public:
            StreamLogger() = default;
            StreamLogger(const std::string& path) : m_logger{path} {}

            friend
            StreamLogger& operator<< (StreamLogger& s, logging_level level) {
                s.m_flag = level;
                return s;
            }

            
            template <class ArgType>
            friend
            StreamLogger& operator<< (StreamLogger& s, const ArgType& msg) { s.m_logger.log(s.m_flag, msg); return s; }
    };
}