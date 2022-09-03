/**
 * @author Michele Tomaiuolo - http://www.ce.unipr.it/people/tomamic
 * @license This software is free - http://www.gnu.org/licenses/gpl.html
 */

#include "gamegui.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QAction>

GameGui::GameGui(Game* game)
{

    game_ = game;
    cols_ = game->cols();
    rows_ = game->rows();

    auto grid = new QGridLayout; setLayout(grid);
    for (auto y = 0; y < rows_; ++y) {
        for (auto x = 0; x < cols_; ++x) {
            auto b = new QPushButton;
            b->setFixedSize(50, 50);
            grid->addWidget(b, y, x);
            connect(b, &QPushButton::clicked,
                    [=]{ handle_click(x, y); });
        }
    }
    update_all_buttons();

    // fix appearance
    layout()->setMargin(0);
    layout()->setSpacing(0);
    setFixedSize(sizeHint());
    SaveMessage();
}

void GameGui::update_button(int x, int y)
{
    auto val = game_->get_val(x, y);
    auto b = layout()->itemAt(y * cols_ + x)->widget();
    dynamic_cast<QPushButton*>(b)->setText(val.c_str());

    if ("0" <= val && val <= "4") b->setStyleSheet("background: black; color: white;");
    else if(val == "5") b->setStyleSheet("background: black; color: black;");
    else if(val == "+") b->setStyleSheet("background: yellow; color: black;");
    else if(val == "@") b->setStyleSheet("background: red; color: black;");
  //  else if(val == "@") b->setIcon(QIcon("bulb.jpg"));
    else b->setStyleSheet("background: white; color: black;");

     //if ("0" <= val && val <= "9") b->setStyleSheet("background: black; color: white;");
     // else b->setStyleSheet("background: white; color: black;");
}

void GameGui::update_all_buttons()
{
    for (auto y = 0; y < rows_; y++) {
        for (auto x = 0; x < cols_; x++) {
            update_button(x, y);
        }
    }
}

void GameGui::SaveMessage()
{
    QMessageBox msgBox;
    msgBox.setText("Hi player,");
    msgBox.setInformativeText("Do you want to save this match?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Open | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
/*
    switch (ret) {
      case QMessageBox::Save:
          akari_->save();
          break;
      case QMessageBox::Cancel:
          break;
      case QMessageBox::Open:
          akari->load();
      default:
          // should never be reached
          break;
    }*/
}

void GameGui::handle_click(int x, int y)
{
    game_->play_at(x, y);
    update_all_buttons();

    if (game_->finished()) {
        QMessageBox::information(this,
                                 tr("Game finished"),
                                 tr(game_->message().c_str()));
        window()->close();
    }
}
