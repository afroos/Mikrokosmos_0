module;

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Diagnostics.Logger;

export namespace mk
{
	class Logger
	{

	public:

		MK_EXPORT static Logger& get()
		{
			static Logger logger;
			return logger;
		}

		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		template<typename StringFormat, typename... Arguments>
		void trace(const StringFormat& format, Arguments&&... arguments);

		template<typename StringFormat, typename... Arguments>
		void info(const StringFormat& format, Arguments&&... arguments);

		template<typename StringFormat, typename... Arguments>
		void warning(const StringFormat& format, Arguments&&... arguments);

		template<typename StringFormat, typename... Arguments>
		void error(const StringFormat& format, Arguments&&... arguments);

	private:

		Logger();
		~Logger() = default;

	private:

		std::shared_ptr<spdlog::logger> _logger;

	};

	template<typename StringFormat, typename... Arguments>
	MK_EXPORT void trace(const StringFormat& format, Arguments&&... arguments)
	{
		Logger::get().trace(format, arguments...);
	}

	template<typename StringFormat, typename... Arguments>
	MK_EXPORT void info(const StringFormat& format, Arguments&&... arguments)
	{
		Logger::get().info(format, arguments...);
	}

	template<typename StringFormat, typename... Arguments>
	MK_EXPORT void warning(const StringFormat& format, Arguments&&... arguments)
	{
		Logger::get().warning(format, arguments...);
	}

	template<typename StringFormat, typename... Arguments>
	MK_EXPORT void error(const StringFormat& format, Arguments&&... arguments)
	{
		Logger::get().error(format, arguments...);
	}

	MK_EXPORT void dummy() // Just to instantiate the template for export.
	{
		Logger::get().trace("");
		mk::trace("");
	}

	template<typename StringFormat, typename... Arguments>
	void Logger::trace(const StringFormat& format, Arguments&&... arguments)   { _logger->trace(format, arguments...); }

	template<typename StringFormat, typename... Arguments>
	void Logger::info(const StringFormat& format, Arguments&&... arguments)    { _logger->info(format, arguments...); }

	template<typename StringFormat, typename... Arguments>
	void Logger::warning(const StringFormat& format, Arguments&&... arguments) { _logger->warn(format, arguments...); }

	template<typename StringFormat, typename... Arguments>
	void Logger::error(const StringFormat& format, Arguments&&... arguments)   { _logger->error(format, arguments...); }

}

module : private;

namespace mk
{

	Logger::Logger()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_logger = spdlog::stdout_color_mt("Mikrokosmos");
		_logger->set_level(spdlog::level::trace);
	}

}