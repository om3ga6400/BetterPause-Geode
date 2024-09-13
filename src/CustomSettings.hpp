#pragma once
#include <Geode/loader/SettingV3.hpp>
#include "SelectQuickSettings.h"
using namespace geode::prelude;

/*
    --- Quick settings layer ---
*/

class SettingQuickSettingsValue;

class SettingQuickSettingsValue : public SettingV3 {
public:
    static Result<std::shared_ptr<SettingQuickSettingsValue>> parse(std::string const& key, std::string const& modID, matjson::Value const& json) {
        auto setting = std::make_shared<SettingQuickSettingsValue>();
        auto root = checkJson(json, "SettingQuickSettingsValue");
        setting->init(key, modID);
        setting->parseNameAndDescription(root);
        return root.ok(setting);
    }

    bool load(matjson::Value const& json) override {
        return true;
    }
    bool save(matjson::Value& json) const override {
        return true;
    }
    bool isDefaultValue() const override {
        return true;
    }
    void reset() override {}
    SettingNodeV3* createNode(float width) override;
};


class SettingQuickSettingsNode : public SettingNodeV3 {
protected:
    bool init(std::shared_ptr<SettingQuickSettingsValue> value, float width) {
        if (!SettingNodeV3::init(value, width))
            return false;
        this->setContentSize({ width, 35.f });
        auto menu = CCMenu::create();
        auto opSpr = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
        opSpr->setScale(0.6f);
        //auto infoBtn
        auto qssBtn = CCMenuItemSpriteExtra::create(
            opSpr,
            this,
            (cocos2d::SEL_MenuHandler)&SettingQuickSettingsNode::onQuickSettings
        );
        qssBtn->setPositionX(140);
        menu->setPosition(width / 2, 18.f);
        menu->addChild(qssBtn);
        this->addChild(menu);
        return true;
    }

public:
    // because for some reason SettingNode doesnt expose description, i have to do all of this, smh.
    void onQuickSettings(CCObject*);

    void onCommit() override {
        // Let the UI know you have committed the value
    }

    // Geode calls this to query if the setting value has been changed, 
    // and those changes haven't been committed
    bool hasUncommittedChanges() const override {
        return false;
    }

    // Geode calls this to query if the setting has a value that is 
    // different from its default value
    bool hasNonDefaultValue() const override {
        return false;
    }

    // Geode calls this to reset the setting's value back to default
    void onResetToDefault() override {

    }
    static SettingQuickSettingsNode* create(std::shared_ptr<SettingQuickSettingsValue> value, float width) {
        auto ret = new SettingQuickSettingsNode;
        if (ret && ret->init(value, width)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};
