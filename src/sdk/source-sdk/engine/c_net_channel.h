#pragma once

class i_net_message
{
public:
	int get_type()
	{
		return memory::call_v_function<int(__thiscall*)(void*)>(this, 7)(this);
	}

	int get_group()
	{
		return memory::call_v_function<int(__thiscall*)(void*)>(this, 8)(this);
	}

	const char* get_name()
	{
		return memory::call_v_function<const char* (__thiscall*)(void*)>(this, 9)(this);
	}
};

class NET_SetConVar : public i_net_message
{
public:
	NET_SetConVar(const char* name, const char* value)
	{
		using NET_SetConVar_t = NET_SetConVar* (__fastcall*)(void*, const char*, const char*);

		static NET_SetConVar_t NET_SetConVar = (NET_SetConVar_t)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("engine.dll"), xorstr("E8 ? ? ? ? 45 33 C9 48 8D 54 24 ? 45 33 C0 48 8D 0D ? ? ? ?")), 1, 6);

		if (!NET_SetConVar)
			return;

		NET_SetConVar(this, name, value);
	}
};

class c_net_channel
{
public:
	char pad[8];
	int unk;
	int out_sequence_nr;
	int in_sequence_nr;
	int out_sequence_nr_ack;
	int out_reliable_state;
	int in_reliable_state;
	int choked_packets;

public:
	const char* get_address()
	{
		return memory::call_v_function<const char* (__thiscall*)(void*)>(this, 1)(this);
	}

	float get_latency(int flow)
	{
		return memory::call_v_function<float(__thiscall*)(void*, int)>(this, 9)(this, flow);	
	}

	void shutdown(const char* msg)
	{
		Sleep(10);
 		return memory::call_v_function<void(__thiscall*)(void*, const char*)>(this, 36)(this, msg);
	}

	bool send_net_msg(i_net_message& msg, bool force_reliable = false, bool voice = false)
	{
		return memory::call_v_function<bool(__thiscall*)(void*, i_net_message&, bool, bool)>(this, 40)(this, msg, force_reliable, voice);
	}
};
