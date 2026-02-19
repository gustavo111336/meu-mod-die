#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("right-side-menu");
        
        if (menu) {
            auto sprite = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline.png");
            auto btn = CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(MyMenuLayer::onMyButton)
            );
            menu->addChild(btn);
            menu->updateLayout();
        }

        return true;
    }

    void onMyButton(CCObject* sender) {
        auto alert = FLAlertLayer::create("Info", "Mod Funcionando", "OK");
        alert->show();
    }
};
