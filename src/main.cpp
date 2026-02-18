#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <geode.devtools/include/DevTools.hpp>

using namespace geode::prelude;

class MySprite : public CCSprite {
public:
    enum class RandomEnum {
        Option1, Option2, Option3
    };

    // Função para registrar as propriedades no DevTools
    static void registerDevTools() {
        devtools::registerNode<MySprite>([](MySprite* node) {
            devtools::label("Configurações do Meu Sprite");
            devtools::property("Ativado", node->m_someFlag);
            devtools::property("Velocidade", node->m_someFloat);
            devtools::property("ID Interno", node->m_someInt);
            devtools::property("Nome do Mod", node->m_someString);
            devtools::property("Cor do Sprite", node->m_someColor);
            
            devtools::enumerable("Opções Extras", node->m_someEnum, {
                { RandomEnum::Option1, "Opção 1" },
                { RandomEnum::Option2, "Opção 2" },
                { RandomEnum::Option3, "Opção 3" }
            });

            devtools::button("Efeito de Tremor", [node]{
                node->runAction(CCShaky3D::create(0.5f, CCSize(10, 10), 5, false));
            });
        });
    }

    // Método para inicializar o sprite com uma imagem do jogo
    bool init() {
        if (!CCSprite::initWithFile("GJ_button_01.png")) return false;
        return true;
    }

    static MySprite* create() {
        auto ret = new MySprite();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

private:
    float m_someFloat = 3.14f;
    int m_someInt = 42;
    std::string m_someString = "Gustavo Mod";
    ccColor3B m_someColor = {255, 0, 0};
    RandomEnum m_someEnum = RandomEnum::Option1;
    bool m_someFlag = true;
};

// Hook para injetar o sprite no menu principal
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto mySprite = MySprite::create();
        mySprite->setPosition({100, 100});
        mySprite->setID("meu-sprite-customizado"_spr);
        this->addChild(mySprite);

        return true;
    }
};

// Ponto de entrada do Mod
$on_mod(Loaded) {
    devtools::waitForDevTools([] {
        MySprite::registerDevTools();
    });
}
