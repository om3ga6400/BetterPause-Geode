#include "SetVolumenPopup.hpp"

SetVolumenPopup* SetVolumenPopup::create(Slider* m_pSliderRef)
{
	auto node = new SetVolumenPopup();
	if (node && node->initAnchored(200.f, 100.f, m_pSliderRef, "GJ_square02.png"))
	{
		node->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(node);
	}
	return node;
}

void SetVolumenPopup::onSet(cocos2d::CCObject* pSender)
{
	int numberAs = 0;
	try
	{
		numberAs = std::stoi(this->m_pInputTextValue->getString());
		if (this->m_pSliderRef) {
			numberAs = std::min(100, std::max(0, numberAs));
			this->m_pSliderRef->setValue(static_cast<float>(numberAs) / 100.f);
			this->m_pSliderRef->getThumb()->activate();
			this->m_pSliderRef->updateBar();
		}
	}
	catch (std::exception const& e)
	{
		//numberAs = this->m_pSliderRef->m_touchLogic->getThumb()->getValue() * 100;
		// FLAlertLayer::create(nullptr, "Error", "OK", nullptr, "There was an error processing the number.")->show();
	}
	this->keyBackClicked();
}

void SetVolumenPopup::keyBackClicked()
{
	FLAlertLayer::keyBackClicked();
}

bool SetVolumenPopup::setup(Slider* m_pSliderRef)
{
	this->m_pSliderRef = m_pSliderRef;

	auto titleLayer = cocos2d::CCLabelBMFont::create("- Set Value -", "goldFont.fnt");
	titleLayer->setScale(0.7f);
	titleLayer->setPosition(100.f, 85.f);
	m_mainLayer->addChild(titleLayer);

	auto underline = cocos2d::CCSprite::createWithSpriteFrameName("floorLine_001.png");
	underline->setPosition({ 100.f, 68.f });
	underline->setScaleX(0.4f);
	underline->setScaleY(0.5f);
	underline->setOpacity(100);
	m_mainLayer->addChild(underline);

	auto buttonSetValue = ButtonSprite::create("Set", 0xFC, false, "goldFont.fnt", "GJ_button_01.png", 30.f, 0.6f);
	m_pSetValueBtn = CCMenuItemSpriteExtra::create(buttonSetValue, this, (cocos2d::SEL_MenuHandler)&SetVolumenPopup::onSet);
	m_pSetValueBtn->setPosition({ 157.f, 35.f });
	m_buttonMenu->addChild(m_pSetValueBtn);

	m_pBGInputTextValue = cocos2d::extension::CCScale9Sprite::create("square02_small.png");
	m_pBGInputTextValue->setContentSize({ 70.f, 30.f });
	m_pBGInputTextValue->setScale(1.f);
	m_pBGInputTextValue->setPosition({ 60.f, 36.f });
	m_pBGInputTextValue->setColor({ 255, 255, 255 });
	m_pBGInputTextValue->setOpacity(100);
	m_mainLayer->addChild(m_pBGInputTextValue);

	m_pInputTextValue = CCTextInputNode::create(50.f, 20.f, "Vol", "bigFont.fnt");
	m_pInputTextValue->setString(gd::string(std::to_string(static_cast<int>(this->m_pSliderRef->getThumb()->getValue() * 100))));
	m_pInputTextValue->setLabelPlaceholderColor({ 0x75, 0xAA, 0xF0 });
	m_pInputTextValue->m_maxLabelLength = 3;
	m_pInputTextValue->setAllowedChars("0123456789");
	m_pInputTextValue->setMaxLabelScale(0.7f);
	m_pInputTextValue->setPosition({ 59.f, 36.f });
	m_pInputTextValue->setDelegate(this);
	m_mainLayer->addChild(m_pInputTextValue);

	auto perSymbol = cocos2d::CCLabelBMFont::create("%", "bigFont.fnt");
	perSymbol->setScale(0.6f);
	perSymbol->setPosition({ 109.f, 35.f });
	m_mainLayer->addChild(perSymbol);

	this->setMouseEnabled(true);
	this->setKeyboardEnabled(true);

	return true;
}

void SetVolumenPopup::keyDown(cocos2d::enumKeyCodes key)
{
	switch (key)
	{
	case cocos2d::enumKeyCodes::KEY_Space:
		this->keyBackClicked();
		break;
	case cocos2d::enumKeyCodes::CONTROLLER_X:
		this->keyBackClicked();
		break;
	case cocos2d::enumKeyCodes::KEY_Left:
	case cocos2d::enumKeyCodes::CONTROLLER_Left:
		break;
	case cocos2d::enumKeyCodes::KEY_Right:
	case cocos2d::enumKeyCodes::CONTROLLER_Right:
		break;
	default:
		CCLayer::keyDown(key);
	}
}
