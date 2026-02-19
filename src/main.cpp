#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Pegamos o menu da direita (onde fica o botão "More Games") pelo ID
        auto rightMenu = this->getChildByID("right-side-menu");

        // Criamos um botão com a logo do Geode
        auto sprite = CircleButtonSprite::createWithSpriteFrameName("geode.loader/geode-logo-outline.png");
        auto btn = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MyMenuLayer::onMyModMenu)
        );

        // Adicionamos o botão ao menu lateral
        btn->setID("my-custom-menu-button");
        rightMenu->addChild(btn);
        rightMenu->updateLayout();

        return true;
    }

    void onMyModMenu(CCObject*) {
        FLAlertLayer::create(
            "GUSTAVO MENU",
            "Opcao 1: [ATIVADO]\nOpcao 2: [DESATIVADO]",
            "FECHAR"
        )->show();
    }
};
