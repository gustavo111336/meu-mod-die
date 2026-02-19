#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        auto m = this->getChildByID("right-side-menu");
        if (m) {
            auto s = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline.png");
            auto b = CCMenuItemSpriteExtra::create(s, this, menu_selector(MyMenuLayer::onM));
            m->addChild(b);
            m->updateLayout();
        }
        return true;
    }
    void onM(CCObject*) {
        FLAlertLayer::create("G", "M", "OK")->show();
    }
};
l