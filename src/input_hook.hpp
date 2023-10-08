#pragma once

class InputHook
{
public:
	static const int open_key = VK_F4;
	static const int back_key = VK_BACK;
	static const int up_key = VK_UP;
	static const int down_key = VK_DOWN;
	static const int left_key = VK_LEFT;
	static const int right_key = VK_RIGHT;
	static const int select_key = VK_RETURN;
	static const int esc_key = VK_ESCAPE;

	struct custom_input_type
	{
		// actual_key = normal key (open=VK_F4, back=VK_BACK...)
		// key = custom key (open=VK_..., back=VK_...)

		std::array<std::pair<int, int>, 8> keys{
			std::make_pair(InputHook::open_key, InputHook::open_key),
			std::make_pair(InputHook::back_key, InputHook::back_key),
			std::make_pair(InputHook::up_key, InputHook::up_key),
			std::make_pair(InputHook::down_key, InputHook::down_key),
			std::make_pair(InputHook::left_key, InputHook::left_key),
			std::make_pair(InputHook::right_key, InputHook::right_key),
			std::make_pair(InputHook::select_key, InputHook::select_key),
			std::make_pair(InputHook::esc_key, InputHook::esc_key),
		};


		void change_key(int actual_key, int key)
		{
			auto it = std::find_if(keys.begin(), keys.end(), [actual_key](const std::pair<int, int>& p)
			{
				return actual_key == p.first;
			});

			if (it != keys.end())
				keys[it - keys.begin()].second = key;
		}

		int get_key(int actual_key)
		{
			auto it = std::find_if(keys.begin(), keys.end(), [actual_key](const std::pair<int, int>& p)
			{
				return actual_key == p.first;
			});

			return it != keys.end() ? keys[it - keys.begin()].second : -1;
		}

		bool apply_preset(MenuInputType preset)
		{
			bool success = false;

			switch (preset)
			{
			case MenuInputType::DEFAULT:
				keys[0].second = VK_F4;
				keys[1].second = VK_BACK;
				keys[2].second = VK_UP;
				keys[3].second = VK_DOWN;
				keys[4].second = VK_LEFT;
				keys[5].second = VK_RIGHT;
				keys[6].second = VK_RETURN;
				keys[7].second = VK_ESCAPE;
				break;
			case MenuInputType::ARROW_KEYS:
				keys[2].second = VK_UP;
				keys[3].second = VK_DOWN;
				keys[4].second = VK_LEFT;
				keys[5].second = VK_RIGHT;
				success = true;
				break;
			case MenuInputType::NUMPAD_NUMS:
				keys[2].second = VK_NUMPAD8;
				keys[3].second = VK_NUMPAD2;
				keys[4].second = VK_NUMPAD4;
				keys[5].second = VK_NUMPAD6;
				success = true;
				break;
			case MenuInputType::NUMPAD_NUMS_SELECT_AND_BACK:
				keys[1].second = VK_NUMPAD0;
				keys[2].second = VK_NUMPAD8;
				keys[3].second = VK_NUMPAD2;
				keys[4].second = VK_NUMPAD4;
				keys[5].second = VK_NUMPAD6;
				keys[6].second = VK_NUMPAD5;
				success = true;
				break;
			default:
				break;
			}

			return success;
		}


		friend void to_json(nlohmann::json& j, const custom_input_type& t)
		{
			j["open_key"] = t.keys[0];
			j["back_key"] = t.keys[1];
			j["up_key"] = t.keys[2];
			j["down_key"] = t.keys[3];
			j["left_key"] = t.keys[4];
			j["right_key"] = t.keys[5];
			j["select_key"] = t.keys[6];
			j["esc_key"] = t.keys[7];
		}
		friend void from_json(const nlohmann::json& j, custom_input_type& t)
		{
			j.at("open_key").get_to(t.keys[0]);
			j.at("back_key").get_to(t.keys[1]);
			j.at("up_key").get_to(t.keys[2]);
			j.at("down_key").get_to(t.keys[3]);
			j.at("left_key").get_to(t.keys[4]);
			j.at("right_key").get_to(t.keys[5]);
			j.at("select_key").get_to(t.keys[6]);
			j.at("esc_key").get_to(t.keys[7]);
		}
	};

	static void init();
	static void cleanup();
	static bool get_key_state(int key_code);
	static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};
