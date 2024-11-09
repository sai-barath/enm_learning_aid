/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2024 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_GUI_BUILDER_LABEL_PROPERTIES_HPP
#define TGUI_GUI_BUILDER_LABEL_PROPERTIES_HPP

#include "WidgetProperties.hpp"

struct LabelProperties : WidgetProperties
{
    // TODO: Scrollbar renderer

    void updateProperty(const tgui::Widget::Ptr& widget, const tgui::String& property, const tgui::String& value) const override
    {
        auto label = widget->cast<tgui::Label>();
        if (property == "Text")
            label->setText(tgui::Deserializer::deserialize(tgui::ObjectConverter::Type::String, value).getString());
        else if (property == "TextSize")
            label->setTextSize(value.toUInt());
        else if (property == "HorizontalAlignment")
            label->setHorizontalAlignment(deserializeHorizontalAlignment(value));
        else if (property == "VerticalAlignment")
            label->setVerticalAlignment(deserializeVerticalAlignment(value));
        else if (property == "ScrollbarPolicy")
            label->getScrollbar()->setPolicy(deserializeScrollbarPolicy(value));
        else if (property == "AutoSize")
            label->setAutoSize(parseBoolean(value, true));
        else if (property == "MaximumTextWidth")
            label->setMaximumTextWidth(value.toFloat());
        else
            WidgetProperties::updateProperty(widget, property, value);
    }

    TGUI_NODISCARD PropertyValueMapPair initProperties(const tgui::Widget::Ptr& widget) const override
    {
        auto pair = WidgetProperties::initProperties(widget);
        auto label = widget->cast<tgui::Label>();
        pair.first["Text"] = {"MultilineString", tgui::Serializer::serialize(label->getText())};
        pair.first["TextSize"] = {"UInt", tgui::String::fromNumber(label->getTextSize())};
        pair.first["HorizontalAlignment"] = {"Enum{Left,Center,Right}", serializeHorizontalAlignment(label->getHorizontalAlignment())};
        pair.first["VerticalAlignment"] = {"Enum{Top,Center,Bottom}", serializeVerticalAlignment(label->getVerticalAlignment())};
        pair.first["ScrollbarPolicy"] = {"Enum{Automatic,Always,Never}", serializeScrollbarPolicy(label->getScrollbar()->getPolicy())};
        pair.first["AutoSize"] = {"Bool", tgui::Serializer::serialize(label->getAutoSize())};
        pair.first["MaximumTextWidth"] = {"Float", tgui::String::fromNumber(label->getMaximumTextWidth())};

        const auto renderer = label->getSharedRenderer();
        pair.second["Borders"] = {"Outline", renderer->getBorders().toString()};
        pair.second["Padding"] = {"Outline", renderer->getPadding().toString()};
        pair.second["TextColor"] = {"Color", tgui::Serializer::serialize(renderer->getTextColor())};
        pair.second["BackgroundColor"] = {"Color", tgui::Serializer::serialize(renderer->getBackgroundColor())};
        pair.second["BorderColor"] = {"Color", tgui::Serializer::serialize(renderer->getBorderColor())};
        pair.second["TextOutlineColor"] = {"Color", tgui::Serializer::serialize(renderer->getTextOutlineColor())};
        pair.second["TextOutlineThickness"] = {"Float", tgui::String::fromNumber(renderer->getTextOutlineThickness())};
        pair.second["TextStyle"] = {"TextStyle", tgui::Serializer::serialize(renderer->getTextStyle())};
        pair.second["TextureBackground"] = {"Texture", tgui::Serializer::serialize(renderer->getTextureBackground())};
        pair.second["ScrollbarWidth"] = {"Float", tgui::String::fromNumber(renderer->getScrollbarWidth())};
        return pair;
    }
};

#endif // TGUI_GUI_BUILDER_LABEL_PROPERTIES_HPP
