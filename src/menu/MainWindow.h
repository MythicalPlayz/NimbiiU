#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../gui/GuiButton.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"

void MakeItemsVisible2(bool b);
class MainWindow : public GuiFrame, public sigslot::has_slots<> {
public:

    ~MainWindow() override;
    MainWindow(int32_t w, int32_t h, Renderer* renderer);
    void process() override;

private:
    GuiText *label = nullptr;
    GuiTrigger *touchTrigger = nullptr;
    GuiTrigger *buttonTrigger = nullptr;
    GuiSound *sound = nullptr;
    GuiImage *bgImage = nullptr;
    GuiSound *bgMusic = nullptr;
};