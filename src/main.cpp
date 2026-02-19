#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto rightMenu = this->getChildByID("right-side-menu");
        
        if (rightMenu) {
            auto sprite = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline.png");
            auto btn = CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(MyMenuLayer::onMyModMenu)
            );

            btn->setID("my-custom-menu-button");
            rightMenu->addChild(btn);
            rightMenu->updateLayout();
        }

        return true;
    }

    void onMyModMenu(CCObject*) {
        FLAlertLayer::create(
            "GUSTAVO MENU",
            "Mod carregado com sucesso!",
            "OK"
        )->show();
    }
};
