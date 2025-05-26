#include <arch/log.h>


namespace mtp
{

	bool g_debug = false;

	void HexDump(std::stringstream & ss, const std::string &prefix, size_t size, InputStream & is)
	{
		ss << prefix << "[" << size << "]:\n";
		size_t i;

		std::string chars;
		chars.reserve(16);
		for(i = 0; i < size; ++i)
		{
			bool first = ((i & 0xf) == 0);
			bool last = ((i & 0xf) == 0x0f);
			if (first)
				ss << hex(i, 8) << ": ";

			u8 value = is.Read8();
			ss << hex(value, 2);
			chars.push_back(value < 0x20 || value >= 0x7f? '.': value);
			if (last)
			{
				ss << " " << chars << "\n";
				chars.clear();
			}
			else
				ss << " ";
		}
		if (chars.size())
		{
			ss << std::string((size_t)(16 - chars.size()) * 3, ' ') << chars << "\n";
		}
	}

	void HexDump(const std::string &prefix, const ByteArray &data, bool force)
	{
		if (!g_debug && !force)
			return;

		std::stringstream ss;
		InputStream is(data);
		HexDump(ss, prefix, data.size(), is);
		error(ss.str());
	}

}
