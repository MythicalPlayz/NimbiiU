#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"
#include "../gui/GuiButton.h"
class ExtraInfo : public GuiFrame, public sigslot::has_slots<> {
public:
     ~ExtraInfo() override;
    ExtraInfo(int32_t w, int32_t h, Renderer* renderer);
     void process() override;
     static void MakeItemsVisible(bool b);
    GuiButton *BackButton = nullptr;
    GuiText *SystemInfo1 = nullptr;
    GuiText *Credits = nullptr;
private:
    GuiTrigger *touchTrigger = nullptr;
    GuiTrigger *buttonTrigger = nullptr;
    GuiSound *sound = nullptr;
};