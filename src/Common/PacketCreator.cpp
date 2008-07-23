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
#include "PacketCreator.h"
#include "Pos.h"
#include "ReadPacket.h"
#include "StringUtilities.h"
#include <boost/tokenizer.hpp>

void Packet::addPos(Pos pos) {
	addShort(pos.x);
	addShort(pos.y);
}

void Packet::addBuffer(ReadPacket *packet) {
	addBuffer(packet->getBuffer(), packet->getBufferLength());
}

void Packet::addBuffer(unsigned char *bytes, size_t len) {
	memcpy_s(packet+pos, len, bytes, len);
	pos += len;
}

void Packet::addIP(const string &ip) { 
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	typedef boost::char_separator<char> separator;

	separator sep(".");
	tokenizer tokens(ip, sep);

	for (tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); iter++) {
		addByte((unsigned char) StringUtilities::toType<short>(*iter)); // Using toType<unsigned char> would cause it to spit ASCII
	}
}

void Packet::addBytes(char *hex) {
	for (size_t i = 0; i< strlen(hex)/2; i++) {
		unsigned char byte1 = hex[i*2];
		unsigned char byte2 = hex[i*2+1];
		if (byte1 >= 'A' && byte1 <= 'F')
			byte1 -= 'A' - 0xa;
		else if (byte1 >= 'a' && byte1 <= 'f')
			byte1 -= 'a' - 0xa;
		else if (byte1 >= '0' && byte1 <= '9')
			byte1 -= '0';
		if (byte2 >= 'A' && byte2 <= 'F')
			byte2 -= 'A' - 0xa;
		else if (byte2 >= 'a' && byte2 <= 'f')
			byte2 -= 'a' - 0xa;
		else if (byte2 >= '0' && byte2 <= '9')
			byte2 -= '0';
		unsigned char byte = byte1*0x10 + byte2;
		packet[pos++] = byte;	
	}
}

void Packet::addString(const string &str, size_t len) {
	size_t slen = str.size();
	if (len < slen) {
		std::cout << "ERROR: addString used with length shorter than string size." << std::endl; // TODO: Throw exception
	}
	strncpy_s((char *) packet + pos, MAX_LEN -pos, str.c_str(), slen);
	for (int i = slen; i < len; i++) {
		packet[pos+i] = 0;
	}
	pos += len;
}

void Packet::addString(const char *str, size_t slen) {
	size_t rlen = strlen(str);
	strncpy_s((char*)packet+pos, slen+1, str, slen);
	for (size_t i = rlen; i < slen; i++) {
		packet[pos+i] = 0;
	}
	pos += slen;
}

void Packet::addString(const string &str) {
	size_t len = str.size();
	addShort(len);
	strcpy_s((char *) packet + pos, MAX_LEN - pos, str.c_str());
	pos += len;
}