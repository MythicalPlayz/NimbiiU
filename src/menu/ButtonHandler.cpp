#include "ButtonHandler.h"
bool IsButtonSelected = false;
int ButtonID = 0;
ButtonHandler::~ButtonHandler(){
 delete Gamebutton;
}
ButtonHandler::ButtonHandler(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h){

Gamebutton = new GuiButton(1,1);
this->append(Gamebutton);
Gamebutton->setVisible(false);
Gamebutton->setPosition(1,1);
UpTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL,GuiTrigger::BUTTON_UP,true);
DownTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL,GuiTrigger::BUTTON_DOWN,true);
RightTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL,GuiTrigger::BUTTON_RIGHT,true);
LeftTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL,GuiTrigger::BUTTON_LEFT,true);
Gamebutton->setTrigger(UpTrigger);
Gamebutton->setTrigger(DownTrigger);
Gamebutton->setTrigger(RightTrigger);
Gamebutton->setTrigger(LeftTrigger);
Gamebutton->clicked.connect(this, &ButtonHandler::GameControllerInput);
}
void ButtonHandler::GameControllerInput(GuiButton *, const GuiController * t, GuiTrigger * Trigger){
    if (IsMainVisible()) {
    if (IsButtonSelected == false) {
        IsButtonSelected = true;
        ButtonID = 1;
        SetActiveButton(1);
    }
    else if (Trigger == UpTrigger){
        ButtonID = 2;
        SetActiveButton(2);
    }
    else if (Trigger == RightTrigger){
        if (ButtonID < 3){ButtonID += 1;}
        SetActiveButton(ButtonID);
    }
    else if (Trigger == LeftTrigger){
        if (ButtonID > 1){ButtonID -= 1;}
        SetActiveButton(ButtonID);
    }
    else if (Trigger == DownTrigger){
        ButtonID = 4;
        SetActiveButton(4);
    }
}
}
void ButtonHandler::process(){
    GuiFrame::process();
}
