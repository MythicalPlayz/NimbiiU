#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../gui/GuiButton.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"

class MainWindow : public GuiFrame, public sigslot::has_slots<> {
public:

    ~MainWindow() override;

    MainWindow(int32_t w, int32_t h, Renderer* renderer);
    void process() override;
    static void MakeItemsVisible(bool b);
    GuiImage *TitleImage = nullptr;

private:
    GuiText *label = nullptr;
    GuiTrigger *touchTrigger = nullptr;
    GuiTrigger *buttonTrigger = nullptr;
    GuiSound *sound = nullptr;
    GuiImage *bgImage = nullptr;
    GuiSound *bgMusic = nullptr;
};