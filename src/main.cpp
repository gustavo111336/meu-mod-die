#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyDeathMod, PlayLayer) {
    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        // Chama a função original primeiro
        PlayLayer::destroyPlayer(p0, p1);

        // Verifica se o objeto que matou o player não é nulo 
        // para evitar que o jogo feche sozinho (crash)
        FLAlertLayer::create(
            "MORREU!", 
            "DIEE DIEE", 
            "OK"
        )->show();
    }
};
