#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        // Chama a função original para o player realmente morrer
        PlayLayer::destroyPlayer(player, obj);

        // Exibe o alerta na tela
        FLAlertLayer::create("DIEE DIEE", "DIEE DIEE", "OK")->show();
    }
};
