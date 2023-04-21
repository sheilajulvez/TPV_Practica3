#pragma once
#ifndef ECS_H_
#define ECS_H_

const int WIN_WIDTH = 800;// anchura de ventana
const int WIN_HEIGHT = 600;// altura de ventana
using cmpId_type = int;
using grpId_type = int;
using sysId_type = int;
using msgId_type = int;
using hdlrId_type = int;
using NETmsgId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM_H_ = 0,
	_DEACELERATION_H_ = 1,
	_IMAGE_H = 2,
	_FRAMEDIMAGE_H = 7,
	_HEALTH_H = 3,
	_FIGHTERCTRL_H = 4,
	_GUN_H = 5,
	_OPPOSITE_H = 6,
	_GENERATIONS_H=8,
	_FOLLOW_H=9,
	_DISABLE_ON_EXIT_H=10,
	
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

enum grpId : grpId_type {
	_grp_GENERAL = 0,
	_grp_ASTEROIDS_GOLD=1,
	_grp_ASTEROIDS_BLACK=2,
	_grp_BULLET=3,
	
	_LAST_GRP_ID
};
constexpr grpId_type maxGroupId = _LAST_GRP_ID;


enum sysId : sysId_type {
	_sys_GAMECTRL=0,
	_sys_ASTEROIDS = 1,
	_sys_BULLET=2,
	_sys_FIGHTER=3,
	_sys_COLLISIONS=4,
	_sys_RENDER=5,
	_sys_NET=6,
	// do not remove this
	_LAST_SYS_ID
};
constexpr sysId_type maxSystemId = _LAST_SYS_ID;

enum msgId : msgId_type {
	M_PAUSE=0,
	M_END=1,
	M_START=2,
	M_ROUND_OVER_ = 3,
	M_ROUND_START=4,


	M_COLLISION_FIGHTER_ASTEROID=5,
	M_COLLISION_BULLET_ASTEROID = 6,
	M_ASTEROIDS_EXTINCTION=7,
	M_BULLET_SPAWN=8,
	
	// do not remove this
	_LAST_MSG_ID
};
constexpr msgId_type maxMessageId = _LAST_MSG_ID;

enum hdlrsId : hdlrId_type {
	_HDLR_FIGHTER,
	_HDLR_NETFIGHTER_2,
	// do not remove this
	_LAST_HDLR_ID
};
constexpr hdlrId_type maxHandlerId = _LAST_HDLR_ID;

enum NETmsgId : NETmsgId_type {
	_FighterPositionMessage_ = 1,
	_I_WANT_TO_PLAY = 2,
	_BulletPositionMessage_ = 3,

	_LAST_NETMSG_ID
};
constexpr  NETmsgId_type maxNETmsgId = _LAST_NETMSG_ID;

#endif // !ECS_H_