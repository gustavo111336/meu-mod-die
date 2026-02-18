#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Vamos mexer no Menu inicial em vez da morte, só para testar
class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		
		log::info("Mod carregado com sucesso!");
		
		return true;
	}
};
