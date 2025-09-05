int __fastcall hooks::handles::send_datagram(c_net_channel* net_channel, void* datagram) {
	if (GetAsyncKeyState(VK_F4) & 0x8000 && interfaces::engine->is_in_game()) {
		utilities::disconnect(globals::disconnect_msg.c_str());
		return 0;
	}

	return originals::send_datagram(net_channel, datagram);
}