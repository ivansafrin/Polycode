#pragma once

#define MAX_PLAYERS 4

#define PLAYER_SHOOT 32

#define SERVER_INFO 42
#define CLIENT_READY 43
#define PLAYER_JOIN 44

typedef struct {
	float posX;
	float posY;
	float angle;
	char state;
	int clientID;	
}ServerClientInfo;

#define NOT_TURNING 0
#define TURNING_LEFT 1
#define TURNING_RIGHT 2

typedef struct {
	char thrusting;
	char turning_state;
} ClientData;

typedef struct {
	ServerClientInfo players[MAX_PLAYERS];
} ServerState;

typedef struct {
	char motd[256];
	ServerState initialServerState;
} ServerInfo;

