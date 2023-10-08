#include <fstream>
#include "stdafx.hpp"

namespace
{
	std::ptrdiff_t get_num_files(const std::regex& r, const std::filesystem::path& dir)
	{
		const auto& dir_iter = std::filesystem::directory_iterator(dir);

		return std::count_if(
			begin(dir_iter),
			end(dir_iter),
			[&](auto& entry)
			{
				std::string entry_name = entry.path().stem().string();
				std::smatch sm;

				return std::regex_search(entry_name, sm, r);
			}
		);
	}
}


#pragma region JsonSettings
void JsonSettings::attempt_save()
{
	const nlohmann::json j = *this;

	if (deep_compare(m_options, j, true))
		save();
}

bool JsonSettings::load()
{
	m_default_options = *this;

	std::ifstream file(JsonService::m_settings_path);

	if (!std::filesystem::exists(JsonService::m_settings_path))
	{
		write_default_config();

		file.open(JsonService::m_settings_path);
	}

	try
	{
		file >> m_options;

		file.close();
	}
	catch (const std::exception& e)
	{
		file.close();

		LOG(WARNING) << "Detected corrupt settings, writing default config...";

		write_default_config(e.what());

		return load();
	}

	const bool should_save = deep_compare(m_options, m_default_options);
	try
	{
		from_json(m_options, *this);
	}
	catch (const nlohmann::detail::type_error& e)
	{
		LOG(ERROR) << e.what();

		return false;
	}

	if (should_save)
	{
		LOG(MESSAGE) << "Updating settings.";
		save();
	}

	return true;
}

bool JsonSettings::deep_compare(
	nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value)
{
	bool should_save = false;

	for (auto& e : default_settings.items())
	{
		const std::string& key = e.key();

		if (current_settings.count(key) == 0 || (compare_value && current_settings[key] != e.value()))
		{
			current_settings[key] = e.value();

			should_save = true;
		}
		else if (current_settings[key].is_object() && e.value().is_object())
		{
			if (deep_compare(current_settings[key], e.value(), compare_value))
				should_save = true;
		}
		else if (!current_settings[key].is_object() && e.value().is_object())
		{
			current_settings[key] = e.value();

			should_save = true;
		}
	}

	return should_save;
}

bool JsonSettings::save()
{
	std::ofstream file(JsonService::m_settings_path, std::ios::out | std::ios::trunc);
	nlohmann::json j = *this;

	file << j.dump(4);
	file.close();

	return true;
}

bool JsonSettings::write_default_config(const char* err)
{
	std::ofstream file(JsonService::m_settings_path, std::ios::out | std::ios::trunc);
	nlohmann::json j = *this;

	if (err != nullptr)
	{
		namespace fs = std::filesystem;
		auto& jpath = JsonService::m_json_path;
		auto& spath = JsonService::m_settings_path;

		if (fs::exists(spath))
		{
			auto file_num = get_num_files(
				std::regex(R"(settings_backup_\d+\.json)"),
				JsonService::m_json_path
			);

			std::string backup_name = std::format("settings_backup_{}.json", file_num);

			LOG(ERROR) << "Error encountered while parsing 'settings.json': " << err;
			LOG(ERROR) << "Writing default values and saving current file as " << backup_name;

			file.close();

			fs::rename(
				spath,
				jpath / fs::path(backup_name)
			);

			file.open(JsonService::m_settings_path, std::ios::out | std::ios::trunc);
		}
	}

	file << j.dump(4);
	file.close();

	return true;
}
#pragma endregion


#pragma region JsonTP
void JsonTP::attempt_save()
{
	if (m_options.size() != m_default_options.size())
	{
		save();
		m_default_options = m_options;

		// this just appends one key
		for (auto& kv: m_options[m_options.size() - 1].items())
			location_names.push_back(kv.key());
	}
}

bool JsonTP::load()
{
	std::ifstream file(JsonService::m_tp_path);

	if (!std::filesystem::exists(JsonService::m_tp_path))
	{
		write_default_config();

		file.open(JsonService::m_tp_path);
	}

	try
	{
		file >> m_options;
		m_default_options = m_options;

		file.close();

		location_names.reserve(m_options.size());

		// extract location names from the json file
		for (auto& key : m_options)
			for (auto& value : key.get<nlohmann::json::object_t>())
			{
				LOG(DEBUG) << value.first;
				location_names.push_back(value.first);
			}
	}
	catch (const std::exception&)
	{
		file.close();

		LOG(WARNING) << "Detected corrupt TP file, writing default one...";

		write_default_config();

		return load();
	}

	return true;
}

bool JsonTP::save()
{
	std::ofstream file(JsonService::m_tp_path, std::ios::out | std::ios::trunc);
	
	file << m_options.dump(4);
	file.close();

	return true;
}

bool JsonTP::write_default_config(const char* err)
{
	std::ofstream file(JsonService::m_tp_path, std::ios::out | std::ios::trunc);

	if (err != nullptr)
	{
		namespace fs = std::filesystem;
		auto& jpath = JsonService::m_json_path;
		auto& tppath = JsonService::m_tp_path;

		if (fs::exists(tppath))
		{
			auto file_num = get_num_files(
				std::regex(R"(tp_backup_\d+\.json)"),
				JsonService::m_json_path
			);

			LOG(ERROR) << "Error encountered while parsing 'tp.json': " << err;
			LOG(ERROR) << "Writing default values and saving current file as " << std::format("tp_backup_{}.json", file_num);

			file.close();

			fs::rename(
				tppath,
				jpath / std::format("tp_backup_{}.json", file_num)
			);

			file.open(JsonService::m_tp_path, std::ios::out | std::ios::trunc);
		}
	}

	file << m_options.dump(4);
	file.close();

	return true;
}

void JsonTP::add_location(std::string name, Vector3 location, Vector3 rotation)
{
	m_options.push_back({ { name, structs::location{ location, rotation } } });
}

void JsonTP::remove_location(std::string name)
{
	if (auto it = std::find(location_names.begin(), location_names.end(), name); it != location_names.end())
		m_options.erase(it - location_names.begin());
}
#pragma endregion


nlohmann::json JsonService::handle_parse_error_and_return(ifstream_wrapper file, nlohmann::json default_j)
{
	namespace fs = std::filesystem;

	try
	{
		return nlohmann::json::parse(file.stream);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		auto file_num = get_num_files(std::regex(std::format(R"({}_backup_\d+\.json)", file.stem)), m_json_path);

		LOG(ERROR) << "Error encountered while parsing " << file.filename << " : " << e.what();
		LOG(ERROR) << "Writing default values and saving current file as " << std::format("{}_backup_{}.json", file.stem, file_num);

		fs::rename(
			m_json_path / std::format("{}.json", file.stem),
			m_json_path / std::format("{}_backup_{}.json", file.stem, file_num)
		);

		std::ofstream new_file(m_json_path / std::format("{}.json", file.stem));
		new_file << default_j.dump(4);
		new_file.close();

		return default_j;
	}
}

nlohmann::ordered_json JsonService::handle_parse_error_and_return(ifstream_wrapper file, nlohmann::ordered_json default_j)
{
	namespace fs = std::filesystem;

	try
	{
		return nlohmann::ordered_json::parse(file.stream);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		auto file_num = get_num_files(std::regex(std::format(R"({}_backup_\d+\.json)", file.stem)), m_json_path);

		LOG(ERROR) << "Error encountered while parsing " << file.filename << " : " << e.what();
		LOG(ERROR) << "Writing default values and saving current file as " << std::format("{}_backup_{}.json", file.stem, file_num);

		fs::rename(
			m_json_path / std::format("{}.json", file.stem),
			m_json_path / std::format("{}_backup_{}.json", file.stem, file_num)
		);

		std::ofstream new_file(m_json_path / std::format("{}.json", file.stem));
		new_file << default_j.dump(4);
		new_file.close();

		return default_j;
	}
}


void JsonService::init()
{
	namespace fs = std::filesystem;

	if (m_init) return;

	LOG(MESSAGE) << "Initing Json Service...";

	m_settings.load();
	m_tp.load();

	m_init = true;
}

void JsonService::attempt_save()
{
	m_settings.attempt_save();
	m_tp.attempt_save();
}
