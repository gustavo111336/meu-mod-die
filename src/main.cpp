#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Variável global simples
bool g_noclipEnabled = false;

// --- Hook para Noclip ---
class $modify(PlayerObject) {
    void destroyPlayer(bool p0, bool p1) {
        if (g_noclipEnabled) {
            return; 
        }
        PlayerObject::destroyPlayer(p0, p1);
    }
};

// --- Interface no Menu ---
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("right-side-menu");
        
        if (menu) {
            auto btnSprite = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline.png");
            auto menuBtn = CCMenuItemSpriteExtra::create(
                btnSprite,
                this,
                menu_selector(MyMenuLayer::onModMenu)
            );

            menuBtn->setID("my-mod-toggle-btn");
            menu->addChild(menuBtn);
            menu->updateLayout();
        }

        return true;
    }

    void onModMenu(CCObject*) {
        g_noclipEnabled = !g_noclipEnabled;
        
        // Usamos const char* para evitar que o Geode tente usar o fmt::format internamente
        const char* mensagem = g_noclipEnabled ? "Noclip: ATIVADO" : "Noclip: DESATIVADO";

        FLAlertLayer::create(
            "GUSTAVO MENU",
            mensagem, 
            "OK"
        )->show();
    }
};
