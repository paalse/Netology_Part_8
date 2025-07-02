Задание 1
В программу рендеринга HTML из лекции (раздел про паттерн «Декоратор») добавьте новые классы для декорирования текста.

class Paragraph: ...

auto text_block = new Paragraph(new Text());
text_block->render("Hello world");

>>> <p>Hello world</p>
class Reversed: ...

auto text_block = new Reversed(new Text());
text_block->render("Hello world");

>>> dlrow olleH
class Link: ...

auto text_block = new Link(new Text());
text_block->render("netology.ru", "Hello world");

>>> <a href=netology.ru>Hello world</a>
Обратите внимание

Сигнатура метода Link::render() не совпадает с сигнатурой оригинального метода.
Для разворота строки используйте функцию std::reverse cppreference.