#pragma once
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <atomic>
#include <thread>

struct channel_struct
{
	std::string author;
	std::string message;
	std::string timestamp;
};

namespace Vahalla {
	class api {
	public:
		std::string n, o, s, v, u;

		api(std::string name, std::string ownerid, std::string secret, std::string version, std::string url);

		void init();
		void license(std::string key);
		void login(std::string username, std::string password);
		void web_login();
		void regstr(std::string username, std::string password, std::string key, std::string email = "");
		void upgrade(std::string username, std::string key);
		void forgot(std::string username, std::string email);

		void check();
		bool checkblack();
		std::string var(std::string varid);
		std::string getvar(std::string var);
		void setvar(std::string var, std::string vardata);
		std::string webhook(std::string id, std::string params, std::string body = "", std::string contenttype = "");
		void log(std::string msg);
		void button(std::string value);
		std::vector<unsigned char> download(std::string fileid);

		void changeUsername(std::string newusername);
		std::string fetchonline();
		void fetchstats();
		void chatget(std::string channel);
		bool chatsend(std::string message, std::string channel);

		void start_heartbeat();
		void stop_heartbeat();
		bool is_authenticated() const;

		class subscriptions_class {
		public:
			std::string name;
			std::string expiry;
		};

		class userdata {
		public:
			std::string username;
			std::string ip;
			std::string hwid;
			std::string createdate;
			std::string lastlogin;
			std::vector<subscriptions_class> subscriptions;
		};

		class appdata {
		public:
			std::string numUsers;
			std::string numOnlineUsers;
			std::string numKeys;
			std::string version;
			std::string customerPanelLink;
		};

		class responsedata {
		public:
			std::vector<channel_struct> channeldata;
			bool success{};
			std::string message;
		};

		userdata user_data;
		appdata app_data;
		responsedata response;
		subscriptions_class espira;

	private:
		std::string sessionid, enckey, session_jwt_token_;

		bool secure_strings_enabled_ = false;
		uint32_t secure_strings_key_ = 0;
		std::string name_enc_;
		std::string ownerid_enc_;
		std::string version_enc_;
		std::string url_enc_;

		std::vector<std::string> allowed_hosts;

		std::atomic<bool> LoggedIn{ false };
		std::atomic<uint64_t> auth_nonce_{ 0 };
		std::atomic<long long> auth_window_{ 0 };
		std::atomic<uint64_t> auth_seal_{ 0 };

		std::thread heartbeat_thread_;
	};
}
