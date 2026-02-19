#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

bool g_noclipEnabled = false;

class $modify(PlayerObject) {
    void destroyPlayer(bool p0, bool p1) {
        if (g_noclipEnabled) return; 
        PlayerObject::destroyPlayer(p0, p1);
    }
};

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

    void onModMenu(CCObject* sender) {
        g_noclipEnabled = !g_noclipEnabled;
        
        // Em vez de alerta, vamos mudar a cor do botão para dar feedback
        // Verde = Ativado, Vermelho = Desativado
        auto btn = static_cast<CCMenuItemSpriteExtra*>(sender);
        if (g_noclipEnabled) {
            btn->setColor({0, 255, 0});
        } else {
            btn->setColor({255, 0, 0});
        }
    }
};
