/*
Copyright (C) 2008 Vana Development Team

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
#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include <ctime>
#include <cstring>

class PacketHandler;

class AbstractPlayer {
public:
	virtual void setPacketHandler (PacketHandler* ph) { packetHandler = ph; }
	virtual void realHandleRequest (unsigned char* buf, int len) = 0;
	void handleRequest (unsigned char* buf, int len);
	void sendPacket(unsigned char *buf, int len);
	void disconnect();

	char * getIP() { return ip; }
	void setIP(const char *ip) { strcpy_s(this->ip, ip); }

	virtual ~AbstractPlayer();
protected:
	PacketHandler *packetHandler;
	char ip[15];
};

class AbstractPlayerFactory {
public:
	virtual AbstractPlayer* createPlayer () = 0;
};
#endif