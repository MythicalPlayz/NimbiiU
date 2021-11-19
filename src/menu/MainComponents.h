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
    GuiButton *AdvancedButton = nullptr;
    GuiButton *QuickButton = nullptr;
private:
GuiText *ExitLabel = nullptr;
GuiText *AdvancedLabel = nullptr;
GuiText *QuickLabel = nullptr;
GuiImage *ExitImage = nullptr;
GuiImage *AdvancedImage = nullptr;
GuiImage *QuickImage = nullptr;
GuiTrigger *touchTrigger = nullptr;
    GuiTrigger *buttonTrigger = nullptr;
    GuiSound *sound = nullptr;
    void CreateButton(GuiButton * Button,GuiImage * Image, GuiText * Text,float WidthOffset,float HeightOffset);
};