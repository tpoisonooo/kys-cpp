#include "UIStatus.h"
#include "Font.h"
#include "others/libconvert.h"
#include "Save.h"
#include "GameUtil.h"
#include "TeamMenu.h"
#include "ShowRoleDifference.h"

UIStatus::UIStatus()
{
    button_medcine_ = new Button();
    button_medcine_->setText("�t��");
    addChild(button_medcine_, 350, 55);

    button_detoxification_ = new Button();
    button_detoxification_->setText("�ⶾ");
    addChild(button_detoxification_, 400, 55);

    button_leave_ = new Button();
    button_leave_->setText("�x�");
    addChild(button_leave_, 450, 55);
}

UIStatus::~UIStatus()
{
}

void UIStatus::draw()
{
    if (role_)
    {
        if (show_button_)
        {
            button_medcine_->setVisible(role_->Medcine > 0);
            button_detoxification_->setVisible(role_->Detoxification > 0);
            button_leave_->setVisible(role_->ID != 0);
        }
    }
    else
    {
        button_medcine_->setVisible(false);
        button_detoxification_->setVisible(false);
        button_leave_->setVisible(false);
        return;
    }
    TextureManager::getInstance()->renderTexture("head", role_->HeadID, x_ + 10, y_ + 20);

    auto font = Font::getInstance();
    BP_Color color = { 255, 255, 255, 255 };
    int font_size = 22;
    font->draw(convert::formatString("%s", role_->Name), 30, x_ + 190, y_ + 50, color);
    font->draw(convert::formatString("�ȼ�%5d", role_->Level), font_size, x_ + 200, y_ + 100, color);
    font->draw(convert::formatString("���%5d", role_->Exp), font_size, x_ + 200, y_ + 125, color);

    std::string str = "���� ----";
    int exp_up = GameUtil::getLevelUpExp(role_->Level);
    if (exp_up != INT_MAX)
    {
        str = convert::formatString("����%5d", exp_up);
    }
    font->draw(str, font_size, x_ + 200, y_ + 150, color);
    font->draw(convert::formatString("����%5d/%5d", role_->HP, role_->MaxHP), font_size, x_ + 355, y_ + 100, color);
    font->draw(convert::formatString("����%5d/%5d", role_->MP, role_->MaxMP), font_size, x_ + 355, y_ + 125, color);
    font->draw(convert::formatString("�w��%5d/%5d", role_->PhysicalPower, 100), font_size, x_ + 355, y_ + 150, color);

    font->draw(convert::formatString("����%5d", role_->Attack), font_size, x_ + 20, y_ + 200, color);
    font->draw(convert::formatString("���R%5d", role_->Defence), font_size, x_ + 220, y_ + 200, color);
    font->draw(convert::formatString("�p��%5d", role_->Speed), font_size, x_ + 420, y_ + 200, color);

    font->draw(convert::formatString("�t��%5d", role_->Medcine), font_size, x_ + 20, y_ + 225, color);
    font->draw(convert::formatString("�ⶾ%5d", role_->Detoxification), font_size, x_ + 220, y_ + 225, color);
    font->draw(convert::formatString("�ö�%5d", role_->UsePoison), font_size, x_ + 420, y_ + 225, color);

    font->draw("����", 25, x_ + 10, y_ + 270, color);
    font->draw(convert::formatString("ȭ��%5d", role_->Fist), font_size, x_ + 20, y_ + 300, color);
    font->draw(convert::formatString("����%5d", role_->Sword), font_size, x_ + 20, y_ + 325, color);
    font->draw(convert::formatString("ˣ��%5d", role_->Knife), font_size, x_ + 20, y_ + 350, color);
    font->draw(convert::formatString("����%5d", role_->Unusual), font_size, x_ + 20, y_ + 375, color);
    font->draw(convert::formatString("����%5d", role_->HiddenWeapon), font_size, x_ + 20, y_ + 400, color);

    font->draw("��W", 25, x_ + 210, y_ + 270, color);
    for (int i = 0; i < 10; i++)
    {
        auto magic = Save::getInstance()->getRoleLearnedMagic(role_, i);
        std::string str = "__________";
        if (magic)
        {
            str = convert::formatString("%-12s%3d", magic->Name, role_->getRoleShowLearnedMagicLevel(i));
        }
        int x = x_ + 220 + i % 2 * 200;
        int y = y_ + 300 + i / 2 * 25;
        font->draw(str, font_size, x, y, color);
    }

    font->draw("�ޟ�", 25, x_ + 10, y_ + 445, color);
    auto book = Save::getInstance()->getItem(role_->PracticeItem);
    if (book)
    {
        TextureManager::getInstance()->renderTexture("item", book->ID, x_ + 20, y_ + 475);
        font->draw(convert::formatString("%s", book->Name), font_size, x_ + 110, y_ + 475, color);
        font->draw(convert::formatString("���%5d", role_->ExpForItem), 18, x_ + 110, y_ + 500, color);
                std::string str = "���� ----";
        int exp_up = GameUtil::getFinishedExpForItem(role_, book);
        if (exp_up != INT_MAX)
        {
            str = convert::formatString("����%5d", exp_up);
        }
        font->draw(str, 18, x_ + 110, y_ + 520, color);
    }

    font->draw("�b��", 25, x_ + 210, y_ + 445, color);
    auto equip1 = Save::getInstance()->getItem(role_->Equip1);
    if (equip1)
    {
        TextureManager::getInstance()->renderTexture("item", equip1->ID, x_ + 220, y_ + 475);
        font->draw(convert::formatString("%s", equip1->Name), font_size, x_ + 310, y_ + 475, color);
        font->draw(convert::formatString("����%+d", equip1->AddAttack), 18, x_ + 310, y_ + 500, color);
        font->draw(convert::formatString("���R%+d", equip1->AddDefence), 18, x_ + 310, y_ + 520, color);
        font->draw(convert::formatString("�p��%+d", equip1->AddSpeed), 18, x_ + 310, y_ + 540, color);
    }

    auto equip2 = Save::getInstance()->getItem(role_->Equip2);
    if (equip2)
    {
        TextureManager::getInstance()->renderTexture("item", equip2->ID, x_ + 420, y_ + 475);
        font->draw(convert::formatString("%s", equip2->Name), font_size, x_ + 510, y_ + 475, color);
        font->draw(convert::formatString("����%+d", equip2->AddAttack), 18, x_ + 510, y_ + 500, color);
        font->draw(convert::formatString("���R%+d", equip2->AddDefence), 18, x_ + 510, y_ + 520, color);
        font->draw(convert::formatString("�p��%+d", equip2->AddSpeed), 18, x_ + 510, y_ + 540, color);
    }
}

void UIStatus::dealEvent(BP_Event& e)
{
}

void UIStatus::pressedOK()
{
    if (role_ == nullptr) { return; }

    if (button_leave_->getState() == Press)
    {
        
    }
    else if (button_medcine_->getState() == Press)
    {
        auto team_menu = new TeamMenu();
        team_menu->run();
        auto role = team_menu->getRole();
        delete team_menu;
        if (role)
        {
            GameUtil::medcine(role_, role);
            Role r = *role;
            auto df = new ShowRoleDifference(&r, role);
            df->run();
            delete df;
        }
    }
    else if (button_detoxification_->getState() == Press)
    {
        auto team_menu = new TeamMenu();
        team_menu->run();
        auto role = team_menu->getRole();
        delete team_menu;
        if (role)
        {
            GameUtil::detoxification(role_, role);
            Role r = *role;
            auto df = new ShowRoleDifference(&r, role);
            df->run();
            delete df;
        }
    }
}
