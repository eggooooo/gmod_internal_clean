#pragma once

class c_engine_client
{
public:
	bool is_in_game()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 26)(this);
	}

	c_net_channel* get_net_channel()
	{
		return memory::call_v_function<c_net_channel * (__thiscall*)(void*)>(this, 72)(this);
	}
};