#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"
#include "../gui/GuiButton.h"
void MakeItemsVisible3(bool b);
class ExtraInfo : public GuiFrame, public sigslot::has_slots<> {
public:
     ~ExtraInfo() override;
    ExtraInfo(int32_t w, int32_t h, Renderer* renderer);
     void process() override;
     void ReturnToMenu(GuiButton *, const GuiController *, GuiTrigger *);
private:
    GuiTrigger *touchTrigger = nullptr;
    GuiTrigger *buttonTrigger = nullptr;
    GuiSound *sound = nullptr;
};