#include <Geode/modify/PlayLayer.hpp>
#include <ctime>

using namespace geode::prelude;

constexpr std::string LEVEL_CREATOR = "tricipital";
constexpr std::string LEVEL_NAME = "Labyrinth";
static std::string achievements[] = { "beginnings","big spender","quick death","cursed","thievery", "upgrade", "min max", "ispy","boom","invigorated","flying","spicy",
							  "freezing", "zap", "shutdown", "mystery", "prepared", "shortcut","sneaky deals", "secret box", "game time", "casino blitz","collector",
							  "speedrunner1","speedrunner2","speedrunner3","speedrunner4","it lives","it rests","sneaky sneaky","droppy","good ending","escapee",
							  "adventurer1","adventurer2","adventurer3","adventurer4","how to adventure","speed of light","blank","blank","blank" };

static std::unordered_set playtesterIDs = { 6061424 ,4712395 , 11826816 , 63047 , 106255 , 4569963 , 1788352 , 1292925 , 2156992 , 1327813 , 8328899 , 2358957 , 201646 , 5375030 , 104497 ,
						42681 , 1696128 , 15875490 , 1521580 , 7060819 , 3578384 , 13842489 , 2671693 , 1249399 , 8002621 , 21476843 , 4103842 , 6192122 , 10905351 ,
						16750360 , 13935562 , 19542150 , 18298730 , 20063614 , 25373869 , 11167197 , 3822295 , 7882688, 571210, 7346996 , 9471312, 20550026, 8921237, 24813127 };

static std::unordered_set contributorIDs = { 6061424 , 7882688 , 63047 , 34602 , 13903094 , 11167197 , 11826816 , 3166813 , 16610096 , 8851103 , 20371964 , 1696128 , 6225348 , 7709071 ,
						 8328899 , 20550026 , 13842489 , 2671693 , 16494507 , 8002621 , 14277495 , 54944 , 19864272 , 21113321 , 21476843 , 19691441 , 7060384 , 
						 20581650 , 21679473 , 5454096 , 7346996};

static std::unordered_set contestIDs = { 6061424 };

static std::unordered_set chatterIDs = { 6061424 , 25373869 , 19542150 , 28154640 , 21476843 , 31384585 , 2671693 , 13842489 , 27995263 , 63047 , 16546314 , 4422848};


bool checkIfLabyrinth(PlayLayer* pl) {
	// std::string levelName = pl->m_level->m_levelName;
	// return ((levelName.compare(0, 9, LEVEL_NAME, 0, 9) == 0) && (pl->m_level->m_creatorName == LEVEL_CREATOR) && (Mod::get()->hasSavedValue("souls") == true));
	return Mod::get()->hasSavedValue("souls") && geode::utils::string::startsWith(pl->m_level->m_levelName, LEVEL_NAME) && pl->m_level->m_creatorName == LEVEL_CREATOR;
}


void specialPrivs(PlayLayer* pl) {
	if (!pl) return; // avoid nullptr crash
	int userAccountID = GJAccountManager::sharedState()->m_accountID;
	// User has Labyrinth+ enabled
	pl->m_effectManager->updateCountForItem(233, 1);
	pl->updateCounters(233, 1);
	
	// Checking for if the user is a playtester
	// for (int i = 0; i < 38; i++) {
	// 	if (playtesterIDs[i] == userAccountID) {
	// 		pl->m_effectManager->updateCountForItem(432, 1);
	// 		pl->updateCounters(432, 1);
	// 	}
	// }
	if (playtesterIDs.contains(userAccountID)) {
		pl->m_effectManager->updateCountForItem(432, 1);
		pl->updateCounters(432, 1);
	}

	// Checking for if the user is a contributor
	// for (int i = 0; i < 30; i++) {
	// 	if (contributorIDs[i] == userAccountID) {
	// 		pl->m_effectManager->updateCountForItem(433, 1);
	// 		pl->updateCounters(433, 1);
	// 	}
	// }
	if (contributorIDs.contains(userAccountID)) {
		pl->m_effectManager->updateCountForItem(433, 1);
		pl->updateCounters(433, 1);
	}

	// Checking for if the user is a contest winner
	// for (int i = 0; i < 1; i++) {
	// 	if (contributorIDs[i] == userAccountID) {
	// 		pl->m_effectManager->updateCountForItem(434, 1);
	// 		pl->updateCounters(434, 1);
	// 	}
	// }
	if (contestIDs.contains(userAccountID)) {
		pl->m_effectManager->updateCountForItem(434, 1);
		pl->updateCounters(434, 1);
	}

	// Checking for if the user is a chatter
	// for (int i = 0; i < 10; i++) {
	// 	if (contributorIDs[i] == userAccountID) {
	// 		pl->m_effectManager->updateCountForItem(435, 1);
	// 		pl->updateCounters(435, 1);
	// 	}
	// }
	if (chatterIDs.contains(userAccountID)) {
		pl->m_effectManager->updateCountForItem(435, 1);
		pl->updateCounters(435, 1);
	}
}

static void saveState(PlayLayer* pl) {
	//Souls
	Mod::get()->setSavedValue<int>("souls", pl->m_effectManager->countForItem(64));

	//Has gotten a soul before
	Mod::get()->setSavedValue<int>("has_gotten_soul", pl->m_effectManager->countForItem(65));

	//Language
	Mod::get()->setSavedValue<int>("language", pl->m_effectManager->countForItem(58));

	//Idle Lookdown
	Mod::get()->setSavedValue<int>("idle_lookdown", pl->m_effectManager->countForItem(99));

	//Bounce Staff Upgrades
	Mod::get()->setSavedValue<int>("upgrade1", pl->m_effectManager->countForItem(113));

	//Teleporter Upgrades
	Mod::get()->setSavedValue<int>("upgrade2", pl->m_effectManager->countForItem(114));

	//Jetpack Upgrades
	Mod::get()->setSavedValue<int>("upgrade3", pl->m_effectManager->countForItem(115));

	//Ice Boots Upgrades
	Mod::get()->setSavedValue<int>("upgrade4", pl->m_effectManager->countForItem(116));

	//Blacksmith Freed
	Mod::get()->setSavedValue<int>("blacksmith", pl->m_effectManager->countForItem(126));

	//Furthest Reached
	Mod::get()->setSavedValue<int>("furthest", pl->m_effectManager->countForItem(122));

	//New NPC
	//Mod::get()->setSavedValue<int>("visitor", pl->m_effectManager->countForItem(127));

	//Times Stolen
	Mod::get()->setSavedValue<int>("times_stolen", pl->m_effectManager->countForItem(123));

	//Entered Stage 1?
	Mod::get()->setSavedValue<int>("entered1", pl->m_effectManager->countForItem(128));

	//Loot Goblin
	Mod::get()->setSavedValue<int>("loot_goblin", pl->m_effectManager->countForItem(177));

	//Shortcut progress
	Mod::get()->setSavedValue<int>("shortcut", pl->m_effectManager->countForItem(180));

	//Trail Selected
	Mod::get()->setSavedValue<int>("trail", pl->m_effectManager->countForItem(119));

	//Perk Selected
	Mod::get()->setSavedValue<int>("equipedpos", pl->m_effectManager->countForItem(8998));

	//Charisma Perk
	Mod::get()->setSavedValue<int>("charismaperk", pl->m_effectManager->countForItem(8996));

	//Eye Spy perk
	Mod::get()->setSavedValue<int>("ispyperk", pl->m_effectManager->countForItem(8995));

	//Blast Process
	Mod::get()->setSavedValue<int>("blastperk", pl->m_effectManager->countForItem(8994));

	//Gambler perk
	Mod::get()->setSavedValue<int>("gamblerperk", pl->m_effectManager->countForItem(8993));

	//Shopping Addict perk
	Mod::get()->setSavedValue<int>("shopcompassperk", pl->m_effectManager->countForItem(8992));

	//Obsidian Skin perk
	Mod::get()->setSavedValue<int>("lavaperk", pl->m_effectManager->countForItem(8991));

	//Shoplifter perk
	Mod::get()->setSavedValue<int>("stealperk", pl->m_effectManager->countForItem(8990));

	//Speedballing perk
	Mod::get()->setSavedValue<int>("speedperk", pl->m_effectManager->countForItem(8989));

	//Big Man perk
	Mod::get()->setSavedValue<int>("bigmanperk", pl->m_effectManager->countForItem(8988));

	//Navigator perk
	Mod::get()->setSavedValue<int>("compassperk", pl->m_effectManager->countForItem(8987));

	//Curse of Greed perk
	Mod::get()->setSavedValue<int>("greedperk", pl->m_effectManager->countForItem(8986));

	//Rooted Step perk
	Mod::get()->setSavedValue<int>("rootedstepperk", pl->m_effectManager->countForItem(8985));

	//Interest perk
	Mod::get()->setSavedValue<int>("interestperk", pl->m_effectManager->countForItem(8984));

	//Rich perk
	Mod::get()->setSavedValue<int>("richperk", pl->m_effectManager->countForItem(8983));

	//Clearance perk
	Mod::get()->setSavedValue<int>("clearanceperk", pl->m_effectManager->countForItem(8982));

	//Surplus perk
	Mod::get()->setSavedValue<int>("surplusperk", pl->m_effectManager->countForItem(8981));

	//Demolitions Expert perk
	Mod::get()->setSavedValue<int>("bombperk", pl->m_effectManager->countForItem(8980));

	//Soulful perk
	Mod::get()->setSavedValue<int>("soulfulperk", pl->m_effectManager->countForItem(8979));

	//Perk key 1
	Mod::get()->setSavedValue<int>("key1", pl->m_effectManager->countForItem(8974));

	//Perk key 2
	Mod::get()->setSavedValue<int>("key2", pl->m_effectManager->countForItem(8973));

	//Perk key 3
	Mod::get()->setSavedValue<int>("key3", pl->m_effectManager->countForItem(8972));

	//Perk key 1 total
	Mod::get()->setSavedValue<int>("key1total", pl->m_effectManager->countForItem(8975));

	//Perk key 2 total
	Mod::get()->setSavedValue<int>("key2total", pl->m_effectManager->countForItem(8976));

	//Perk key 3 total
	Mod::get()->setSavedValue<int>("key3total", pl->m_effectManager->countForItem(8977));

	//Perk witch progress
	Mod::get()->setSavedValue<int>("perkwitch", pl->m_effectManager->countForItem(438));

	//How many times stage 1 has been entered for cutscene
	Mod::get()->setSavedValue<int>("stage1cutscene", pl->m_effectManager->countForItem(439));

	//trail ghost npc
	Mod::get()->setSavedValue<int>("trailghost", pl->m_effectManager->countForItem(441));

	//Death effect disable
	Mod::get()->setSavedValue<int>("deatheffect", pl->m_effectManager->countForItem(419));

	//Speedrun timer setting
	Mod::get()->setSavedValue<int>("speedruntimer", pl->m_effectManager->countForItem(358));

	//Secret Combination 1
	Mod::get()->setSavedValue<int>("combo1", pl->m_effectManager->countForItem(278));
	//Secret Combination 2
	Mod::get()->setSavedValue<int>("combo2", pl->m_effectManager->countForItem(279));
	//Secret Combination 3
	Mod::get()->setSavedValue<int>("combo3", pl->m_effectManager->countForItem(280));
	//Secret Combination 4
	Mod::get()->setSavedValue<int>("combo4", pl->m_effectManager->countForItem(281));


	// for (int i = 0; i < 40; i++) {
	// 	Mod::get()->setSavedValue<int>(achievements[i], pl->m_effectManager->countForItem(i + 1000));
	// }
	int i = 0;
	for (const auto& achievementKey : achievements) {
		Mod::get()->setSavedValue<int>(achievementKey, pl->m_effectManager->countForItem(i + 1000));
		i++;
	}
}
class $modify(MyPlayerLayer, PlayLayer) {
	void setupHasCompleted() {
		PlayLayer::setupHasCompleted();
		if (checkIfLabyrinth(this)) {
			// Checking for IRL day or night
			time_t currentTime = time(NULL);
			struct tm* localTime = localtime(&currentTime);
			int currentHour = localTime->tm_hour;
			if ((currentHour >= 19) || (currentHour <= 6)){
				this->m_effectManager->updateCountForItem(431, 1);
				this->updateCounters(431, 1);
			}

			
			this->m_effectManager->updateCountForItem(233, 1);
			this->updateCounters(233, 1);

			//Souls
			this->m_effectManager->updateCountForItem(64, Mod::get()->getSavedValue("souls", 0));
			this->updateCounters(64, Mod::get()->getSavedValue("souls", 0));

			//Has gotten a soul before
			this->m_effectManager->updateCountForItem(65, Mod::get()->getSavedValue("has_gotten_soul", 0));
			this->updateCounters(65, Mod::get()->getSavedValue("has_gotten_soul", 0));

			//Language
			this->m_effectManager->updateCountForItem(58, Mod::get()->getSavedValue("language", 0));
			this->updateCounters(58, Mod::get()->getSavedValue("language", 0));

			//Idle Lookdown
			this->m_effectManager->updateCountForItem(99, Mod::get()->getSavedValue("idle_lookdown", 2));
			this->updateCounters(99, Mod::get()->getSavedValue("idle_lookdown", 2));

			//Bounce Staff Upgrades
			this->m_effectManager->updateCountForItem(113, Mod::get()->getSavedValue("upgrade1", 0));
			this->updateCounters(113, Mod::get()->getSavedValue("upgrade1", 0));

			//Teleporter Upgrades
			this->m_effectManager->updateCountForItem(114, Mod::get()->getSavedValue("upgrade2", 0));
			this->updateCounters(114, Mod::get()->getSavedValue("upgrade2", 0));

			//Jetpack Upgrades
			this->m_effectManager->updateCountForItem(115, Mod::get()->getSavedValue("upgrade3", 0));
			this->updateCounters(115, Mod::get()->getSavedValue("upgrade3", 0));

			//Ice Boots Upgrades
			this->m_effectManager->updateCountForItem(116, Mod::get()->getSavedValue("upgrade4", 0));
			this->updateCounters(116, Mod::get()->getSavedValue("upgrade4", 0));

			//Blacksmith Freed
			this->m_effectManager->updateCountForItem(126, Mod::get()->getSavedValue("blacksmith", 0));
			this->updateCounters(126, Mod::get()->getSavedValue("blacksmith", 0));

			//Furthest Reached
			this->m_effectManager->updateCountForItem(122, Mod::get()->getSavedValue("furthest", 0));
			this->updateCounters(122, Mod::get()->getSavedValue("furthest", 0));

			//New NPC
			//this->m_effectManager->updateCountForItem(127, Mod::get()->getSavedValue("visitor", 0));
			//this->updateCounters(127, Mod::get()->getSavedValue("visitor", 0));

			//Times Stolen
			this->m_effectManager->updateCountForItem(123, Mod::get()->getSavedValue("times_stolen", 0));
			this->updateCounters(123, Mod::get()->getSavedValue("times_stolen", 0));

			//Entered Stage 1?
			this->m_effectManager->updateCountForItem(128, Mod::get()->getSavedValue("entered1", 0));
			this->updateCounters(128, Mod::get()->getSavedValue("entered1", 0));

			//Loot Goblin
			this->m_effectManager->updateCountForItem(177, Mod::get()->getSavedValue("loot_goblin", 0));
			this->updateCounters(177, Mod::get()->getSavedValue("loot_goblin", 0));

			//Shortcut progress
			this->m_effectManager->updateCountForItem(180, Mod::get()->getSavedValue("shortcut", 0));
			this->updateCounters(180, Mod::get()->getSavedValue("shortcut", 0));

			//Trail selected
			this->m_effectManager->updateCountForItem(119, Mod::get()->getSavedValue("trail", 0));
			this->updateCounters(119, Mod::get()->getSavedValue("trail", 0));

			//Perk equiped
			this->m_effectManager->updateCountForItem(8998, Mod::get()->getSavedValue("equipedpos", 0));
			this->updateCounters(8998, Mod::get()->getSavedValue("equipedpos", 0));

			//Charisma Perk
			this->m_effectManager->updateCountForItem(8996, Mod::get()->getSavedValue("charismaperk", 0));
			this->updateCounters(8996, Mod::get()->getSavedValue("charismaperk", 0));

			//Eye Spy Perk
			this->m_effectManager->updateCountForItem(8995, Mod::get()->getSavedValue("ispyperk", 0));
			this->updateCounters(8995, Mod::get()->getSavedValue("ispyperk", 0));

			//Blast Process Perk
			this->m_effectManager->updateCountForItem(8994, Mod::get()->getSavedValue("blastperk", 0));
			this->updateCounters(8994, Mod::get()->getSavedValue("blastperk", 0));

			//Gambler Perk
			this->m_effectManager->updateCountForItem(8993, Mod::get()->getSavedValue("gamblerperk", 0));
			this->updateCounters(8993, Mod::get()->getSavedValue("gamblerperk", 0));

			//Shopping Addict Perk
			this->m_effectManager->updateCountForItem(8992, Mod::get()->getSavedValue("shopcompassperk", 0));
			this->updateCounters(8992, Mod::get()->getSavedValue("shopcompassperk", 0));

			//Obsidian Skin Perk
			this->m_effectManager->updateCountForItem(8991, Mod::get()->getSavedValue("lavaperk", 0));
			this->updateCounters(8991, Mod::get()->getSavedValue("lavaperk", 0));

			//Shoplifter Perk
			this->m_effectManager->updateCountForItem(8990, Mod::get()->getSavedValue("stealperk", 0));
			this->updateCounters(8990, Mod::get()->getSavedValue("lavaperk", 0));

			//Speedballing Perk
			this->m_effectManager->updateCountForItem(8989, Mod::get()->getSavedValue("speedperk", 0));
			this->updateCounters(8989, Mod::get()->getSavedValue("speedperk", 0));

			//Big Man Perk
			this->m_effectManager->updateCountForItem(8988, Mod::get()->getSavedValue("bigmanperk", 0));
			this->updateCounters(8988, Mod::get()->getSavedValue("bigmanperk", 0));

			//Navigator Perk
			this->m_effectManager->updateCountForItem(8987, Mod::get()->getSavedValue("compassperk", 0));
			this->updateCounters(8987, Mod::get()->getSavedValue("compassperk", 0));

			//Curse of Greed Perk
			this->m_effectManager->updateCountForItem(8986, Mod::get()->getSavedValue("greedperk", 0));
			this->updateCounters(8986, Mod::get()->getSavedValue("greedperk", 0));\

			//Rooted Step Perk
			this->m_effectManager->updateCountForItem(8985, Mod::get()->getSavedValue("rootedstepperk", 0));
			this->updateCounters(8985, Mod::get()->getSavedValue("rootedstepperk", 0));
			
			//Interest Perk
			this->m_effectManager->updateCountForItem(8984, Mod::get()->getSavedValue("interestperk", 0));
			this->updateCounters(8984, Mod::get()->getSavedValue("interestperk", 0));

			//Rich Perk
			this->m_effectManager->updateCountForItem(8983, Mod::get()->getSavedValue("richperk", 0));
			this->updateCounters(8983, Mod::get()->getSavedValue("richperk", 0));

			//Clearance Perk
			this->m_effectManager->updateCountForItem(8982, Mod::get()->getSavedValue("clearanceperk", 0));
			this->updateCounters(8982, Mod::get()->getSavedValue("clearanceperk", 0));

			//Surplus Perk
			this->m_effectManager->updateCountForItem(8981, Mod::get()->getSavedValue("surplusperk", 0));
			this->updateCounters(8981, Mod::get()->getSavedValue("surplusperk", 0));

			//Demolitions Expert Perk
			this->m_effectManager->updateCountForItem(8980, Mod::get()->getSavedValue("bombperk", 0));
			this->updateCounters(8980, Mod::get()->getSavedValue("bombperk", 0));

			//Soulful Perk
			this->m_effectManager->updateCountForItem(8979, Mod::get()->getSavedValue("soulfulperk", 0));
			this->updateCounters(8979, Mod::get()->getSavedValue("soulfulperk", 0));

			//Perk key 1
			this->m_effectManager->updateCountForItem(8974, Mod::get()->getSavedValue("key1", 0));
			this->updateCounters(8974, Mod::get()->getSavedValue("key1", 0));

			//Perk key 2
			this->m_effectManager->updateCountForItem(8973, Mod::get()->getSavedValue("key2", 0));
			this->updateCounters(8973, Mod::get()->getSavedValue("key2", 0));

			//Perk key 3
			this->m_effectManager->updateCountForItem(8972, Mod::get()->getSavedValue("key3", 0));
			this->updateCounters(8972, Mod::get()->getSavedValue("key3", 0));

			//Perk key 1 total
			this->m_effectManager->updateCountForItem(8975, Mod::get()->getSavedValue("key1total", 0));
			this->updateCounters(8975, Mod::get()->getSavedValue("key1total", 0));

			//Perk key 2 total
			this->m_effectManager->updateCountForItem(8976, Mod::get()->getSavedValue("key2total", 0));
			this->updateCounters(8976, Mod::get()->getSavedValue("key2total", 0));

			//Perk key 3 total
			this->m_effectManager->updateCountForItem(8977, Mod::get()->getSavedValue("key3total", 0));
			this->updateCounters(8977, Mod::get()->getSavedValue("key3total", 0));

			//Perk witch progress
			this->m_effectManager->updateCountForItem(438, Mod::get()->getSavedValue("perkwitch", 0));
			this->updateCounters(438, Mod::get()->getSavedValue("perkwitch", 0));

			//How many times stage 1 has been entered for cutscene
			this->m_effectManager->updateCountForItem(439, Mod::get()->getSavedValue("stage1cutscene", 0));
			this->updateCounters(439, Mod::get()->getSavedValue("stage1cutscene", 0));

			//trail ghost
			this->m_effectManager->updateCountForItem(441, Mod::get()->getSavedValue("trailghost", 0));
			this->updateCounters(441, Mod::get()->getSavedValue("trailghost", 0));

			//Death effect disable
			this->m_effectManager->updateCountForItem(419, Mod::get()->getSavedValue("deatheffect", 0));
			this->updateCounters(419, Mod::get()->getSavedValue("deatheffect", 0));

			//Speedrun timer setting
			this->m_effectManager->updateCountForItem(358, Mod::get()->getSavedValue("speedruntimer", 0));
			this->updateCounters(358, Mod::get()->getSavedValue("speedruntimer", 0));

			//Secret Combination 1
			this->m_effectManager->updateCountForItem(278, Mod::get()->getSavedValue("combo1", 0));
			this->updateCounters(278, Mod::get()->getSavedValue("combo1", 0));
			//Secret Combination 2
			this->m_effectManager->updateCountForItem(279, Mod::get()->getSavedValue("combo2", 0));
			this->updateCounters(279, Mod::get()->getSavedValue("combo2", 0));
			//Secret Combination 3
			this->m_effectManager->updateCountForItem(280, Mod::get()->getSavedValue("combo3", 0));
			this->updateCounters(280, Mod::get()->getSavedValue("combo3", 0));
			//Secret Combination 4
			this->m_effectManager->updateCountForItem(281, Mod::get()->getSavedValue("combo4", 0));
			this->updateCounters(281, Mod::get()->getSavedValue("combo4", 0));
			
			
			for (int i = 0; i < 40; i++) {
				this->m_effectManager->updateCountForItem(i+1000, Mod::get()->getSavedValue(achievements[i], 0));
				this->updateCounters(i+1000, Mod::get()->getSavedValue(achievements[i], 0));
			}

			specialPrivs(this);
		}
	}

	// arguably, PlayLayer::onQuit() is a better choice for when exiting the level, but i guess it cant hurt to save this information during game pause as well
	virtual void onExit() {
		PlayLayer::onExit();
		saveState(this);
	}

	void startGameDelayed() {
		PlayLayer::startGameDelayed();
		if (checkIfLabyrinth(this)) {
			saveState(this);
			specialPrivs(this);
		}
	}
};
