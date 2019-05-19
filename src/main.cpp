#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#define DEFAULT_SITE_COUNT 100

std::list<sf::Vector2f> pointList;

std::list<sf::Vector2f> generatePointList(int, float, float);

int main() {
  //TODO: better support for windowed mode or different resolutions
  std::vector vec = sf::VideoMode::getFullscreenModes();
  sf::RenderWindow renderWindow(sf::VideoMode(vec.at(0).width, vec.at(0).height, vec.at(0).bitsPerPixel), "SFML works!", sf::Style::Fullscreen);

  renderWindow.resetGLStates();
  sfg::SFGUI gui;

  auto d_labelCount = sfg::Label::Create("Site count: ");
  auto d_entryCount = sfg::Entry::Create();
  auto d_labelXMax = sfg::Label::Create("Max X: ");
  auto d_entryXMax = sfg::Entry::Create();
  auto d_labelYMax = sfg::Label::Create("Max Y: ");
  auto d_entryYMax = sfg::Entry::Create();
  auto d_buttonGenerate = sfg::Button::Create("Generate");
  auto d_window = sfg::Window::Create();

  d_entryCount->SetText(std::to_string(DEFAULT_SITE_COUNT));
  d_entryXMax->SetText(std::to_string(vec.at(0).width));
  d_entryYMax->SetText(std::to_string(vec.at(0).height));
  d_window->SetTitle("Debug");

  d_buttonGenerate->GetSignal(sfg::Widget::OnLeftClick).Connect([&d_entryCount, &d_entryXMax, &d_entryYMax] {
    unsigned int buf_entryCount(0);
    unsigned int buf_entryXMax(0);
    unsigned int buf_entryYMax(0);

    std::stringstream countStr(static_cast<std::string>(d_entryCount->GetText()));
    std::stringstream xMaxStr(static_cast<std::string>(d_entryXMax->GetText()));
    std::stringstream yMaxStr(static_cast<std::string>(d_entryYMax->GetText()));

    countStr >> buf_entryCount;
    xMaxStr >> buf_entryXMax;
    yMaxStr >> buf_entryYMax;

    pointList = generatePointList(buf_entryCount, buf_entryXMax, buf_entryYMax);
  });

  auto table = sfg::Table::Create();
  table->Attach(d_labelCount, sf::Rect<sf::Uint32>(0,0,1,1), sfg::Table::FILL, sfg::Table::FILL);
  table->Attach(d_entryCount, sf::Rect<sf::Uint32>(1,0,2,1), sfg::Table::FILL, sfg::Table::FILL);
  table->Attach(d_labelXMax, sf::Rect<sf::Uint32>(0,1,1,1), sfg::Table::FILL, sfg::Table::FILL);
  table->Attach(d_entryXMax, sf::Rect<sf::Uint32>(1,1,2,1), sfg::Table::FILL, sfg::Table::FILL);
  table->Attach(d_labelYMax, sf::Rect<sf::Uint32>(0,2,1,1), sfg::Table::FILL, sfg::Table::FILL);
  table->Attach(d_entryYMax, sf::Rect<sf::Uint32>(1,2,2,1), sfg::Table::FILL, sfg::Table::FILL);
  table->Attach(d_buttonGenerate, sf::Rect<sf::Uint32>(0,3,3,1), sfg::Table::FILL, sfg::Table::FILL);

  table->SetColumnSpacings(5.f);
  table->SetRowSpacings(5.f);

  auto d_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
  d_box->Pack(table);
  d_window->Add(d_box);
  d_window->SetPosition(
      sf::Vector2f(
          static_cast<float>(renderWindow.getSize().x/2) - d_window->GetAllocation().width/2.f,
          static_cast<float>(renderWindow.getSize().y/2) - d_window->GetAllocation().height/2.f
          )
      );

  d_window->Refresh();

  sf::RectangleShape shape(sf::Vector2f(2.f, 2.f));
  shape.setFillColor(sf::Color::White);

  while (renderWindow.isOpen()) {
    sf::Event event;
    while (renderWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        renderWindow.close();
      } else if (event.key.code == sf::Keyboard::Escape) {
        renderWindow.close();
      }
      d_window->HandleEvent(event);
    }

    d_window->Update(0.f);
    renderWindow.clear();
    //TODO: Fix this demonstration hack
    for (sf::Vector2f x : pointList) {
      shape.setPosition(x);
      renderWindow.draw(shape);
    }
    gui.Display(renderWindow);
    renderWindow.display();
  }

  return 0;
}

std::list<sf::Vector2f> generatePointList(int count, float xMax, float yMax) {
  float x;
  float y;
  std::list<sf::Vector2f> result;
  srand(static_cast<unsigned> (time(0)));
  for (int i = 0; i < count; i++) {
    x = static_cast<float>(rand())/(static_cast<float>(RAND_MAX/xMax));
    y = static_cast<float>(rand())/(static_cast<float>(RAND_MAX/yMax));
    result.push_back(sf::Vector2f(x,y));
  }
  return result;
}