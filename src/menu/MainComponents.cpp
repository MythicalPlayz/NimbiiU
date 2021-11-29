#include "MainComponents.h"
#include "MainWindow.h"
#include "../resources/Resources.h"
#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>  
#include <proc.hpp>




MainComponents::~MainComponents() {
    delete ExitButton;
    delete ExitLabel;
}
MainComponents::MainComponents(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h) {
    auto Exit0_Path = "Exit0.png";
    auto Quick0_Path = "Quick0.png";
    auto Advanced0_Path = "Advanced0.png";
    auto font_path = "Poppins.ttf";
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


    ExitLabel = new GuiText("Exit Installer", {255, 255, 0, 255}, fc_font);
    if (!ExitLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    ExitImage = new GuiImage(Resources::GetTexture(Exit0_Path));
    if (!ExitImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    ExitButton = new GuiButton(ExitImage->getWidth(),ExitImage->getHeight());
    CreateButton(ExitButton,ExitImage,ExitLabel,300,0,0,50);

    QuickLabel = new GuiText("Quick Install", {255, 255, 0, 255}, fc_font);
    if (!QuickLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    QuickImage = new GuiImage(Resources::GetTexture(Quick0_Path));
    if (!QuickImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    QuickButton = new GuiButton(QuickImage->getWidth(),QuickImage->getHeight());
    CreateButton(QuickButton,QuickImage,QuickLabel,-300,0,0,50);

    AdvancedLabel = new GuiText("Advanced", {255, 255, 0, 255}, fc_font);
    if (!AdvancedLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    AdvancedImage = new GuiImage(Resources::GetTexture(Advanced0_Path));
    if (!AdvancedImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    AdvancedButton = new GuiButton(AdvancedImage->getWidth(),AdvancedImage->getHeight());
    CreateButton(AdvancedButton,AdvancedImage,AdvancedLabel,0,0,0,50);
    CreateMiscs(renderer);

   // buttonTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL, GuiTrigger::BUTTON_A, true);
   // ExitButton->setTrigger(buttonTrigger);

    ExitButton->clicked.connect(this, &MainComponents::Exit);
    QuickButton->clicked.connect(this, &MainComponents::Quick);
    AdvancedButton->clicked.connect(this, &MainComponents::Advanced);
    
}
void MainComponents::process() {
    GuiFrame::process();
 }
// Functions of Buttons
void MainComponents::Exit(GuiButton *, const GuiController *, GuiTrigger *) {
   
   ProcShutdown();
 
}
void MainComponents::ExtraInfo(GuiButton *, const GuiController *, GuiTrigger *){
 MakeItemsVisible(false);
 MainWindow::MakeItemsVisible(false);
}
void MainComponents::Quick(GuiButton *, const GuiController *, GuiTrigger *) {
auto r = IOSU_Kernel_Exploit(true,NULL);
if (r == 0) {
    auto SFXPATH = "Status_success.mp3";
GuiSound *SFX = Resources::GetSound(SFXPATH);
SFX->Play();
}
}
void MainComponents::Advanced(GuiButton *, const GuiController *, GuiTrigger *) {
    //SDL_StartTextInput();
}
//
void MainComponents::CreateButton(GuiButton * Button,GuiImage * Image, GuiText * Text,float WidthOffset,float HeightOffset,float TextOffsetX,float TextOffsetY){   
       //Handles Button Creation
        this->append(Button);
        Button->setAlignment(ALIGN_CENTERED);
    Button->setPosition(Button->getOffsetX()+ WidthOffset,Button->getOffsetY()+ HeightOffset);
    Button->setImage(Image);
    Text->setAlignment(ALIGN_CENTERED);
    auto postiony = Text->getOffsetY();
    auto postionx = Text->getOffsetX();
    Text->setPosition(postionx + TextOffsetX,postiony + TextOffsetY);
    Button->setLabel(Text);
   Text->setMaxWidth(Button->getWidth() - TextOffsetX);
    Button->setEffectGrow();
        auto music_click = "button_click.mp3";
            sound = Resources::GetSound(music_click);
    Button->setSoundClick(sound);    
    touchTrigger = new GuiTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::TOUCHED);
        Button->setTrigger(touchTrigger);
}
void MainComponents::CreateMiscs(Renderer* renderer){
    //Create Misc Buttons (Extra Info)
    auto font_path = "Poppins.ttf";
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
    auto Info_Path = "Info0.png";
    auto InfoIcon_Path = "InfoI0.png";
    GuiText * InfoText = new GuiText("Extra Info", {255, 255, 0, 255}, fc_font);
    GuiImage * InfoImage = new GuiImage(Resources::GetTexture(Info_Path));
      InfoButton = new GuiButton(InfoImage->getWidth(),InfoImage->getHeight());
    CreateButton(InfoButton,InfoImage,InfoText,0,200,30,0);
   InfoImageIcon = new GuiImage(Resources::GetTexture(InfoIcon_Path)); 
   this->append(InfoImageIcon);
    InfoImageIcon->setAlignment(ALIGN_CENTERED);
    InfoImageIcon->setPosition(InfoImageIcon->getOffsetX() - (InfoImage->getWidth()/2)+ + (InfoImageIcon->getWidth()/2) + 5,InfoImageIcon->getOffsetY() + 200);
    InfoImageIcon->setSize(30,30);
    InfoButton->clicked.connect(this, &MainComponents::ExtraInfo);
}
void MainComponents::MakeItemsVisible(bool b) {
    //Disables All Input and Hides The Buttons

     if (b) {
     InfoButton->setState(STATE_DISABLED,0);
     QuickButton->setState(STATE_DISABLED,0);
    AdvancedButton->setState(STATE_DISABLED,0);
    ExitButton->setState(STATE_DISABLED,0);
    }else{
    InfoButton->setState(STATE_DEFAULT,0);
    QuickButton->setState(STATE_DEFAULT,0);
    AdvancedButton->setState(STATE_DEFAULT,0);
    ExitButton->setState(STATE_DEFAULT,0);
    }     
        ExitButton->setVisible(b);

     AdvancedButton->setVisible(b);

     QuickButton->setVisible(b);

     InfoButton->setVisible(b);

     InfoImageIcon->setVisible(b);
}
void MainComponents::Patch() {
  //__IOSU_MQ_EXP::IOSU_Kernel_Exploit(true,NULL);
}
