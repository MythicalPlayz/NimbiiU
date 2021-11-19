#include "MainComponents.h"
#include "../resources/Resources.h"
#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>  
#include <whb/proc.h>

MainComponents::~MainComponents() {
    delete ExitButton;
    delete ExitLabel;
}
MainComponents::MainComponents(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h) {
    auto Exit0_Path = "Exit0.png";
    auto Quick0_Path = "Quick0.png";
    auto Advanced0_Path = "Advanced0.png";
    auto font_path = "Poppins.ttf";
    auto music_click = "button_click.mp3";
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
    sound = Resources::GetSound(music_click);
    DEBUG_FUNCTION_LINE("FontCache init %d", res);



    ExitLabel = new GuiText("Exit Installer", {255, 255, 0, 255}, fc_font);
    if (!ExitLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    ExitImage = new GuiImage(Resources::GetTexture(Exit0_Path));
    if (!ExitImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    ExitButton = new GuiButton(ExitImage->getWidth(),ExitImage->getHeight());
    CreateButton(ExitButton,ExitImage,ExitLabel,300,0);

    QuickLabel = new GuiText("Quick Install", {255, 255, 0, 255}, fc_font);
    if (!QuickLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    QuickImage = new GuiImage(Resources::GetTexture(Quick0_Path));
    if (!QuickImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    QuickButton = new GuiButton(QuickImage->getWidth(),QuickImage->getHeight());
    CreateButton(QuickButton,QuickImage,QuickLabel,-300,0);

    AdvancedLabel = new GuiText("Advanced", {255, 255, 0, 255}, fc_font);
    if (!AdvancedLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    AdvancedImage = new GuiImage(Resources::GetTexture(Advanced0_Path));
    if (!AdvancedImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    AdvancedButton = new GuiButton(AdvancedImage->getWidth(),AdvancedImage->getHeight());
    CreateButton(AdvancedButton,AdvancedImage,AdvancedLabel,0,0);

    touchTrigger = new GuiTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::TOUCHED);
   // buttonTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL, GuiTrigger::BUTTON_A, true);
    ExitButton->setTrigger(touchTrigger);
    ExitButton->setTrigger(buttonTrigger);
    ExitButton->setSoundClick(sound);
    ExitButton->clicked.connect(this, &MainComponents::test);
}
void MainComponents::process() {
    GuiFrame::process();
}
void MainComponents::test(GuiButton *, const GuiController *, GuiTrigger *) {
        DEBUG_FUNCTION_LINE("Hello, you have clicked the button");
    WHBProcShutdown();
 //        button->setState(STATE_DISABLED,0);
}
void MainComponents::CreateButton(GuiButton * Button,GuiImage * Image, GuiText * Text,float WidthOffset,float HeightOffset){   
        this->append(Button);
        Button->setAlignment(ALIGN_CENTERED);
    Button->setPosition(Button->getOffsetX()+ WidthOffset,Button->getOffsetY()+ HeightOffset);
    Button->setImage(Image);
    auto postiony = ExitButton->getOffsetY();
    auto postionx = ExitLabel->getOffsetX();
    Text->setAlignment(ALIGN_CENTERED);
    Text->setPosition(postionx,postiony + 50);
    Button->setLabel(Text);
   Text->setMaxWidth(Button->getWidth());
    Button->setEffectGrow();
}