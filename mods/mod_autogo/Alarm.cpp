// Alarm.cpp: implementation of the Alarm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mod_autogo.h"
#include "Alarm.h"
#include "MemReaderProxy.h"
#include "PackSenderProxy.h"
#include "TibiaItemProxy.h"
#include "IPCBackPipeProxy.h"
#include "TibiaContainer.h"
#include "ModuleUtil.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Alarm::Alarm() {
	alarmDescriptor = "<none>";
	spell = "";
	spellDelay = 0;
	manaCost = 0;
	sound = "";
	logEvents = false;
	windowAction = -1;
	shutdown = false;
	killTibia = false;
	logout = false;
	depot = false;
	start = false;
	runaway = true;
	screenshot = 0;
	condition = 0;
	attribute = 0;
	alarmType = 0;
	stopWalking = false;

// execution markers only, no need to save record here
	onScreenAt = 0;
	spellCast = 0;
	screenshotsTaken = 0;
	currentLoc = point(0,0,0);
	movedTime = time(NULL);
	trigger;//Default constructor(UNDEFINED,"")

	//Alarm Variables
	alarmState=0;
	runCycle=1;
}



Alarm::Alarm(int type, int attr, int cond, int trigType, CString strTrig, bool run, bool sta, bool dep, CString spe, int cost, int delay, int scr, bool stopwalk, bool log, bool kill, bool shut, int winAct, CString audio, bool event, list<CString> beginModules, list<CString> endModules) {
	alarmDescriptor = "";
	startModules = beginModules;
	stopModules = endModules;
	spell = spe;
	spellDelay = delay;
	manaCost = cost;
	sound = audio;
	logEvents = event;
	windowAction = winAct;
	shutdown = shut;
	killTibia = kill;
	logout = log;
	depot = dep;
	start = sta;
	runaway = run;
	screenshot = scr;
	condition = cond;
	attribute = attr;
	alarmType = type;
	setTrigger(trigType, strTrig);

	stopWalking = stopwalk;
	
	onScreenAt = 0;
	spellCast = 0;
	screenshotsTaken = 0;
	currentLoc=point(0,0,0);
	movedTime=time(NULL);

	//Alarm Variables
	alarmState=0;
	runCycle=1;
}

Alarm::~Alarm(){
}

//////////////////////////////////////////////////////////////////////
// Setters
//////////////////////////////////////////////////////////////////////

void Alarm::setType(int type) {
	alarmType = type;
}

void Alarm::setAttribute(int attrib) {
	attribute = attrib;
}

void Alarm::setCondition(int cond) {
	condition = cond;
}

void Alarm::setTrigger(int triggerType, CString trig) {
	trigger.setType(triggerType);
	trigger.setTriggerText(trig);
}

void Alarm::setStartModules(list<CString> beginModules) {
	startModules = beginModules;
}

void Alarm::setStopModules(list<CString> endModules) {
	stopModules = endModules;
}

void Alarm::setGoToRunaway(bool onOff) {
	runaway = onOff;
}

void Alarm::setGoToStart(bool onOff) {
	start = onOff;
}

void Alarm::setGoToDepot(bool onOff) {
	depot = onOff;
}

void Alarm::setCastSpell(CString spellToCast) {
	spell = spellToCast;
}

void Alarm::setTakeScreenshot(int screenshotOption) {
	screenshot = screenshotOption;
}

void Alarm::setStopWalking(bool onOff) {
	stopWalking = onOff;
}

void Alarm::setLogout(bool onOff) {
	logout = onOff;
}

void Alarm::setKillClient(bool onOff) {
	killTibia = onOff;
}

void Alarm::setShutdownComputer(bool onOff) {
	shutdown = onOff;
}

void Alarm::setWindowAction(int windowActionOpt) {
	windowAction = windowActionOpt;
}

void Alarm::setAudioAlarm(CString waveToPlay) {
	sound = waveToPlay;
}

void Alarm::setLogEvents(bool onOff) {
	logEvents = onOff;
}

//////////////////////////////////////////////////////////////////////
// Actions/Accessors
//////////////////////////////////////////////////////////////////////

list<CString> Alarm::doStopModules() {
	return stopModules;
}

list<CString> Alarm::doStartModules() {
	return startModules;
}

bool Alarm::doLogout() {
	return logout;
}

bool Alarm::doKillClient() {
	return killTibia;
}

bool Alarm::doShutdownComputer() {
	return shutdown;
}

int Alarm::doWindowAction() {
	return windowAction;
}

CString Alarm::doAlarm() {
	return sound;
}

bool Alarm::doLogEvents() {
	return logEvents;
}

int Alarm::doTakeScreenshot() {
	return screenshot;
}

bool Alarm::doGoToRunaway() {
	return runaway;
}

bool Alarm::doGoToStart() {
	return start;
}

bool Alarm::doGoToDepot() {
	return depot;
}

CString Alarm::doCastSpell() {
	return spell;
}

bool Alarm::doStopWalking() {
	return stopWalking;
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void Alarm::initializeCharacter() {
	//Initialize the character's starting info 
	CMemReaderProxy reader;
	CTibiaCharacter *self = reader.readSelfCharacter();
	lvlInit = self->lvl;
	mlvlInit = self->mlvl;
	skillFishInit = self->skillFish;
	skillFistInit = self->skillFist;
	skillClubInit = self->skillClub;
	skillSwordInit = self->skillSword;
	skillAxeInit = self->skillAxe;
	skillDistInit = self->skillDist;
	skillShieldInit = self->skillShield;
	positionXInit = self->x;
	positionYInit = self->y;
	positionZInit = self->z;
	healthInit = self->hp;
	delete self;
}

bool Alarm::checkAlarm(char whiteList[100][32], int options, tibiaMessage* msg) {
	bool retval = false;
	CMemReaderProxy reader;
	CTibiaCharacter *self = reader.readSelfCharacter();
	if (currentLoc.x!=self->x || currentLoc.y!=self->y || currentLoc.z!=self->z){
		currentLoc=point(self->x,self->y,self->z);
		movedTime=time(NULL);
	}

	switch (alarmType) {
	case SKILL:
		switch (condition) {
		case LEVELUP:
			switch (attribute) {
			case ALL:
				retval |= (self->lvl > lvlInit);
				retval |= (self->mlvl > mlvlInit);
				retval |= (self->skillFish > skillFishInit);
				retval |= (self->skillFist > skillFistInit);
				retval |= (self->skillClub > skillClubInit);
				retval |= (self->skillSword > skillSwordInit);
				retval |= (self->skillAxe > skillAxeInit);
				retval |= (self->skillDist > skillDistInit);
				retval |= (self->skillShield > skillShieldInit);
				lvlInit=self->lvl;
				mlvlInit=self->mlvl;
				skillFishInit=self->skillFish;
				skillFistInit=self->skillFist;
				skillClubInit=self->skillClub;
				skillSwordInit=self->skillSword;
				skillAxeInit=self->skillAxe;
				skillDistInit=self->skillDist;
				skillShieldInit=self->skillShield;
				break;
			case LEVEL:
				retval = self->lvl > lvlInit;
				lvlInit=self->lvl;
				break;
			case MAGICLVL:
				retval = self->mlvl > mlvlInit;
				mlvlInit=self->mlvl;
				break;
			case FISHING:
				retval = self->skillFish > skillFishInit;
				skillFishInit=self->skillFish;
				break;
			case FIST:
				retval = self->skillFist > skillFistInit;
				skillFistInit=self->skillFist;
				break;
			case CLUB:
				retval = self->skillClub > skillClubInit;
				skillClubInit=self->skillClub;
				break;
			case SWORDSKILL:
				retval=self->skillSword > skillSwordInit;
				skillSwordInit=self->skillSword;
				break;
			case AXE:
				retval = self->skillAxe > skillAxeInit;
				skillAxeInit=self->skillAxe;
				break;
			case DISTANCE:
				retval = self->skillDist > skillDistInit;
				skillDistInit=self->skillDist;
				break;
			case SHIELD:
				retval = self->skillShield > skillShieldInit;
				skillShieldInit=self->skillShield;
				break;
			}
			break;
		case PERCLVLACHIEVED: 
			{
			int lvlExp=(50*pow(self->lvl-1,3)-150*pow(self->lvl-1,2)+400*(self->lvl-1))/3;
			switch (attribute) {
			case ALL:
				retval |= (100 - (self->exp-lvlExp)/((self->lvl-1)*(self->lvl-2)*50+100) >= trigger.getIntTrigger());
				retval |= (100 - self->mlvlPercLeft >= trigger.getIntTrigger());
				retval |= (100 - self->skillFishPercLeft >= trigger.getIntTrigger());
				retval |= (100 - self->skillFistPercLeft >= trigger.getIntTrigger());
				retval |= (100 - self->skillClubPercLeft >= trigger.getIntTrigger());
				retval |= (100 - self->skillSwordPercLeft >= trigger.getIntTrigger());
				retval |= (100 - self->skillAxePercLeft >= trigger.getIntTrigger());
				retval |= (100 - self->skillDistPercLeft >= trigger.getIntTrigger());
				retval |= (100 - self->skillShieldPercLeft >= trigger.getIntTrigger());
				break;
			case LEVEL:
				retval=100 - (self->exp-lvlExp)/((self->lvl-1)*(self->lvl-2)*50+100) >= trigger.getIntTrigger();
				break;
			case MAGICLVL:
				retval=100 - self->mlvlPercLeft >= trigger.getIntTrigger();
				break;
			case FISHING:
				retval=100 - self->skillFishPercLeft >= trigger.getIntTrigger();
				break;
			case FIST:
				retval=100 - self->skillFistPercLeft >= trigger.getIntTrigger();
				break;
			case CLUB:
				retval=100 - self->skillClubPercLeft >= trigger.getIntTrigger();
				break;
			case SWORDSKILL:
				retval=100 - self->skillSwordPercLeft >= trigger.getIntTrigger();
				break;
			case AXE:
				retval=100 - self->skillAxePercLeft >= trigger.getIntTrigger();
				break;
			case DISTANCE:
				retval=100 - self->skillDistPercLeft >= trigger.getIntTrigger();
				break;
			case SHIELD:
				retval=100 - self->skillShieldPercLeft >= trigger.getIntTrigger();
				break;
			}
			break;
			}
		case PERCLVLREMAINING:
			{
			int lvlExp=(50 * pow(self->lvl-1,3)-150 * pow(self->lvl-1,2)+400*(self->lvl-1))/3;
			switch (attribute) {
			case ALL:
				retval |= ((self->exp-lvlExp)/((self->lvl-1)*(self->lvl-2)*50+100) <= trigger.getIntTrigger());
				retval |= (self->mlvlPercLeft <= trigger.getIntTrigger());
				retval |= (self->skillFishPercLeft <= trigger.getIntTrigger());
				retval |= (self->skillFistPercLeft <= trigger.getIntTrigger());
				retval |= (self->skillClubPercLeft <= trigger.getIntTrigger());
				retval |= (self->skillSwordPercLeft <= trigger.getIntTrigger());
				retval |= (self->skillAxePercLeft <= trigger.getIntTrigger());
				retval |= (self->skillDistPercLeft <= trigger.getIntTrigger());
				retval |= (self->skillShieldPercLeft <= trigger.getIntTrigger());
				break;
			case LEVEL:
				retval=(self->exp-lvlExp)/((self->lvl-1)*(self->lvl-2)*50+100) <= trigger.getIntTrigger();
				break;
			case MAGICLVL:
				retval=self->mlvlPercLeft <= trigger.getIntTrigger();
				break;
			case FISHING:
				retval=self->skillFishPercLeft <= trigger.getIntTrigger();
				break;
			case FIST:
				retval=self->skillFistPercLeft <= trigger.getIntTrigger();
				break;
			case CLUB:
				retval=self->skillClubPercLeft <= trigger.getIntTrigger();
				break;
			case SWORDSKILL:
				retval=self->skillSwordPercLeft <= trigger.getIntTrigger();
				break;
			case AXE:
				retval=self->skillAxePercLeft <= trigger.getIntTrigger();
				break;
			case DISTANCE:
				retval=self->skillDistPercLeft <= trigger.getIntTrigger();
				break;
			case SHIELD:
				retval=self->skillShieldPercLeft <= trigger.getIntTrigger();
				break;
			}
			break;
			}
		}
		break;
	case RESOURCE:
		switch (condition) {
		case EQUAL:
			switch(attribute) {
			case HP:
				retval=self->hp == trigger.getIntTrigger();
				break;
			case MP:
				retval=self->mana == trigger.getIntTrigger();
				break;
			case XP:
				retval=self->exp == trigger.getIntTrigger();
				break;
			case SP:
				retval=self->soulPoints == trigger.getIntTrigger();
				break;
			case STAMINA:
				retval=self->stamina == trigger.getIntTrigger();
				break;
			case CAPACITY:
				retval=self->cap == trigger.getIntTrigger();
				break;
			case SPACE:
				retval=spaceAvailable() == trigger.getIntTrigger();
				break;
			} 
			break;
		case LESS:
			switch(attribute) {
			case HP:
				retval= self->hp < trigger.getIntTrigger();
				break;
			case MP:
				retval= self->mana < trigger.getIntTrigger();
				break;
			case XP:
				retval= self->exp < trigger.getIntTrigger();
				break;
			case SP:
				retval= self->soulPoints < trigger.getIntTrigger();
				break;
			case STAMINA:
				retval= self->stamina < trigger.getIntTrigger();
				break;
			case CAPACITY:
				retval= self->cap < trigger.getIntTrigger();
				break;
			case SPACE:
				retval= spaceAvailable() < trigger.getIntTrigger();
				break;
			}
			break;
		case MORE:
			switch(attribute) {
			case HP:
				retval= self->hp > trigger.getIntTrigger();
				break;
			case MP:
				retval= self->mana > trigger.getIntTrigger();
				break;
			case XP:
				retval= self->exp > trigger.getIntTrigger();
				break;
			case SP:
				retval=self->soulPoints > trigger.getIntTrigger();
				break;
			case STAMINA:
				retval= self->stamina > trigger.getIntTrigger();
				break;
			case CAPACITY:
				retval= self->cap > trigger.getIntTrigger();
				break;
			case SPACE:
				retval= spaceAvailable() > trigger.getIntTrigger();
				break;
			}
			break;
		}
		break;
	case ITEMS:
		switch (condition) {
		case EQUAL:
			switch(attribute) {
			case 0:
				retval= countAllFood() == trigger.getIntTrigger();
				break;
			default:
				retval= countAllItemsOfType(attribute) == trigger.getIntTrigger();
				break;
			}
			break;
		case LESS:
			switch(attribute) {
			case 0:
				retval= countAllFood() < trigger.getIntTrigger();
				break;
			default:
				retval= countAllItemsOfType(attribute) < trigger.getIntTrigger();
				break;
			}
			break;
		case MORE:
			switch(attribute) {
			case 0:
				retval= countAllFood() > trigger.getIntTrigger();
				break;
			default:
				retval= countAllItemsOfType(attribute) > trigger.getIntTrigger();
				break;
			}
			break;
		}
		break;
	case PROXIMITY:
		{
			int bitarray=onScreenCheck(whiteList, options);
			switch (condition) {
			case NEARBY:
				retval = (bitarray & (1<<attribute))!=0;
				break;
			case DISAPPEARS:
				retval = (bitarray & (1<<attribute))==0;
				break;
			case ISONSCREENFOR:
				{
					bool onscreen = (bitarray & (1<<attribute))!=0;
					if(onscreen && onScreenAt != 0 && time(NULL) - onScreenAt >= trigger.getIntTrigger())
						retval=true;
					else if (onscreen && onScreenAt == 0){
						onScreenAt = time(NULL);
					}
					else if (!onscreen) {
						onScreenAt = 0;
						retval=false;
					}
				}
				break;
			}
		}
		break;
	case ONLINE:
		switch (condition) {
		case LOGON:
			switch (attribute) {
			case CURRENTPLAYERONLINE:
				retval=reader.getConnectionState() == 8;
				break;
			case VIPPLAYERONLINE:
				retval=vipNameOnline(trigger.getTriggerText(), false);
				break;
			default:
				retval=vipOnline(attribute - 2);
				break;
			}
			break;
		case LOGOFF:
			switch (attribute) {
			case CURRENTPLAYERONLINE:
				retval=reader.getConnectionState() != 8;
				break;
			case VIPPLAYERONLINE:
				retval=!vipNameOnline(trigger.getTriggerText(), true);
				break;
			default:
				retval=!vipOnline(attribute - 2);
				break;
			}
			break;
		}
		break;
	case CHARACTER_STATUS:
		switch (condition){
		case PRESENT:
			retval = (reader.getSelfEventFlags() & (int)pow(2,attribute))!=0;
			break;
		case ABSENT:
			retval = (reader.getSelfEventFlags() & (int)pow(2,attribute))==0;
			break;
		}		
		break;
	case MESSAGE: {
		int isSpell = msg && (options & OPTIONS_IGNORE_SPELLS) && isSpellMessage(msg->msg);
		switch (attribute) {
		case ALLMESSAGES:
			retval = !isSpell && msg && (msg->type == 1 || msg->type == 2 || msg->type == 6 || msg->type == 4);
			if (retval) {
				if (condition == FROM) {
					if (strcmp(msg->nick, trigger.getTriggerText()))
						retval = false;
				}
				if (condition == CONTAINS) {
					if (strstr(msg->msg, trigger.getTriggerText()) == NULL)
						retval = false;
				}
			}
			break;
		case PUBLICMESSAGES:
			retval =  !isSpell && msg && (msg->type == 1 || msg->type == 2);
			if (retval) {
				if (condition == FROM) {
					if (strcmp(msg->nick, trigger.getTriggerText()))
						retval = false;
				}
				if (condition == CONTAINS) {
					if (strstr(msg->msg, trigger.getTriggerText()) == NULL)
						retval = false;
				}
			}
			break;
		case PRIVATEMESSAGES:
			retval = !isSpell && msg && (msg->type == 6 || msg->type == 4);
			if (retval) {
				if (condition == FROM) {
					if (strcmp(msg->nick, trigger.getTriggerText()))
						retval = false;
				}
				if (condition == CONTAINS) {
					if (strstr(msg->msg, trigger.getTriggerText()) == NULL)
						retval = false;
				}
			}
			break;
		}
		break;
				  }
	case EVENT:
		switch (attribute) {
		case CHARACTERMOVED:
			retval = positionXInit != self->x || positionYInit != self->y || positionZInit != self->z;
			break;
		case CHARACTERHIT:
			switch (condition) {
			case EQUAL:
				retval = healthInit - self->hp > 0 && healthInit - self->hp == trigger.getIntTrigger();
				break;
			case LESS:
				retval = healthInit - self->hp > 0 && healthInit - self->hp < trigger.getIntTrigger();
				break;
			case MORE:
				retval = healthInit - self->hp > 0 && healthInit - self->hp > trigger.getIntTrigger();
				break;
			}
			healthInit = self->hp;
			break;
		case CHARACTERNOTMOVED:
			switch (condition) {
			case EQUAL:
				retval=time(NULL)-movedTime == trigger.getIntTrigger();
				break;
			case LESS:
				retval=time(NULL)-movedTime < trigger.getIntTrigger();
				break;
			case MORE:
				retval=time(NULL)-movedTime > trigger.getIntTrigger();
				break;
			}
			break;
		case WAYPOINTREACHED:
			//Insert check code here
			int x = trigger.getMultiIntTrigger(0);
			int y = trigger.getMultiIntTrigger(1);
			int z = trigger.getMultiIntTrigger(2);
			int radius = trigger.getMultiIntTrigger(3);
			retval = abs(self->x - x) <= radius && abs(self->y - y) <= radius && self->z == z;
			break;
		}
		break;
	}
	delete self;
	return retval;
}

//////////////////////////////////////////////////////////////////////
// Triggers
//////////////////////////////////////////////////////////////////////

int Alarm::spaceAvailable() {
	CTibiaItemProxy itemProxy;	
	CMemReaderProxy reader;
	int space = 0;
	
	for (int contNr = 0; contNr < itemProxy.getValueForConst("maxContainers"); contNr++) {		
		CTibiaContainer *cont = reader.readContainer(contNr);
		if (cont->flagOnOff)
			space += cont->size - cont->itemsInside;
		delete cont;
	}	
	return space;
}

int Alarm::onScreenCheck(char whiteList[100][32], int options) {
	CMemReaderProxy reader;
	CMemConstData memConstData = reader.getMemConstData();
	CTibiaCharacter *self = reader.readSelfCharacter();
	
	int retval=0;
	for (int creatureNr = 0; creatureNr < memConstData.m_memMaxCreatures; creatureNr++) {
		CTibiaCharacter *ch = reader.readVisibleCreature(creatureNr);		
		if (ch->tibiaId == 0){
			delete ch;
			break;
		}
		if (ch->visible) {		
			if (ch->tibiaId != self->tibiaId && (!OnList(whiteList, (char*)ch->name) ^ ((options & OPTIONS_MAKE_BLACKLIST)!=0))) {
				if (ch->z == self->z || (options & OPTIONS_BATTLE_PARANOIA) || ((options & OPTIONS_BATTLE_ANXIETY) && abs(ch->z - self->z) <= 1)) {
					if (unsigned int(ch->tibiaId) < 0x40000000) {
						retval |= 1<<PLAYER;
						if (reader.getCurrentTm() - ch->lastAttackTm < 60*1000)//player has attacked in last minute
						{
							retval |= 1<<ATTACKINGPLAYER;
						}
					}					
					if (ch->name[0] == 'G' && ch->name[1] == 'M' || ch->name[0] == 'C' && ch->name[1] == 'M') { // this is GM						
						retval |= 1<<GM;
					}					
					if (ch->tibiaId >= 0x40000000) { // this is monster/npc
						retval |= 1<<MONSTER;
					}					
				}
				if (ch->z == self->z && abs(ch->x - self->x)<=7 && abs(ch->y - self->y)<=5){
					retval |= 1<<BATTLELIST;
				}
			}			
			if (ch->tibiaId != self->tibiaId && (ch->z == self->z || (options & OPTIONS_BATTLE_PARANOIA) || ((options & OPTIONS_BATTLE_ANXIETY) && abs(ch->z - self->z) <= 1))) {
				switch(ch->skulls){
				case YELLOW_SKULL: retval |= 1<<YELLOWSKULL; break;
				case GREEN_SKULL: retval |= 1<<GREENSKULL; break;
				case WHITE_SKULL: retval |= 1<<WHITESKULL; break;
				case RED_SKULL: retval |= 1<<REDSKULL; break;
				case BLACK_SKULL: retval |= 1<<BLACKSKULL; break;
				}
			}
		}
		delete ch;
	}
	delete self;
	return retval;
}

bool Alarm::vipOnline(int iconIndex) {
	CMemReaderProxy reader;
	CMemConstData memConstData = reader.getMemConstData();
	CTibiaVIPEntry *vip;

	for (int vipNr = 0; strcmp((vip = reader.readVIPEntry(vipNr))->name, ""); vipNr++) {
		if (vip->icon == iconIndex && vip->status == 1) {
			delete vip;
			return true;
		}
		delete vip;
	}
	return false;
}
bool Alarm::vipNameOnline(CString name,bool deflt) {
	CMemReaderProxy reader;
	CMemConstData memConstData = reader.getMemConstData();
	CTibiaVIPEntry *vip;

	for (int vipNr = 0; strcmp((vip = reader.readVIPEntry(vipNr))->name, ""); vipNr++) {
		if (strcmpi((vip = reader.readVIPEntry(vipNr))->name, name)==0) {
			int ret=vip->status;
			delete vip;
			return ret!=0;
		}
		delete vip;
	}
	return deflt;
}


//////////////////////////////////////////////////////////////////////
// Helper Functions
//////////////////////////////////////////////////////////////////////

int Alarm::countAllItemsOfType(int objectId) {
	CTibiaItemProxy itemProxy;	
	CMemReaderProxy reader;
	CMemConstData memConstData = reader.getMemConstData();
	int itemCount = 0;

	for (int contNr = 0; contNr < itemProxy.getValueForConst("maxContainers"); contNr++) {
		CTibiaContainer *cont = reader.readContainer(contNr);		
		if (cont->flagOnOff)
			itemCount += cont->countItemsOfType(objectId);
		delete cont;
	}
	for (int slotNr = 0; slotNr < 10; slotNr++) { // Loops through all 10 inventory slots(backwards)
		CTibiaItem *item = reader.readItem(memConstData.m_memAddressSlotArrow-slotNr*memConstData.m_memLengthItem);
		if (item->objectId==objectId)
			itemCount += item->quantity?item->quantity:1;
		delete item;
	}
	return itemCount;
}

int Alarm::countAllFood() {
	CMemReaderProxy reader;
	CTibiaItemProxy itemProxy;
	int foodCount = 0;

	CUIntArray* foods = itemProxy.getFoodIdArrayPtr();
	for (int i=0;i<itemProxy.getFoodCount();i++){
		foodCount+=countAllItemsOfType(itemProxy.getFoodIdAtIndex(i));
	}

//--Old code--
//	for (int contNr = 0; contNr < itemProxy.getValueForConst("maxContainers"); contNr++) {
//		CTibiaItem *item = CModuleUtil::lookupItem(contNr, itemProxy.getFoodIdArrayPtr());
//		if (item->objectId)
//			foodCount += countAllItemsOfType(item->objectId);
//		delete item;
//	}	
	return foodCount;
}

bool Alarm::OnList(char whiteList[100][32],char name[]) {
	int i=0;
	while (IsCharAlphaNumeric(whiteList[i][0])) {
		if (!strcmpi(whiteList[i],name))
			return true;
		i++;
	}
	return false;
}

bool Alarm::isSpellMessage(char *msg) {
	const char *spellPre[] = {"ex",	"ad", "ut", "al", NULL};
	const char *spellSuf[] = {"ana", "eta", "evo", "ito", "ori", "ura", "ani", "iva", "amo", NULL};
	char newmsg[128] = {'\0'};

	//get 5 characters from msg discarding all spaces
	int count=0;
	for (int i = 0; count < 5 && msg[i]; i++) {
		if (msg[i] != ' ') {
			newmsg[count] = msg[i];
			count++;
		}
	}
	newmsg[count] = '\0';

	if (strlen(newmsg) != 5) return false;

	//if string starts with prefix and is = prefix+suffix, return 1
	for (int pos = 0; spellPre[pos]; pos++) {
		if (strnicmp(newmsg, spellPre[pos], 2) == 0) {
			for (int pos2 = 0; spellSuf[pos2]; pos2++) {
				char tmp[10];
				tmp[0]=0;
				strcat(tmp,spellPre[pos]);
				strcat(tmp,spellSuf[pos2]);
				tmp[5]='\0';
				if (strnicmp(newmsg, tmp, 5) == 0) {
					return true;
				}
			}
		}
	}
	return false;
}

int Alarm::getAlarmType() {
	return alarmType;
}

int Alarm::getAttribute() {
	return attribute;
}

int Alarm::getCondition() {
	return condition;
}

int Alarm::getManaCost() {
	return manaCost;
}

void Alarm::setManaCost(int cost) {
	manaCost = cost;
}

CString Alarm::getDescriptor() {
	return alarmDescriptor;
}

void Alarm::setDescriptor(CString descriptor) {
	alarmDescriptor = descriptor;
}

void Alarm::setSpellDelay(int delay) {
	spellDelay = delay;
}

int Alarm::getSpellDelay() {
	return spellDelay;
}

CTrigger Alarm::getTrigger() {
	return trigger;
}
