#include "CustomSettings.hpp"

SettingNodeV3* SettingQuickSettingsValue::createNode(float width) {
    return SettingQuickSettingsNode::create(std::static_pointer_cast<SettingQuickSettingsValue>(shared_from_this()), width);
}

void SettingQuickSettingsNode::onQuickSettings(CCObject* sender) {
    auto zOrderP = CCScene::get()->getHighestChildZ();
    auto popup = SelectQuickSettings::create(false);
    popup->show();
    popup->setZOrder(zOrderP);
}