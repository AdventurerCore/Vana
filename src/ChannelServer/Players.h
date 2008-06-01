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
#ifndef PLAYERS_H
#define PLAYERS_H

#include <hash_map>

using namespace std;
using namespace stdext;

class Player;

struct Pos;

namespace Players {
	extern hash_map <int, Player*> players;
	void addPlayer(Player *player);
	void deletePlayer(Player *player);
	void handleMoving(Player *player, unsigned char* packet, int size);
	void damagePlayer(Player *player, unsigned char* packet);
	void faceExperiment(Player *player, unsigned char* packet);
	void chatHandler(Player *player, unsigned char* packet);
	void healPlayer(Player *player, unsigned char* packet);
	void getPlayerInfo(Player *player, unsigned char* packet);
	void commandHandler(Player *player, unsigned char* packet);
};

#endif