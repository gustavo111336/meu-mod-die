#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Variável de controle
bool g_noclipEnabled = false;

// --- Hook do Noclip ---
class $modify(PlayerObject) {
    void destroyPlayer(bool p0, bool p1) {
        if (g_noclipEnabled) return; 
        PlayerObject::destroyPlayer(p0, p1);
    }
};

// --- Hook do Menu ---
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("right-side-menu");
        if (menu) {
            auto btnSprite = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline.png");
            auto menuBtn = CCMenuItemSpriteExtra::create(
                btnSprite, this, menu_selector(MyMenuLayer::onModMenu)
            );
            menuBtn->setID("noclip-btn");
            menu->addChild(menuBtn);
            menu->updateLayout();
        }
        return true;
    }

    void onModMenu(CCObject*) {
        g_noclipEnabled = !g_noclipEnabled;
        
        // Em vez de criar uma mensagem com o status, vamos usar um título fixo
        // Isso evita que o compilador tente converter strings
        FLAlertLayer::create(
            "MOD STATUS", 
            "O Noclip foi alternado!", 
            "OK"
        )->show();
    }
};
