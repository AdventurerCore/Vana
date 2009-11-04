/*
Copyright (C) 2008-2009 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#pragma once

#include "AbstractServer.h"
#include "ConfigFile.h"
#include "Configuration.h"
#include "LoginServerConnection.h"
#include "Types.h"
#include "WorldServerAcceptConnection.h"
#include <string>
#include <boost/utility.hpp>

using std::string;

// WorldServer main application class, implemented as singleton
class WorldServer : public AbstractServer, boost::noncopyable {
public:
	static WorldServer * Instance() {
		if (singleton == 0)
			singleton = new WorldServer;
		return singleton;
	}
	void loadData();
	void loadConfig();
	void listen();

	void setWorldId(int8_t id) { m_worldId = id; }
	void setInterPort(uint16_t port) { m_port = port; }
	void setScrollingHeader(const string &message);
	void setConfig(const Configuration &config) { m_config = config; }

	bool isConnected() const { return (m_worldId != -1); }
	int8_t getWorldId() const { return m_worldId; }
	uint16_t getInterPort() const { return m_port; }
	size_t getMaxChannels() const { return m_config.maxChannels; }
	string getScrollingHeader() { return m_config.scrollingHeader.c_str(); }
	Configuration & getConfig() { return m_config; }
	LoginServerConnection * getLoginConnection() const { return m_loginConnection; }
private:
	WorldServer() : m_worldId(-1) { }
	static WorldServer *singleton;

	int8_t m_worldId;
	uint16_t m_loginPort;
	uint16_t m_port;
	uint32_t m_loginIp;
	Configuration m_config;
	LoginServerConnection *m_loginConnection;
};
