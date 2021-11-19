#include "MainWindow.h"
#include "../resources/Resources.h"



MainWindow::~MainWindow() {
    delete label;
    delete touchTrigger;
    delete buttonTrigger;
    delete sound;
    delete TitleImage;
    delete bgMusic;
}

MainWindow::MainWindow(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h)  {
    auto picture_path = "Title.png";
    auto font_path = "Poppins.ttf";
    auto bgMusic_path = "bgMusic.ogg";
    auto bgImage_Path = "Background.png";
     bgImage = new GuiImage(Resources::GetTexture(bgImage_Path));
     
    if(!bgImage){
     DEBUG_FUNCTION_LINE("Failed to add image");
      return;
  }
    this->append(bgImage);



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

    TitleImage = new GuiImage(Resources::GetTexture(picture_path));
     if(!TitleImage){
        DEBUG_FUNCTION_LINE("Failed to load %s", bgMusic_path);
        return;
    }
    this->append(TitleImage);
    TitleImage->setAlignment(ALIGN_CENTERED);
    auto postionx = TitleImage->getOffsetX();
    auto postiony = TitleImage->getOffsetX();
    TitleImage->setPosition(postionx,postiony - 200);
    bgMusic = Resources::GetSound(bgMusic_path);
    if(!bgMusic){
        DEBUG_FUNCTION_LINE("Failed to load %s", bgMusic_path);
        return;
    }
    bgMusic->SetLoop(true);
    bgMusic->Play();
}

void MainWindow::process() {
    GuiFrame::process();

 /*   if(!button){
        return;
    }
    // Rotate the button for fun.
    auto res = button->getAngle() + 0.5f;
    if(res > 360){
        res = 0;
  //  auto x = button->GetPositionX();
   // auto y = button->GetPositionY();
   // button->setPosition(x+1,y+1);
    }
    button->setAngle(res);
    */
}
