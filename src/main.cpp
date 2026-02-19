#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Variável global para o Noclip
bool g_noclipEnabled = false;

// --- Hook para Noclip ---
class $modify(PlayerObject) {
    void destroyPlayer(bool p0, bool p1) {
        // Se noclip estiver on, apenas ignoramos a função de morte
        if (g_noclipEnabled) {
            return; 
        }
        PlayerObject::destroyPlayer(p0, p1);
    }
};

// --- Interface no Menu Principal ---
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // "right-side-menu" é o ID padrão do Geode para o menu da direita
        auto menu = this->getChildByID("right-side-menu");
        
        if (menu) {
            // Usando um sprite padrão do jogo para o botão (GJ_checkOn_001.png)
            auto btnSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
            
            auto menuBtn = CCMenuItemSpriteExtra::create(
                btnSprite,
                this,
                menu_selector(MyMenuLayer::onModMenu)
            );

            menuBtn->setID("noclip-toggle-btn");
            menu->addChild(menuBtn);
            
            // Recalcula o posicionamento dos botões no menu lateral automaticamente
            menu->updateLayout();
        }

        return true;
    }

    void onModMenu(CCObject*) {
        g_noclipEnabled = !g_noclipEnabled;
        
        // O segredo para o Build passar: fmt::format
        std::string status = g_noclipEnabled ? "ATIVADO" : "DESATIVADO";
        auto mensagem = fmt::format("Noclip agora esta: <cl>{}</c>", status);

        auto alert = FLAlertLayer::create(
            "GUSTAVO MENU",
            mensagem, // Geode aceita std::string aqui se formatado via fmt
            "OK"
        );
        alert->show();
    }
};
