#include <Geode/Geode.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

class $modify(MenuLayerHook, MenuLayer) {

	static void startRandomizeCBF() {
		srand(time(0));
		Mod* cbf = Loader::get()->getLoadedMod("syzzi.click_between_frames");
		cbf->setSettingValue("soft-toggle", rand() % 2 >= 1);
		FLAlertLayer::create(
			"CBF randomized!",
			"You can check whether it is enabled or disabled by going to CBF's geode settings.",
			"OK"
		)->show();
	}

	void buttonPressed(CCObject*) {
		geode::createQuickPopup(
			"Randomize CBF?",
			"This will randomly turn on or off the \"Disable CBF\" setting in the Geode settings for CBF.",
			"Cancel", "Continue",
			[](auto, bool btn2) {
				if (btn2) {
					startRandomizeCBF();
				}
			}
		);
	}

	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::create("placebo_cbf_logo.png"_spr),
			this,
			menu_selector(MenuLayerHook::buttonPressed)
		);

		auto menu = this->getChildByID("right-side-menu");
		menu->addChild(myButton);

		menu->updateLayout();
		return true;
	}
};