//TODO: EXTRA INFO
/* 
What we want:
Serial ID
System Language
System Battery
System Version
System Time
Model Number
Online Status
& more
Credits to the Devs
Link to the Discord
*/
#include "ExtraInfo.h"
#include "MainComponents.h"
#include "MainWindow.h"
#include "../resources/Resources.h"
#include "../gui/GuiElement.h"

GuiButton *BackButton = nullptr;
GuiText *SystemInfo1 = nullptr;
GuiText *Credits = nullptr;

ExtraInfo::~ExtraInfo(){
    delete touchTrigger;
    delete sound;
    delete buttonTrigger;
}
ExtraInfo::ExtraInfo(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h){

    auto font_path = "Light.ttf";
    TTF_Font *font;

    auto music_click = "button_click.mp3";
    sound = Resources::GetSound(music_click);

    SDL_RWops *rw = SDL_RWFromMem((void *) Resources::GetFile(font_path), Resources::GetFileSize(font_path));

    DEBUG_FUNCTION_LINE("load font %08X %d", Resources::GetFile(font_path), Resources::GetFileSize(font_path));

    font = TTF_OpenFontRW(rw, 0, 28);
    if(!font){
        DEBUG_FUNCTION_LINE("Failed to load the font");
        return;
    }

    FC_Font* fc_font = FC_CreateFont();
    if(!fc_font){
        DEBUG_FUNCTION_LINE("Failed to create font");
    }

    auto res = FC_LoadFontFromTTF(fc_font, renderer->getRenderer(), font, {255, 255, 255, 255});
    DEBUG_FUNCTION_LINE("FontCache init %d", res);
    GuiText * BackText = new GuiText("Go Back", {255, 255, 0, 255}, fc_font);
    GuiImage * BackImage = new GuiImage(Resources::GetTexture("Info0.png"));
    BackButton = new GuiButton(BackImage->getWidth(),BackImage->getHeight());
    this->append(BackButton);
    BackButton->setImage(BackImage);
    BackButton->setAlignment(ALIGN_CENTERED);
    BackButton->setPosition(BackButton->getOffsetX() - 50,BackButton->getOffsetY() - 250);
    BackText->setAlignment(ALIGN_CENTERED);
    BackText->setPosition(BackText->getOffsetX() + 30,BackText->getOffsetY() + 0);
    BackButton->setLabel(BackText);
    BackText->setMaxWidth(BackButton->getWidth() - 30);
    BackButton->setEffectGrow();
    BackButton->setSoundClick(sound); 
    touchTrigger = new GuiTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::TOUCHED);
    // buttonTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL, GuiTrigger::BUTTON_A, true);
    //BackButton->setTrigger(buttonTrigger);
    BackButton->setTrigger(touchTrigger);
    BackButton->clicked.connect(this, &ExtraInfo::ReturnToMenu);
    MakeItemsVisible3(false); //TODO: FIX TEXT NOT ALLIGN
};
void ExtraInfo::process(){
    GuiFrame::process();
}

void MakeItemsVisible3(bool b){
     if (!b) {
     BackButton->setState(GuiElement::STATE_HIDDEN,0);
     }
     else {
     BackButton->resetState();
     }
}
void ExtraInfo::ReturnToMenu(GuiButton *, const GuiController *, GuiTrigger *){
    MakeItemsVisible(true);
    MakeItemsVisible2(true);
    MakeItemsVisible3(false);
}
