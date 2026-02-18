
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        // Chama a função original
        PlayLayer::destroyPlayer(p0, p1);

        // Alerta simplificado para evitar erro de FMT
        auto alert = FLAlertLayer::create(
            "Morte", 
            "DIEE DIEE", 
            "OK"
        );
        alert->m_noElasticity = true; // Ajuda a evitar crash em algumas versões
        alert->show();
    }
};
