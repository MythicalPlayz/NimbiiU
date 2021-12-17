#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"
#include "../gui/GuiButton.h"
#include "../patch/iosu_kernel.h"
void MakeItemsVisible(bool b);
void SetActiveButton(int BUTTONID);
bool IsMainVisible();
GuiButton* GetButtonFromID(int ID);
int ChangeButtonImage(bool IsSelected,GuiButton * Button);
class MainComponents : public GuiFrame, public sigslot::has_slots<>{
public:
void Exit(GuiButton *, const GuiController *, GuiTrigger *);
void ExtraInfo(GuiButton *, const GuiController *, GuiTrigger *);
void Advanced(GuiButton *, const GuiController *, GuiTrigger *);
void Quick(GuiButton *, const GuiController *, GuiTrigger *);
   ~MainComponents() override;
    MainComponents(int32_t w, int32_t h, Renderer* renderer);
    void process() override;
private:
bool LP = false;
GuiText *ExitLabel = nullptr;
GuiText *AdvancedLabel = nullptr;
GuiText *QuickLabel = nullptr;
GuiImage *ExitImage = nullptr;
GuiImage *AdvancedImage = nullptr;
GuiImage *QuickImage = nullptr;
GuiSound *SFX = nullptr;
GuiTrigger *touchTrigger = nullptr;
    GuiSound *sound = nullptr;
    void CreateButton(GuiButton * Button,GuiImage * Image, GuiText * Text,float WidthOffset,float HeightOffset,float TextOffsetX,float TextOffsetY);
    void CreateMiscs(Renderer* renderer);
};
