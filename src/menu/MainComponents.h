#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"
#include "../gui/GuiButton.h"
class MainComponents : public GuiFrame, public sigslot::has_slots<> {
public:
void test(GuiButton *, const GuiController *, GuiTrigger *);
   ~MainComponents() override;
    MainComponents(int32_t w, int32_t h, Renderer* renderer);
    void process() override;
    GuiButton *ExitButton = nullptr;
private:
GuiText *ExitLabel = nullptr;
GuiTrigger *touchTrigger = nullptr;
    GuiTrigger *buttonTrigger = nullptr;
    GuiSound *sound = nullptr;
};