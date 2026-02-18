#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        PlayLayer::destroyPlayer(p0, p1);

        // Usando strings simples para não ativar o FMT_COMPILE_STRING
        auto title = std::string("MORREU!");
        auto message = std::string("DIEE DIEE");
        
        FLAlertLayer::create(title.c_str(), message.c_str(), "OK")->show();
    }
};
