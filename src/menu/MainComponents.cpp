#include "MainComponents.h"
#include "../resources/Resources.h"


MainComponents::~MainComponents() {
    delete ExitButton;
    delete ExitLabel;
}
MainComponents::MainComponents(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h) {
    auto Exit0_Path = "Exit0.png";
    auto font_path = "Poppins.ttf";
    auto music_click = "button_click.mp3";
    GuiImage *Image = new GuiImage(Resources::GetTexture(Exit0_Path));
    if (!Image) { 
        DEBUG_FUNCTION_LINE("Failed to add image");
    return;}
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
    if (!ExitLabel) {DEBUG_FUNCTION_LINE("ERROR: LOADING TEXT FAILED");}
    ExitButton = new GuiButton(Image->getWidth(),Image->getHeight());
    this->append(ExitButton);
    this->append(Image);
    ExitButton->setAlignment(ALIGN_CENTERED);
    ExitButton->setImage(Image);
    ExitButton->setEffectGrow();
    //ExitLabel->setAlignment(ALIGN_CENTERED);
    //auto postionx = ExitButton->getOffsetX();
    //auto postiony = ExitButton->getOffsetY();
   // ExitLabel->setPosition(postionx,postiony + 50);
    ExitButton->setLabel(ExitLabel);
    ExitLabel->setMaxWidth(ExitButton->getWidth());
    touchTrigger = new GuiTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::TOUCHED);
    buttonTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL, GuiTrigger::BUTTON_A, true);
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
 //        button->setState(STATE_DISABLED,0);
 ExitButton->setVisible(false);
}