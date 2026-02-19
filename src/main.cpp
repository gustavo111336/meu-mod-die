#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Variável global
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
            // Usando um sprite de círculo simples do Geode
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
        
        // Criando a string manualmente ANTES de passar para o alerta
        // Isso evita o erro de template do fmt no Android
        std::string status = g_noclipEnabled ? "ATIVADO" : "DESATIVADO";
        std::string mensagem = "Noclip agora esta: " + status;

        FLAlertLayer::create(
            "GUSTAVO MENU",
            mensagem, 
            "OK"
        )->show();
    }
};
