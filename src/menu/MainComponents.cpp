#include "MainComponents.h"
#include "ExtraInfo.h"
#include "MainWindow.h"
#include "../resources/Resources.h"
#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>
#include <sysapp/launch.h>
#include "../resources/proc.hpp"
#include "../gui/GuiElement.h"
    Renderer *Render;
    GuiButton *ExitButton;
    GuiButton *AdvancedButton;
    GuiButton *QuickButton;
    GuiButton *InfoButton;
    GuiImage *InfoImageIcon;
    int OLDBUTTONID = 0;
    GuiTrigger *NTrigger;
    GuiTrigger *ATrigger;
    bool GoBackToMenu = false;

#ifdef __NONCHANNEL__

float QuickXLocation = -300;
float AdvancedXLocation = 0;

#else

float QuickXLocation = -150;
float AdvancedXLocation = 150;

#endif

MainComponents::~MainComponents() {
    //delete ExitButton;
    delete ExitImage;
    delete ExitLabel;
    //delete AdvancedButton;
    delete AdvancedImage;
    delete AdvancedLabel;
    //delete QuickButton;
    delete QuickImage;
    delete QuickLabel;
    delete SFX;
    delete sound;
    delete touchTrigger;
}
MainComponents::MainComponents(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h) {
    auto Exit0_Path = "Exit0.png";
    auto Quick0_Path = "Quick0.png";
    auto Advanced0_Path = "Advanced0.png";
    auto font_path = "Poppins.ttf";
    auto SFXPATH = "Status_success.mp3";
    SFX = Resources::GetSound(SFXPATH);
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

#ifdef __NONCHANNEL__
    ExitLabel = new GuiText("Exit Installer", {255, 255, 0, 255}, fc_font);
    if (!ExitLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    ExitImage = new GuiImage(Resources::GetTexture(Exit0_Path));
    if (!ExitImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    ExitButton = new GuiButton(ExitImage->getWidth(),ExitImage->getHeight());
    CreateButton(ExitButton,ExitImage,ExitLabel,300,0,0,50);
    ExitButton->clicked.connect(this, &MainComponents::Exit);
#endif
    QuickLabel = new GuiText("Quick Install", {255, 255, 0, 255}, fc_font);
    if (!QuickLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    QuickImage = new GuiImage(Resources::GetTexture(Quick0_Path));
    if (!QuickImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    QuickButton = new GuiButton(QuickImage->getWidth(),QuickImage->getHeight());
    CreateButton(QuickButton,QuickImage,QuickLabel,QuickXLocation,0,0,50);

    AdvancedLabel = new GuiText("Advanced", {255, 255, 0, 255}, fc_font);
    if (!AdvancedLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED"); return;}
    AdvancedImage = new GuiImage(Resources::GetTexture(Advanced0_Path));
    if (!AdvancedImage) {  DEBUG_FUNCTION_LINE("Failed to add image"); return;}
    AdvancedButton = new GuiButton(AdvancedImage->getWidth(),AdvancedImage->getHeight());
    CreateButton(AdvancedButton,AdvancedImage,AdvancedLabel,AdvancedXLocation,0,0,50);
    CreateMiscs(renderer);

    ATrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL,GuiTrigger::BUTTON_A,true);
    NTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL,GuiTrigger::BUTTON_NONE,true);
    QuickButton->clicked.connect(this, &MainComponents::Quick);
    AdvancedButton->clicked.connect(this, &MainComponents::Advanced);
    
}
void MainComponents::process() {
    GuiFrame::process();
 }
// Functions of Buttons
void MainComponents::Exit(GuiButton *, const GuiController *, GuiTrigger *) {
   
   SFX->Stop();
   StopSound();
     if (IsRunningFromHomeBrew) {
   ProcShutdown();
    }
    else{
        GoBackToMenu = true;
    }
   
}
void MainComponents::ExtraInfo(GuiButton *, const GuiController *, GuiTrigger *){
 MakeItemsVisible(false);
 MakeItemsVisible2(false);
 MakeItemsVisible3(true);
}
void MainComponents::Quick(GuiButton *, const GuiController *, GuiTrigger *) {
auto r = IOSU_Kernel_Exploit();
if (r == 0) {
SFX->Play();
}
}
void MainComponents::Advanced(GuiButton *, const GuiController *, GuiTrigger *) {
   // SDL_StartTextInput();
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
    CreateButton(InfoButton,InfoImage,InfoText,0,275,30,0);
   InfoImageIcon = new GuiImage(Resources::GetTexture(InfoIcon_Path)); 
   this->append(InfoImageIcon);
    InfoImageIcon->setAlignment(ALIGN_CENTERED);
    InfoImageIcon->setPosition(InfoImageIcon->getOffsetX() - (InfoImage->getWidth()/2)+ + (InfoImageIcon->getWidth()/2) + 5,InfoImageIcon->getOffsetY() + 275);
    InfoImageIcon->setSize(30,30);
    InfoButton->clicked.connect(this, &MainComponents::ExtraInfo);
}
void MakeItemsVisible(bool b) {
    //Disables All Input and Hides The Buttons

     if (!b) {
    InfoButton->setState(GuiElement::STATE_HIDDEN,0);
    QuickButton->setState(GuiElement::STATE_HIDDEN,0);
    AdvancedButton->setState(GuiElement::STATE_HIDDEN,0);
    #ifdef __NONCHANNEL__
    ExitButton->setState(GuiElement::STATE_HIDDEN,0);
    #endif
    }else{
    InfoButton->resetState();
    QuickButton->resetState();
    AdvancedButton->resetState();
    #ifdef __NONCHANNEL__
    ExitButton->resetState();
    #endif
    }     
     InfoImageIcon->setVisible(b);
}
void SetActiveButton(int BUTTONID){
    if (OLDBUTTONID > 0) {ChangeButtonImage(false,GetButtonFromID(OLDBUTTONID));}
    if (BUTTONID == 1){OLDBUTTONID = ChangeButtonImage(true,QuickButton);}
   else if (BUTTONID == 2){OLDBUTTONID = ChangeButtonImage(true,AdvancedButton);}
   #ifdef __NONCHANNEL__ 
   else if (BUTTONID == 3){OLDBUTTONID = ChangeButtonImage(true,ExitButton);}
   #endif
   else if (BUTTONID == 4){OLDBUTTONID = ChangeButtonImage(true,InfoButton);}
}
int ChangeButtonImage(bool IsSelected,GuiButton * Button)
{
    int ReturnValue = 0;
    if (IsSelected == true){
        Button->setTrigger(ATrigger,1);
        if (Button == QuickButton){
         auto Path = "Quick1.png";
         GuiImage * Image = new GuiImage(Resources::GetTexture(Path));
         Button->setImage(Image);
         ReturnValue = 1;
        }
    else if (Button == AdvancedButton){
        auto Path = "Advanced1.png";
         GuiImage * Image = new GuiImage(Resources::GetTexture(Path));
         Button->setImage(Image);
         ReturnValue = 2;
    }
    else if (Button == ExitButton){
        auto Path = "Exit1.png";
         GuiImage * Image = new GuiImage(Resources::GetTexture(Path));
         Button->setImage(Image);
         ReturnValue = 3;
    }
    else if (Button == InfoButton){
        auto Path = "Info1.png";
         GuiImage * Image = new GuiImage(Resources::GetTexture(Path));
         Button->setImage(Image);
         ReturnValue = 4;
    }
    }
    else {
        Button->setTrigger(NTrigger,1);
        if (Button == QuickButton){
         auto Path = "Quick0.png";
         GuiImage * Image = new GuiImage(Resources::GetTexture(Path));
         Button->setImage(Image);
        }
    else if (Button == AdvancedButton){
        auto Path = "Advanced0.png";
         GuiImage * Image = new GuiImage(Resources::GetTexture(Path));
         Button->setImage(Image);
    }
    else if (Button == ExitButton){
        auto Path = "Exit0.png";
         GuiImage * Image = new GuiImage(Resources::GetTexture(Path));
         Button->setImage(Image);
    }
    else if (Button == InfoButton){
        auto Path = "Info0.png";
         GuiImage * Image = new GuiImage(Resources::GetTexture(Path));
         Button->setImage(Image);
    }
    ReturnValue = 0;
    }
    return ReturnValue;
}

GuiButton* GetButtonFromID(int ID){
    GuiButton * Button;
    if (ID == 1){Button = QuickButton;}
    else if (ID == 2){Button = AdvancedButton;}
 #ifdef __NONCHANNEL__
    else if (ID == 3){Button = ExitButton;}
    #endif
    else if (ID == 4){Button = InfoButton;}
    return Button;
}
bool IsMainVisible(){
    return QuickButton->isVisible();
}
bool ReturnToMenu(){
    return GoBackToMenu;
}