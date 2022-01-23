#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"
#include "../gui/GuiButton.h"
#include "MainComponents.h"
class ButtonHandler : public GuiFrame, public sigslot::has_slots<>{
public:
     ~ButtonHandler() override;
    ButtonHandler(int32_t w, int32_t h, Renderer* renderer);
    void process() override;
    void GameControllerInput(GuiButton *, const GuiController * t, GuiTrigger * Trigger);
    private:
    GuiButton *Gamebutton = nullptr;
    GuiTrigger *UpTrigger = nullptr;
    GuiTrigger *DownTrigger = nullptr;
    GuiTrigger *RightTrigger = nullptr;
    GuiTrigger *LeftTrigger = nullptr;
};
