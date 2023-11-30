#pragma once
#include "../CommonUtilities/source/cli/CliFramework.h"

namespace clio
{
	using namespace pmon::util::cli;
	struct Options : public OptionsBase<Options>
	{
		Flag debug{ this, "--debug,-d", "Stall service by running in a loop after startup waiting for debugger to connect" };
		Option<std::string> logDir{ this, "--log-dir", "", "Enable logging to specified directory" };
		static constexpr const char* description = "Intel PresentMon service for frame and system performance measurement";
		static constexpr const char* name = "PresentMonService.exe";
	};
}