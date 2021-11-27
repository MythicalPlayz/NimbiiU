#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"
#include "../gui/GuiButton.h"
#include "../patch/iosu_kernel.h"

class MainComponents : public GuiFrame, public sigslot::has_slots<> {
public:
void Exit(GuiButton *, const GuiController *, GuiTrigger *);
void ExtraInfo(GuiButton *, const GuiController *, GuiTrigger *);
void Advanced(GuiButton *, const GuiController *, GuiTrigger *);
void Quick(GuiButton *, const GuiController *, GuiTrigger *);
static void Patch();
void MakeItemsVisible(bool b);
   ~MainComponents() override;
    MainComponents(int32_t w, int32_t h, Renderer* renderer);
    void process() override;
    GuiButton *ExitButton = nullptr;
    GuiButton *AdvancedButton = nullptr;
    GuiButton *QuickButton = nullptr;
    GuiButton *InfoButton = nullptr;
    GuiImage *InfoImageIcon = nullptr;
private:
bool LP = false;
GuiText *ExitLabel = nullptr;
GuiText *AdvancedLabel = nullptr;
GuiText *QuickLabel = nullptr;
GuiImage *ExitImage = nullptr;
GuiImage *AdvancedImage = nullptr;
GuiImage *QuickImage = nullptr;
GuiTrigger *touchTrigger = nullptr;
    GuiTrigger *buttonTrigger = nullptr;
    GuiSound *sound = nullptr;
    void CreateButton(GuiButton * Button,GuiImage * Image, GuiText * Text,float WidthOffset,float HeightOffset,float TextOffsetX,float TextOffsetY);
    void CreateMiscs(Renderer* renderer);
};

