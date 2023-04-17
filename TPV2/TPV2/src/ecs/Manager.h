#pragma once
#include "../utils/checkML.h"
#include "../utils//Singleton.h"
#include "Entity.h"
#include "System.h"
#include <vector>

#include  "../systems/GameControlSystem.h"




using namespace std;
class Manager:public Singleton <Manager> {

protected:
	/*Entity* fighter;
	Vector2D F_position = { WIN_WIDTH/2,WIN_HEIGHT/2};
	Vector2D F_velocity = { 0,0 };
	float F_Width = 40;
	float F_Heigth = 40;
	Texture* t_fighter;
	Transform* trans_player;
	Health* health;
	std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;*/

	//	vector<System*> systems_;
	GameCtrlSystem* gamecontrolsystem = nullptr;

private:
	array<Entity*, maxHandlerId> hdlrs_;
	array<std::vector<Entity*>, maxGroupId> entsByGroup_;
	array<System*, maxSystemId> sys_;
	
public:

	Manager();
	virtual ~Manager();

	
	inline Entity* addEntity(grpId_type gId) {
		Entity* e = new Entity(gId);
		setAlive(e,true);
		e->setContext(this);
		entsByGroup_[gId].push_back(e);
		return e;
	}
	
	
	inline const auto& getEntitiesByGroup(grpId_type gId) {
		return entsByGroup_[gId];
	}


	virtual void refresh();
	virtual void update();

	virtual void handleEvents() {};
	virtual string getStateID() { return "nothing"; }

	inline void setHandler(hdlrId_type hId, Entity* e) {
		hdlrs_[hId] = e;
	}
	inline Entity* getHandler(hdlrId_type hId) {
		return hdlrs_[hId];
	}

	

	template<typename T, typename ...Ts>
	inline T* addComponent(Entity* e, Ts&&...args) {
		T* c = new T(forward<Ts>(args)...);
		constexpr cmpId_type cId = T::id;
		//removeComponent<T>(e);
		e->currCmps_.push_back(c);
		e->cmps_[cId] = c;
		c->setContext(e,this);
		e->cmps_[cId]->initComponent();
		//e->initComponent();
		return c;
	}

	
	template<typename T>
	inline void removeComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		if (e->cmps_[cId] != nullptr) {
			auto iter = std::find(e->currCmps_.begin(),
				e->currCmps_.end(),
				e->cmps_[cId]);
			e->currCmps_.erase(iter);
			delete e->cmps_[cId];
			e->cmps_[cId] = nullptr;
		}
	}
	template<typename T>
	inline bool hasComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return e->cmps_[cId] != nullptr;
	}
	template<typename T>
	inline T* getComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(e->cmps_[cId]);
	}
	inline void setAlive(Entity* e, bool alive) {
		e->alive_ = alive;
	}
	inline bool isAlive(Entity* e);
	inline grpId_type groupId(Entity* e) {
		return e->gId_;
	}

	inline void send(const Message& m) {
  		for (System* s : sys_) {
			if (s != nullptr)
				s->receive(m);
		}
	}

	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward<Ts>(args)...);
		s->setContext(this);
		s->initSystem();
		sys_[sId] = s;
		
		return static_cast<T*>(s);
		
	
	}
	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(sys_[sId]);
	}
	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (sys_[sId] != nullptr) {
			delete sys_[sId];
			sys_[sId] = nullptr;
		}
	}
	

};


		
		

