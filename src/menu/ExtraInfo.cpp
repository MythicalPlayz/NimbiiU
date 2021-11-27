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
#include "../resources/Resources.h"


bool IsVisible = false;

ExtraInfo::~ExtraInfo(){

}
ExtraInfo::ExtraInfo(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h){

    auto font_path = "Light.ttf";
    TTF_Font *font;

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
    BackButton->setPosition(100,100);
    BackButton->setImage(BackImage);
    auto postiony = BackButton->getOffsetY();
    auto postionx = BackButton->getOffsetX();
    BackText->setAlignment(ALIGN_CENTERED);
    BackText->setPosition(postionx + 30,postiony + 0);
    BackButton->setLabel(BackText);
   BackText->setMaxWidth(BackButton->getWidth() - 30);
    BackButton->setEffectGrow();
        auto music_click = "button_click.mp3";
            sound = Resources::GetSound(music_click);
    BackButton->setSoundClick(sound);    
    touchTrigger = new GuiTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::TOUCHED);
        BackButton->setTrigger(touchTrigger);
        BackButton->setVisible(IsVisible);
};
void ExtraInfo::process(){
    GuiFrame::process();
}

void ExtraInfo::MakeItemsVisible(bool b){
    IsVisible = b;
}