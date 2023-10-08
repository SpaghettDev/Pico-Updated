#pragma once

namespace sessions_data
{
	std::vector<std::string_view> session_types{
		"Join Public", "New Public", "Closed Crew",
		"Crew", "Closed Friends", "Find Friends",
		"Solo", "Invite Only", "Join Crew",
		"SCTV", "Leave Online"
	};
	std::map<std::string_view, eSessionType> str_to_session{
		{ "Join Public", eSessionType::JOIN_PUBLIC },
		{ "New Public", eSessionType::NEW_PUBLIC },
		{ "Closed Crew", eSessionType::CLOSED_CREW },
		{ "Crew", eSessionType::CREW },
		{ "Closed Friends", eSessionType::CLOSED_FRIENDS },
		{ "Find Friends", eSessionType::FIND_FRIEND },
		{ "Solo", eSessionType::SOLO },
		{ "Invite Only", eSessionType::INVITE_ONLY },
		{ "Join Crew", eSessionType::JOIN_CREW },
		{ "SCTV", eSessionType::SC_TV },
		{ "Leave Online", eSessionType::LEAVE_ONLINE }
	};
}
